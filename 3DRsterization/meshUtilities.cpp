/**
 * meshUtilities Implementation
 *
 * Wooyoung Chung
 *
 * 3/5/14
 *
 */

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

   std::list<Triangle *>::iterator it;
   
   Matrix<4,3> each;
   Matrix<4,2> eachResult;
   ret = getBounds((*triangles.begin())->vertices);
 
   for(it = triangles.begin(); it != triangles.end(); ++it)
   {
        eachResult = getBounds((*it)->vertices);
        for(int i = 0; i < 4; ++i)
        {
            if(ret(i,0) > eachResult(i,0))
                ret(i,0) = eachResult(i,0);
            if(ret(i,1) < eachResult(i,1))
                ret(i,1) = eachResult(i,1);
        }
   }

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
   if(in == NULL)
   {
        printf("did not open file [%s] properly\n", fileName);
        exit(1);
   }
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
   Matrix<4,2> bound = findBounds(triangles); 
   double x = (bound(0,1) - bound(0,0));
   double y = (bound(1,1) - bound(1,0));
   double z = (bound(2,1) - bound(2,0));
   
   // find longest distance to fit    
   double longest = x, cscale = width/x;
   if(longest < y)
       longest = y, cscale = height/y;
   if(longest < z)
       cscale = depth/z;

   Matrix<4,4> scale, translate, m;
   // Setup the scaling matrix
   scale = {cscale,     0,    0,0,
                0, cscale,    0,0,
                0,     0, cscale,0,
                0,     0,    0,1};
   // Setup the translation matrix to center the object
   // find center of mass
   double xsum, ysum, zsum;
   xsum = (bound(0,1) + bound(0,0)) * 4;
   ysum = (bound(1,1) + bound(1,0)) * 4;
   zsum = (bound(2,1) + bound(2,0)) * 4;
   translate = {1, 0, 0, -xsum/8.0,
                0, 1, 0, -ysum/8.0,
                0, 0, 1, -zsum/8.0,
                0, 0, 0, 1};
   // Setup the transformation matrix
   //   Translate first (since the translation was calculated in the
   //   original units) and then scale
   m = scale * translate;
   std::list<Triangle*>::iterator it;

   // Transform
   Matrix<4,3> each;
   for(it = triangles.begin(); it != triangles.end(); ++it)
   {
        each = (*it)->vertices;
        (*it)->vertices = m * each;
   }
}
