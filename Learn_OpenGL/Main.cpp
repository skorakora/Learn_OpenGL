#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

//Processes keyboard input
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

}

int main()
{
    //initializes GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Initializes window
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);


    //initalizes glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //sets viewport to 800x600
    glViewport(0, 0, 800, 600);


    //First triangle and second triangle definition
    float firstTriangle[] = {
        -0.9f, -0.5f, 0.0f,  // left 
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top 
    };
    float secondTriangle[] = {
        0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f   // top 
    };


    GLuint first_Indices[] =
    {
        0,1,2
    };

    GLuint second_Indices[] =
    {
        0,1,2
    };

    //==========================================FIRST OBJECT=================================
    // Generates Vertex Array Object and binds it
    VAO VAO1;
    VAO1.Bind();

    // Generates Vertex Buffer Object and links it to vertices
    VBO VBO1(firstTriangle, sizeof(firstTriangle));
    // Generates Element Buffer Object and links it to indices
    EBO EBO1(first_Indices, sizeof(first_Indices));

    // Links VBO to VAO
    VAO1.LinkVBO(VBO1, 0);
    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();


    //===========================================SECOND OBJECT===============================
    // Generates Vertex Array Object and binds it
    VAO VAO2;
    VAO2.Bind();

    // Generates Vertex Buffer Object and links it to vertices
    VBO VBO2(secondTriangle, sizeof(secondTriangle));
    // Generates Element Buffer Object and links it to indices
    EBO EBO2(second_Indices, sizeof(second_Indices));

    // Links VBO to VAO
    VAO2.LinkVBO(VBO2, 0);
    // Unbind all to prevent accidentally modifying them
    VAO2.Unbind();
    VBO2.Unbind();
    EBO2.Unbind();
    
  
    // Generates Shader object using shaders defualt.vert and default.frag
    Shader shaderProgram("default.vert", "default.frag");
    Shader shaderProgram2("default.vert", "default2.frag");



    //main loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        //sets background color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.Activate();
        
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        shaderProgram2.Activate();

        VAO2.Bind();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
 
    shaderProgram.Delete();
    shaderProgram2.Delete();

    glfwTerminate();
    return 0;
}