#ifndef __Triangle_h__
#define __Triangle_h__

#include "../2D_Rasterization/Color.h"
#include "../Matrix/Matrix.hpp"

/**
 * A simple encapsulation of a Triangle
 */
struct Triangle
{
   Color          backColor, frontColor;   
   Matrix<4,3>    normals, vertices;
};


#endif
