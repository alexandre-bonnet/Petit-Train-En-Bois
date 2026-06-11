#include "rails.hpp"
#include "draw_scene.hpp"
#include "gare.hpp"

void drawPillar(float x, float y) {
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.setFlatColor(1.0, 0.8, 0.7);
	myEngine.mvMatrixStack.addTranslation({x, y, 0.f});
	myEngine.mvMatrixStack.addHomothety({1.f, 1.f, 8.f});
	myEngine.updateMvMatrix();
	cube->draw();
	myEngine.mvMatrixStack.popMatrix();
}

void drawRoofPart(float x, float rotation) {
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.setFlatColor(0.4, 0.4, 0.4);
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation({x, 0.f, 0.f});
	myEngine.updateMvMatrix();
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addRotation(rotation, {0.f, 1.f, 0.f});
	myEngine.updateMvMatrix();
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addHomothety({0.5f, 20.f, 4.7f});
	myEngine.updateMvMatrix();
	cube->draw();
	myEngine.mvMatrixStack.popMatrix();
	myEngine.mvMatrixStack.popMatrix();
	myEngine.mvMatrixStack.popMatrix();
	myEngine.mvMatrixStack.popMatrix();
}

void drawRoof() {
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation({0.f, 0.f, 5.5f});
	drawRoofPart(-1.5f, M_PI / 4.f);
	drawRoofPart(1.5f, -M_PI / 4.f);
	myEngine.mvMatrixStack.popMatrix();
}

void drawRoofClosures() {
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.setFlatColor(0.4, 0.4, 0.4);
	myEngine.mvMatrixStack.addTranslation({0.f, 0.f, 4.f});
	myEngine.mvMatrixStack.addRotation(M_PI / 4.f, {0.f, 1.f, 0.f});
	myEngine.updateMvMatrix();
	
	for(int i = 0; i < 2; i++) {
		myEngine.mvMatrixStack.pushMatrix();
		myEngine.mvMatrixStack.addTranslation({0.f, (8.4f * (1 - 2*i)), 0.f});
		myEngine.mvMatrixStack.addHomothety({4.5f, 1.f, 4.5f});
		myEngine.updateMvMatrix();
		cube->draw();
		myEngine.mvMatrixStack.popMatrix();
	}
	myEngine.mvMatrixStack.popMatrix();
}

void drawLiaisionRoofPart(float y, float rotation) {
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.setFlatColor(0.4, 0.4, 0.4);
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation({0.f, y, 0.f});
	myEngine.updateMvMatrix();
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addRotation(rotation, {1.f, 0.f, 0.f});
	myEngine.updateMvMatrix();
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addHomothety({16.f, 0.5f, 3.8f});
	myEngine.updateMvMatrix();
	cube->draw();
	myEngine.mvMatrixStack.popMatrix();
	myEngine.mvMatrixStack.popMatrix();
	myEngine.mvMatrixStack.popMatrix();
	myEngine.mvMatrixStack.popMatrix();
}

void drawLiaisionRoof() {
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation({9.f, 0.f, 5.f});
	myEngine.updateMvMatrix();
	
	drawLiaisionRoofPart(-1.5f, -M_PI / 3.f);
	drawLiaisionRoofPart(1.5f, M_PI / 3.f);
	
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation({0.f, 0.f, -1.f});
	myEngine.mvMatrixStack.addHomothety({16.f, 6.f, 0.3f});
	myEngine.updateMvMatrix();
	cube->draw();
	myEngine.mvMatrixStack.popMatrix();
	
	myEngine.mvMatrixStack.popMatrix();
}

void drawClock() {
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.setFlatColor(1.0, 1.0, 0.0);
	myEngine.mvMatrixStack.addTranslation({1.6f, 0.f, 1.f});
	myEngine.mvMatrixStack.addRotation(M_PI / 2.f, {0.f, 0.f, 1.f});
	
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation({0.f, 0.1f, 0.f});
	myEngine.mvMatrixStack.addHomothety({1.f, 0.1f, 1.f});
	myEngine.updateMvMatrix();
	sphere->draw();
	myEngine.mvMatrixStack.popMatrix();
	
	myEngine.setFlatColor(0.0, 0.0, 0.0);
	
	for(int i = 0; i < 2; i++) {
		myEngine.mvMatrixStack.pushMatrix();
		float angle = (i == 0) ? (M_PI / 4.f) : (-M_PI / 3.f);
		float z = (i == 0) ? (0.45f) : (0.25f);
		float scale = (i == 0) ? (0.9f) : (0.5f);
		myEngine.mvMatrixStack.addRotation(angle, {0.f, 1.f, 0.f});
		myEngine.mvMatrixStack.addTranslation({0.f, 0.f, z});
		myEngine.mvMatrixStack.addHomothety({0.1f, 0.1f, scale});
		myEngine.updateMvMatrix();
		cube->draw();
		myEngine.mvMatrixStack.popMatrix();
	}
	
	myEngine.mvMatrixStack.popMatrix();
}

void drawStone(float angle, float radius, bool noRotation) {
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation({0.f, radius * std::cos(angle), 1.25f + radius * std::sin(angle)});
	if(!noRotation) {
		myEngine.mvMatrixStack.addRotation(angle + M_PI / 2.f, {1.f, 0.f, 0.f});
	} else {
		myEngine.mvMatrixStack.addRotation(M_PI / 2.f, {1.f, 0.f, 0.f});
	}
	myEngine.mvMatrixStack.addHomothety({0.4f, 0.8f, 0.4f});
	myEngine.updateMvMatrix();
	cube->draw();
	myEngine.mvMatrixStack.popMatrix();
}

void drawWindowStones() {
	myEngine.setFlatColor(0.4, 0.4, 0.4);
	for(int i = 0; i < 7; i++) {
		float angle = (M_PI / 5.f) * i - M_PI / 10.f;
		float radius = 1.5f;
		drawStone(angle, radius, i==0 || i==6);
	}
}

void drawWindow(float y) {
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation({0.f, y, 0.f});
	myEngine.updateMvMatrix();
	
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.setFlatColor(0.4, 0.4, 1.0);
	myEngine.mvMatrixStack.addHomothety({0.1f, 2.5f, 2.5f});
	myEngine.updateMvMatrix();
	cube->draw();
	myEngine.mvMatrixStack.popMatrix();
	
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation({0.f, 0.f, 1.25f});
	myEngine.mvMatrixStack.addHomothety({0.1f, 1.25f, 1.25f});
	myEngine.updateMvMatrix();
	sphere->draw();
	myEngine.mvMatrixStack.popMatrix();
	
	drawWindowStones();
	
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.setFlatColor(0.4, 0.4, 0.4);
	myEngine.mvMatrixStack.addTranslation({0.f, 0.f, -1.25f});
	myEngine.mvMatrixStack.addHomothety({1.f, 2.5f, 0.5f});
	myEngine.updateMvMatrix();
	cube->draw();
	myEngine.mvMatrixStack.popMatrix();
	
	myEngine.mvMatrixStack.popMatrix();
}

void drawFacade() {
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation({3.f, 0.f, 0.f});
	myEngine.updateMvMatrix();
	
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.setFlatColor(0.4, 0.4, 1.0);
	myEngine.mvMatrixStack.addTranslation({0.f, 0.f, -1.f});
	myEngine.mvMatrixStack.addHomothety({0.1f, 3.5f, 5.f});
	myEngine.updateMvMatrix();
	cube->draw();
	myEngine.mvMatrixStack.popMatrix();
	
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation({0.f, 0.f, 1.5f});
	myEngine.mvMatrixStack.addHomothety({0.1f, 1.75f, 1.75f});
	myEngine.updateMvMatrix();
	sphere->draw();
	myEngine.mvMatrixStack.popMatrix();
	
	drawWindow(5.5f);
	drawWindow(-5.5f);
	
	myEngine.mvMatrixStack.popMatrix();
}

void drawStation(){
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.setFlatColor(1.0, 0.0, 0.0);

	myEngine.mvMatrixStack.addTranslation({10.f*stationPlacement[0], 10.f*stationPlacement[1], 0.f});
	myEngine.mvMatrixStack.addTranslation({5.f, 10.f, 3.f});
	myEngine.updateMvMatrix();

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addHomothety({6.f, 18.f, 8.f});
	myEngine.updateMvMatrix();
	cube->draw();
	myEngine.mvMatrixStack.popMatrix();

	drawPillar(-3.f, -9.f);
	drawPillar(3.f, -9.f);
	drawPillar(3.f, 9.f);
	drawPillar(-3.f, 9.f);

	drawRoof();
	drawRoofClosures();

	drawPillar(16.f, 2.5f);
	drawPillar(16.f, -2.5f);

	drawLiaisionRoof();

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.setFlatColor(0., 1., 0.);
	myEngine.mvMatrixStack.addTranslation({0.f, 0.f, 7.f});
	myEngine.updateMvMatrix();

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addHomothety({3.f, 3.f, 5.f});
	myEngine.updateMvMatrix();
	cube->draw();
	myEngine.mvMatrixStack.popMatrix();

	drawClock();

	myEngine.mvMatrixStack.popMatrix();

	drawFacade();

	myEngine.mvMatrixStack.popMatrix();
}