//
//  NGMorseToneGenerator.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 01.01.22.
//

#include "NGMorseToneGenerator.h"

NGMorseToneGenerator::NGMorseToneGenerator() {
    _create();
}

void NGMorseToneGenerator::_create() {
    _sm = new NGSoundMachine();
}

void NGMorseToneGenerator::_playJingleDit() {
    if (_jingleDit >= 0) {
        if (_tempo == 0) {
            _sm->play(_jingleDit);
        } else {
            _sm->play(_jingleDit, _tempo);
        }
    }
}

void NGMorseToneGenerator::_playJingleDah() {
    if (_jingleDah >= 0) {
        if (_tempo == 0) {
            _sm->play(_jingleDah);
        } else {
            _sm->play(_jingleDah, _tempo);
        }
    }
}

void NGMorseToneGenerator::_playJingleBreakLetter() {
    if (_jingleBreakLetter >= 0) {
        if (_tempo == 0) {
            _sm->play(_jingleBreakLetter);
        } else {
            _sm->play(_jingleBreakLetter, _tempo);
        }
    }
}

void NGMorseToneGenerator::_playJingleBreakWord() {
    if (_jingleBreakWord >= 0) {
        if (_tempo == 0) {
            _sm->play(_jingleBreakWord);
        } else {
            _sm->play(_jingleBreakWord, _tempo);
        }
    }
}

void NGMorseToneGenerator::initialize() {
    _sm->initialize();
}

void NGMorseToneGenerator::registerJingleDit(NGCustomJingle *jingle) {
    _jingleDit = _sm->registerJingle(jingle);
}

void NGMorseToneGenerator::registerJingleDah(NGCustomJingle *jingle) {
    _jingleDah = _sm->registerJingle(jingle);
}

void NGMorseToneGenerator::registerJingleBreakLetter(NGCustomJingle *jingle) {
    _jingleBreakLetter = _sm->registerJingle(jingle);
}

void NGMorseToneGenerator::registerJingleBreakWord(NGCustomJingle *jingle) {
    _jingleBreakWord = _sm->registerJingle(jingle);
}

void NGMorseToneGenerator::setTempo(int tempo) {
    _tempo = tempo;
}

void NGMorseToneGenerator::playLetterA() {
    _playJingleDit();
    _playJingleDah();
}

void NGMorseToneGenerator::playLetterB() {
    _playJingleDah();
    for (int i = 0; i < 3; i++) {
        _playJingleDit();
    }
}

void NGMorseToneGenerator::playLetterC() {
    for (int i = 0; i < 2; i++) {
        _playJingleDah();
        _playJingleDit();
    }
}

void NGMorseToneGenerator::playLetterD() {
    _playJingleDah();
    for (int i = 0; i < 2; i++) {
        _playJingleDit();
    }
}

void NGMorseToneGenerator::playLetterE() {
    _playJingleDit();
}

void NGMorseToneGenerator::playLetterF() {
    for (int i = 0; i < 2; i++) {
        _playJingleDit();
    }
    _playJingleDah();
    _playJingleDit();
}

void NGMorseToneGenerator::playLetterG() {
    for (int i = 0; i < 2; i++) {
        _playJingleDah();
    }
    _playJingleDit();
}

void NGMorseToneGenerator::playLetterH() {
    for (int i = 0; i < 4; i++) {
        _playJingleDit();
    }
}

void NGMorseToneGenerator::playLetterI() {
    for (int i = 0; i < 2; i++) {
        _playJingleDit();
    }
}

void NGMorseToneGenerator::playLetterJ() {
    _playJingleDit();
    for (int i = 0; i < 3; i++) {
        _playJingleDah();
    }
}

void NGMorseToneGenerator::playLetterK() {
    _playJingleDah();
    _playJingleDit();
    _playJingleDah();
}

void NGMorseToneGenerator::playLetterL() {
    _playJingleDit();
    _playJingleDah();
    for (int i = 0; i < 2; i++) {
        _playJingleDit();
    }
}

void NGMorseToneGenerator::playLetterM() {
    for (int i = 0; i < 2; i++) {
        _playJingleDah();
    }
}

void NGMorseToneGenerator::playLetterN() {
    _playJingleDah();
    _playJingleDit();
}

void NGMorseToneGenerator::playLetterO() {
    for (int i = 0; i < 3; i++) {
        _playJingleDah();
    }
}

void NGMorseToneGenerator::playLetterP() {
    _playJingleDit();
    for (int i = 0; i < 2; i++) {
        _playJingleDah();
    }
    _playJingleDit();
}

void NGMorseToneGenerator::playLetterQ() {
    for (int i = 0; i < 2; i++) {
        _playJingleDah();
    }
    _playJingleDit();
    _playJingleDah();
}

void NGMorseToneGenerator::playLetterR() {
    _playJingleDit();
    _playJingleDah();
    _playJingleDit();
}

void NGMorseToneGenerator::playLetterS() {
    for (int i = 0; i < 3; i++) {
        _playJingleDit();
    }
}

void NGMorseToneGenerator::playLetterT() {
    _playJingleDah();
}

void NGMorseToneGenerator::playLetterU() {
    for (int i = 0; i < 2; i++) {
        _playJingleDit();
    }
    _playJingleDah();
}

void NGMorseToneGenerator::playLetterV() {
    for (int i = 0; i < 3; i++) {
        _playJingleDit();
    }
    _playJingleDah();
}

void NGMorseToneGenerator::playLetterW() {
    _playJingleDit();
    for (int i = 0; i < 2; i++) {
        _playJingleDah();
    }
}

void NGMorseToneGenerator::playLetterX() {
    _playJingleDah();
    for (int i = 0; i < 2; i++) {
        _playJingleDit();
    }
    _playJingleDah();
}

void NGMorseToneGenerator::playLetterY() {
    _playJingleDah();
    _playJingleDit();
    for (int i = 0; i < 2; i++) {
        _playJingleDah();
    }
}

void NGMorseToneGenerator::playLetterZ() {
    for (int i = 0; i < 2; i++) {
        _playJingleDah();
    }
    for (int i = 0; i < 2; i++) {
        _playJingleDit();
    }
}

void NGMorseToneGenerator::playLetter(char letter) {
    String s = String(letter);
    s.toUpperCase();
    if (s == "A") {
        playLetterA();
    } else if (s == "B") {
        playLetterB();
    } else if (s == "C") {
        playLetterC();
    } else if (s == "D") {
        playLetterD();
    } else if (s == "E") {
        playLetterE();
    } else if (s == "F") {
        playLetterF();
    } else if (s == "G") {
        playLetterG();
    } else if (s == "H") {
        playLetterH();
    } else if (s == "I") {
        playLetterI();
    } else if (s == "J") {
        playLetterJ();
    } else if (s == "K") {
        playLetterK();
    } else if (s == "L") {
        playLetterL();
    } else if (s == "M") {
        playLetterM();
    } else if (s == "N") {
        playLetterN();
    } else if (s == "O") {
        playLetterO();
    } else if (s == "P") {
        playLetterP();
    } else if (s == "Q") {
        playLetterQ();
    } else if (s == "R") {
        playLetterR();
    } else if (s == "S") {
        playLetterS();
    } else if (s == "T") {
        playLetterT();
    } else if (s == "U") {
        playLetterU();
    } else if (s == "V") {
        playLetterV();
    } else if (s == "W") {
        playLetterW();
    } else if (s == "X") {
        playLetterY();
    } else if (s == "Y") {
        playLetterY();
    } else if (s == "Z") {
        playLetterZ();
    }
    if (s == " ") {
        _playJingleBreakWord();
    } else {
        _playJingleBreakLetter();
    }
}

void NGMorseToneGenerator::play(char* value) {
    for (int i = 0; i < strlen(value); i++) {
        playLetter(value[i]);
    }
}

void NGMorseToneGenerator::playSOS() {
    play("SOS");
}
