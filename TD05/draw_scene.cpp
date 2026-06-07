#include "draw_scene.hpp"

#include "tools/stb_image.h"
#include "glbasimac/glbi_texture.hpp"

/// Camera parameters
float angle_theta {45.0};      // Angle between x axis and viewpoint
float angle_phy {30.0};      // Angle between z axis and viewpoint
float dist_zoom {30.0};      // Distance between origin and viewpoint

GLBI_Engine myEngine;
GLBI_Set_Of_Points somePoints(3);
GLBI_Convex_2D_Shape ground{3};

GLBI_Texture textureGrass{};

void initScene() {
	std::vector<float> points {0.0,0.0,0.0};
	somePoints.initSet(points,1.0,1.0,1.0);

	std::vector<float> baseCarre{-10.0,-10.0,0.0,
								 10.0,-10.0,0.0,
								 10.0,10.0,0.0,
								 -10.0,10.0,0.0};
	ground.initShape(baseCarre);
	ground.changeNature(GL_TRIANGLE_FAN);
	int x,y,n;
	unsigned char * grassImage = stbi_load("../assets/textures/Grass.jpg",& x,& y,& n,0);
	
	if(grassImage==nullptr){
		std::cerr << "Failed to open image "<<std::endl;
		exit(1);
	}
	textureGrass.createTexture();
	textureGrass.attachTexture();
	textureGrass.setParameters(GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	textureGrass.setParameters(GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	textureGrass.loadImage(x,y,n,grassImage);
	textureGrass.detachTexture();
	stbi_image_free(grassImage);
}

void drawFrame() {
	// TO DO
}

void drawBase() {
	// TO DO
}

void drawArm() {
	// TO DO
}

void drawPan() {
	// TO DO
}

void drawScene() {
	glPointSize(10.0);

	somePoints.drawSet();

	myEngine.setFlatColor(0.2,0.0,0.0);
	myEngine.activateTexturing(true);
	textureGrass.attachTexture();
	ground.drawShape();
	textureGrass.detachTexture();
	myEngine.activateTexturing(false);
}



