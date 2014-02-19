#include "Color.h"
#include "FrameBuffer.h"
#include "GraphicsWindow.h"
#include "../Matrix/Matrix.hpp"
#include "Rasterizer2D.h"
#include "../Matrix/Vector.hpp"


/**
 * An integration test for PA6
 */
int main(int argc, char* argv[])
{
   Color             WHITE = {255,255,255};
   Color             YELLOW = {255,255,0};   
   FrameBuffer*      fb;
   GraphicsWindow*   window;
   
   window = new GraphicsWindow(501,501);
   fb     = window->getFrameBuffer();
   
   
   Rasterizer2D*   rasterizer;   
   rasterizer = new Rasterizer2D(fb);
   rasterizer->clear(WHITE);   


   // Fill and draw some polygons
   {
      bool             yellow;       
      double           delta, size, x, xStart, y;       
      Matrix<2,4>      polygon;      
      size   = 50.0;
      delta  =  0.0;
      yellow = true;
          
      xStart = -100.0;          
      for (y=200.0; y>=-200.0; y-=size)
      {
         for (x=xStart; x<=xStart+300; x+=size)
         {
            polygon(0,0) = x + delta;
            polygon(1,0) = y;

            polygon(0,1) = x + size + delta;
            polygon(1,1) = y;

            polygon(0,2) = x + size;
            polygon(1,2) = y + size;

            polygon(0,3) = x;
            polygon(1,3) = y + size;

            yellow = !yellow;
             
            if (yellow)
            {
               rasterizer->fillQuadrilateral(polygon, YELLOW);
            }
            else
            {
               rasterizer->fillQuadrilateral(polygon, WHITE);
            }
            
            rasterizer->drawQuadrilateral(polygon, YELLOW);
                
         }
         if (y <= - 50.0)   delta = -50.0;
         if (y <= -100.0)   xStart += delta;             
      }
          
   }


   // Fill and draw some triangles
   {          

      Vector<2>    p[9];
      p[0] = {-30,30};
      p[1] = {115,135};
      p[2] = {-90,145};
      p[3] = {-180,-45};
      p[4] = {-85,-170};
      p[5] = {-30,-180};
      p[6] = {110,-190};
      p[7] = {165,-70};
      p[8] = {195,-5};

      int faces[8][3] = {{0,1,2},
                         {0,2,3},
                         {0,3,5},
                         {0,5,7},
                         {0,7,1},
                         {3,4,5},
                         {5,6,7},
                         {1,7,8}
      };


      Color colors[8] = {{100,100,255},
                         {110,110,255},
                         {80,80,225},
                         {70,70,190},
                         {80,80,215},
                         {35,35,115},
                         {30,30,105},
                         {25,30,80}};


      for (int i=0; i<8; i++)
      {
          
         rasterizer->fillTriangle(p[faces[i][0]] | p[faces[i][1]] | p[faces[i][2]], colors[i]);
         rasterizer->drawTriangle(p[faces[i][0]] | p[faces[i][1]] | p[faces[i][2]], colors[i]);

      }
   }


   fb->show();
   
   delete rasterizer;   
   delete window; // The window will delete the FrameBuffer
   
}
