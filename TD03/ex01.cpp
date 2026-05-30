#include "glbasimac/glbi_convex_2D_shape.hpp"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "tools/shaders.hpp"
#include <iostream>
#include <cmath>

using namespace glbasimac;
using namespace STP3D;

/* My properties */
double xpos{-1}, ypos{-1};
float beta = 0;
int frame = 0;

/* Window properties */
static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 800;
static const char WINDOW_TITLE[] = "TD02 Ex02";
static float aspectRatio = 1.0f;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

/* Virtual windows space */
static const float GL_VIEW_SIZE = 20;

/* OpenGL Engine */
GLBI_Engine myEngine;
GLBI_Set_Of_Points thePoints;
GLBI_Convex_2D_Shape carre;
GLBI_Convex_2D_Shape trapeze;
GLBI_Convex_2D_Shape triangle;
GLBI_Convex_2D_Shape cercle;

/* Error handling function */
void onError(int error, const char* description) {
	std::cout << "GLFW Error ("<<error<<") : " << description << std::endl;
}

void onWindowResized(GLFWwindow* /*window*/, int width, int height)
{
	WINDOW_HEIGHT = height;
	WINDOW_WIDTH = width;

	aspectRatio = width / (float) height;

	glViewport(0, 0, width, height);

	if( aspectRatio > 1)
	{
		myEngine.set2DProjection(-GL_VIEW_SIZE / 2. * aspectRatio, GL_VIEW_SIZE / 2. * aspectRatio,
								 -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
	}
	else
	{
		myEngine.set2DProjection(-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
								 -GL_VIEW_SIZE / 2. / aspectRatio, GL_VIEW_SIZE / 2. / aspectRatio);
	}
}

void onKey(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/)
{
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
   if (key == GLFW_KEY_F && action == GLFW_PRESS) {
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
   }
   if (key == GLFW_KEY_P && action == GLFW_PRESS) {
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
   }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) 
    {
      beta += M_PI * 1/36;
    }
    if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) 
    {
      beta -= M_PI * 1/36;
    }
    
}

void initScene() {
   std::vector<float> points{
		0.0, 0.0,
		0.5, 0.0,
		0.0, 0.5,
		-.5, -.5
	};
	std::vector<float> colors{
		1.0, 1.0, 1.0,
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		1.0, 0.0, 1.0
	};
	thePoints.initSet(points, colors);


	std::vector<float> points_carre{
		0.5, 0.5,
		0.5, -0.5,
		-0.5, -0.5,
		-0.5, 0.5
		
	};
	carre.initShape(points_carre);
	carre.changeNature(GL_TRIANGLE_FAN);

	std::vector<float> points_triangle{
		-1, -1,
		1, -1,
		0.0, 1
		
	};
	triangle.initShape(points_triangle);
	triangle.changeNature(GL_TRIANGLES);

	std::vector<float> points_trapeze{
		0.0, 2.0,
		0.0, -2.0,
		6.0, -1.0,
		6.0, 1.0
	};
	trapeze.initShape(points_trapeze);

	std::vector<float> points_cercle;
	int nb_points = 100;
	for (int i = 0; i <= nb_points; i++)
	{
		float angle = 2 * M_PI / nb_points;
		points_cercle.push_back(cos(angle * i));
		points_cercle.push_back(sin(angle * i));
	}
	cercle.initShape(points_cercle);
	cercle.changeNature(GL_TRIANGLE_FAN);
}

void drawFirstArm(){
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.setFlatColor(0.8,0.8,0.8);
	trapeze.drawShape();

	myEngine.mvMatrixStack.addHomothety(2.0);
	myEngine.setFlatColor(0.5,0.5,0.5);
	myEngine.updateMvMatrix();
	cercle.drawShape();

	myEngine.mvMatrixStack.popMatrix();
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.updateMvMatrix();

	Vector3D tr{6.0,0.0,0.0};
	myEngine.mvMatrixStack.addTranslation(tr);
	myEngine.updateMvMatrix();

	cercle.drawShape();
}

void drawSecondArm(){
	myEngine.setFlatColor(0.3,0.3,0.3);
	myEngine.mvMatrixStack.pushMatrix(); // Rotation Bras 2
	myEngine.mvMatrixStack.addRotation(0.5,{0.0,0.0,1.0});

	myEngine.updateMvMatrix();
	carre.drawShape();

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation({2,0.0,0.0});
	myEngine.mvMatrixStack.addHomothety({4.6,0.6,0.0});
	myEngine.updateMvMatrix();
	carre.drawShape();
	myEngine.mvMatrixStack.popMatrix();

	myEngine.mvMatrixStack.addTranslation({4.6,0.0,0.0}); 
	myEngine.mvMatrixStack.pushMatrix(); //Translation Bras 2
	myEngine.updateMvMatrix();
	carre.drawShape();
}

void drawThirdArm(){
	myEngine.setFlatColor(0.0,0.0,0.0);
	myEngine.mvMatrixStack.pushMatrix(); // Rotation Bras 3
	myEngine.mvMatrixStack.addRotation(0.3,{0.0,0.0,1.0});
	myEngine.mvMatrixStack.addHomothety({0.6,0.6,0.0});

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addHomothety(0.5);
	myEngine.updateMvMatrix();
	cercle.drawShape();
	myEngine.mvMatrixStack.popMatrix();

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation({2,0.0,0.0});
	myEngine.mvMatrixStack.addHomothety({4.6,0.6,0.0});
	myEngine.updateMvMatrix();
	carre.drawShape();
	myEngine.mvMatrixStack.popMatrix();

	myEngine.mvMatrixStack.addTranslation({4.6,0.0,0.0}); 
	myEngine.mvMatrixStack.addHomothety(0.5);
	myEngine.mvMatrixStack.pushMatrix(); //Translation Bras 3
	myEngine.updateMvMatrix();
	cercle.drawShape();
	myEngine.mvMatrixStack.popMatrix(); //Translation Bras 2
	myEngine.mvMatrixStack.popMatrix(); // Rotation Bras 3
}

void renderScene(GLFWwindow* window) {
	glClearColor(1.0,1.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glLineWidth(10);

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation({-4.0,0.0,0.0});
	myEngine.mvMatrixStack.addRotation(0,{0.0,0.0,1.0});
	myEngine.updateMvMatrix();
	drawFirstArm();
	drawSecondArm();
	for(int i{-1};i<2;i++){
		myEngine.mvMatrixStack.pushMatrix();
		myEngine.mvMatrixStack.addRotation(i*(M_PI/4),{0.0,0.0,1.0});
		myEngine.updateMvMatrix();
		drawThirdArm();
		myEngine.mvMatrixStack.popMatrix();
	}
	myEngine.mvMatrixStack.popMatrix(); //Translation Bras 2
	myEngine.mvMatrixStack.popMatrix(); // Rotation Bras 2
	myEngine.mvMatrixStack.popMatrix(); //Décalage Bras1
	myEngine.mvMatrixStack.popMatrix(); // ROtation Bras Entier
	myEngine.updateMvMatrix();

}

int main(int /*argc*/, char** /*argv*/)
{
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
	if (!window)
	{
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
	while (!glfwWindowShouldClose(window))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		/* Render here */
      renderScene(window);


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
