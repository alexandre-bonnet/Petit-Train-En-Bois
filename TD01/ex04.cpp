#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "glbasimac/glbi_engine.hpp"
#include <iostream>

using namespace glbasimac;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;
static float aspectRatio = 1.0f;
/* Espace virtuel */
static const float GL_VIEW_SIZE = 1.;
static bool colorMode = true;
static float color1,color2,color3;
// L'univers 2D visible a une taille de 1.0 en x et en y

/* OpenGL Engine */
GLBI_Engine myEngine;

/* Error handling function */
void onError(int error, const char* description) {
	std::cout << "GLFW Error ("<<error<<") : " << description << std::endl;
}

void onWindowResized(GLFWwindow* /*window*/, int width, int height){
    aspectRatio = width / (float) height;
    glViewport(0, 0, width, height);
    if( aspectRatio > 1.0){
        myEngine.set2DProjection(-GL_VIEW_SIZE * aspectRatio/ 2.,
        GL_VIEW_SIZE * aspectRatio / 2. ,
        -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
    } else {
        myEngine.set2DProjection(-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
        -GL_VIEW_SIZE / (2. * aspectRatio),
        GL_VIEW_SIZE / (2. * aspectRatio));
    }
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    } if (key == GLFW_KEY_E && action == GLFW_PRESS){
        colorMode = !colorMode;
        std::cout << "Color mode "<<colorMode << std::endl;
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && colorMode){
        double xpos, ypos;
        int width, height;
        glfwGetWindowSize(window,&width,&height);
        glfwGetCursorPos(window, &xpos, &ypos);
        color1 = int(xpos)%width/float(width);
        color2 = int(ypos)%height/float(height);
        color3 = 0;
    }
}

int main() {
    // Initialize the library
    if (!glfwInit()) {
        return -1;
    }

    /* Try to uncomment this for Mac if it did not work */
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


    /* Callback to a function if an error is rised by GLFW */
	glfwSetErrorCallback(onError);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 800, "TD 01 Ex 03", nullptr, nullptr);
    glfwSetWindowSizeCallback(window, onWindowResized);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    // Make the window's context current
    glfwMakeContextCurrent(window);

	// Intialize glad (loads the OpenGL functions)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return -1;
	}

	// Initialize Rendering Engine
	myEngine.initGL();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		/* Render here */
        if(!colorMode){
            double xpos, ypos;
            int width, height;
            glfwGetWindowSize(window,&width,&height);
            glfwGetCursorPos(window, &xpos, &ypos);
            color1 = int(xpos)%width/float(width);
            color2 = 0;
            color3 = int(ypos)%height/float(height);
        }
        glClearColor(color1,color2,color3,0.f);
		glClear(GL_COLOR_BUFFER_BIT);

        // render here

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		/* Elapsed time computation from loop begining */
		double elapsedTime = glfwGetTime() - startTime;
		/* If to few time is spend vs our wanted FPS, we wait */
		while(elapsedTime < FRAMERATE_IN_SECONDS)
		{
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS-elapsedTime);
			elapsedTime = glfwGetTime() - startTime;
		}
	}

    glfwTerminate();
    return 0;
}
