//
//  NGColorDotMatrix.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 23.10.22.
//

#ifndef NGColorDotMatrix_h
#define NGColorDotMatrix_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <rgbMatrix.h>

struct colorRGBStruct
{
    byte red;
    byte green;
    byte blue;
};
typedef struct colorRGBStruct colorRGB;

#define COORDMINTOP     0
#define COORDMINLEFT    0
#define COORDMAXBOTTOM  7
#define COORDMAXRIGHT   7

#define COLOR_BLACK  { .red = 0, .green = 0, .blue = 0 }
#define COLOR_WHITE  { .red = 255, .green = 255, .blue = 255 }
#define COLOR_RED    { .red = 255, .green = 0, .blue = 0 }
#define COLOR_GREEN  { .red = 0, .green = 255, .blue = 0 }
#define COLOR_BLUE   { .red = 0, .green = 0, .blue = 255 }
#define COLOR_YELLOW { .red = 255, .green = 255, .blue = 0 }

class NGColorDotMatrix {
    
private:
    int _updateCount = 0;
    
protected:
    void _create();
    
public:
    NGColorDotMatrix();
    
    void initialize();
    
    void render();
    
    void beginUpdate();
    
    void endUpdate();
    
    void drawPoint(byte x, byte y, colorRGB color);
    
    void drawLine(byte x1, byte y1, byte x2, byte y2, colorRGB color);
    
    void drawRect(byte top, byte left, byte bottom, byte right, colorRGB color);
    
    void fillRect(byte top, byte left, byte bottom, byte right, colorRGB color);
    
    void clearRect(byte top, byte left, byte bottom, byte right);
    
    void clear();
    
    void drawImage(byte coord[][2], colorRGB color, int size);

    void drawImage(byte coord[][2], byte color[][3], int size);
};

#endif /* NGColorDotMatrix_h */
