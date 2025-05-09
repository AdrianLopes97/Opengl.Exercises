#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "ApplyTransformationTriangle.h"
#include "CreateBasicTriangle.h"
#include "ShaderSources.h"

void renderTriangle(GLFWwindow* window) {
    // Vertex data
    float vertices[] = {
        // Positions         // Colors
        0.0f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, // Top
       -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // Bottom left
        0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f  // Bottom right
    };

    // Create VAO and VBO
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind VAO
    glBindVertexArray(VAO);

    // Bind and set VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind VAO
    glBindVertexArray(0);

    // Compile Vertex Shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // Check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Compile Fragment Shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // Check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Link shaders to create a program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // Delete shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // Uniform location in shader
    int transformLoc = glGetUniformLocation(shaderProgram, "transform");

    // Transformation matrices
    float translation[4][4], rotation[4][4], scale[4][4], transform[4][4];

    // Transformation parameters
    float tx = 0.0f, ty = 0.0f, tz = 0.0f; // Translation
    float angle = 45.0f;                  // Rotation in degrees
    float sx = 1.0f, sy = 1.0f, sz = 1.0f; // Scale

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // Input
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // Update transformation parameters
        angle += 1.0f; // Increase angle for continuous rotation
        tx = sin(glfwGetTime()) * 0.5f; // Dynamic translation on the X axis
        ty = cos(glfwGetTime()) * 0.5f; // Dynamic translation on the Y axis

        // Create transformation matrices
        createTranslationMatrix(translation, tx, ty, tz);
        createRotationMatrixZ(rotation, angle);
        createScaleMatrix(scale, sx, sy, sz);

        // Combine the matrices: transform = scale * rotation * translation
        multiplyMatrices(transform, scale, rotation);
        multiplyMatrices(transform, transform, translation);

        // Send the transformation matrix to the shader
        glUniformMatrix4fv(transformLoc, 1, GL_TRUE, &transform[0][0]);

        // Rendering commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
}