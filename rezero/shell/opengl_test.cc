// Created by Dong Zhong on 2021/09/25.

#include "rezero/shell/opengl_test.h"

#include <mutex>

#include "rezero/base/build_config.h"
#if defined(REZERO_PLATFORM_ANDROID)
#include <GLES2/gl2.h>
#elif defined(REZERO_PLATFORM_IOS)
#import <OpenGLES/ES2/gl.h>
#endif

namespace rezero {
namespace shell {

const GLchar* vertex_source =
    "attribute vec4 position;                     \n"
    "void main()                                  \n"
    "{                                            \n"
    "  gl_Position = vec4(position.xyz, 1.0);     \n"
    "}                                            \n";

const GLchar* fragment_source =
    "precision mediump float;\n"
    "void main()                                  \n"
    "{                                            \n"
    "  gl_FragColor[0] = gl_FragCoord.x/640.0;    \n"
    "  gl_FragColor[1] = gl_FragCoord.y/480.0;    \n"
    "  gl_FragColor[2] = 0.5;                     \n"
    "}                                            \n";

GLfloat vertices[] = { 0.0f, 1.0f, 1.0f, 1.0f,
                       1.0f, -1.0f, 0.0f, 1.0f,
                       -1.0f, -1.0f, 0.0f, 1.0f };

std::once_flag init_flag;

void InitOpenGLInternal() {
  glViewport(0, 0, 640, 480);

  GLuint vbo;
  glGenBuffers(1, &vbo);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_source, nullptr);
  glCompileShader(vertex_shader);

  GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_source, nullptr);
  glCompileShader(fragment_shader);

  GLuint shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);
  glUseProgram(shader_program);

  GLint posAttrib = glGetAttribLocation(shader_program, "position");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

void InitOpenGL() {
  std::call_once(init_flag,
                 InitOpenGLInternal);
}

void DrawOpenGL(TimePoint start_time, TimePoint end_time) {
  const uint32_t milliseconds_since_start = start_time.ToEpochDelta().ToMilliseconds();
  const uint32_t milliseconds_per_loop = 3000;
  vertices[0] = (milliseconds_since_start % milliseconds_per_loop) / float(milliseconds_per_loop) - 0.5f;
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glDrawArrays(GL_TRIANGLES, 0, 3);
}

} // namespace shell
} // namespace rezero
