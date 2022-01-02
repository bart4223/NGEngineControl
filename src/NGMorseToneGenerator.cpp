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

void NGMorseToneGenerator::_playLetter(byte letter) {
    if (letter == 0x41 || letter == 0x61) {
        playLetterA();
    } else if (letter == 0x42 || letter == 0x62) {
        playLetterB();
    } else if (letter == 0x43 || letter == 0x63) {
        playLetterC();
    } else if (letter == 0x44 || letter == 0x64) {
        playLetterD();
    } else if (letter == 0x45 || letter == 0x65) {
        playLetterE();
    } else if (letter == 0x46 || letter == 0x66) {
        playLetterF();
    } else if (letter == 0x47 || letter == 0x67) {
        playLetterG();
    } else if (letter == 0x48 || letter == 0x68) {
        playLetterH();
    } else if (letter == 0x49 || letter == 0x69) {
        playLetterI();
    } else if (letter == 0x4A || letter == 0x6A) {
        playLetterJ();
    } else if (letter == 0x4B || letter == 0x6B) {
        playLetterK();
    } else if (letter == 0x4C || letter == 0x6C) {
        playLetterL();
    } else if (letter == 0x4D || letter == 0x6D) {
        playLetterM();
    } else if (letter == 0x4E || letter == 0x6E) {
        playLetterN();
    } else if (letter == 0x4F || letter == 0x6F) {
        playLetterO();
    } else if (letter == 0x50 || letter == 0x70) {
        playLetterP();
    } else if (letter == 0x51 || letter == 0x71) {
        playLetterQ();
    } else if (letter == 0x52 || letter == 0x72) {
        playLetterR();
    } else if (letter == 0x53 || letter == 0x73) {
        playLetterS();
    } else if (letter == 0x54 || letter == 0x74) {
        playLetterT();
    } else if (letter == 0x55 || letter == 0x75) {
        playLetterU();
    } else if (letter == 0x56 || letter == 0x76) {
        playLetterV();
    } else if (letter == 0x57 || letter == 0x77) {
        playLetterW();
    } else if (letter == 0x58 || letter == 0x78) {
        playLetterY();
    } else if (letter == 0x59 || letter == 0x79) {
        playLetterY();
    } else if (letter == 0x5A || letter == 0x7A) {
        playLetterZ();
    } else if (letter == 0x84 || letter == 0xA4) {
        playLetterAe();
    } else if (letter == 0x96 || letter == 0xB6) {
        playLetterOe();
    } else if (letter == 0x9C || letter == 0xBC) {
        playLetterUe();
    } else if (letter == 0x9F) {
        playLetterSz();
    } else if (letter == 0x31) {
        playDigit1();
    } else if (letter == 0x32) {
        playDigit2();
    } else if (letter == 0x33) {
        playDigit3();
    } else if (letter == 0x34) {
        playDigit4();
    } else if (letter == 0x35) {
        playDigit5();
    } else if (letter == 0x36) {
        playDigit6();
    } else if (letter == 0x37) {
        playDigit7();
    } else if (letter == 0x38) {
        playDigit8();
    } else if (letter == 0x39) {
        playDigit9();
    } else if (letter == 0x30) {
        playDigit0();
    } else if (letter == 0x2E) {
        playSignPoint();
    } else if (letter == 0x2C) {
        playSignComma();
    } else if (letter == 0x3A) {
        playSignDoublePoint();
    } else if (letter == 0x3B) {
        playSignSemicolon();
    } else if (letter == 0x3F) {
        playSignQuestionMark();
    } else if (letter == 0x21) {
        playSignExclamationMark();
    } else if (letter == 0x2D) {
        playSignHyphen();
    } else if (letter == 0x5F) {
        playSignUnderscore();
    } else if (letter == 0x28) {
        playSignBracketOpen();
    } else if (letter == 0x29) {
        playSignBracketClose();
    } else if (letter == 0x27) {
        playSignApostrophe();
    } else if (letter == 0x22) {
        playSignQuotationMarks();
    } else if (letter == 0x3D) {
        playSignEqualSign();
    } else if (letter == 0x2B) {
        playSignPlus();
    } else if (letter == 0x2F) {
        playSignSlash();
    } else if (letter == 0x40) {
        playSignCommercialA();
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

void NGMorseToneGenerator::playLetterAe() {
    _playJingleDit();
    _playJingleDah();
    _playJingleDit();
    _playJingleDah();
}

void NGMorseToneGenerator::playLetterOe() {
    for (int i = 0; i < 3; i++) {
        _playJingleDah();
    }
    _playJingleDit();
}

void NGMorseToneGenerator::playLetterUe() {
    for (int i = 0; i < 2; i++) {
        _playJingleDit();
    }
    for (int i = 0; i < 2; i++) {
        _playJingleDah();
    }
}

void NGMorseToneGenerator::playLetterSz() {
    for (int i = 0; i < 3; i++) {
        _playJingleDit();
    }
    for (int i = 0; i < 2; i++) {
        _playJingleDah();
    }
    for (int i = 0; i < 2; i++) {
        _playJingleDit();
    }
}

void NGMorseToneGenerator::playDigit1() {
    _playJingleDit();
    for (int i = 0; i < 4; i++) {
        _playJingleDah();
    }
}

void NGMorseToneGenerator::playDigit2() {
    for (int i = 0; i < 2; i++) {
        _playJingleDit();
    }
    for (int i = 0; i < 3; i++) {
        _playJingleDah();
    }
}

void NGMorseToneGenerator::playDigit3() {
    for (int i = 0; i < 3; i++) {
        _playJingleDit();
    }
    for (int i = 0; i < 2; i++) {
        _playJingleDah();
    }
}

void NGMorseToneGenerator::playDigit4() {
    for (int i = 0; i < 4; i++) {
        _playJingleDit();
    }
    _playJingleDah();
}

void NGMorseToneGenerator::playDigit5() {
    for (int i = 0; i < 5; i++) {
        _playJingleDit();
    }
}

void NGMorseToneGenerator::playDigit6() {
    _playJingleDah();
    for (int i = 0; i < 4; i++) {
        _playJingleDit();
    }
}

void NGMorseToneGenerator::playDigit7() {
    for (int i = 0; i < 2; i++) {
        _playJingleDah();
    }
    for (int i = 0; i < 3; i++) {
        _playJingleDit();
    }
}

void NGMorseToneGenerator::playDigit8() {
    for (int i = 0; i < 3; i++) {
        _playJingleDah();
    }
    for (int i = 0; i < 2; i++) {
        _playJingleDit();
    }
}

void NGMorseToneGenerator::playDigit9() {
    for (int i = 0; i < 4; i++) {
        _playJingleDah();
    }
    _playJingleDit();
}

void NGMorseToneGenerator::playDigit0() {
    for (int i = 0; i < 5; i++) {
        _playJingleDah();
    }
}

void NGMorseToneGenerator::playSignPoint() {
    for (int i = 0; i < 3; i++) {
        _playLetter(0x41);
    }
}

void NGMorseToneGenerator::playSignComma() {
    _playLetter(0x4D);
    _playLetter(0x49);
    _playLetter(0x4D);
}

void NGMorseToneGenerator::playSignDoublePoint() {
    _playLetter(0x4F);
    _playLetter(0x53);
}

void NGMorseToneGenerator::playSignSemicolon() {
    for (int i = 0; i < 3; i++) {
        _playLetter(0x4E);
    }
}

void NGMorseToneGenerator::playSignQuestionMark() {
    _playLetter(0x49);
    _playLetter(0x4D);
    _playLetter(0x49);
}

void NGMorseToneGenerator::playSignExclamationMark() {
    _playJingleDah();
    _playJingleDit();
    _playJingleDah();
    _playJingleDit();
    for (int i = 0; i < 2; i++) {
        _playJingleDah();
    }
}

void NGMorseToneGenerator::playSignHyphen() {
    _playLetter(0x42);
    _playLetter(0x41);
}

void NGMorseToneGenerator::playSignUnderscore() {
    _playLetter(0x55);
    _playLetter(0x4B);
}

void NGMorseToneGenerator::playSignBracketOpen() {
    _playLetter(0x4B);
    _playLetter(0x4E);
}

void NGMorseToneGenerator::playSignBracketClose() {
    _playLetter(0x4B);
    _playLetter(0x4B);
}

void NGMorseToneGenerator::playSignApostrophe() {
    _playLetter(0x4A);
    _playLetter(0x4E);
}

void NGMorseToneGenerator::playSignQuotationMarks() {
    int t = _tempo;
    if (_jingleDit >= 0) {
        _tempo = _sm->getDefaultTempo(_jingleDit) / 2;
    }
    _playJingleDit();
    _tempo = t;
}

void NGMorseToneGenerator::playSignEqualSign() {
    _playLetter(0x42);
    _playLetter(0x54);
}

void NGMorseToneGenerator::playSignPlus() {
    _playLetter(0x41);
    _playLetter(0x52);
}

void NGMorseToneGenerator::playSignSlash() {
    _playLetter(0x44);
    _playLetter(0x4E);
}

void NGMorseToneGenerator::playSignCommercialA() {
    _playLetter(0x41);
    _playLetter(0x43);
}

void NGMorseToneGenerator::playLetter(byte letter) {
    _playLetter(letter);
    if (letter == 0x20) {
        _playJingleBreakWord();
    } else {
        _playJingleBreakLetter();
    }
}

void NGMorseToneGenerator::play(char* value) {
    bool twobytes = false;
    for (int i = 0; i < strlen(value); i++) {
        byte b = value[i];
        if (!twobytes) {
            twobytes = b > 0x80;
            if (!twobytes) {
                playLetter(b);
            }
        } else {
            playLetter(b);
            twobytes = false;
        }
    }
}

void NGMorseToneGenerator::playSOS() {
    play("SOS");
}

void NGMorseToneGenerator::playQAM() {
    play("QAM");
}

void NGMorseToneGenerator::playCQ(char* name) {
    char text[100];
    sprintf(text, "cq cq cq de %s %s %s pse k", name, name, name);
    play(text);
}
