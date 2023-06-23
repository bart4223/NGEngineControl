//
//  NGBluetoothRemoteUnitControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 19.06.23.
//

#include "NGCommon.h"
#include "NGBluetoothRemoteUnitControl.h"

NGBluetoothRemoteUnitControl::NGBluetoothRemoteUnitControl() {
    _create(NONAME, NOADDRESS, DEFAULTSERIALRATE);
}

NGBluetoothRemoteUnitControl::NGBluetoothRemoteUnitControl(char* name) {
    _create(name, NOADDRESS, DEFAULTSERIALRATE);
}
              
NGBluetoothRemoteUnitControl::NGBluetoothRemoteUnitControl(char* name, byte address) {
    _create(name, address, DEFAULTSERIALRATE);
}

NGBluetoothRemoteUnitControl::NGBluetoothRemoteUnitControl(char* name, byte address, int serialRate) {
    _create(name, address, serialRate);
}

void NGBluetoothRemoteUnitControl::_create(char* name, byte address, int serialRate) {
    NGWirelessRemoteUnitControl::_create(name, address, serialRate);
    _version = BTVERSION;
}

void NGBluetoothRemoteUnitControl::processingLoop() {
    NGWirelessRemoteUnitControl::processingLoop();
    for (int i = 0; i < _remoteControlCount; i++) {
        switch(_remoteControls[i].kind) {
            case wrckJoystick:
                if (_remoteControls[i].joystick->hasLastMovement()) {
                    Serial.println(_remoteControls[i].joystick->getLastValue());
                }
                break;
        }
    }
}
