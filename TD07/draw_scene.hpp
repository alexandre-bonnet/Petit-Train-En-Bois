#pragma once

#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "tools/basic_mesh.hpp"

using namespace glbasimac;

/* Camera parameters and functions */
static const float Z_NEAR {0.1f};
static const float Z_FAR {500.f};
extern float angle_theta;      // Angle between x axis and viewpoint
extern float angle_phy  ;      // Angle between z axis and viewpoint
extern float dist_zoom  ;      // Distance between origin and viewpoint

/* OpenGL Engine */
extern GLBI_Engine myEngine;


extern GLBI_Set_Of_Points frame;
extern GLBI_Set_Of_Points grille;
extern GLBI_Convex_2D_Shape ground;
extern GLBI_Convex_2D_Shape cercle;

extern IndexedMesh* sphere;
extern IndexedMesh* cylindre;
extern StandardMesh* cone;


void initScene();

void drawFrame();

void drawScene();

