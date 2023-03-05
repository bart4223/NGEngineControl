//
//  NGCommonGraphics.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 05.03.23.
//

#include "NGCommonGraphics.h"

int convertColorRGBToInt(colorRGB c) {
    int red_565 = map(c.red, 0, 255, 0, 31);
    int green_565 = map(c.green, 0, 255, 0, 63);
    int blue_565 = map(c.blue, 0, 255, 0, 31);
    return (red_565 << 11) | (green_565<<5) | blue_565;
}
