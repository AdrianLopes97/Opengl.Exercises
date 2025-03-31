#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "ApplyTransformationTriangle.h"
#include "CreateBasicSquare.h"
#include "ShaderSources.h"

void renderSquare(GLFWwindow* window) {
    // Vertex data for a square
    float vertices[] = {
        // Positions         // Colors
       -0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, // Top left
        0.5f,  0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // Top right
        0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f, // Bottom right
       -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f  // Bottom left
    };

    unsigned int indices[] = {
        0, 1, 2, // First triangle
        0, 2, 3  // Second triangle
    };

    // Create VAO, VBO, and EBO
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind VAO
    glBindVertexArray(VAO);

    // Bind and set VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind and set EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind VAO
    glBindVertexArray(0);

    // Compile shaders and create shader program (reuse existing shader code)
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    int transformLoc = glGetUniformLocation(shaderProgram, "transform");

    float rotation[4][4], scale[4][4], transform[4][4];
    float angle = 0.0f;
    float sx = 1.0f, sy = 1.0f, sz = 1.0f;

    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        angle += 1.0f;
        sx = 0.5f + 0.5f * sin(glfwGetTime());
        sy = 0.5f + 0.5f * cos(glfwGetTime());

        createRotationMatrixZ(rotation, angle);
        createScaleMatrix(scale, sx, sy, sz);

        multiplyMatrices(transform, scale, rotation);

        glUniformMatrix4fv(transformLoc, 1, GL_TRUE, &transform[0][0]);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
}