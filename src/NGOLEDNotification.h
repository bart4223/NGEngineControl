//
//  NGOLEDNotification.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 07.12.21.
//

#ifndef NGOLEDNotification_h
#define NGOLEDNotification_h

#include <Arduino.h>
#include <SSD1306Ascii.h>
#include <SSD1306AsciiWire.h>
#include <NGCommon.h>
#include <NGINotification.h>

#ifdef NG_PLATFORM_MEGA
#define MAXOLEDLINES    16
#define MAXOLEDCOLUMNS  32
#else
#define MAXOLEDLINES    8
#define MAXOLEDCOLUMNS  16
#endif
#define DEFLINEFACTOR   1

enum oledTechnology {ot128x64, ot128x32};

class NGOLEDNotification : public NGINotification {

private:
    int _columns;
    int _lines;
    int _linefactor;
    char _display[MAXOLEDLINES][MAXOLEDCOLUMNS];
    SSD1306AsciiWire _oled;
    
protected:
    void _create(oledTechnology technology, byte address, int columns, int lines, int linefactor);
    void _write(char* value, int line, int column);
    void _clear();
    void _clear(int line);
    void _render();

public:
    NGOLEDNotification(byte address, int columns, int lines);
    NGOLEDNotification(oledTechnology technology, byte address, int columns, int lines);
    NGOLEDNotification(byte address, int columns, int lines, int linefactor);
    NGOLEDNotification(oledTechnology technology, byte address, int columns, int lines, int linefactor);
    void initialize();
    char* getName();
    void clear();
    void clear(int line);
    void writeInfo(char* info);
    void writeInfo(char* info, int line);
    void writeInfo(char* info, int line, int column);
    void setInvertDisplay(bool invert);

};

#endif /* NGOLEDNotification_h */
