#ifndef edu_jmu_cs_GraphicsWindow_h
#define edu_jmu_cs_GraphicsWindow_h

#include "FrameBuffer.h"
#include "SDL2/SDL.h" 
#include <stdexcept>

class GraphicsWindow
{
  public:
   /**
    * Explicit Value Constructor
    *
    * @param width   The width of the usable area of the GraphicsWindow
    * @param height  The height of the usable area of the GraphicsWindow
    */
   GraphicsWindow(int width, int height);

   /**
    * Destructor
    */
   ~GraphicsWindow();

   /**
    * Get a pointer to the FrameBuffer that is associated with this
    * GraphicsWindow
    *
    * @return A pointer to the FrameBuffer
    */
   FrameBuffer* getFrameBuffer();
   

  private:
   FrameBuffer*   frameBuffer;   
   int            height, width;
   SDL_Window*    window;
   

};

#endif
