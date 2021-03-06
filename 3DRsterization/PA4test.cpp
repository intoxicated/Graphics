#include "../2DRasterization/FrameBuffer.h"
#include "../2DRasterization/GraphicsWindow.h"
#include <list>
#include "Triangle.h"

#include "Rasterizer3D.h"
#include "meshUtilities.h"

#define PI 3.14159265358979323846

Color             GRAY  = {102,102,102};
Color             WHITE = {255,255,255};
Color             YELLOW = {255,255,0};   
int               view;
list<Triangle *>  triangles;
Rasterizer3D*     rasterizer;   

int main(int argc, char* argv[])
{
   FrameBuffer*      frameBuffer;
   GraphicsWindow*   window;
   int               depth, height, width;   

   view = 0;
   
   width  = 801;   
   height = 801;
   depth  = 801;   
   
   window      = new GraphicsWindow(width, height);
   frameBuffer = window->getFrameBuffer();
   //frameBuffer->setKeyboardHandler(keyboardHandler);
   rasterizer = new Rasterizer3D(frameBuffer);

   // Read and scale the triangular mesh
   // (In an IDE you may need to hard-code the path to the file)
   if (argc == 1) 
       read("teapot.txt", triangles);
   else           
       read(argv[1],      triangles);
  
   view = atoi(argv[2]);
   
   if(triangles.size() == 0)
   {
        printf("did not read file properly\n");
        exit(1);
   }
   
   scaleAndTranslate(triangles, width, height, depth);

   // Setup the rasterizer
   //rasterizer->useIsometricView();
   //rasterizer->useTrimetricView(-view*(PI/4.0),0.0);
   //rasterizer->useDimetricView(-view*(PI/4.0));
   //rasterizer->useTwoPointPerspectiveView
   //    (0, 100, 100, 0.0);
   rasterizer->useThreePointPerspectiveView(50,20,100,-50, -view*(PI/4.0), 0.0);
   rasterizer->clear(GRAY);   

   // Draw the triangles
   rasterizer->draw(triangles);
   frameBuffer->show();
   
   
   // Delete the triangles pointed to by the elements of the list
   for (list<Triangle*>::iterator i=triangles.begin(); i!=triangles.end(); i++)
   {
      delete (*i);      
   }
   
   delete rasterizer;   
   delete window; // The window will delete the FrameBuffer
}
  
