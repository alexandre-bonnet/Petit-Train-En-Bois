#include "rails.hpp"
#include "draw_scene.hpp"
#include "train.hpp"



void drawTrain(){
	
	myEngine.mvMatrixStack.pushMatrix(); // all
	myEngine.setFlatColor(0.8,0.2,0.2);

	myEngine.mvMatrixStack.addTranslation({5.f,5.f,2*rr+sr});
	myEngine.mvMatrixStack.addTranslation({0.f,0.f,2.f});
	myEngine.mvMatrixStack.addHomothety({4.f,8.f,4.f});
	myEngine.updateMvMatrix();
	cube->draw();
	myEngine.mvMatrixStack.popMatrix(); // all
}