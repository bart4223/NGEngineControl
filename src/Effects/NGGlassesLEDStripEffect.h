//
//  NGGlassesLEDStripEffect.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 10.07.26.
//

#ifndef NGGlassesLEDStripEffect_h
#define NGGlassesLEDStripEffect_h

#include <Arduino.h>
#include <Effects/NGIGlassesEffect.h>
#include <Visuals/NGColorLEDStrip.h>

#define DEFAULTGLASSESLEDSTRIPEFFECTKIND glekNone
#define DEFAULTDELAY 500

class NGGlassesLEDStripEffect : public NGIGlassesEffect {

private:
    NGColorLEDStrip *_colorLEDStrip;
    colorRGB _color = COLOR_BLACK;
    glassesEffectKind _kind = DEFAULTGLASSESLEDSTRIPEFFECTKIND;
    int _rotationPosition = 0;
    long _lastRenderTime = 0;
    int _delay = DEFAULTDELAY;

protected:
    void _create(NGColorLEDStrip *colorLEDStrip, glassesEffectKind kind);

    void _render();

public:
    NGGlassesLEDStripEffect(NGColorLEDStrip *colorLEDStrip);

    NGGlassesLEDStripEffect(NGColorLEDStrip *colorLEDStrip, glassesEffectKind kind);

    void initialize();

    void reset();

    void setKind(glassesEffectKind kind);

    glassesEffectKind getKind();

    void setColor(colorRGB color);

    colorRGB getColor();

    void setDelay(int delay);

    int getDelay();

    void processingLoop();
};

#endif /* NGGlassesLEDStripEffect_h */