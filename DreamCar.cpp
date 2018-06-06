// CopyRight belongs to Liu Yuanjian
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Model.h"
#include "Camera.h"
//Matrices and vectors library
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using std::string;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void translateAndRotate(const Shader & shader);
const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;
bool MouseDown = false;
//Camera camera(glm::vec3(0.7f, 4.0f, 2.0f));
Camera camera(glm::vec3(0.0f, 0.0f, 10.0f));

double lastX = SCR_WIDTH / 2.0f;
double lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

double deltaTime = 0.0f;	// Time between current frame and last frame
double lastFrame = 0.0f; // Time of last frame
glm::vec3 lightPos(1.0f, 1.0f, 3.0f);
glm::vec3 pointLightPositions[] = {
        glm::vec3( 12.5f,  5.32f,  19.38f),
        //glm::vec3( 16.6f,  3.3f, -4.23f),
};
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_buttonCallback(GLFWwindow* window, int button, int action, int mods);
int main(int argc,char* argv[]){
    const string CURDIR="/Users/hython/CLionProjects/GLUT_Learning";
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Dream Car SUV", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window,scroll_callback);
    glfwSetMouseButtonCallback(window,mouse_buttonCallback);
    //Don't forget to load GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    std::cout<<argv[0]<<std::endl;
    Shader shader(CURDIR+"/shaders/lighting.vert",
                  CURDIR+"/shaders/lighting.frag");
    //Shader lamp(CURDIR + "/shaders/lamp.vert",
//                CURDIR + "/shaders/lamp.frag",CURDIR+"/shaders/lamp.geom.glsl");

    //string modelPath=CURDIR+"/Resources/SUV_BF3/suv.obj";
    //string modelPath = CURDIR + "/Resources/Aventador/Avent.obj";
    //string modelPath = CURDIR + "/Resources/Car2/Porsche_911_GT2.obj";
    string modelPathSUV=CURDIR+"/Resources/SUV_BF3/suv.obj";
    string modelPath1967ford = CURDIR + "/Resources/1967ford/1967ford.dae";
    //string modelPathAventSport = CURDIR + "/Resources/Aventador_sport/Avent_sport.obj";
    //string modelPathBezier = CURDIR + "/Resources/Bezier/bezier.obj";
    Model modelFord(modelPath1967ford);
    Model modelSUV(modelPathSUV);
    //Model modelAvent(modelPathAventSport);
    //Model modelBezier(modelPathBezier);
    shader.use();
    glEnable(GL_DEPTH_TEST);

    float points[] = {
            -2.5f,  2.5f, 0.0f, 1.0f,1.0f,0.0f, // top-left
            2.5f,  2.5f, 0.0f, 1.0f,0.0f,0.0f, // top-right
            2.5f, -2.5f, 0.0f, 0.0f, 1.0f, 0.0f,// bottom-right
            -2.5f, -2.5f, 0.0f, 0.0f,0.0f,1.0f  // bottom-left
    };
    GLfloat ctrlpoints_top[4][4][3]={
            {{-1.5, -2.2, 1.6},
                    {-0.5, -2.2, 6.0},
                    {6.0, -2.2, 4.0},
                    {7.0, -2.7, -0.5}},
            {{-1.5, -0.5, 1.6},
                    {-0.5, -0.5, 6.0},
                    {6.0, -0.5, 4.0},
                    {7.0, -0.5, -0.5}},
            {{-1.5, 0.5, 1.6},
                    {-0.5, 0.5, 6.0},
                    {6.0, 0.5, 4.0},
                    {7.0, 0.5, -0.5}},
            {{-1.5, 2.2, 1.6},
                    {-0.5, 2.2, 6.0},
                    {6.0, 2.2, 4.0},
                    {7.0, 2.7, -0.5}}
    };


//    GLuint VAO;
//    glGenVertexArrays(1,&VAO);
//    GLuint VBO;
//
//    glGenBuffers(1,&VBO);
//    glBindVertexArray(VAO);
//    glBindBuffer(GL_ARRAY_BUFFER,VBO);
//    glBufferData(GL_ARRAY_BUFFER,sizeof(points),&ctrlpoints_top[0],GL_STATIC_DRAW);
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void *)0);
//    glEnableVertexAttribArray(0);



    glm::vec3 lightColor;
    lightColor.x = sin(2.0f);
    lightColor.y = sin(0.7f);
    lightColor.z = sin(1.3f);



    glm::vec3 diffuseColor = lightColor * glm::vec3(0.7f);
    glm::vec3 ambientColor = diffuseColor * glm::vec3(0.5f);
    while(!glfwWindowShouldClose(window)){
        processInput(window);
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        double currentFrame = glfwGetTime();
        deltaTime = currentFrame-lastFrame;
        lastFrame = currentFrame;
        //glBindTexture(GL_TEXTURE_2D,texture);




        shader.use();
        // directional light
        shader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        shader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        shader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        shader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
        for(int i=0; i< sizeof (pointLightPositions) / sizeof(glm::vec3);i++) {
            string lights = "lights[";
            lights+=char(i+'0');
            //std::cout<<lights<<std::endl;
            shader.setFloat(lights+"].linear", 0.0039f);
            shader.setFloat(lights+"].constant", 1.0f);
            shader.setFloat(lights+"].quadratic", 0.0004f);
            shader.setVec3(lights+"].position", lightPos);
            shader.setVec3(lights+"].ambient", ambientColor);
            shader.setVec3(lights+"].diffuse", diffuseColor);
            shader.setVec3(lights+"].specular", 1.0f, 1.0f, 1.0f);
        }
        shader.setVec3("viewPos", camera.Position);
        // material properties
//        lightingShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
//        lightingShader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
        shader.setInt("material.diffuse",0);
        //lightingShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f); // specular lighting doesn't have full effect on this object's material
        shader.setInt("material.specular",1);
        shader.setFloat("material.shininess", 32.0f);
        
        
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);
        //lightingShader.setMat4("projection",projection);
        //lightingShader.setMat4("view",view);
        glm::mat4 model;
        model = glm::translate(model, glm::vec3(10.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1000.0f, 1000.00f, 1000.0f));

        model = glm::rotate(model, glm::radians(180.0f),glm::vec3(0.0f,1.0f,0.0f));
        shader.setMat4("model", model);
        //lightingShader.setMat4("model",model);
        //lightingShader.use();
        modelFord.Draw(shader);
        model = glm::mat4(1.0f);



        //shader.setMat4("model",model);
        //modelAvent.Draw(shader);
        //model = glm::rotate(model,glm::radians(90.0f),glm::vec3(1.0f,0.0f,0.0f));
        //modelBezier.Draw(shader);
        model = glm::mat4(1.0f);
        //model = glm::translate(model,glm::vec3(-10.0f,0.0,0.0f));
        model = glm::scale(model, glm::vec3(0.03f,0.03f,0.03f));
        shader.setMat4("model",model);
        modelSUV.Draw(shader);

//        lamp.use();
//        model = glm::mat4(1.0f);
//        lamp.setMat4("model", model);
//        lamp.setMat4("projection", projection);
//        lamp.setMat4("view", view);
//        lamp.setInt("Segments",4);
        //glBindVertexArray(VAO);
        //glDrawArrays(GL_LINE_STRIP,0,48);
        //glBindVertexArray(0);
        //ourModel.Draw(lightingShader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;

}
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0,0,width,height);
}
void processInput(GLFWwindow *window){
    if(glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS){
        glfwSetWindowShouldClose(window,true);
    }
    //float cameraSpeed = deltaTime*2.5f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD,deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD,deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT,deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT,deltaTime);
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS){
        std::cout<<"cameraPos("<<camera.Position.x<<","<<camera.Position.y<<","<<camera.Position.z<<")"<<std::endl;
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(!MouseDown)return;
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

    camera.ProcessMouseMovement(xoffset, yoffset);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

void mouse_buttonCallback(GLFWwindow* window, int button, int action,int mods){
    if(button == GLFW_MOUSE_BUTTON_LEFT)
        switch(action){
            case GLFW_PRESS:
                MouseDown = true;

                break;
            case GLFW_RELEASE:
                MouseDown = false;
                firstMouse= true;
                break;
        }
}