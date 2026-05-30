#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "tools/shaders.hpp"
#include <iostream>
#include <vector>

using namespace glbasimac;
using namespace STP3D;

/* Window properties */
static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 800;
static const char WINDOW_TITLE[] = "TD02 Ex01";
static float aspectRatio = 1.0f;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

/* Virtual windows space */
static const float GL_VIEW_SIZE = 4.;

/* OpenGL Engine */
GLBI_Engine myEngine;
GLBI_Set_Of_Points thePoints;

/*Shapes*/
GLBI_Convex_2D_Shape square;
GLBI_Convex_2D_Shape triangle;
GLBI_Convex_2D_Shape circle;

/* Error handling function */
void onError(int error, const char* description){
	std::cout << "GLFW Error ("<<error<<") : " << description << std::endl;
}

void onWindowResized(GLFWwindow* /*window*/, int width, int height){
	aspectRatio = width / (float) height;

	glViewport(0, 0, width, height);
	if( aspectRatio > 1) {
		myEngine.set2DProjection(-GL_VIEW_SIZE / 2. * aspectRatio, GL_VIEW_SIZE / 2. * aspectRatio,
								 -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
	} else {
		myEngine.set2DProjection(-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
								 -GL_VIEW_SIZE / 2. / aspectRatio, GL_VIEW_SIZE / 2. / aspectRatio);
	}
}

void onKey(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/){
	if (key == GLFW_KEY_A && action == GLFW_PRESS){
		std::cout << "keyPressed Quit ('Q')"<<std::endl;
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	} else if (key == GLFW_KEY_P && action == GLFW_PRESS){
		std::cout << "keyPressed Points ('P')"<<std::endl;
		thePoints.changeNature(GL_POINTS);
	} else if (key == GLFW_KEY_L && action == GLFW_PRESS){
		std::cout << "keyPressed Lines ('L')"<<std::endl;
		thePoints.changeNature(GL_LINE_STRIP);
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
	std::cout << "click"<<std::endl;
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        double xpos, ypos;
        int width, height;
        glfwGetWindowSize(window,&width,&height);
        glfwGetCursorPos(window, &xpos, &ypos);
		float xCord{};
		float yCord{};
		if( aspectRatio > 1) {
			xCord = (xpos - width/2)*GL_VIEW_SIZE/height;
			yCord = -(ypos - height/2)*GL_VIEW_SIZE/height;
		} else {
			xCord = (xpos - width/2)*GL_VIEW_SIZE/width;
			yCord = -(ypos - height/2)*GL_VIEW_SIZE/width;
		}
		std::vector<float> newPoint = {xCord,yCord};
		std::vector<float> newColor = {1.0,1.0,1.0};
		thePoints.addAPoint(newPoint.data(),newColor.data());
    }
}

void initScene(){
	glClearColor(1.f,1.f,1.f,1.f);
	square.initShape({0.5,0.5,
	0.5,-0.5,
	-0.5,-0.5,
	-0.5,0.5});
	//thePoints.initSet(cords,color);
	glPointSize(10.0);
}

void renderScene(GLFWwindow* window){
		/* Render here */
		glClearColor(0.2f,0.0,0.0,0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		thePoints.drawSet();
		myEngine.setFlatColor(1.f,1.f,1.f);
		square.drawShape();
}

int main(int /*argc*/, char** /*argv*/){
	/* GLFW initialisation */
	GLFWwindow* window;
	if (!glfwInit()) return -1;
	
	
    /* Try to uncomment this for MAC OS if it did not work */
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	
	/* Callback to a function if an error is rised by GLFW */
	glfwSetErrorCallback(onError);
	
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (!window) {
		// If no context created : exit !
		glfwTerminate();
		return -1;
	}
	
	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	
	std::cout<<"Loading GL extension"<<std::endl;
	// Intialize glad (loads the OpenGL functions)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return -1;
	}
	
	glfwSetWindowSizeCallback(window,onWindowResized);
	glfwSetKeyCallback(window, onKey);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	
	std::cout<<"Engine init"<<std::endl;
	myEngine.initGL();
	onWindowResized(window,WINDOW_WIDTH,WINDOW_HEIGHT);
	CHECK_GL;
	initScene();
	
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		renderScene(window);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		
		/* Poll for and process events */
		glfwPollEvents();

		/* Elapsed time computation from loop begining */
		double elapsedTime = glfwGetTime() - startTime;
		/* If to few time is spend vs our wanted FPS, we wait */
		while(elapsedTime < FRAMERATE_IN_SECONDS){
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS-elapsedTime);
			elapsedTime = glfwGetTime() - startTime;
		}
	}
	glfwTerminate();
	return 0;
}