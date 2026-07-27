//
//  NGIGlassesEffect.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 27.07.26.
//

#ifndef NGIGlassesEffect_h
#define NGIGlassesEffect_h

#include <NGCommonGraphics.h>
#include <NGIEffect.h>

class NGIGlassesEffect : public NGIEffect {
    
public:
    virtual void setColor(colorRGB color);

    virtual colorRGB getColor();
};

#endif /* NGIGlassesEffect_h */
