//
//  NGIPaintableComponent.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 03.03.23.
//

#ifndef NGIPaintableComponent_h
#define NGIPaintableComponent_h

#include <NGCommonGraphics.h>

class NGIPaintableComponent {
    
public:
    virtual int getWidth();
    
    virtual int getHeight();
    
    virtual void beginUpdate();
    
    virtual void endUpdate();
    
    virtual void clear();
    
    virtual bool drawPoint(int x, int y, colorRGB color);
    
    virtual void setScale(int scale);
    
};

#endif /* NGIPaintableComponent_h */