#include "rails.hpp"
#include "draw_scene.hpp"

float sr = 0.5f;
float rr = 0.2f;
float sx = 1-rr;

void drawStraightRail() {
	
	myEngine.mvMatrixStack.pushMatrix(); // all
	//CUBE placed at origin to help orientation
	myEngine.setFlatColor(0.0,0.0,0.0);
	myEngine.updateMvMatrix();
	cube->draw();
	myEngine.setFlatColor(0.7,0.7,0.7);
	
	for(int i = 3; i <8;i+=4){
		myEngine.mvMatrixStack.pushMatrix(); // rails
		//myEngine.mvMatrixStack.addTranslation({0.0,5.0,0.0});
		myEngine.mvMatrixStack.addTranslation({float(i),5.0,2*rr+sr/2});
		myEngine.mvMatrixStack.addHomothety({sr,10.0,sr});
		myEngine.updateMvMatrix();
		cube->draw();
		myEngine.mvMatrixStack.popMatrix(); // rails
	}

	myEngine.setFlatColor(0.7,0.4,0.2);
	for(float i = sx;i<10.f-sx;i+=2*sx+2*rr){
		myEngine.mvMatrixStack.pushMatrix(); // balast
			myEngine.mvMatrixStack.addTranslation({2.0,i,rr/2});
			myEngine.mvMatrixStack.addRotation(-M_PI_2,{0.0,0.0,1.0});
			myEngine.mvMatrixStack.pushMatrix(); // cylindre
				myEngine.mvMatrixStack.addHomothety({rr,6.0,rr});
				myEngine.updateMvMatrix();
				cylindre->draw();
			myEngine.mvMatrixStack.popMatrix(); // cylindre
			myEngine.mvMatrixStack.pushMatrix(); // cerlcles
				myEngine.mvMatrixStack.addRotation(-M_PI_2,{1.0,0.0,0.0});
				myEngine.mvMatrixStack.pushMatrix(); // cerlcle1
					myEngine.mvMatrixStack.addHomothety({rr,rr,1.0});
					myEngine.updateMvMatrix();
					cercle.drawShape();
				myEngine.mvMatrixStack.popMatrix(); // cercle1
				myEngine.mvMatrixStack.addTranslation({0.0,0.0,6.0});
				myEngine.mvMatrixStack.addHomothety({rr,rr,1.0});
				myEngine.updateMvMatrix();
				cercle.drawShape();
			myEngine.mvMatrixStack.popMatrix(); // cerlcles
		myEngine.mvMatrixStack.popMatrix(); // balast
	}
	myEngine.mvMatrixStack.popMatrix(); // all
}

void temp(){
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