#include "draw_scene.hpp"
#include "rails.hpp"

/// Camera parameters
float angle_theta {45.0};      // Angle between x axis and viewpoint
float angle_phy {30.0};      // Angle between z axis and viewpoint
float dist_zoom {15.0};      // Distance between origin and viewpoint

GLBI_Engine myEngine;

GLBI_Set_Of_Points frame(3);
GLBI_Set_Of_Points grille(3);
GLBI_Convex_2D_Shape ground{3};
GLBI_Convex_2D_Shape cercle{3};

IndexedMesh* sphere;
IndexedMesh* cylindre;
IndexedMesh* cube;
StandardMesh* cone;

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
	std::vector<float> baseCarre{-50.0,-50.0,0.0,
								 50.0,-50.0,0.0,
								 50.0,50.0,0.0,
								 -50.0,50.0,0.0};
	ground.initShape(baseCarre);
	ground.changeNature(GL_TRIANGLE_FAN);
	}
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

void initScene() {
	initFrame();
	initGrille();
	initCurved();
	initJson();
	initConvex2dShapes();
	initMeshes();
}

void drawGround(){
	myEngine.updateMvMatrix();
	grille.drawSet();
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation({0.0f,0.0f,-0.1f});
	myEngine.updateMvMatrix();
	myEngine.setFlatColor(0.2,0.5,0.2);
	ground.changeNature(GL_TRIANGLE_FAN);
	ground.drawShape();
	myEngine.mvMatrixStack.popMatrix(); 
}

void drawFrame() {
	frame.drawSet();
}

void drawScene() {
	glPointSize(10.0);

	drawFrame();
	drawRails();
	drawGround();
}