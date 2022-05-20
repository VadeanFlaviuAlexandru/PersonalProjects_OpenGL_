#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include<vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "model.h"
#include "mesh.h"
#include "obiect.h"
#include "scena.h"

#define STB_IMAGE_IMPLEMENTATION
#include"stb/stb_image.h"

// functii ce creaza shaderele
GLuint createProgram(char* VSFile, char* FSFile);
std::string readFile(const char *filePath);

// functie ce creaza scena
// aceasta functie trebuie rescrisa de voi
Scena createScena(GLuint programShadere);


// functii ce initializeaza fereastra si
// proceseaza intrarile de la mouse si tastatura
GLFWwindow* initializari();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// configurari
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
glm::vec3 cameraPos   = glm::vec3(0.0f, 1.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, -1.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
float fov   =  45.0f;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
    // initializam fereastra
    GLFWwindow* fereastra = initializari();

    // cream shaderele si folosim programul creat
    // (avand o scena simpla folosim un singur program)
    GLuint program = createProgram("obiect1.vert","obiect1.frag");
    glUseProgram(program);

    //cream scena
    Scena S = createScena(program);


    while(!glfwWindowShouldClose(fereastra))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // procesam intrarile ferestrei: din taste si/sau mouse
        processInput(fereastra);

        // trimitem matricea projection catre shadere
        glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glUniformMatrix4fv(glGetUniformLocation(program,"projection"), 1, GL_FALSE,&projection[0][0]);

        // camera/view transformation
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, &view[0][0]);


        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        S.DrawScene();

        glfwSwapBuffers(fereastra);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

Scena createScena(GLuint program){

    Scena aux = Scena();
    // load models
    // -----------



    // TO DO: aici incarcati modelele voastre
    // fie luati datele dintr-un fisier, fie puneti datele aici


    // aici aveti un exemplu extrem de sumar cum puteti incarca si folosi doua obiecte.

    locatie l = {0.0, 0.0, 0.0};
    rotatie r = {0.0, 1.0, 1.0, 1.0};
    scalare s = {1.0f, 1.0f, 1.0f};





    aux.addObiect(Obiect(11, "resurse/tombstone.obj", {4.0,0.0,10.0}, r, {0.1f, 0.1f, 0.1f}, program));
    aux.addObiect(Obiect(111, "resurse/tombstone.obj", {15.0,0.0,10.0}, r, {0.1f, 0.1f, 0.1f}, program));
    aux.addObiect(Obiect(211, "resurse/tombstone.obj", {18.0,0.0,4.0}, r, {0.1f, 0.1f, 0.1f}, program));
    aux.addObiect(Obiect(311, "resurse/tombstone.obj", {4.0,0.0,19.0}, r, {0.1f, 0.1f, 0.1f}, program));
    aux.addObiect(Obiect(411, "resurse/tombstone.obj", {7.0,0.0,7.0}, r, {0.1f, 0.1f, 0.1f}, program));
    aux.addObiect(Obiect(511, "resurse/tombstone.obj", {1.0,0.0,1.0}, r, {0.1f, 0.1f, 0.1f}, program));
    aux.addObiect(Obiect(91, "resurse/tombstone.obj", {14.0,0.0,14.0}, r, {0.1f, 0.1f, 0.1f}, program));
    aux.addObiect(Obiect(991, "resurse/tombstone.obj", {15.0,0.0,13.0}, r, {0.1f, 0.1f, 0.1f}, program));
    aux.addObiect(Obiect(22, "resurse/ObjTomb.obj", {3.0,0.36,5.0}, r, {0.1f, 0.1f, 0.1f}, program));
    aux.addObiect(Obiect(33, "resurse/Ghost.obj", {9.0,0.36,5.0}, r, {0.01f, 0.01f, 0.01f}, program));
    aux.addObiect(Obiect(44, "resurse/Moon.obj", {9.0,35.0,5.0}, r, {0.01f, 0.01f, 0.01f}, program));
    aux.addObiect(Obiect(33, "resurse/Gravestone2.obj", {10.0,1.0,8.0}, r, {0.15f, 0.15f, 0.15f}, program));
    aux.addObiect(Obiect(33, "resurse/low_poly_log.obj", {13.0,0.0,11.0}, r, {0.01f, 0.01f, 0.01f}, program));

    // exemplu de a crea o bucata de "podea" de gresie
    aux.addObiect(Obiect(0, "resurse/pereti/tiles.obj", l, r, s, program));
    // refolosim modelul folosit in alt obiect pentru a reduce consumul de memorie pe GPU
    // precum si traficul de date spre GPU
    aux.addObiect(Obiect(1, aux.getObiect(0), {1.0, 0.0, 0.0}, r, s, program));
    // putem crea o suprafata de 20 pe 20 cu ele
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){
                if (i+j*20 > 1){ //ca sa nu mai adaugam cele 2 obiecte create anterior
                    aux.addObiect(Obiect(i+j*20, aux.getObiect(0), {i*1.0, 0.0, j*1.0}, r, s, program));
                }
        }
    }

    // putem pune pereti de caramida la marginea lor


    aux.addObiect(Obiect(500, "resurse/pereti/brickwall.obj", {-0.5,0.5,0}, {90, 1, 0, 0}, s, program));
    // adaugam o rotatie acolo pentru a fi corect amplasat
    aux.addRotatieObiect(500,{90, 1, 0, 0});

    // putem pune peretii de jur imrejurul suprafetei de 20 pe 20
    for(int i = 0; i < 20; i++){
        aux.addObiect(Obiect(500+i+1, aux.getObiect(500), {i,0.5,-0.5}, {90, 0, 1 , 0}, s, program));
        if(i%2==0)
            aux.addRotatieObiect(500+i+1,{180, 0, 0, 1});
    }
    for(int i = 0; i < 20; i++){
        aux.addObiect(Obiect(500+20+i+1, aux.getObiect(500), {-0.5,0.5,i}, {90, 1, 0, 0}, s, program));
        if(i%2==0)
            aux.addRotatieObiect(500+20+i+1,{180, 1, 0, 0});
    }
    for(int i = 0; i < 20; i++){
        aux.addObiect(Obiect(500+2*20+i+1, aux.getObiect(500), {i,0.5,20-0.5}, {90, 0, 1, 0}, s, program));
        if(i%2==0)
            aux.addRotatieObiect(500+2*20+i+1,{180, 0, 0, 1});
    }
    for(int i = 0; i < 20; i++){
        aux.addObiect(Obiect(500+3*20+i+1, aux.getObiect(500), {20-0.5,0.5,i}, {90, 1, 0, 0}, s, program));
         if(i%2==0)
            aux.addRotatieObiect(500+3*20+i+1,{180, 1, 0, 0});
    }
    // observati ca putem trece prin pereti, si ca textura se repeta deranjant
    // solutii:
    // puteti impune pozitiei camerei restrictii - sa nu trecem prin pereti
    // folositi mai multe obiecte tip 'perete' luate aleator, si nu repetati acelasi obiect.

    return aux;
}


GLFWwindow* initializari()
{
    /*
        functia initializeaza bibliotecile glfw si glad, creaza o fereastra si
            o ataseaza  unui context OpenGL
    */

    //initializam glfw
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //cream fereastra
    GLFWwindow * window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "scena_01", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    // facem ca aceasta fereastra sa fie contextul curent


    //atasam fereastra contextului opengl
    //glfwMakeContextCurrent(window);

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);



    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout<<" nu s-a initializat biblioteca GLAD!";
    }


    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);


    return window;

}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = static_cast<float>(6.5 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        cameraPos += cameraSpeed * cameraFront;

        std::cout<<cameraPos[0]<<"f, "<<cameraPos[1]<<"f, "<<cameraPos[2]<<"f"<<'\n';
        }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        cameraPos -= cameraSpeed * cameraFront;}
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;


    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

    }
    /*
    if(cameraPos[0]>-1.0f){
        cameraPos[0]=-1.0f;
    }else
    if(cameraPos[0]<-21.0f){
        cameraPos[0]=-21.0f;
    }

    if(cameraPos[1]> 0.4f){
        cameraPos[1]=0.4f;
    }else
    if(cameraPos[1]<8.9f){
        cameraPos[1]=8.9f;
    }

    if(cameraPos[2]>-0.6f){
        cameraPos[2]=-0.6f;
    }else
    if(cameraPos[2]<19.6f){
        cameraPos[2]=19.6f;
    }
    */
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}


GLuint createProgram(char* VSFile, char* FSFile)
{

    /*
        functia creaza un program shader folosind ca fisiere sursa VSFile si FSFile
        IN: numele fisierelor sursa
        OUT: aliasul programului shader
    */

    GLuint vertexShader, fragmentShader, shaderProgram;
    int success;
    char infoLog[512];


    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    if( 0 == vertexShader )
    {
        std::cout << "Error creating vertex shader." << std::endl;
        exit(1);
    }

    std::string shaderCode = readFile(VSFile);
    const char *codeArray = shaderCode.c_str();
    glShaderSource( vertexShader, 1, &codeArray, NULL );

    glCompileShader(vertexShader);

    // verficam daca s-a reusit compilarea codului

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    if( 0 == fragmentShader )
    {
        std::cout << "Error creating fragment shader." << std::endl;
        exit(1);
    }


    shaderCode = readFile(FSFile);
    codeArray = shaderCode.c_str();
    glShaderSource( fragmentShader, 1, &codeArray, NULL );


    glCompileShader(fragmentShader);

    // se verifica compilarea codului

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //cream programul

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // se verifica procesul de link

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}


std::string readFile(const char *filePath)
{
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if(!fileStream.is_open())
    {
        std::cerr << "Could not read file " << filePath;
        std::cerr << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while(!fileStream.eof())
    {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}
