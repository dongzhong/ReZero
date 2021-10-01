// Created by Dong Zhong on 2021/09/25.

#ifndef REZERO_SHELL_OPENGL_TEST_H_
#define REZERO_SHELL_OPENGL_TEST_H_

#include "rezero/base/time/time_point.h"

namespace rezero {
namespace shell {

void InitOpenGL();

void DrawOpenGL(TimePoint start_time, TimePoint end_time);

} // namespace shell
} // namespace rezero

#endif // REZERO_SHELL_OPENGL_TEST_H_