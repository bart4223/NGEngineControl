//
//  NGOLEDNotification.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 07.12.21.
//

#include "NGOLEDNotification.h"

NGOLEDNotification::NGOLEDNotification(byte address, int columns, int lines) {
    _create(ot128x64, address, columns, lines, DEFLINEFACTOR);
}

NGOLEDNotification::NGOLEDNotification(oledTechnology technology, byte address, int columns, int lines) {
    _create(technology, address, columns, lines, DEFLINEFACTOR);
}

NGOLEDNotification::NGOLEDNotification(byte address, int columns, int lines, int linefactor) {
    _create(ot128x64, address, columns, lines, linefactor);
}

NGOLEDNotification::NGOLEDNotification(oledTechnology technology, byte address, int columns, int lines, int linefactor) {
    _create(technology, address, columns, lines, linefactor);
}

void NGOLEDNotification::_create(oledTechnology technology, byte address, int columns, int lines, int linefactor) {
    switch (technology) {
        case ot128x64:
            _oled.begin(&Adafruit128x64, address);
            break;
        case ot128x32:
            _oled.begin(&Adafruit128x32, address);
            break;
    }
    _columns = columns;
    _lines = lines;
    _linefactor = linefactor;
}

void NGOLEDNotification::_write(char* value, int line, int column) {
    int len = 0;
    char text[100];
    // Condense substrings (#...#)
    for (int i = 0; i < strlen(value); i++) {
        if (value[i] == '(') {
            if (i + 1 < strlen(value)) {
                if (value[i + 1] == '#') {
                    i++;
                    for (int j = i; j < strlen(value); j++) {
                        if (value[j] == '#') {
                            if (j + 1 < strlen(value)) {
                                if (value[j + 1] == ')') {
                                    i = i + 2;
                                    break;
                                }
                            }
                        } else {
                            i++;
                        }
                    }
                }
            }
        } else {
            text[len] = value[i];
            len++;
        }
    }
    text[len] = '\0';
    for (int i = 0; i < len; i++) {
        int x = (column + i)%_columns;
        int y = line * _linefactor + (column + i) / _columns;
        _display[y][x] = text[i];
    }
    _render();
}

void NGOLEDNotification::_clear() {
    for (int y = 0; y < _lines / _linefactor; y++) {
        _clear(y);
    }
}

void NGOLEDNotification::_clear(int line) {
    int y = line * _linefactor;
    for (int i = 0; i < _linefactor; i++) {
        for (int x = 0; x < _columns; x++) {
            _display[y + i][x] = ' ';
        }
    }
}

void NGOLEDNotification::_render() {
    _oled.home();
    for (int y = 0; y < _lines; y++) {
        for (int x = 0; x < _columns; x++) {
            if (x == _columns - 1) {
                _oled.println(_display[y][x]);
            } else {
                _oled.print(_display[y][x]);
            }
        }
    }
}

void NGOLEDNotification::initialize() {
    _oled.setFont(font8x8);
    _clear();
}

char* NGOLEDNotification::getName() {
    return (char*)"OLED";
}

void NGOLEDNotification::clear() {
    _clear();
    _render();
}

void NGOLEDNotification::clear(int line) {
    _clear(line);
    _render();
}

void NGOLEDNotification::writeInfo(char* info) {
    writeInfo(info, 0, 0);
}

void NGOLEDNotification::writeInfo(char* info, int line) {
    writeInfo(info, line, 0);
}

void NGOLEDNotification::writeInfo(char* info, int line, int column) {
    _write(info, line, column);
}

void NGOLEDNotification::setInvertDisplay(bool invert) {
    _oled.invertDisplay(invert);
}
