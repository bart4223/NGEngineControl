//
//  NGSerialNotification.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 11.06.21.
//

#ifndef NGSerialNotification_h
#define NGSerialNotification_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomNotification.h>

class NGSerialNotification : public NGCustomNotification {

private:
    int _serialRate;
  
protected:
    void _create(int serialRate);

public:
    NGSerialNotification();
    NGSerialNotification(int serialRate);
    void initialize();
    char* getName();
    void writeInfo(char* info);

};

#endif /* NGSerialNotification_h */
