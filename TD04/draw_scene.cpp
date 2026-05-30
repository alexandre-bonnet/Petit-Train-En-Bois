#include "draw_scene.hpp"

/// Camera parameters
float angle_theta {45.0};      // Angle between x axis and viewpoint
float angle_phy {30.0};      // Angle between z axis and viewpoint
float dist_zoom {30.0};      // Distance between origin and viewpoint

GLBI_Engine myEngine;
GLBI_Set_Of_Points somePoints(3);
GLBI_Set_Of_Points frame(3);
GLBI_Convex_2D_Shape ground{3};
GLBI_Convex_2D_Shape cercle{3};

IndexedMesh* sphere;
StandardMesh* cone;

void initScene() {

	std::vector<float> points {0.0,0.0,0.0};
	somePoints.initSet(points,1.0,1.0,1.0);

	{
	std::vector<float> pointsFrame{0.0,0.0,0.0,
							 10.0,0.0,0.0,
							 0.0,0.0,0.0,
							 0.0,10.0,0.0,
							 0.0,0.0,0.0,
							 0.0,0.0,10.0};

	std::vector<float> frameColors{1.0,0.0,0.0,
							 1.0,0.0,0.0,
							 0.0,1.0,0.0,
							 0.0,1.0,0.0,
							 0.0,0.0,1.0,
							 0.0,0.0,1.0};

	frame.initSet(pointsFrame,frameColors);
	frame.changeNature(GL_LINES);
	}
	{
	std::vector<float> baseCarre{-10.0,-10.0,0.0,
								 10.0,-10.0,0.0,
								 10.0,10.0,0.0,
								 -10.0,10.0,0.0};
	ground.initShape(baseCarre);
	ground.changeNature(GL_TRIANGLE_FAN);
	}
	{
	std::vector<float> points_cercle;
	int nb_points = 10;
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
	{
	sphere = basicSphere();
	sphere->createVAO();
	}
	{
	cone = basicCone(1.f,1.f);
	cone->createVAO();
	}
}

void drawFrame() {
	frame.drawSet();
}

void drawBase() {
	myEngine.mvMatrixStack.pushMatrix(); // cercle
	myEngine.setFlatColor(1.0,1.0,1.0);
	myEngine.mvMatrixStack.addHomothety({3.0,3.0,1.0});
	myEngine.updateMvMatrix();
	cercle.drawShape();
	myEngine.mvMatrixStack.popMatrix(); // cercle
	myEngine.mvMatrixStack.pushMatrix(); // cone
	myEngine.mvMatrixStack.addRotation(M_PI/2,{1.0,0.0,0.0});
	myEngine.mvMatrixStack.addHomothety({2.0,10.0,2.0});
	myEngine.updateMvMatrix();
	cone->draw();
	myEngine.mvMatrixStack.popMatrix(); // cone
}

void drawArm() {
	myEngine.mvMatrixStack.pushMatrix(); // sphere
	myEngine.setFlatColor(0.0,1.0,1.0);
	myEngine.mvMatrixStack.addHomothety(1.6);
	myEngine.updateMvMatrix();
	sphere->draw();
	myEngine.mvMatrixStack.popMatrix(); // sphere
	for(int i = 0;i<2;i++){
		myEngine.mvMatrixStack.pushMatrix(); // cone
		myEngine.mvMatrixStack.addRotation(i*M_PI,{1.0,0.0,0.0});
		myEngine.mvMatrixStack.addHomothety({1.0,10.0,1.0});
		myEngine.updateMvMatrix();
		cone->draw();
		myEngine.mvMatrixStack.popMatrix(); // cone
	}
}

void drawPan() {
	myEngine.setFlatColor(1.0,1.0,0.0);
	std::vector<float> pointsFrame{0.0,0.0,0.0,
							 10.0,0.0,0.0,
							 0.0,0.0,0.0,
							 0.0,10.0,0.0,
							 0.0,0.0,0.0,
							 0.0,0.0,10.0};
	myEngine.mvMatrixStack.pushMatrix(); // cercle
	myEngine.mvMatrixStack.addTranslation({0.0f,0.0f,0.1f});
	myEngine.mvMatrixStack.addHomothety({6.0,6.0,1.0});
	myEngine.updateMvMatrix();
	cercle.drawShape();
	myEngine.mvMatrixStack.popMatrix(); // cercle
}

void drawScene() {
	glPointSize(10.0);

	drawFrame();

	myEngine.mvMatrixStack.pushMatrix(); // Base
	myEngine.mvMatrixStack.addTranslation({0.0f,0.0f,0.1f});
	myEngine.updateMvMatrix();
	drawBase();
	myEngine.mvMatrixStack.addTranslation({0.0f,0.0f,10.0f});
	myEngine.updateMvMatrix();
	drawArm();
	myEngine.mvMatrixStack.popMatrix(); // base
	
	myEngine.setFlatColor(0.2,0.0,0.0);
	myEngine.updateMvMatrix();
	ground.drawShape();
	
}