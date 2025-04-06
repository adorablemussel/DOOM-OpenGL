#include "renderer.h"
#include "gl_helpers.h"

#include <glad/glad.h>

static void init_shader();
static void init_quad();

const char* vertSrc =
"#version 330 core\n"
"layout (location = 0) in vec2 pos;\n"
"uniform mat4 model;\n"
"uniform mat4 projection;\n"
"void main() {\n"
"    gl_Position = projection * model * vec4(pos, 0.0, 1.0);\n"
"}\n";

const char* fragSrc =
"#version 330 core\n"
"out vec4 fragColor;\n"
"uniform vec4 color;\n"
"void main() {\n"
"    fragColor = color;\n"
"}\n";

static float width, height;
static GLuint program;

void renderer_init(int w, int h) {
    width = w;
    height = h;

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	init_quad();
    init_shader();
}

void renderer_clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

static void init_shader() {
    GLuint vertex   = compile_shader(GL_VERTEX_SHADER, vertSrc);
    GLuint fragment = compile_shader(GL_FRAGMENT_SHADER, fragSrc);
    program         = link_program({ vertex, fragment });
}

static void init_quad() {
    float vertices[] = {
        0.5f, 0.5f,     // top right
        0.5f, -0.5f,    // bottom right
        -0.5f, -0.5f,   // bottom left
        -0.5f, 0.5f,    // top left
    };
    uint32_t indices[] = {
        0, 1, 3,        // first triangle
        1, 2, 3,        // second triangle
    };

    GLuint vbo, vao, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Unbind the vbo; vao and ebo are still bound
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
