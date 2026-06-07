#include "rails.hpp"
#include "draw_scene.hpp"
#include "train.hpp"

GLBI_Convex_2D_Shape carre{3};
GLBI_Convex_2D_Shape triangle{3};
GLBI_Convex_2D_Shape rampe{3};

GLBI_Convex_2D_Shape supportBottom{3};
GLBI_Convex_2D_Shape supportSide{3};



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
		myEngine.mvMatrixStack.addTranslation({-1.f,float(i)-0.25f,0.5f});
		myEngine.mvMatrixStack.addHomothety(0.5);
		for(int i = 0; i<9;i+=4){
			myEngine.mvMatrixStack.addTranslation({-float(i),0.f,0.f});
			myEngine.updateMvMatrix();
			drawWheel();
		}
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

void initSupport(){
	int num = 7;
	std::vector<float> supportBottomVector{};
	std::vector<float> supportSideVector{};
	//supportSideVector.insert(supportSideVector.end(),{0.f,-0.5f,1.f,0.f,0.5f,1.f});
	for(int i = 0; i<=num;i++){
		float angle = i*M_PI/num-M_PI_2;
		supportBottomVector.insert(supportBottomVector.end(),{-0.5f,0.5f*float(sin(angle)),0.4f*float(cos(angle))});
		supportBottomVector.insert(supportBottomVector.end(),{0.5f,0.5f*float(sin(angle)),0.4f*float(cos(angle))});

		supportSideVector.insert(supportSideVector.end(),{0.f,0.5f*float(sin(angle)),0.4f*float(cos(angle))});
		supportSideVector.insert(supportSideVector.end(),{0.f,0.5f*float(sin(angle)),0.5f});
	}
	supportBottom.initShape(supportBottomVector);
	supportBottom.changeNature(GL_TRIANGLE_STRIP);

	supportSide.initShape(supportSideVector);
	supportSide.changeNature(GL_TRIANGLE_STRIP);

}

void drawSupport(){
	myEngine.mvMatrixStack.pushMatrix(); // all
	myEngine.mvMatrixStack.addRotation(M_PI_2,{0.0,0.0,1.0});
	myEngine.updateMvMatrix();
	supportBottom.drawShape();
	for(int i{-1};i<2;i+=2){
		myEngine.mvMatrixStack.pushMatrix(); // side
		myEngine.mvMatrixStack.addTranslation({0.5f*i,0.f,0.f});
		myEngine.updateMvMatrix();
		supportSide.drawShape();
		myEngine.mvMatrixStack.popMatrix(); // side
	}
	myEngine.mvMatrixStack.pushMatrix(); // top
	myEngine.mvMatrixStack.addTranslation({0.f,0.f,1.f});
	myEngine.updateMvMatrix();
	carre.drawShape();
	myEngine.mvMatrixStack.popMatrix(); // top

	for(int i{0};i<2;i++){
		myEngine.mvMatrixStack.pushMatrix(); // LastSides
		myEngine.mvMatrixStack.addRotation(-M_PI_2,{1.0,0.0,0.0});
		myEngine.mvMatrixStack.addTranslation({0.f,-0.25f,float(i)});
		myEngine.mvMatrixStack.addHomothety({1.f,0.5f,1.f});
		myEngine.updateMvMatrix();
		carre.drawShape();
		myEngine.mvMatrixStack.popMatrix(); // LastSides
	}

	myEngine.mvMatrixStack.popMatrix(); // all
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

void drawGrate(){
	myEngine.setFlatColor(0.373, 0.008, 0.122);
	for(int i{-1};i<2;i+=2){
		myEngine.mvMatrixStack.pushMatrix(); // top/bottom
		myEngine.mvMatrixStack.addTranslation({0.f,0.f,float(i)*0.2f});
		myEngine.mvMatrixStack.addHomothety({2.f,0.1f,0.1f});
		myEngine.updateMvMatrix();
		cube->draw();
		myEngine.mvMatrixStack.popMatrix(); // top/bottom
	}
	for(int i{-4};i<5;i++){
		myEngine.mvMatrixStack.pushMatrix(); // straight
		myEngine.mvMatrixStack.addTranslation({float(i)*0.25f,0.f,0.f});
		myEngine.mvMatrixStack.addHomothety({0.1f,0.1f,0.5f});
		myEngine.updateMvMatrix();
		cube->draw();
		myEngine.mvMatrixStack.popMatrix(); // straight
	}
}

void drawCabin(){
	myEngine.mvMatrixStack.pushMatrix(); // all
	myEngine.mvMatrixStack.addTranslation({5.f,2.25f,2.f});
	myEngine.setFlatColor(0.639, 0.149, 0.216);
	for(int i{1};i<4;i++){
		myEngine.mvMatrixStack.pushMatrix(); // bordure
		myEngine.mvMatrixStack.addRotation(M_PI_2*i,{0.0,0.0,1.0});
		myEngine.mvMatrixStack.addTranslation({0.f,1.5f,0.f});
		myEngine.mvMatrixStack.addHomothety({3.5f,0.5f,1.f});
		myEngine.updateMvMatrix();
		cube->draw();
		myEngine.mvMatrixStack.popMatrix(); // bordure
	}
	myEngine.mvMatrixStack.addTranslation({0.f,0.f,1.f});
	for(int i{-1};i<2;i+=2){
		for(int j{-1};j<2;j+=2){
		myEngine.mvMatrixStack.pushMatrix(); // poteau
		myEngine.mvMatrixStack.addTranslation({1.5f*i,1.5f*j,0.25f});
		myEngine.mvMatrixStack.addHomothety({0.5f,0.5f,3.5f});
		myEngine.updateMvMatrix();
		cube->draw();
		myEngine.mvMatrixStack.popMatrix(); // poteau
		}
	}
	for(int i{0};i<4;i++){
		myEngine.mvMatrixStack.pushMatrix(); // supports
		myEngine.mvMatrixStack.addRotation(M_PI_2*i,{0.0,0.0,1.0});
		myEngine.mvMatrixStack.addTranslation({0.f,1.5f,1.f});
		myEngine.mvMatrixStack.addHomothety({2.5f,0.5f,2.f});
		myEngine.updateMvMatrix();
		drawSupport();
		myEngine.mvMatrixStack.popMatrix(); // supports
	}
	myEngine.mvMatrixStack.addTranslation({0.f,0.f,2.25f});
	myEngine.mvMatrixStack.addHomothety({4.f,4.f,0.5f});
	myEngine.setFlatColor(0.373, 0.008, 0.122);
	myEngine.updateMvMatrix();
	cube->draw();
	myEngine.mvMatrixStack.popMatrix(); // all
}

void drawPerso(){
	myEngine.mvMatrixStack.pushMatrix(); // all
	for(int i{-1};i<2;i+=2){
		myEngine.mvMatrixStack.pushMatrix(); // Bottom
		myEngine.mvMatrixStack.addTranslation({0.f,0.5f*i,0.f});
		myEngine.mvMatrixStack.pushMatrix(); // foot
		myEngine.setFlatColor(0.f,0.f,0.f);
		myEngine.mvMatrixStack.addHomothety(0.5);
		myEngine.updateMvMatrix();
		sphere->draw();
		myEngine.mvMatrixStack.popMatrix(); // foot
		myEngine.mvMatrixStack.pushMatrix(); // leg
		myEngine.setFlatColor(0.2f,0.2f,0.8f);
		myEngine.mvMatrixStack.addTranslation({0.f,0.f,1.f});
		myEngine.mvMatrixStack.addRotation(-M_PI_2,{1.0,0.0,0.0});
		myEngine.mvMatrixStack.addHomothety({0.25,1.0,0.25});
		myEngine.updateMvMatrix();
		drawClosedCylinder();
		myEngine.mvMatrixStack.popMatrix(); // leg
		myEngine.mvMatrixStack.popMatrix(); // Bottom
	}
	myEngine.activateTexturing(true);
	texturePull.attachTexture();
	myEngine.mvMatrixStack.pushMatrix(); // body
	myEngine.setFlatColor(0.7f,0.f,0.2f);
	myEngine.mvMatrixStack.addTranslation({0.f,0.f,1.5f});
	myEngine.mvMatrixStack.addHomothety({0.5,1,1});
	myEngine.updateMvMatrix();
	sphere->draw();
	myEngine.mvMatrixStack.popMatrix(); // body

	myEngine.mvMatrixStack.pushMatrix(); // arm1
	myEngine.mvMatrixStack.addTranslation({0.f,-1.f,1.5f});
	myEngine.mvMatrixStack.addRotation(-0.2,{1.0,0.0,0.0});
	myEngine.mvMatrixStack.addHomothety({0.25,1,0.25});
	myEngine.updateMvMatrix();
	sphere->draw();
	myEngine.mvMatrixStack.popMatrix(); // arm1

	myEngine.mvMatrixStack.pushMatrix(); // arm2
	myEngine.mvMatrixStack.addTranslation({0.f,0.75f,1.5f});
	myEngine.mvMatrixStack.addRotation(0.3*sin(float(frameCount)/3.f)+0.3,{1.0,0.0,0.0});
	myEngine.mvMatrixStack.addHomothety({0.25,1,0.25});
	myEngine.updateMvMatrix();
	sphere->draw();
	myEngine.mvMatrixStack.popMatrix(); // arm2
	texturePull.detachTexture();
	myEngine.activateTexturing(false);

	myEngine.mvMatrixStack.pushMatrix(); // head
	myEngine.setFlatColor(0.7f,0.5f,0.2f);
	myEngine.mvMatrixStack.addTranslation({0.f,0.f,3.f});
	myEngine.updateMvMatrix();
	sphere->draw();
	for(int i{-1};i<2;i+=2){
		myEngine.mvMatrixStack.pushMatrix(); // eye
		myEngine.mvMatrixStack.addRotation(-0.2,{0.0,1.0,0.0});
		myEngine.setFlatColor(1.f,1.f,1.f);
		myEngine.mvMatrixStack.addRotation(0.4*i,{0.0,0.0,1.0});
		myEngine.mvMatrixStack.addTranslation({0.8f,0.f,0.f});
		myEngine.mvMatrixStack.addHomothety(0.25);
		myEngine.updateMvMatrix();
		sphere->draw();
		myEngine.setFlatColor(0.f,0.f,0.f);
		myEngine.mvMatrixStack.addTranslation({0.8f,0.f,0.f});
		myEngine.mvMatrixStack.addHomothety(0.5);
		myEngine.updateMvMatrix();
		sphere->draw();
		myEngine.mvMatrixStack.popMatrix(); // eye
	}
	myEngine.mvMatrixStack.pushMatrix(); // Hat
	myEngine.setFlatColor(0.f,0.f,0.f);
	myEngine.mvMatrixStack.addTranslation({0.f,0.f,0.75f});
	myEngine.mvMatrixStack.pushMatrix(); // rim
	myEngine.mvMatrixStack.addHomothety({1.2f,1.2f,1.0f});
	myEngine.updateMvMatrix();
	cercle.drawShape();
	myEngine.mvMatrixStack.popMatrix(); // rim
	myEngine.mvMatrixStack.addHomothety({0.75f,0.75f,1.0f});
	myEngine.mvMatrixStack.addRotation(M_PI_2,{1.0,0.0,0.0});
	myEngine.updateMvMatrix();
	drawClosedCylinder();
	myEngine.mvMatrixStack.popMatrix(); // Hat
	myEngine.mvMatrixStack.popMatrix(); // head

	myEngine.mvMatrixStack.pushMatrix(); // Pelle
	myEngine.setFlatColor(0.5f,0.5f,0.5f);
	myEngine.mvMatrixStack.addTranslation({0.f,-1.6f,-0.5f});
	myEngine.mvMatrixStack.pushMatrix(); // Manche
	myEngine.mvMatrixStack.addHomothety({0.1f,0.1f,3.0f});
	myEngine.mvMatrixStack.addRotation(M_PI_2,{1.0,0.0,0.0});
	myEngine.updateMvMatrix();
	drawClosedCylinder();
	myEngine.mvMatrixStack.popMatrix(); // Manche
	
	myEngine.mvMatrixStack.addTranslation({-0.5f,0.f,3.5f});
	myEngine.mvMatrixStack.addRotation(-M_PI_2,{0.0,1.0,0.0});

	myEngine.updateMvMatrix();
	carre.drawShape();
	myEngine.mvMatrixStack.addTranslation({0.5f,0.f,-0.5f});
	myEngine.mvMatrixStack.addHomothety({0.5,0.5,1});
	myEngine.updateMvMatrix();
	cercle.drawShape();
	myEngine.mvMatrixStack.popMatrix(); // pelle
	
	myEngine.mvMatrixStack.popMatrix(); // all
}

void drawTrain(){
	myEngine.mvMatrixStack.pushMatrix(); // all
	myEngine.mvMatrixStack.addTranslation({0.f,0.f,2*rr+sr});
	drawWheels();
	
	myEngine.mvMatrixStack.pushMatrix(); // base
	myEngine.mvMatrixStack.addTranslation({5.f,4.f,1.f});
	myEngine.mvMatrixStack.addHomothety({3.5f,7.f,1.f});
	myEngine.setFlatColor(0.373, 0.008, 0.122);
	myEngine.updateMvMatrix();
	cube->draw();
	myEngine.mvMatrixStack.popMatrix(); // base

	myEngine.mvMatrixStack.pushMatrix(); // rampe
	myEngine.mvMatrixStack.addTranslation({5.f,8.f,1.f});
	myEngine.mvMatrixStack.addHomothety({3.5f,1.f,1.f});
	myEngine.updateMvMatrix();
	drawRamp();
	myEngine.mvMatrixStack.popMatrix(); // rampe

	myEngine.mvMatrixStack.pushMatrix(); // cylindre
	myEngine.mvMatrixStack.addTranslation({5.f,4.f,2.5f});
	myEngine.mvMatrixStack.addHomothety({1.5f,3.5f,1.5f});
	myEngine.setFlatColor(0.561, 0.02, 0.192);
	myEngine.updateMvMatrix();
	drawClosedCylinder();
	myEngine.mvMatrixStack.popMatrix(); // cylindre

	myEngine.mvMatrixStack.pushMatrix(); // cheminée
	myEngine.mvMatrixStack.addTranslation({5.f,7.f,4.6f});
	myEngine.mvMatrixStack.addRotation(-M_PI_2,{1.0,0.0,0.0});
	myEngine.mvMatrixStack.addHomothety({0.4f,0.8f,0.4f});
	myEngine.setFlatColor(0.373, 0.008, 0.122);
	myEngine.updateMvMatrix();
	cylindre->draw();
	myEngine.mvMatrixStack.addTranslation({0.f,-2.f,0.f});
	myEngine.mvMatrixStack.addHomothety({2.f,4.f,2.f});
	myEngine.updateMvMatrix();
	cone->draw();
	myEngine.mvMatrixStack.popMatrix(); // cheminée

	myEngine.mvMatrixStack.pushMatrix(); // lumiere
	myEngine.mvMatrixStack.addTranslation({5.f,7.f,3.f});
	myEngine.mvMatrixStack.pushMatrix(); // lumiereCyl
	myEngine.mvMatrixStack.addHomothety(0.6);
	myEngine.updateMvMatrix();
	drawClosedCylinder();
	myEngine.mvMatrixStack.popMatrix(); // lumiereCyl
	myEngine.setFlatColor(0.8,0.8,0.1);
	myEngine.mvMatrixStack.addTranslation({0.f,0.5f,0.f});
	myEngine.mvMatrixStack.addHomothety(0.5);
	myEngine.updateMvMatrix();
	sphere->draw();
	myEngine.mvMatrixStack.popMatrix(); // lumiere

	myEngine.mvMatrixStack.pushMatrix(); // grate
	myEngine.mvMatrixStack.addTranslation({5.f,7.5f,2.1f});
	myEngine.updateMvMatrix();
	drawGrate();
	myEngine.mvMatrixStack.addTranslation({1.f,-3.5f,0.5f});
	myEngine.mvMatrixStack.pushMatrix(); // coalgrate
	myEngine.mvMatrixStack.addRotation(0.4,{0.0,0.0,1.0});
	myEngine.mvMatrixStack.addTranslation({-1.f,0.f,0.f});
	myEngine.mvMatrixStack.addHomothety({1.f,1.f,3.f});
	myEngine.updateMvMatrix();
	drawGrate();
	myEngine.mvMatrixStack.popMatrix(); // coalgrate
	myEngine.mvMatrixStack.addTranslation({-0.5f,1.999f,0.f});
	myEngine.mvMatrixStack.addRotation(-M_PI_2,{1.0,0.0,0.0});
	myEngine.mvMatrixStack.addTranslation({-0.5f,0.f,0.f});
	myEngine.mvMatrixStack.addHomothety({2.f,1.f,4.f});
	myEngine.updateMvMatrix();
	carre.drawShape();
	myEngine.setFlatColor(0.8f,0.4f,0.f);
	myEngine.mvMatrixStack.addTranslation({0.f,0.f,-0.001f});
	myEngine.mvMatrixStack.addHomothety({0.8f,0.8f,1.f});
	myEngine.updateMvMatrix();
	carre.drawShape();
	myEngine.mvMatrixStack.popMatrix(); // grate
	myEngine.setFlatColor(0.f,0.f,0.f);
	drawCabin();

	myEngine.mvMatrixStack.pushMatrix(); // perso
	myEngine.mvMatrixStack.addTranslation({5.5f,2.2f,2.f});
	myEngine.mvMatrixStack.addHomothety(0.6);
	drawPerso();
	myEngine.mvMatrixStack.popMatrix(); // perso
	myEngine.mvMatrixStack.popMatrix(); // all
}