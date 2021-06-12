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
    int j = line;
    int col;
    int offset = column;
    for (int i = 0; i < strlen(value); i++) {
        col = offset + i;
        if (col != 0 && col%_columns == 0) {
            j = (j + 1)%_lines;
            offset = 0;
        }
        _lcd->setCursor(col%_columns, j);
        _lcd->print(value[i]);
    }
    _lcd->backlight();
}

void NGLCDNotification::initialize() {
    _lcd->init();
}

char* NGLCDNotification::getName() {
    return "LCD";
}

void NGLCDNotification::clear() {
    for (int i = 0; i < _lines; i++) {
        for (int j = 0; j < _columns; j++) {
            _lcd->setCursor(j, i);
            _lcd->print(" ");
        }
    }
}

void NGLCDNotification::writeInfo(char* info) {
    writeInfo(info, 0, 0);
}

void NGLCDNotification::writeInfo(char* info, int line) {
    writeInfo(info, line, 0);
}

void NGLCDNotification::writeInfo(char* info, int line, int column) {
    _write(info, line, column);
}
