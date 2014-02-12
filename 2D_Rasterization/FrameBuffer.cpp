#include "FrameBuffer.h"

/**
 * Explicit Value Constructor
 *
 * @param window   The SDL_Window to render into
 * @param width    The width (in pixels) of the FrameBuffer
 * @param height   The height (in pixels) of the FrameBuffer
 */
FrameBuffer::FrameBuffer(SDL_Window* window, int width, int height)
{
   keepRunning = true;
   renderer = SDL_CreateRenderer(window, -1, 0);

   this->height = height;
   this->width = width;   

   xMin = -(width/2);
   xMax =  (width/2);
   yMin = -(height/2);
   yMax =  (height/2);

   keyboardHandler = NULL;   
}

/**
 * Destructor
 */
FrameBuffer::~FrameBuffer()
{
  SDL_DestroyRenderer(renderer);   
}

/**
 * Clear the FrameBuffer (i.e., set each pixel to the given Color)
 *
 * @param color   The color to clear to
 */
void FrameBuffer::clear(const Color& color)
{
   SDL_SetRenderDrawColor(renderer, 
                          color.red, color.green, color.blue, 
                          255);
   SDL_RenderClear(renderer);
}

/**
 * Get the height of this FrameBuffer in pixels
 *
 * @return   The height
 */
int FrameBuffer::getHeight()
{
   return height;   
}


/**
 * Get the width of this FrameBuffer in pixels
 *
 * @return   The width
 */
int FrameBuffer::getWidth()
{
   return width;   
}

/**
 * Set the keyboard handler to use
 *
 * NOTE: While this method must be public (because of the design of SDL)
 * it is not part of the FrameBuffer API.
 *
 * @param handler   The keyboard handler
 */
void FrameBuffer::setKeyboardHandler(void (*handler)(const SDL_Event& event))
{
   this->keyboardHandler = handler;   
}

/**
 * Set a particular pixel to a particular color
 *
 * @param x      The horizontal coordinate of the pixel
 * @param y      The vertical coordinate of the pixel
 * @param color  The Color
 */
void FrameBuffer::setPixel(int x, int y, const Color& color)
{
   if ((x >= xMin) && (x <=xMax) && (y >= yMin) & (y <= yMax))
   {
      SDL_SetRenderDrawColor(renderer, 
                             color.red, color.green, color.blue,
                             255);
      SDL_RenderDrawPoint(renderer, x-xMin, yMax-y);
   }
}

/**
 * Show this FrameBuffer in the window
 */
void FrameBuffer::show()
{
   SDL_Event       event;
   
   SDL_RenderPresent(renderer);
   while(keepRunning)
   {
      while(SDL_PollEvent(&event))
      {
         if (event.type == SDL_QUIT)  // The window was closed
         {
            keepRunning = false;
            break; // Don't handle pending events
         }
         else
         {
            if ((event.type == SDL_KEYDOWN) && (keyboardHandler != NULL))
            {
               keyboardHandler(event);               
               SDL_RenderPresent(renderer);
            }
            else if (event.type == SDL_WINDOWEVENT)
            {
               // Comment this line out under OS X
               SDL_RenderPresent(renderer);
            }
         }
      }
   }
}
