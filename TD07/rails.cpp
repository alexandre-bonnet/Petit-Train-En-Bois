#include "rails.hpp"
#include "draw_scene.hpp"


void drawStraightRail() {
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