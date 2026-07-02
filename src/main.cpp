#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include<chrono>
#include<cmath>
#include<shader.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "HELLO", NULL, NULL);
    if (window == NULL) {
        std::cout << "FAILED TO CREATE WINDOW\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "FAILED TO INITIALIZE GLAD\n";
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    float vertices[] = { 
         0.5f, -0.5f, 0.0f, 1.0f,0.0f,0.0f,
         0.5f,  0.5f, 0.0f, 0.0f,1.0f,0.0f,
        -0.5f,-0.5f,0.0f, 0.0f,0.0f,1.0f,
         -0.5f,0.5f,0.0f, 0.0f,0.3f,1.0f,
    };

    unsigned int indices[] = {
      2,0,1,
      1,3,2
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    unsigned int EBO;
    glBindVertexArray(VAO);

    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

   
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6 * sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    Shader shaderObject("../src/vertexShader.vert","../src/fragmentShader.frag");

     while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.3f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderObject.useProgram();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1,&EBO);
    shaderObject.deleteProgram();
    glfwTerminate();
    return 0;
}
