//
//  NGNotificationSerial.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 11.06.21.
//

#ifndef NGNotificationSerial_h
#define NGNotificationSerial_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomNotification.h>

class NGNotificationSerial : public NGCustomNotification {

private:
    int _serialRate;
  
protected:
    void _create(int serialRate);

public:
    NGNotificationSerial();
    NGNotificationSerial(int serialRate);
    void initialize();
    char* getName();
    void writeInfo(char* info);

};

#endif /* NGNotificationSerial_h */
