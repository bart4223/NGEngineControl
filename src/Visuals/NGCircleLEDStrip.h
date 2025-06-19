//
//  NGCircleLEDStrip.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 19.06.25.
//

#ifndef NGCircleLEDStrip_h
#define NGCircleLEDStrip_h

#include <Arduino.h>
#include <Visuals/NGColorLEDStrip.h>

#define DEFRADIUSCOUNT  1 
#define MAXRADIUSCOUNT 10 

struct circleLEDStripRadiusStruct
{
    int startpixel;
};
typedef struct circleLEDStripRadiusStruct circleLEDStripRadius;

class NGCircleLEDStrip : public NGColorLEDStrip {

private:
    circleLEDStripRadius _radius[MAXRADIUSCOUNT];
    int _radiusCount = DEFRADIUSCOUNT;

protected:
    void _create(byte pin, int pixelcount, int radiuscount, int pinautodetection);

public:
    NGCircleLEDStrip(byte pin, int pixelcount);

    NGCircleLEDStrip(byte pin, int pixelcount, int radiuscount);

    void registerRadius(int radius, int startpixel);

    void testSequenceStart();

    void drawCircle(int x0, int y0, int radius, colorRGB color);
};

#endif /* NGCircleLEDStrip_h */