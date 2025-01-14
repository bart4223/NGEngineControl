//
//  NGColorDotMatrixGradientPoint.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 01.05.24.
//

#ifndef NGColorDotMatrixGradientPoint_h
#define NGColorDotMatrixGradientPoint_h

#include <Arduino.h>
#include <NGDimmableColor.h>
#include <NGIPaintableComponent.h>

#define DEFGRADIENTSTAGES 5

class NGColorDotMatrixGradientPoint {
    
private:
    NGIPaintableComponent *_ipc;
    NGDimmableColor *_dc;
    int _x = 0;
    int _y = 0;
    int _gradientX = 0;
    int _gradientY = 0;
    int _updateCount = 0;
    byte _gradientStages = DEFGRADIENTSTAGES;
    
protected:
    void _create(NGIPaintableComponent *ipc, colorRGB color, int gradientStages, bool randomPosition);
    
    void _render();
    
    void _clear();
    
public:
    NGColorDotMatrixGradientPoint(NGIPaintableComponent *ipc, colorRGB color);
    
    NGColorDotMatrixGradientPoint(NGIPaintableComponent *ipc, colorRGB color, int gradientStages);
    
    NGColorDotMatrixGradientPoint(NGIPaintableComponent *ipc, colorRGB color, int gradientStages, bool randomPosition);
    
    void refresh();
    
    void clear();
    
    byte getGradientStages();
    
    void setPosition(int x, int y);
    
    int getPositionX();
    
    int getPositionY();
    
    int getGradientX();
    
    int getGradientY();
    
    void setGradient(int gradientX, int gradientY);
    
    void beginUpdate();
    
    void endUpdate();
};

#endif /* NGColorDotMatrixGradientPoint_h */
