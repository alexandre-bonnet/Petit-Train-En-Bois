#include "rails.hpp"
#include "draw_scene.hpp"
#include "gare.hpp"

void drawStation(){
	
	myEngine.mvMatrixStack.pushMatrix(); // all
	myEngine.setFlatColor(1.0,0.0,0.0);

	myEngine.mvMatrixStack.addTranslation({10.f*stationPlacement[0],10.f*stationPlacement[1],0.f});
	myEngine.mvMatrixStack.addTranslation({5.f,10.f,3.f});
	myEngine.updateMvMatrix();

	myEngine.mvMatrixStack.pushMatrix(); // centre

	myEngine.mvMatrixStack.addHomothety({6.f,18.f,8.f});
	myEngine.updateMvMatrix();

	cube->draw();

	myEngine.mvMatrixStack.popMatrix(); // centre
	myEngine.mvMatrixStack.pushMatrix(); // Pilier 1

	myEngine.setFlatColor(1.0,0.8,0.7);

	myEngine.mvMatrixStack.addTranslation({-3.f,-9.f,0.f});
	myEngine.mvMatrixStack.addHomothety({1.f,1.f,8.f});
	myEngine.updateMvMatrix();

	cube->draw();

	myEngine.mvMatrixStack.popMatrix(); // Pilier 1
	myEngine.mvMatrixStack.pushMatrix(); // Pilier 2

	myEngine.mvMatrixStack.addTranslation({3.f,-9.f,0.f});
	myEngine.mvMatrixStack.addHomothety({1.f,1.f,8.f});
	myEngine.updateMvMatrix();

	cube->draw();

	myEngine.mvMatrixStack.popMatrix(); // Pilier 2
	myEngine.mvMatrixStack.pushMatrix(); // Pilier 3

	myEngine.mvMatrixStack.addTranslation({3.f,9.f,0.f});
	myEngine.mvMatrixStack.addHomothety({1.f,1.f,8.f});
	myEngine.updateMvMatrix();

	cube->draw();

	myEngine.mvMatrixStack.popMatrix(); // Pilier 3
	myEngine.mvMatrixStack.pushMatrix(); // Pilier 4

	myEngine.mvMatrixStack.addTranslation({-3.f,9.f,0.f});
	myEngine.mvMatrixStack.addHomothety({1.f,1.f,8.f});
	myEngine.updateMvMatrix();

	cube->draw();

	myEngine.mvMatrixStack.popMatrix(); // Pilier 4
	myEngine.mvMatrixStack.pushMatrix(); // Toit

	myEngine.setFlatColor(0.4,0.4,0.4);

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation({-1.5f,0.f,5.5f});
	myEngine.updateMvMatrix();

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addRotation(M_PI/4.f, {0.f,1.f,0.f});
	myEngine.updateMvMatrix();

	myEngine.mvMatrixStack.pushMatrix();

	myEngine.mvMatrixStack.addHomothety({0.5f,20.f,4.7f});
	myEngine.updateMvMatrix();

	cube->draw();

	myEngine.mvMatrixStack.popMatrix(); // Toit
	myEngine.mvMatrixStack.popMatrix(); // Toit
	myEngine.mvMatrixStack.popMatrix(); // Toit
	myEngine.mvMatrixStack.popMatrix(); // Toit

	myEngine.mvMatrixStack.pushMatrix(); // Toit

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation({1.5f,0.f,5.5f});
	myEngine.updateMvMatrix();

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addRotation(-M_PI/4.f, {0.f,1.f,0.f});
	myEngine.updateMvMatrix();

	myEngine.mvMatrixStack.pushMatrix();

	myEngine.mvMatrixStack.addHomothety({0.5f,20.f,4.7f});
	myEngine.updateMvMatrix();

	cube->draw();

	myEngine.mvMatrixStack.popMatrix(); // Toit
	myEngine.mvMatrixStack.popMatrix(); // Toit
	myEngine.mvMatrixStack.popMatrix(); // Toit
	myEngine.mvMatrixStack.popMatrix(); // Toit

	myEngine.mvMatrixStack.pushMatrix(); // Pilier 5

	myEngine.setFlatColor(1.0,0.8,0.7);

	myEngine.mvMatrixStack.addTranslation({16.f,3.f,0.f});
	myEngine.mvMatrixStack.addHomothety({1.f,1.f,8.f});
	myEngine.updateMvMatrix();

	cube->draw();

	myEngine.mvMatrixStack.popMatrix(); // Pilier 5
	myEngine.mvMatrixStack.pushMatrix(); // Pilier 6

	myEngine.mvMatrixStack.addTranslation({16.f,-3.f,0.f});
	myEngine.mvMatrixStack.addHomothety({1.f,1.f,8.f});
	myEngine.updateMvMatrix();

	cube->draw();

	myEngine.mvMatrixStack.popMatrix(); // Pilier 6

	myEngine.mvMatrixStack.popMatrix(); // all
}