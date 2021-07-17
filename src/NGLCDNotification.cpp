//
//  NGLCDNotification.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 12.06.21.
//

#include "Wire.h"
#include "NGLCDNotification.h"

NGLCDNotification::NGLCDNotification(byte address, int columns, int lines) {
    _create(address, columns, lines);
}

void NGLCDNotification::_create(byte address, int columns, int lines) {
    _lcd = new LiquidCrystal_I2C(address, columns, lines);
    _columns = columns;
    _lines = lines;
}

void NGLCDNotification::_write(char* value, int line, int column ) {
    int col;
    int j = 0;
    if (line >= 0) {
        j = line;
    }
    int offset = 0;
    if (column >= 0) {
        offset = column;
    }
    for (int i = 0; i < strlen(value); i++) {
        col = offset + i;
        if (line == -1) {
            if (col != 0 && col%_columns == 0) {
                j = (j + 1)%_lines;
                offset = 0;
            }
        }
        if (column == -1) {
            _lcd->setCursor(col%_columns, j);
        } else {
            if ((col < _columns) && (j < _lines)) {
                _lcd->setCursor(col, j);
            }
        }
        if ((col < _columns) && (j < _lines)) {
            _lcd->print(value[i]);
        }
    }
    _lcd->backlight();
}

void NGLCDNotification::initialize() {
    _lcd->init();
}

char* NGLCDNotification::getName() {
    return (char*)"LCD";
}

void NGLCDNotification::clear() {
    for (int i = 0; i < _lines; i++) {
        for (int j = 0; j < _columns; j++) {
            _lcd->setCursor(j, i);
            _lcd->print(" ");
        }
    }
}

void NGLCDNotification::clear(int line) {
    for (int i = 0; i < _columns; i++) {
        _lcd->setCursor(i, line);
        _lcd->print(" ");
    }
}

void NGLCDNotification::writeInfo(char* info) {
    writeInfo(info, -1, -1);
}

void NGLCDNotification::writeInfo(char* info, int line) {
    writeInfo(info, line, -1);
}

void NGLCDNotification::writeInfo(char* info, int line, int column) {
    _write(info, line, column);
}
