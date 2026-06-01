#include "rails.hpp"
#include "draw_scene.hpp"
#include "train.hpp"



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
		myEngine.mvMatrixStack.addTranslation({0.f,float(i)-sr/2,2*rr+sr+0.5});
		myEngine.mvMatrixStack.addHomothety(0.5);
		myEngine.updateMvMatrix();
		drawWheel();
		myEngine.mvMatrixStack.popMatrix(); //Wheel
	}
	myEngine.mvMatrixStack.popMatrix(); // all
}

void drawTrain(){
	
	myEngine.mvMatrixStack.pushMatrix(); // all
	myEngine.setFlatColor(0.8,0.2,0.2);
	drawWheels();

	myEngine.mvMatrixStack.popMatrix(); // all
}

void temp(){
	myEngine.mvMatrixStack.addTranslation({5.f,5.f,2*rr+sr});
	myEngine.mvMatrixStack.addTranslation({0.f,0.f,2.f});
	myEngine.mvMatrixStack.addHomothety({4.f,8.f,4.f});
	myEngine.updateMvMatrix();
	cube->draw();
}