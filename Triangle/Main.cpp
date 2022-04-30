#include<iostream>
#include<glad/glad.h>
#include<GLfW/glfw3.h>
#include <math.h>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main ()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main ()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main()
{
    glfwInit(); //we use glfw to initialize a window

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //glfw doesnt know what type of opengl we're using so we're telling him that with this
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //same as before
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // last hint about what opengl profile we gonna use
    //a opengl profile is like a package of funtioncs. Core profile for more modern functions





	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
	};
    //now we have the source code for our fragment shader and vertex shader, but dont have the shader themselves. they are opengl objects
















    GLFWwindow* window = glfwCreateWindow(800, 800,"PersonalProject", NULL, NULL); // data type for a window object in glfw
    //width, height, name of the window,if we want it fullscreen or not and last thing not important.
    if (window==NULL)   //this is error checking if the windows fails to create
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); //this is to tell glfw to use the window
    //context=object that holds the whole of opengl. kinda abstract, i know

    gladLoadGL(); //load the needed configuration for opengl

    glViewport(0,0,800,800);//the erea of the window where we want opengl to render in

    //lets create a value/a referenec to store our vertex shader in
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //now that we have a vertex shader, lets feed it the source code earlier
    glShaderSource(vertexShader,1, &vertexShaderSource, NULL);
    //the gpu cant understand the source code, so we compile it right now
    glCompileShader(vertexShader);

    //now we have a vertex shader, and we do the same thing for fragment shaderr
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //now we have to wrap them up in a shader program
    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);    //to wrap up
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //sendin stuff its slow, so we gonna use buffers.
    //lets create a vertex buffer object where we will store our vertex data;
    GLuint VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1,&VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0,3, GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f); //.specify the color of the background. last number if for transparency
    glClear(GL_COLOR_BUFFER_BIT);//clear the back buffer and assign the new color to it
    glfwSwapBuffers(window);//swap the back buffer with the front buffer

    while (!glfwWindowShouldClose(window)) // to make the window close when we press the close button or if another function tells it to close
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);
        glfwSwapBuffers(window);
        glfwPollEvents(); //to process all the pulled events, such as the window appearing
    }

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window); //to destroy the window
    glfwTerminate();//to terminate the window
    return 0;
}
