//
//  NGQuestionDialog.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 09.12.21.
//

#ifndef NGQuestionDialog_h
#define NGQuestionDialog_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#define DLGQMAXDELAY 500

class NGQuestionDialog {
       
private:
    byte _pinYes;
    byte _pinNo;
    int _delay;
    bool _initialized = false;
    
protected:
    void _create(byte pinYes, byte pinNo, int delay);
    void _ensureInitialize();
    
public:
    NGQuestionDialog(byte pinYes, byte pinNo);
    
    NGQuestionDialog(byte pinYes, byte pinNo, int delay);
    
    void initialize();
    
    void setDelay(int delay);
    
    bool confirm();
};

#endif /* NGQuestionDialog_h */
