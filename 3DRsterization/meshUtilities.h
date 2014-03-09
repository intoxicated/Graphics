/**
 * meshUtilities Header
 *
 * Wooyoung Chung
 *
 * 3/5/14
 *
 */

#ifndef __meshUtilities_H__
#define __meshUtilities_H__

#include "../2DRasterization/Color.h"
#include "../2DRasterization/Geometry.hpp"
#include <list>
#include "../Matrix/Matrix.hpp"
#include <stdio.h>
#include "Triangle.h"

/**
 * Functions for working with triangular meshes.
 *
 * A triangular mesh is stored as a list<Triangle*> (i.e., a list of pointers
 * to Triangle objects). 
 * 
 * Notes: 
 *
 * 1. We are using a list rather than a vector to avoid confusion
 * between vector and Vector.
 *
 * 2. We are using a list of pointers so that we can change the contents
 * of the list (e.g., so we don't have to create a copy of the entire list
 * when the Triangle objects are scaled)
 */





/**
 * Find the bounds of a triangular mesh.
 *
 * The bounds are returned as a Matrix of 2 points in 4-D. One
 * point contains the minimum value for all dimensions and the other
 * contains the maximum value for all dimensions.
 *
 * @param triangles   The "triangular mesh" (i.e., the list of Triangle*)
 * @return            The bounds
 */
Matrix<4,2> findBounds(list<Triangle*> triangles);

/**
 * Read a triangular mesh
 *
 * @param fileName   The name of the file to read from
 * @param triangles  The "triangular mesh" to populat
 */

void read(const char* fileName, list<Triangle*>& triangles);

/**
 * Scales and translates the given Triangle objects so that they
 * fit within a rectangular solid and are centered at 0,0. 
 * The aspect ratio of the Triangle objects will remain unchanged.
 *
 * @param triangles   The Triangle objects to scale and translate
 * @param width       The width of the rectangle
 * @param height      The height of the rectangle
 * @param depth       The depth of the rectangle
 */
void scaleAndTranslate(list<Triangle*> triangles, 
                       double width, double height, double depth);


#endif
