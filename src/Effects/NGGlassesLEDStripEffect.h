//
//  NGGlassesLEDStripEffect.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 10.06.26.
//

#ifndef NGGlassesLEDStripEffect_h
#define NGGlassesLEDStripEffect_h

#include <Arduino.h>
#include <NGIEffect.h>
#include <Visuals/NGColorLEDStrip.h>

#define DEFAULTGLASSESLEDSTRIPEFFECTKIND glekNone

enum glassesLEDStripEffectKind { glekNone, glekSolid };

class NGGlassesLEDStripEffect : public NGIEffect {

private:
    NGColorLEDStrip *_colorLEDStrip;
    glassesLEDStripEffectKind _kind = DEFAULTGLASSESLEDSTRIPEFFECTKIND;

protected:
    void _create(NGColorLEDStrip *colorLEDStrip, glassesLEDStripEffectKind kind);

    void _render();

public:
    NGGlassesLEDStripEffect(NGColorLEDStrip *colorLEDStrip);

    NGGlassesLEDStripEffect(NGColorLEDStrip *colorLEDStrip, glassesLEDStripEffectKind kind);

    void initialize();

    void reset();

    void setKind(glassesLEDStripEffectKind kind);

    void setColor(colorRGB color);

    void processingLoop();
};

#endif /* NGGlassesLEDStripEffect_h */