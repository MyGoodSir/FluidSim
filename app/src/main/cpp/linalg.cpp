//
// Created by joesc on 11/27/2021.
//

#include "linalg.h"
#ifndef PI
#define PI 3.141592653589f
#endif

ivec3::operator vec3() const {return vec3((GLfloat)x,(GLfloat)y, (GLfloat)z);}
vec3::operator ivec3() const {return ivec3((GLint)x,(GLint)y, (GLint)z);}
ivec2::operator vec2() const {return vec2((GLfloat)x,(GLfloat)y);}
vec2::operator ivec2() const {return ivec2((GLint)x,(GLint)y);}
