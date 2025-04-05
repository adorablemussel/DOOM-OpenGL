#include <iostream>
#include <vector>

#include <glad/glad.h>
//#include <stddef.h>

#include "gl_helpers.h"

GLuint compile_shader(GLenum type, const char* src) {
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar info_log[512];
		glGetShaderInfoLog(shader, sizeof(info_log), NULL, info_log);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << info_log << std::endl;
	}

	return shader;
}

GLuint link_program(std::vector<GLuint> shaders, ...) { // using std::vector instead of size_t from <stddef.h>
	GLuint program = glCreateProgram();

	for (GLuint shader : shaders) {
		glAttachShader(program, shader);
	}

	glLinkProgram(program);
	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar info_log[512];
		glGetProgramInfoLog(program, sizeof(info_log), NULL, info_log);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << info_log << std::endl;
	}

	return program;
}
