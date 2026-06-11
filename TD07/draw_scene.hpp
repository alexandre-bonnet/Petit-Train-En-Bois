#pragma once

#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"

//#define STB_IMAGE_IMPLEMENTATION
#include "tools/stb_image.h"
#include "glbasimac/glbi_texture.hpp"

#include "tools/basic_mesh.hpp"
#include "json.hpp"


using namespace glbasimac;
using json = nlohmann::json;

/* Camera parameters and functions */
static const float Z_NEAR {0.1f};
static const float Z_FAR {500.f};
extern float angle_theta;      // Angle between x axis and viewpoint
extern float angle_phy  ;      // Angle between z axis and viewpoint
extern float dist_zoom  ;      // Distance between origin and viewpoint

extern bool enableRealisticLight;
extern bool enableTrainLight;

/* OpenGL Engine */
extern GLBI_Engine myEngine;

extern int frameCount;

extern GLBI_Set_Of_Points frame;
extern GLBI_Set_Of_Points grille;
extern GLBI_Convex_2D_Shape ground;
extern GLBI_Convex_2D_Shape cercle;

extern IndexedMesh* sphere;
extern IndexedMesh* cylindre;
extern IndexedMesh* cube;
extern StandardMesh* cone;

extern std::array<int,2> stationPlacement;
extern std::vector<std::array<int,2>> railsPlacement;
extern std::vector<std::array<int,3>> vegetationPlacement;

extern GLBI_Texture texturePull;
extern GLBI_Texture textureGrass;

void initJson();

void initScene();

void drawFrame();
void drawClosedCylinder();

void drawScene();

void initTextures();