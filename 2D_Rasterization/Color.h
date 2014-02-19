#ifndef __COLOR_H__
#define __COLOR_H__

/**
 * A simple representation of a Color
 */
struct Color
{
    // Declare the components in logical order rather than alphabetic order
    // so that an initializer list can be used for assignment
    int      red, green, blue;
};

#endif
