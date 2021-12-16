//
// Created by joesc on 11/27/2021.
//

#ifndef FLUIDSIM_LINALG_H
#define FLUIDSIM_LINALG_H
#include <math.h>
#include <GLES/gl.h>
#ifndef M_PI
#define M_PI 3.141592653f
#endif


struct vec2;
struct vec3;
struct vec4;
struct ivec2;
struct ivec3;
struct ivec4;
struct ivec2
{

    GLint x;
    GLint y;

    ivec2() : x(0), y(0) { }
    ivec2(GLint X, GLint Y) : x(X), y(Y){ }
    explicit ivec2(GLint S) : x(S), y(S) { }
    operator vec2() const;
    ivec2 operator + (const ivec2 &rhs) const { return ivec2(x + rhs.x, y + rhs.y); }
    ivec2 operator * (const ivec2 &rhs) const { return ivec2(x * rhs.x, y * rhs.y); }
    ivec2 operator - (const ivec2 &rhs) const { return ivec2(x - rhs.x, y - rhs.y); }
    ivec2 operator * (const GLint s)  const  { return ivec2(x * s, y * s); }
    ivec2 operator / (const GLint s)  const  { return ivec2(x / s, y / s); }

    ivec2 &operator *= (const GLint s)   { *this = *this * s; return *this; }
    ivec2 &operator += (const ivec2 &rhs) { *this = *this + rhs; return *this; }
    ivec2 &operator *= (const ivec2 &rhs) { *this = *this * rhs; return *this; }
    ivec2 &operator -= (const ivec2 &rhs) { *this = *this - rhs; return *this; }
    GLint &operator [] (GLuint i)             { return (&x)[i]; }
    const GLint &operator [] (GLuint i) const { return (&x)[i]; }

};
inline bool operator==(const ivec2& lhs, const ivec2& rhs){ return (lhs.x==rhs.x)&&(lhs.y==rhs.y); }
inline bool operator!=(const ivec2& lhs, const ivec2& rhs){ return !(lhs == rhs); }


struct ivec3
{
    GLint x, y, z;

    ivec3() : x(0), y(0), z(0) { }
    ivec3(GLint X, GLint Y, GLint Z) : x(X), y(Y), z(Z) { }
    explicit ivec3(GLint S) : x(S), y(S), z(S) { }
    operator vec3() const;
    ivec3 operator - () const { return ivec3(-x, -y, -z); }
    ivec3 operator + (const ivec3 &rhs) const { return ivec3(x + rhs.x, y + rhs.y, z + rhs.z); }
    ivec3 operator * (const ivec3 &rhs) const { return ivec3(x * rhs.x, y * rhs.y, z * rhs.z); }
    ivec3 operator - (const ivec3 &rhs) const { return ivec3(x - rhs.x, y - rhs.y, z - rhs.z); }
    ivec3 operator * (const GLint s)  const  { return ivec3(x * s, y * s, z * s); }
    ivec3 operator / (const GLint s)  const  { return ivec3(x / s, y / s, z / s); }

    ivec3 &operator += (const ivec3 &rhs) { *this = *this + rhs; return *this; }
    ivec3 &operator *= (const ivec3 &rhs) { *this = *this * rhs; return *this; }
    ivec3 &operator -= (const ivec3 &rhs) { *this = *this - rhs; return *this; }

    GLint &operator [] (GLuint i)             { return (&x)[i]; }
    const GLint &operator [] (GLuint i) const { return (&x)[i]; }

};
inline bool operator==(const ivec3& lhs, const ivec3& rhs){ return (lhs.x==rhs.x)&&(lhs.y==rhs.y)&&(lhs.z==rhs.z); }
inline bool operator!=(const ivec3& lhs, const ivec3& rhs){ return !(lhs == rhs); }

struct ivec4
{
    GLint x, y, z, w;

    ivec4() : x(0), y(0), z(0), w(0) { }
    ivec4(ivec3 V, GLint W) : x(V.x), y(V.y), z(V.z), w(W) { }
    ivec4(GLint X, GLint Y, GLint Z, GLint W) : x(X), y(Y), z(Z), w(W) { }
    explicit ivec4(GLint S) : x(S), y(S), z(S), w(S) { }
    ivec4 operator - () const { return ivec4(-x, -y, -z, -w); }
    ivec4 operator + (const ivec4 &rhs) const { return ivec4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w); }
    ivec4 operator * (const ivec4 &rhs) const { return ivec4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w); }
    ivec4 operator - (const ivec4 &rhs) const { return ivec4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w); }
    ivec4 operator * (const GLint s)  const  { return ivec4(x * s, y * s, z * s, w * s); }
    ivec4 operator / (const GLint s)  const  { return ivec4(x / s, y / s, z / s, w / s); }

    ivec4 &operator *= (const GLint s)   { *this = *this * s; return *this; }
    ivec4 &operator += (const ivec4 &rhs) { *this = *this + rhs; return *this; }
    ivec4 &operator *= (const ivec4 &rhs) { *this = *this * rhs; return *this; }
    ivec4 &operator -= (const ivec4 &rhs) { *this = *this - rhs; return *this; }

    GLint &operator [] (GLuint i)             { return (&x)[i]; }
    const GLint &operator [] (GLuint i) const { return (&x)[i]; }

    ivec3 xyz() const { return ivec3(x, y, z); }

};
inline bool operator==(const ivec4& lhs, const ivec4& rhs){ return (lhs.x==rhs.x)&&(lhs.y==rhs.y)&&(lhs.z==rhs.z)&&(lhs.w==rhs.w); }
inline bool operator!=(const ivec4& lhs, const ivec4& rhs){ return !(lhs == rhs); }


struct vec2
{
    union{
        struct{
            GLfloat x, y;
        };
        struct{
            GLfloat far, near;
        };
        struct{
            GLfloat sigma,beta;
        };
    };



    vec2() : x(0.0f), y(0.0f) { }
    vec2(GLfloat X, GLfloat Y) : x(X), y(Y){ }
    explicit vec2(GLfloat S) : x(S), y(S) { }
    operator ivec2() const;
    vec2 operator + (const vec2 &rhs) const { return vec2(x + rhs.x, y + rhs.y); }
    vec2 operator * (const vec2 &rhs) const { return vec2(x * rhs.x, y * rhs.y); }
    vec2 operator - (const vec2 &rhs) const { return vec2(x - rhs.x, y - rhs.y); }
    vec2 operator * (const GLfloat s)  const  { return vec2(x * s, y * s); }
    inline friend vec2 operator * (const GLfloat s, const vec2 &rhs) { return rhs * s; }
    vec2 operator / (const GLfloat s)  const  { return vec2(x / s, y / s); }

    vec2 &operator *= (const GLfloat s)   { *this = *this * s; return *this; }
    vec2 &operator += (const vec2 &rhs) { *this = *this + rhs; return *this; }
    vec2 &operator *= (const vec2 &rhs) { *this = *this * rhs; return *this; }
    vec2 &operator -= (const vec2 &rhs) { *this = *this - rhs; return *this; }

    GLfloat &operator [] (GLuint i)             { return (&x)[i]; }
    const GLfloat &operator [] (GLuint i) const { return (&x)[i]; }

};
inline bool operator==(const vec2& lhs, const vec2& rhs){ return (lhs.x==rhs.x)&&(lhs.y==rhs.y); }
inline bool operator!=(const vec2& lhs, const vec2& rhs){ return !(lhs == rhs); }

struct vec3
{
    GLfloat x, y, z;

    vec3() : x(0.0f), y(0.0f), z(0.0f) { }
    vec3(GLfloat X, GLfloat Y, GLfloat Z) : x(X), y(Y), z(Z) { }
    vec3(vec2 XY, GLfloat Z) : x(XY.x), y(XY.y), z(Z) { }
    explicit vec3(GLfloat S) : x(S), y(S), z(S) { }
    operator ivec3() const;
    vec3 operator - () const { return vec3(-x, -y, -z); }
    vec3 operator + (const vec3 &rhs) const { return vec3(x + rhs.x, y + rhs.y, z + rhs.z); }
    vec3 operator * (const vec3 &rhs) const { return vec3(x * rhs.x, y * rhs.y, z * rhs.z); }
    vec3 operator - (const vec3 &rhs) const { return vec3(x - rhs.x, y - rhs.y, z - rhs.z); }
    vec3 operator * (const GLfloat s)  const  { return vec3(x * s, y * s, z * s); }
    inline friend vec3 operator * (const GLfloat s, const vec3 &rhs) { return rhs * s; }
    vec3 operator / (const GLfloat s)  const  { return vec3(x / s, y / s, z / s); }

    vec3 &operator += (const vec3 &rhs) { *this = *this + rhs; return *this; }
    vec3 &operator *= (const vec3 &rhs) { *this = *this * rhs; return *this; }
    vec3 &operator -= (const vec3 &rhs) { *this = *this - rhs; return *this; }

    GLfloat &operator [] (GLuint i)             { return (&x)[i]; }
    const GLfloat &operator [] (GLuint i) const { return (&x)[i]; }

};
inline bool operator==(const vec3& lhs, const vec3& rhs){ return (lhs.x==rhs.x)&&(lhs.y==rhs.y)&&(lhs.z==rhs.z); }
inline bool operator!=(const vec3& lhs, const vec3& rhs){ return !(lhs == rhs); }

struct vec4
{
    union{
        struct{
            GLfloat x, y, z, w;
        };
        struct{
            GLfloat r, g, b, a;
        };

    };


    vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) { }
    vec4(vec3 V, GLfloat W) : x(V.x), y(V.y), z(V.z), w(W) { }
    vec4(GLfloat X, GLfloat Y, GLfloat Z, GLfloat W) : x(X), y(Y), z(Z), w(W) { }
    explicit vec4(GLfloat S) : x(S), y(S), z(S), w(S) { }
    vec4 operator - () const { return vec4(-x, -y, -z, -w); }
    vec4 operator + (const vec4 &rhs) const { return vec4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w); }
    vec4 operator * (const vec4 &rhs) const { return vec4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w); }
    vec4 operator - (const vec4 &rhs) const { return vec4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w); }
    vec4 operator * (const GLfloat s)  const  { return vec4(x * s, y * s, z * s, w * s); }
    inline friend vec4 operator * (const GLfloat s, const vec4 &rhs) { return rhs * s; }
    vec4 operator / (const GLfloat s)  const  { return vec4(x / s, y / s, z / s, w / s); }

    vec4 &operator *= (const GLfloat s)   { *this = *this * s; return *this; }
    vec4 &operator += (const vec4 &rhs) { *this = *this + rhs; return *this; }
    vec4 &operator *= (const vec4 &rhs) { *this = *this * rhs; return *this; }
    vec4 &operator -= (const vec4 &rhs) { *this = *this - rhs; return *this; }

    GLfloat &operator [] (GLuint i)             { return (&x)[i]; }
    const GLfloat &operator [] (GLuint i) const { return (&x)[i]; }

    vec3 xyz() const { return vec3(x, y, z); }

};
inline bool operator==(const vec4& lhs, const vec4& rhs){ return (lhs.x==rhs.x)&&(lhs.y==rhs.y)&&(lhs.z==rhs.z)&&(lhs.w==rhs.w); }
inline bool operator!=(const vec4& lhs, const vec4& rhs){ return !(lhs == rhs); }

static vec3 normalize(const vec3 &v){
    return v / sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}
static GLfloat dot(vec2 a, vec2 b){
    return a.x*b.x+a.y*b.y;
}
static GLfloat dot(vec3 a, vec3 b){
    return a.x*b.x+a.y*b.y+a.z*b.z;
}
static GLfloat dot(vec4 a, vec4 b){
    return a.x*b.x+a.y*b.y+a.z*b.z+a.w*b.w;
}
static GLfloat len2(const vec2 &v){
    return dot(v,v);
}
static GLfloat len(const vec2 &v){
    return sqrt(len2(v));
}
static vec2 normalize(const vec2 &v){
    return v/len(v);
}
static GLfloat length(const vec3 &v){
    return sqrt(dot(v,v));
}
static vec3 floor(const vec3 &v){
    return vec3(floor(v.x),floor(v.y),floor(v.z));
}
static vec2 floor(const vec2 &v){
    return vec2(floor(v.x),floor(v.y));
}

#endif //FLUIDSIM_LINALG_H
