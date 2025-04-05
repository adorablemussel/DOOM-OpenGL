#pragma once

#include <vector>

#include <glad/glad.h>
//#include <stddef.h>

GLuint compile_shader(GLenum type, const char* src);
GLuint link_program(std::vector<GLuint> shaders, ...); // using std::vector instead of size_t from <stddef.h>
