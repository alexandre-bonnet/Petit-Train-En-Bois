#include "arbres.hpp"
#include "draw_scene.hpp"

void drawBushySphere(){
	myEngine.mvMatrixStack.pushMatrix(); // all
	sphere->draw();
	int num = 7;
	for(int i{0};i<num;i++){
		for(int j{0};j<num;j++){
			myEngine.mvMatrixStack.pushMatrix(); // circle
			myEngine.mvMatrixStack.addRotation(i*M_PI*2/num,{0.0,0.0,1.0});
			myEngine.mvMatrixStack.addRotation(j*M_PI*2/num,{0.0,1.0,0.0});
			myEngine.mvMatrixStack.addTranslation({1.f,0.f,0.f});
			myEngine.mvMatrixStack.addHomothety(0.5f);
			myEngine.updateMvMatrix();
			sphere->draw();
			myEngine.mvMatrixStack.popMatrix(); // circle
		}
	}
	myEngine.mvMatrixStack.popMatrix(); // all
}

void drawBush(){
	myEngine.mvMatrixStack.pushMatrix(); // all
	myEngine.setFlatColor(0.1,0.3,0.1);
	for(int i{0};i<3;i++){
		myEngine.mvMatrixStack.pushMatrix(); // circle
		myEngine.mvMatrixStack.addRotation(i*M_PI*2/3,{0.0,0.0,1.0});
		myEngine.mvMatrixStack.addTranslation({2.f,0.f,0.f});
		myEngine.mvMatrixStack.addHomothety(2);
		myEngine.updateMvMatrix();
		drawBushySphere();
		myEngine.mvMatrixStack.popMatrix(); // circle
	}
	myEngine.mvMatrixStack.addTranslation({0.f,0.f,2.f});
	myEngine.mvMatrixStack.addHomothety(2);
	myEngine.updateMvMatrix();
	drawBushySphere();
	myEngine.mvMatrixStack.popMatrix(); // all
}

void drawTree(){
	myEngine.mvMatrixStack.pushMatrix(); // all
	myEngine.setFlatColor(0.2,0.2,0.1);
	myEngine.mvMatrixStack.pushMatrix(); // basetrunk
	myEngine.mvMatrixStack.addRotation(M_PI_2,{1.0,0.0,0.0});
	myEngine.mvMatrixStack.addHomothety({1.5f,2.f,1.5f});
	myEngine.updateMvMatrix();
	cone->draw();
	myEngine.mvMatrixStack.popMatrix(); // basetrunk
	myEngine.mvMatrixStack.pushMatrix(); // trunk
	myEngine.mvMatrixStack.addRotation(M_PI_2,{1.0,0.0,0.0});
	myEngine.mvMatrixStack.addHomothety({1.f,10.f,1.f});
	myEngine.updateMvMatrix();
	drawClosedCylinder();
	myEngine.mvMatrixStack.popMatrix(); // trunk
	myEngine.mvMatrixStack.addTranslation({0.f,0.f,10.f});
	drawBush();
	myEngine.mvMatrixStack.popMatrix(); // all
}

void drawBosquet(){
	myEngine.mvMatrixStack.pushMatrix(); // all
	myEngine.setFlatColor(0.2,0.2,0.1);
	myEngine.mvMatrixStack.pushMatrix(); // tree1
	myEngine.mvMatrixStack.addTranslation({3.f,2.f,0.f});
	myEngine.mvMatrixStack.addRotation(M_PI_2,{0.0,0.0,1.0});
	myEngine.mvMatrixStack.addHomothety({0.7});
	myEngine.updateMvMatrix();
	drawTree();
	myEngine.mvMatrixStack.popMatrix(); // tree1
	myEngine.mvMatrixStack.pushMatrix(); // tree2
	myEngine.mvMatrixStack.addTranslation({-1.f,-1.f,0.f});
	myEngine.updateMvMatrix();
	drawTree();
	myEngine.mvMatrixStack.popMatrix(); // tree2
	myEngine.mvMatrixStack.pushMatrix(); // tree1
	myEngine.mvMatrixStack.addTranslation({-2.f,2.f,0.f});
	myEngine.mvMatrixStack.addRotation(M_PI_2,{0.0,0.0,1.0});
	myEngine.mvMatrixStack.addHomothety({0.3});
	myEngine.updateMvMatrix();
	drawTree();
	myEngine.mvMatrixStack.addTranslation({0.f,-2.f,0.f});
	drawBush();
	myEngine.mvMatrixStack.popMatrix(); // tree1
	myEngine.mvMatrixStack.addTranslation({2.f,-3.f,0.f});
	myEngine.mvMatrixStack.addHomothety({0.5});
	drawBush();
	myEngine.mvMatrixStack.popMatrix(); // all
}
void drawEnvironnement(){
	myEngine.mvMatrixStack.pushMatrix(); // all
	for(std::array<int,3> arbre : vegetationPlacement){
		myEngine.mvMatrixStack.pushMatrix(); // tree
		myEngine.mvMatrixStack.addTranslation({float(arbre[0])*10+5,float(arbre[1])*10+5,0.f});
		switch(arbre[2]) {
			case 0 :
				drawBush();
				break;
			case 1 :
				drawTree();
				break;
			case 2 :
				drawBosquet();
				break;
		}
		myEngine.mvMatrixStack.popMatrix(); // tree
	}
	myEngine.mvMatrixStack.popMatrix(); // all
}