#include "meshUtilities.h"

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
Matrix<4,2> findBounds(list<Triangle*> triangles)
{
   Matrix<4,2> ret;
   return ret;
}




/**
 * Read a triangular mesh
 *
 * @param fileName   The name of the file to read from
 * @param triangles  The "triangular mesh" to populat
 */
void read(const char* fileName, list<Triangle*>& triangles)
{
   char                s[80];   
   double              x, y, z, nx, ny, nz;   
   FILE*               in;
   int                 br, bg, bb, fr, fg, fb, size;
   Triangle*           t;
   Matrix<4,3>         v, n;


   in = fopen(fileName, "r");
   
   // Read the number of triangles
   fscanf(in, "%d", &size);
   
   // Read the triangles
   for (int k=0; k<size; k++)
   {
      t = new Triangle();      

      fscanf(in, "%s",s);

      fscanf(in, "%d %d %d %d %d %d",&fr,&fg,&fb,&br,&bg,&bb);
      t->frontColor.red   = fr;
      t->frontColor.green = fg;
      t->frontColor.blue  = fb;
      t->backColor.red    = br;
      t->backColor.green  = bg;
      t->backColor.blue   = bb;

      for (int c=0; c<3; c++)
      {
         fscanf(in, "%lf %lf %lf %lf %lf %lf", &x, &y, &z, &nx, &ny, &nz);
         v(0,c) = x;
         v(1,c) = y;
         v(2,c) = z;
         v(3,c) = 1.0;
         
         n(0,c) = nx;
         n(1,c) = ny;
         n(2,c) = nz;
         n(3,c) = 1.0;
      }
      
      
      t->vertices = v;
      t->normals  = n;
      
      triangles.push_back(t);
   }

   fclose(in);
}



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
                       double width, double height, double depth)
{
   // Find the bounds


   // Setup the scaling matrix
   

   // Setup the translation matrix to center the object

   
   // Setup the transformation matrix
   //   Translate first (since the translation was calculated in the
   //   original units) and then scale
   // m = scale * translate;
   


   // Transform
}
