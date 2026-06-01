#include "rails.hpp"
#include "draw_scene.hpp"
#include "train.hpp"

GLBI_Convex_2D_Shape carre{3};
GLBI_Convex_2D_Shape triangle{3};
GLBI_Convex_2D_Shape rampe{3};



void drawWheel(){
	myEngine.mvMatrixStack.pushMatrix(); // all
	myEngine.setFlatColor(0.8,0.2,0.2);
	myEngine.updateMvMatrix();
	drawClosedCylinder();
	myEngine.setFlatColor(0.7,0.7,0.7);	
	myEngine.mvMatrixStack.addTranslation({0.f,-0.2f,0.f});
	myEngine.mvMatrixStack.addHomothety({0.5f,1.4f,0.5f});	
	myEngine.updateMvMatrix();
	drawClosedCylinder();
	myEngine.mvMatrixStack.popMatrix(); // all
}

void drawWheels(){
	myEngine.mvMatrixStack.pushMatrix(); // all
	myEngine.mvMatrixStack.addRotation(-M_PI_2,{0.0,0.0,1.0});
	for(int i = 3;i<8; i+=4){
		myEngine.mvMatrixStack.pushMatrix(); //Wheel
		myEngine.mvMatrixStack.addTranslation({-1.f,float(i)-sr/2,0.5});
		myEngine.mvMatrixStack.addHomothety(0.5);
		myEngine.updateMvMatrix();
		drawWheel();
		myEngine.mvMatrixStack.addTranslation({-4.f,0.f,0.f});
		myEngine.updateMvMatrix();
		drawWheel();
		myEngine.mvMatrixStack.addTranslation({-8.f,0.f,0.f});
		myEngine.updateMvMatrix();
		drawWheel();
		myEngine.mvMatrixStack.popMatrix(); //Wheel
	}
	myEngine.mvMatrixStack.popMatrix(); // all
}

void initRamp(){
	{
	std::vector<float> carreTab{-0.5,-0.5,-0.5,
								 0.5,-0.5,-0.5,
								 0.5,0.5,-0.5,
								 -0.5,0.5,-0.5};
	carre.initShape(carreTab);
	carre.changeNature(GL_TRIANGLE_FAN);
	}
	{
	std::vector<float> triangleTab{-0.5,-0.5,-0.5,
								 -0.5,0.5,-0.5,
								 -0.5,-0.5,0.5};
	triangle.initShape(triangleTab);
	triangle.changeNature(GL_TRIANGLE_STRIP);
	}
	{
	std::vector<float> rampeTab{ -0.5,0.5,-0.5,
								 -0.5,-0.5,0.5,
								 0.5,0.5,-0.5,
								 0.5,-0.5,0.5};
	rampe.initShape(rampeTab);
	rampe.changeNature(GL_TRIANGLE_STRIP);
	}
}

void drawRamp(){
	myEngine.mvMatrixStack.pushMatrix(); // all
	myEngine.updateMvMatrix();
	carre.drawShape();
	triangle.drawShape();
	rampe.drawShape();
	myEngine.mvMatrixStack.pushMatrix(); // carreFond
	myEngine.mvMatrixStack.addTranslation({0.5f,0.f,0.f});
	myEngine.mvMatrixStack.addRotation(-M_PI_2,{1.0,0.0,0.0});
	myEngine.mvMatrixStack.addTranslation({-0.5f,0.f,0.f});
	myEngine.updateMvMatrix();
	carre.drawShape();
	myEngine.mvMatrixStack.popMatrix(); // carreFond
	myEngine.mvMatrixStack.pushMatrix(); // triangleFond
	myEngine.mvMatrixStack.addTranslation({1.f,0.f,0.f});
	myEngine.updateMvMatrix();
	triangle.drawShape();
	myEngine.mvMatrixStack.popMatrix(); // triangleFond
	myEngine.mvMatrixStack.popMatrix(); // all
}

void drawTrain(){
	
	myEngine.mvMatrixStack.pushMatrix(); // all
	myEngine.mvMatrixStack.addTranslation({0.f,0.f,2*rr+sr});
	drawWheels();
	myEngine.mvMatrixStack.pushMatrix(); // base
	myEngine.mvMatrixStack.addTranslation({5.f,4.f,1.f});
	//myEngine.mvMatrixStack.addTranslation({0.f,0.f,2.f});
	myEngine.mvMatrixStack.addHomothety({3.5f,7.f,1.f});
	myEngine.setFlatColor(0.8,0.8,0.8);
	myEngine.updateMvMatrix();
	cube->draw();
	myEngine.mvMatrixStack.popMatrix(); // base
	myEngine.mvMatrixStack.pushMatrix(); // rampe
	myEngine.mvMatrixStack.addTranslation({5.f,8.f,1.f});
	myEngine.mvMatrixStack.addHomothety({3.5f,1.f,1.f});
	myEngine.updateMvMatrix();
	drawRamp();
	myEngine.mvMatrixStack.popMatrix(); // rampe
	myEngine.mvMatrixStack.popMatrix(); // all
}

void temp(){
	myEngine.mvMatrixStack.addTranslation({5.f,5.f,2*rr+sr});
	myEngine.mvMatrixStack.addTranslation({0.f,0.f,2.f});
	myEngine.mvMatrixStack.addHomothety({4.f,8.f,4.f});
	myEngine.updateMvMatrix();
	cube->draw();
}