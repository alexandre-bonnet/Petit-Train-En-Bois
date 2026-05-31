#include "rails.hpp"
#include "draw_scene.hpp"

float sr = 0.5f;
float rr = 0.2f;
float sx = 1-rr;

GLBI_Convex_2D_Shape inRailTop{3};
GLBI_Convex_2D_Shape inRailBottom{3};
GLBI_Convex_2D_Shape inRailNear{3};
GLBI_Convex_2D_Shape inRailFar{3};

GLBI_Convex_2D_Shape outRailTop{3};
GLBI_Convex_2D_Shape outRailBottom{3};
GLBI_Convex_2D_Shape outRailNear{3};
GLBI_Convex_2D_Shape outRailFar{3};

std::array<int,2> stationPlacement{};
std::vector<std::array<int,2>> railsPlacement{};


void drawBalast();

void drawStraightRail(){
	
	myEngine.mvMatrixStack.pushMatrix(); // all
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
			myEngine.mvMatrixStack.addTranslation({2.0,i,0.0});
			drawBalast();
		myEngine.mvMatrixStack.popMatrix(); // balast
	}
	myEngine.mvMatrixStack.popMatrix(); // all
}

void drawCurvedRail() {
	
	myEngine.mvMatrixStack.pushMatrix(); // all

	myEngine.mvMatrixStack.pushMatrix(); // rails
	myEngine.setFlatColor(0.7,0.7,0.7);
	inRailTop.drawShape();
	inRailBottom.drawShape();
	inRailNear.drawShape();
	inRailFar.drawShape();

	outRailTop.drawShape();
	outRailBottom.drawShape();
	outRailNear.drawShape();
	outRailFar.drawShape();
	myEngine.mvMatrixStack.popMatrix(); // rails

	myEngine.setFlatColor(0.7,0.4,0.2);
	for(int i =1; i<4;i++){
		myEngine.mvMatrixStack.pushMatrix(); // balast
		myEngine.mvMatrixStack.addRotation(M_PI_2*i/4,{0.0,0.0,1.0});
		myEngine.mvMatrixStack.addTranslation({2.0,0.0,0.0});
		myEngine.updateMvMatrix();
		drawBalast();
		myEngine.mvMatrixStack.popMatrix(); // balast
	}

	myEngine.mvMatrixStack.popMatrix(); // all
}

void drawBalast(){
	myEngine.mvMatrixStack.pushMatrix(); // balast
		myEngine.mvMatrixStack.addTranslation({0.0,0.0,rr});
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

void initCurved(){

	int num = 5;
	std::vector<float> inRailTopVector{};
	std::vector<float> inRailBottomVector{};
	std::vector<float> inRailNearVector{};
	std::vector<float> inRailFarVector{};

	std::vector<float> outRailTopVector{};
	std::vector<float> outRailBottomVector{};
	std::vector<float> outRailNearVector{};
	std::vector<float> outRailFarVector{};

	for(int i = 0; i<=num;i++){
		float angle = i*M_PI_2/num;
		inRailTopVector.insert(inRailTopVector.end(),{(3.f+sr/2)*float(cos(angle)),(3.f+sr/2)*float(sin(angle)),2*rr+sr});
		inRailTopVector.insert(inRailTopVector.end(),{(3.f-sr/2)*float(cos(angle)),(3.f-sr/2)*float(sin(angle)),2*rr+sr});

		inRailBottomVector.insert(inRailBottomVector.end(),{(3.f+sr/2)*float(cos(angle)),(3.f+sr/2)*float(sin(angle)),2*rr});
		inRailBottomVector.insert(inRailBottomVector.end(),{(3.f-sr/2)*float(cos(angle)),(3.f-sr/2)*float(sin(angle)),2*rr});

		inRailNearVector.insert(inRailNearVector.end(),{(3.f-sr/2)*float(cos(angle)),(3.f-sr/2)*float(sin(angle)),2*rr});
		inRailNearVector.insert(inRailNearVector.end(),{(3.f-sr/2)*float(cos(angle)),(3.f-sr/2)*float(sin(angle)),2*rr+sr});

		inRailFarVector.insert(inRailFarVector.end(),{(3.f+sr/2)*float(cos(angle)),(3.f+sr/2)*float(sin(angle)),2*rr});
		inRailFarVector.insert(inRailFarVector.end(),{(3.f+sr/2)*float(cos(angle)),(3.f+sr/2)*float(sin(angle)),2*rr+sr});


		outRailTopVector.insert(outRailTopVector.end(),{(7.f+sr/2)*float(cos(angle)),(7.f+sr/2)*float(sin(angle)),2*rr+sr});
		outRailTopVector.insert(outRailTopVector.end(),{(7.f-sr/2)*float(cos(angle)),(7.f-sr/2)*float(sin(angle)),2*rr+sr});

		outRailBottomVector.insert(outRailBottomVector.end(),{(7.f+sr/2)*float(cos(angle)),(7.f+sr/2)*float(sin(angle)),2*rr});
		outRailBottomVector.insert(outRailBottomVector.end(),{(7.f-sr/2)*float(cos(angle)),(7.f-sr/2)*float(sin(angle)),2*rr});

		outRailNearVector.insert(outRailNearVector.end(),{(7.f-sr/2)*float(cos(angle)),(7.f-sr/2)*float(sin(angle)),2*rr});
		outRailNearVector.insert(outRailNearVector.end(),{(7.f-sr/2)*float(cos(angle)),(7.f-sr/2)*float(sin(angle)),2*rr+sr});

		outRailFarVector.insert(outRailFarVector.end(),{(7.f+sr/2)*float(cos(angle)),(7.f+sr/2)*float(sin(angle)),2*rr});
		outRailFarVector.insert(outRailFarVector.end(),{(7.f+sr/2)*float(cos(angle)),(7.f+sr/2)*float(sin(angle)),2*rr+sr});
	}
	inRailTop.initShape(inRailTopVector);
	inRailTop.changeNature(GL_TRIANGLE_STRIP);

	inRailBottom.initShape(inRailBottomVector);
	inRailBottom.changeNature(GL_TRIANGLE_STRIP);

	inRailNear.initShape(inRailNearVector);
	inRailNear.changeNature(GL_TRIANGLE_STRIP);

	inRailFar.initShape(inRailFarVector);
	inRailFar.changeNature(GL_TRIANGLE_STRIP);


	outRailTop.initShape(outRailTopVector);
	outRailTop.changeNature(GL_TRIANGLE_STRIP);

	outRailBottom.initShape(outRailBottomVector);
	outRailBottom.changeNature(GL_TRIANGLE_STRIP);

	outRailNear.initShape(outRailNearVector);
	outRailNear.changeNature(GL_TRIANGLE_STRIP);

	outRailFar.initShape(outRailFarVector);
	outRailFar.changeNature(GL_TRIANGLE_STRIP);
	
}

void jsonInit(){
	 std::ifstream file("../assets/RailPlacement.json");

    if (!file) {
        std::cout << "Impossible d'ouvrir ou de trouver le fichier json"<<std::endl;
        return;
    }

	json data;
    file >> data;

	stationPlacement = data["origin"].get<std::array<int,2>>();
	std::cout << "la station est en " << stationPlacement[0] <<"," << stationPlacement[1]<<std::endl;

	railsPlacement = data["path"].get<std::vector<std::array<int,2>>>();
}

void drawRails(){
	bool curved{false};
	int size{railsPlacement.size()};
	float angle{0.f};
	for (int i = 0; i<size;i++) {
		std::array<int,2> current = railsPlacement[i];
		std::array<int,2> prev = railsPlacement[(i - 1 + size) % size];
		std::array<int,2> next = railsPlacement[(i + 1) % size];

		if(prev[0]!=next[0]&&prev[1]!=next[1]){ 
			curved = true; 
		}
		if(curved){
			if (prev[1]<current[1]&&current[0]>next[0]){  
				angle = 0.f;
			}  //ok
			if (prev[0]>current[0]&&current[1]>next[1]){  
				angle = M_PI_2;
			}  
			if ((prev[1]>current[1]&&current[0]>next[0])||(prev[0]<current[0]&&current[1]<next[1])){  
				angle = -M_PI_2;
			}  
			if (prev[1]>current[1]&&current[0]<next[0]){  
				angle = M_PI;
			} 
		} else {
			if(prev[1]==current[1]){
				angle = M_PI_2;
			} else if(prev[0]==current[0]){
				angle = 0.f;
			}
		}

		myEngine.mvMatrixStack.pushMatrix(); // all
		myEngine.mvMatrixStack.addTranslation({10.f*railsPlacement[i][0],10.f*railsPlacement[i][1],0.f});
		myEngine.mvMatrixStack.addTranslation({5.f,5.f,0.f});
		myEngine.mvMatrixStack.addRotation(angle,{0.0,0.0,1.0});

		myEngine.mvMatrixStack.addTranslation({-5.f,-5.f,0.f});
		myEngine.updateMvMatrix();
		if(curved){
			drawCurvedRail();
		} else {
			drawStraightRail();
		}
		curved = false;
		myEngine.mvMatrixStack.popMatrix(); // all
	}
}