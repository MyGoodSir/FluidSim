#include <jni.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fluid.h"
#include "logger.h"
#include <GLES/gl.h>
#include <EGL/egl.h>

static void printGlString(const char* name, GLenum s) {
    const char* v = (const char*)glGetString(s);
    LOG_VER("GL %s: %s\n", name, v);
}

static Fluid* fluid = NULL;

extern "C" {
JNIEXPORT void JNICALL Java_com_adriansimmons_fluidsim_FluidSimNativeLib_init(JNIEnv* env, jobject obj, jint num_particles);
JNIEXPORT void JNICALL Java_com_adriansimmons_fluidsim_FluidSimNativeLib_resize(JNIEnv* env, jobject obj, jint width, jint height);
JNIEXPORT void JNICALL Java_com_adriansimmons_fluidsim_FluidSimNativeLib_step(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_com_adriansimmons_fluidsim_FluidSimNativeLib_display(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_com_adriansimmons_fluidsim_FluidSimNativeLib_rotate(JNIEnv* env, jobject obj, jfloat theta);
};


JNIEXPORT void JNICALL
Java_com_adriansimmons_fluidsim_FluidSimNativeLib_init(JNIEnv* env, jobject obj, jint num_particles) {
    if (fluid) {
        delete fluid;
        fluid = NULL;
    }
    printGlString("Version", GL_VERSION);
    printGlString("Vendor", GL_VENDOR);
    printGlString("Renderer", GL_RENDERER);
    printGlString("Extensions", GL_EXTENSIONS);
    fluid = make_fluid(num_particles);
}

JNIEXPORT void JNICALL
Java_com_adriansimmons_fluidsim_FluidSimNativeLib_resize(JNIEnv* env, jobject obj, jint width, jint height) {
    if (fluid) {
        fluid->resize(width, height);
    }
}

JNIEXPORT void JNICALL
Java_com_adriansimmons_fluidsim_FluidSimNativeLib_rotate(JNIEnv* env, jobject obj, jfloat x) {
    if (fluid) {
        fluid->update_gravity(x);
    }
}

JNIEXPORT void JNICALL
Java_com_adriansimmons_fluidsim_FluidSimNativeLib_step(JNIEnv* env, jobject obj) {
    if (fluid) {
        fluid->step();
    }
}

JNIEXPORT void JNICALL
Java_com_adriansimmons_fluidsim_FluidSimNativeLib_display(JNIEnv* env, jobject obj) {
    if (fluid) {
        fluid->display();
    }
}