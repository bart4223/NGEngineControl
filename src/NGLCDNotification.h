//
//  NGLCDNotification.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 12.06.21.
//

#ifndef NGLCDNotification_h
#define NGLCDNotification_h

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <NGINotification.h>

class NGLCDNotification : public NGINotification {

private:
    int _columns;
    int _lines;
    LiquidCrystal_I2C *_lcd;
    
protected:
    void _create(byte address, int columns, int lines);
    void _write(char* value, int line, int column);

public:
    NGLCDNotification(byte address, int columns, int lines);
    void initialize();
    char* getName();
    void clear();
    void clear(int line);
    void writeInfo(char* info);
    void writeInfo(char* info, int line);
    void writeInfo(char* info, int line, int column);

};

#endif /* NGLCDNotification_h */
