#include "draw_scene.hpp"
#include "rails.hpp"
#include "gare.hpp"
#include "train.hpp"
#include "arbres.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "tools/stb_image.h"

/// Camera parameters
float angle_theta {45.0};      // Angle between x axis and viewpoint
float angle_phy {30.0};      // Angle between z axis and viewpoint
float dist_zoom {15.0};      // Distance between origin and viewpoint

GLBI_Engine myEngine;

int frameCount{0};

GLBI_Set_Of_Points frame(3);
GLBI_Set_Of_Points grille(3);
GLBI_Convex_2D_Shape ground{3};
GLBI_Convex_2D_Shape cercle{3};

IndexedMesh* sphere;
IndexedMesh* cylindre;
IndexedMesh* cube;
StandardMesh* cone;

std::array<int,2> stationPlacement{};
std::vector<std::array<int,2>> railsPlacement{};
std::vector<std::array<int,3>> vegetationPlacement{};

GLBI_Texture texturePull{};
GLBI_Texture textureGrass{};


void initGrille(){
	std::vector<float> grilleFrame{};
	std::vector<float> grilleColor{};
	for(int i  = -5;i<6;i++){
		grilleFrame.insert(grilleFrame.end(),{10.f*i,-50.f,0.f,10.f*i,50.f,0.f});
		grilleFrame.insert(grilleFrame.end(),{-50.f,10.f*i,0.f,50.f,10.f*i,0.f});
		for(int j = 0;j<12;j++){
			grilleColor.push_back(1.0);
		}
	}
	grille.initSet(grilleFrame,grilleColor);
	grille.changeNature(GL_LINES);
}

void initFrame(){
	std::vector<float> pointsFrame{0.0,0.0,0.0,
							 50.0,0.0,0.0,
							 0.0,0.0,0.0,
							 0.0,50.0,0.0,
							 0.0,0.0,0.0,
							 0.0,0.0,50.0};

	std::vector<float> frameColors{1.0,0.0,0.0,
							 1.0,0.0,0.0,
							 0.0,1.0,0.0,
							 0.0,1.0,0.0,
							 0.0,0.0,1.0,
							 0.0,0.0,1.0};

	frame.initSet(pointsFrame,frameColors);
	frame.changeNature(GL_LINES);
}

void initConvex2dShapes(){
	{
	std::vector<float> points_cercle;
	int nb_points = 25;
	for (int i = 0; i <= nb_points; i++)
	{
		float angle = 2 * M_PI / nb_points;
		points_cercle.push_back(cos(angle * i));
		points_cercle.push_back(sin(angle * i));
		points_cercle.push_back(0);
	}
	cercle.initShape(points_cercle);
	cercle.changeNature(GL_TRIANGLE_FAN);
	}
}

void initMeshes(){
	{
	sphere = basicSphere();
	sphere->createVAO();
	}
	{
	cone = basicCone(1.f,1.f);
	cone->createVAO();
	}
	{
	cylindre = basicCylinder(1.f,1.f);
	cylindre->createVAO();
	}
	{
	cube = basicCube();
	cube->createVAO();
	}
}

void initJson(){
	std::ifstream file("../assets/RailPlacement.json");
	//std::ifstream file("../assets/AlternativeRailPlacement.json");

    if (!file) {
        std::cout << "Impossible d'ouvrir ou de trouver le fichier json"<<std::endl;
        return;
    }

	json data;
    file >> data;

	stationPlacement = data["origin"].get<std::array<int,2>>();

	railsPlacement = data["path"].get<std::vector<std::array<int,2>>>();

	vegetationPlacement = data["Vegetation"].get<std::vector<std::array<int,3>>>();
}

void initPullTexture(){
	int x,y,n;
	unsigned char * pullImage = stbi_load("../assets/textures/yellow_wool.png",& x,& y,& n,0);
	
	if(pullImage==nullptr){
		std::cerr << "Failed to open image "<<std::endl;
		exit(1);
	}

	texturePull.createTexture();
	texturePull.attachTexture();
	texturePull.setParameters(GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	texturePull.setParameters(GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	texturePull.loadImage(x,y,n,pullImage);
	texturePull.detachTexture();
	stbi_image_free(pullImage);
}

void initGrassTexture(){
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

void initTextures(){
	initGrassTexture();
	initPullTexture();
}

void initScene() {
	initFrame();
	initGrille();
	initCurved();
	initRamp();
	initSupport();
	initJson();
	initConvex2dShapes();
	initMeshes();
	initTextures();
}

void drawGround(){
	myEngine.updateMvMatrix();
	grille.drawSet();
	myEngine.activateTexturing(true);
	textureGrass.attachTexture();
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation({0.0f,0.0f,-0.1f});
	myEngine.mvMatrixStack.addHomothety({100.f,100.f,0.001f});
	myEngine.updateMvMatrix();
	cube->draw();
	myEngine.mvMatrixStack.popMatrix(); 
	textureGrass.detachTexture();
	myEngine.activateTexturing(false);
}

void drawFrame() {
	frame.drawSet();
}

void drawClosedCylinder(){
	myEngine.mvMatrixStack.pushMatrix(); // all
	myEngine.updateMvMatrix();
	cylindre->draw();
		myEngine.mvMatrixStack.addRotation(-M_PI_2,{1.0,0.0,0.0});
		myEngine.updateMvMatrix();
		cercle.drawShape();
		myEngine.mvMatrixStack.addTranslation({0.0,0.0,1.0});
		myEngine.updateMvMatrix();
		cercle.drawShape();
	myEngine.mvMatrixStack.popMatrix(); // all
}

void drawScene() {
	glPointSize(10.0);

	drawFrame();
	
	drawRails();
	drawStation();
	drawTrain();
	drawEnvironnement();
	drawGround();
	frameCount++;
}