#include "GraphicsWindow.h"


/**
 * Explicit Value Constructor
 *
 * @param width   The width of the usable area of the GraphicsWindow
 * @param height  The height of the usable area of the GraphicsWindow
 */
GraphicsWindow::GraphicsWindow(int width, int height)
{
   // Make the width and height odd (so the GraphicsWindow has a center pixel)
   if ((width%2)  == 0) width++;
   if ((height%2) == 0) height++;
   
   this->width = width;
   this->height = height;   


   SDL_Init(SDL_INIT_VIDEO);
   
   // Note: The size of the window is actually the size of the renderable area
   window   = SDL_CreateWindow("JMU - CS488", 
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               width, height, 
                               0);
   if(window==NULL) throw(std::runtime_error("Unable to construct a window."));

   frameBuffer = new FrameBuffer(window, width, height);
}


/**
 * Destructor
 */
GraphicsWindow::~GraphicsWindow()
{
   delete frameBuffer;
   SDL_DestroyWindow(window); 
   SDL_Quit(); 
   
}


/**
 * Get a pointer to the FrameBuffer that is associated with this
 * GraphicsWindow
 *
 * @return A pointer to the FrameBuffer
 */
FrameBuffer* GraphicsWindow::getFrameBuffer()
{
   return frameBuffer;
}
