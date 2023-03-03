//
//  NGIPaintableComponent.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 03.03.23.
//

#ifndef NGIPaintableComponent_h
#define NGIPaintableComponent_h

struct colorRGBStruct
{
    byte red;
    byte green;
    byte blue;
};
typedef struct colorRGBStruct colorRGB;

#define COLOR_BLACK         { .red = 0, .green = 0, .blue = 0 }
#define COLOR_WHITE         { .red = 255, .green = 255, .blue = 255 }
#define COLOR_WHITE_LOW     { .red = 55, .green = 55, .blue = 55 }
#define COLOR_RED           { .red = 255, .green = 0, .blue = 0 }
#define COLOR_RED_LOW       { .red = 55, .green = 0, .blue = 0 }
#define COLOR_GREEN         { .red = 0, .green = 255, .blue = 0 }
#define COLOR_GREEN_LOW     { .red = 0, .green = 55, .blue = 0 }
#define COLOR_LIME          { .red = 191, .green = 255, .blue = 0 }
#define COLOR_BLUE          { .red = 0, .green = 0, .blue = 255 }
#define COLOR_BLUE_LOW      { .red = 0, .green = 0, .blue = 55 }
#define COLOR_YELLOW        { .red = 255, .green = 255, .blue = 0 }
#define COLOR_YELLOW_LOW    { .red = 55, .green = 55, .blue = 0 }
#define COLOR_TEAL          { .red = 0, .green = 255, .blue = 255 }
#define COLOR_TEAL_LOW      { .red = 0, .green = 55, .blue = 55 }
#define COLOR_PURPLE        { .red = 255, .green = 0, .blue = 255 }
#define COLOR_PURPLE_LOW    { .red = 55, .green = 0, .blue = 55 }
#define COLOR_ORANGE        { .red = 255, .green = 33, .blue = 0 }
#define COLOR_BROWN         { .red = 139, .green = 69, .blue = 8 }

class NGIPaintableComponent {
    
public:
    virtual int getWidth();
    
    virtual int getHeight();
    
    virtual void beginUpdate();
    
    virtual void endUpdate();
    
    virtual void clear();
    
    virtual bool drawPoint(byte x, byte y, colorRGB color);
    
};

#endif /* NGIPaintableComponent_h */
