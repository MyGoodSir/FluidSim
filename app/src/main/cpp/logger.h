//
// Created by joesc on 12/6/2021.
//

#ifndef FLUIDSIM_LOGGER_H
#define FLUIDSIM_LOGGER_H
#include <android/log.h>
#include <android/api-level.h>
#define DEBUG 1

#define LOG_ERR(...) __android_log_print(ANDROID_LOG_ERROR, "FluidSim", __VA_ARGS__)
#if DEBUG
#define LOG_VER(...) __android_log_print(ANDROID_LOG_VERBOSE, "FluidSim", __VA_ARGS__)
#else
#define LOG_VER(...)
#endif
#endif //FLUIDSIM_LOGGER_H
