#pragma once

#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "tools/basic_mesh.hpp"
#include "json.hpp"

#include <fstream>
#include <iostream>

using namespace glbasimac;
using json = nlohmann::json;

void drawStraightRail();
void drawCurvedRail();
void initCurved();
void initJson();
void drawRails();