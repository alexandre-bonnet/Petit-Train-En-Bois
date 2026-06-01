#include "rails.hpp"
#include "draw_scene.hpp"
#include "gare.hpp"



void drawStation(){
	
	myEngine.mvMatrixStack.pushMatrix(); // all
	myEngine.setFlatColor(0.4,0.4,0.4);

	myEngine.mvMatrixStack.addTranslation({10.f*stationPlacement[0],10.f*stationPlacement[1],0.f});
	myEngine.mvMatrixStack.addTranslation({5.f,5.f,3.f});
	myEngine.mvMatrixStack.addHomothety(6.0);
	myEngine.updateMvMatrix();
	cube->draw();
	myEngine.mvMatrixStack.popMatrix(); // all
}