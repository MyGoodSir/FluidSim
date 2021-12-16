
#include "fluid.h"
#include "logger.h"
#include <GLES/gl.h>
#include <jni.h>
#include <string>

inline GLfloat mRand(){ return (GLfloat)rand() * (1.f / RAND_MAX); }
constexpr int num_threads = 4;
constexpr GLfloat gravity_strength = .005f,
                  particle_space = 1.25f,
                  k = particle_space / 1000.f,
                  kn = k * 10,
                  rest_dens = 6,
                  support_rad = particle_space * 1.25f,
                  support_rad2 = support_rad * support_rad,
                  grid_width = 50,
                  max_velocity = 2.0f;
Hasher hasher( 4093, support_rad);

Fluid* make_fluid(cuint N) {
    Fluid* fluid = new Fluid;

    if (!fluid->init(N)) {
        delete fluid;
        return NULL;
    }
    return fluid;
}

bool Fluid::init(cuint N)
{
    particles = std::vector<Particle>();
    particles.reserve(N);
    GLfloat w = grid_width / 4;
    for(GLfloat y = 1; y <= 10000; y += support_rad * 0.5f){
        for(GLfloat x = -w; x <= w; x += support_rad * 0.5f){
            if( particles.size() >= N ) break;

            Particle p;
            p.pos = vec2(x,y);
            p.col = vec4(1.f);
            p.pos_old = p.pos + 0.001f * vec2(mRand(), mRand());
            p.force = vec2(0,0);
            p.visc = vec2(3.f, 4.f);
            p.neighbors.reserve(64);
            particles.push_back(p);
        }
    }
    return true;
}


void Fluid::step_prep(int i){
    particles[i].pos += particles[i].force;//apply forces
    particles[i].force = gravity_dir*gravity_strength;//apply gravity
    particles[i].vel = particles[i].pos - particles[i].pos_old; //update velocity

    //velocity cap... this is hacky
    if(len2(particles[i].vel) > max_velocity*max_velocity) particles[i].vel *= .5f;

    // position integration
    particles[i].pos_old = particles[i].pos;
    particles[i].pos += particles[i].vel;

    // wall constraints
    if( particles[i].pos.x < -grid_width*.5 ) particles[i].force.x -= ( particles[i].pos.x - (-grid_width*.5) ) / 8;
    if( particles[i].pos.x >  grid_width*.5 ) particles[i].force.x -= ( particles[i].pos.x - (grid_width*.5) ) / 8;
    if( particles[i].pos.y < 0) particles[i].force.y -= ( particles[i].pos.y) / 8;
    if( particles[i].pos.y > grid_width * 2 ) particles[i].force.y -= ( particles[i].pos.y - grid_width * 2 ) / 8;

    //reset density and neighbors
    particles[i].dens = vec2(0, 0);
    particles[i].neighbors.clear();
}
void Fluid::step_density(int i){
    particles[i].dens = vec2(0, 0);

    GLfloat d = 0, dn = 0; //density

    std::vector<Particle*> nbrs;
    nbrs.reserve( 64 );
    hasher.make_nlist(particles[i].pos, nbrs );
    for(int j=0; j<nbrs.size(); j++){
        if(nbrs[j] != &particles[i]) {
            const vec2 p2n = nbrs[j]->pos - particles[i].pos;   // particle to neighbor. (vector pointing from particles[i] to nbrs[j])
            const GLfloat p2n_d2 = len2(p2n);                   // particle to neighbor distance squared

            if (p2n_d2 < support_rad2) {
                GLfloat p2n_d = sqrt(p2n_d2); //particle to neighbor distance
                const GLfloat q = 1.f - (p2n_d / support_rad), q2 = q * q;
                d += q2;
                dn += q2 * q;

                Neighbor n = {nbrs[j], q, q2};
                particles[i].neighbors.push_back(n);
            }
        }
    }

    particles[i].dens += vec2(d,dn);
}
void Fluid::step_pressure(int i){
    particles[i].press = vec2(
                            k * ( particles[i].dens.far - rest_dens ),
                            kn * particles[i].dens.near
                            );
}
void Fluid::step_pressure_force(int i){
    vec2 pf = {0.f,0.f}; //force vector from pressure
    for(Neighbor& n : particles[i].neighbors)
        pf +=/*direction*/ normalize(n.j->pos - particles[i].pos ) * /*magnitude*/dot(particles[i].press + n.j->press,vec2(n.q, n.q2));

    particles[i].force -= pf;
}
void Fluid::step_viscosity(int i){
    for(Neighbor& n : particles[i].neighbors){
        const vec2 p2n = n.j->pos - particles[i].pos;
        const GLfloat l = len(p2n), q = l / support_rad;
        const vec2 p2n_dir = p2n / l;

        const GLfloat u = dot( particles[i].vel - n.j->vel, p2n_dir );//project particle velocities on to p2n vector
        //if magnitude of projected velocity is positive, add viscosity impulse contribution
        if( u > 0 ) particles[i].vel -= 0.5 * (1-q) * dot(n.j->visc, vec2(u,u*u)) * p2n_dir;

    }
}
void Fluid::step_color(int i){
    particles[i].col = vec4(1.1f - (0.15f * particles[i].dens.far ),
                            1.1f - (0.15f * particles[i].dens.far ),
                            0.8f + (0.1f * particles[i].dens.far ),
                            1.f);
}
void Fluid::step(){
    std::thread ts[num_threads];
    const int iters = particles.size()/num_threads;
    auto splitter = [&](auto fn){
        for(int i = 0; i<num_threads; i++)
            ts[i] = std::thread([&, i](){for(int j = iters*i; j<iters*(i+1); j++)fn(j);});
        for(int i = 0; i<num_threads; i++)
            ts[i].join();
    };
    splitter([&](int i) { step_prep(i); });
    hasher.clear();
    for(auto& p : particles) hasher.insert(p.pos, &p);
    splitter([&](int i) { step_density(i); });
    splitter([&](int i) { step_pressure(i); });
    splitter([&](int i) { step_pressure_force(i); });
    splitter([&](int i) { step_viscosity(i); });
    splitter([&](int i) { step_color(i); });
}


void Fluid::resize(int w, int h){
    window.w=w; window.h=h;
    glViewport( 0, 0, window.w, window.h );
}



void Fluid::display()
{
    glClearColor( 0, 0, 0, 1 );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    const GLfloat ar = window.w / static_cast< GLfloat >( window.h );
    glOrthof( ar * -grid_width, ar * grid_width, 0, 2*grid_width, -1, 1 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();


    glPointSize( support_rad*4 );
    glVertexPointer( 2, GL_FLOAT, sizeof(Particle), &particles[0].pos.x );
    glColorPointer( 4, GL_FLOAT, sizeof(Particle), &particles[0].col.r );
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_COLOR_ARRAY );
    glDrawArrays( GL_POINTS, 0, static_cast< GLsizei >( particles.size() ) );
    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_COLOR_ARRAY );
}
