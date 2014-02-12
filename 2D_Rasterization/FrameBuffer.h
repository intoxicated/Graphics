#ifndef edu_jmu_cs_FrameBuffer_h
#define  edu_jmu_cs_FrameBuffer_h

#include "Color.h"
#include "SDL2/SDL.h" 

/**
 * An encapsulation of a FrameBuffer that can be used to implement
 * and test various 2D and 3D graphics algorithms.
 *
 * A FrameBuffer uses traditional Euclidean coordinates, with the origin
 * (0,0) at the center.
 *
 * This encapsulation is built on SDL.
 */
class FrameBuffer
{
  public:
  /**
   * Explicit Value Constructor
   *
   * @param window   The SDL_Window to render into
   * @param width    The width (in pixels) of the FrameBuffer
   * @param height   The height (in pixels) of the FrameBuffer
   */
   FrameBuffer(SDL_Window* window, int width, int height);


  /**
   * Destructor
   */
   ~FrameBuffer();

  /**
   * Clear the FrameBuffer (i.e., set each pixel to the given Color)
   *
   * @param color   The color to clear to
   */
   void clear(const Color& color);

  /**
   * Get the height of this FrameBuffer in pixels
   *
   * @return   The height
   */
   int  getHeight();

  /**
   * Get the width of this FrameBuffer in pixels
   *
   * @return   The width
   */
   int  getWidth();

  /**
   * Set the keyboard handler to use
   *
   * NOTE: While this method must be public (because of the design of SDL)
   * it is not part of the FrameBuffer API.
   *
   * @param handler   The keyboard handler
   */
   void setKeyboardHandler(void (*handler)(const SDL_Event& event));


  /**
   * Set a particular pixel to a particular color
   *
   * @param x      The horizontal coordinate of the pixel
   * @param y      The vertical coordinate of the pixel
   * @param color  The Color
   */
   void setPixel(int x, int y, const Color& color);   

  /**
   * Show this FrameBuffer in the window
   */
   void show();
   

  private:
   bool           keepRunning;   
   int            height, width, xMax, xMin, yMax, yMin;
   SDL_Renderer*  renderer;   

   void (*keyboardHandler)(const SDL_Event& event);
};

#endif
