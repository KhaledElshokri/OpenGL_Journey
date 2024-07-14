#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "My Journey", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "ERROR: GLEW INIT" << std::endl;
    }

    {
        float positions[] = {
            -0.5f, -0.5f, //0
             0.5f, -0.5f, //1
             0.5f,  0.5f, //2
            -0.5f,  0.5f, //3
        };

        unsigned int indices[] = {

            0, 1, 2,
            2, 3, 0
        };

        unsigned int vao; //holds the vertex array object i.e vao
        GLCall(glGenVertexArrays(1, &vao));
        GLCall(glBindVertexArray(vao));


        VertexArray va;
        VertexBuffer vb(positions, 4 * 2 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);


        IndexBuffer ib(indices, 6);


        Shader shader("res/shaders/Basic.shader");
        shader.Bind(); // Binding my shader
        shader.SetUniform4f("u_color", 0.8f, 0.3f, 0.8f, 1.0f); // set data in the shader and retreiving the location of this color uniform


        va.UnBind();
        vb.Unbind();
        ib.Unbind();
        shader.UnBind();

        float r = 0.0f;
        float increment = 0.05f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            GLCall(glClear(GL_COLOR_BUFFER_BIT));

            shader.Bind(); // Binding shader
            shader.SetUniform4f("u_color", r, 0.3f, 0.8f, 1.0f);

            va.Bind();
            ib.Bind(); // Binding index buffer

            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr)); // issuing Draw Call

            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;

            r += increment;

            /* Swap front and back buffers */
            GLCall(glfwSwapBuffers(window));

            /* Poll for and process events */
            GLCall(glfwPollEvents());
        }

    } // scope added to terminate the program when the window is closed

    glfwTerminate();
    return 0;
}