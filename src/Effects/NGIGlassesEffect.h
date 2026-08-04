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

enum glassesEffectKind { glekNone, glekSolid, glekRotateOne, glekRotateTwo, glekRotateThree, glekOppositeRotateOne, glekOppositeRotateTwo, glekOppositeRotateThree, glekRandom, glekOppositeRandom };

class NGIGlassesEffect : public NGIEffect {
    
public:
    virtual void setKind(glassesEffectKind kind);

    virtual glassesEffectKind getKind();

    virtual void setColor(colorRGB color);

    virtual colorRGB getColor();

    virtual void setDelay(int delay);

    virtual int getDelay();
};

#endif /* NGIGlassesEffect_h */
