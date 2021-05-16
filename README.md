#  NGEngineControl

NGEngineControl is an [Arduino](http://arduino.cc) library for [eNGine Shield](https://github.com/bart4223/NGEngineControl/wiki/Engine-Control).
The code only works with eNGine Shield.

## Documentation

### NGEngineControl

The NGEngineControl class can controls 4 engines in cooperation with eNGine Shield.

#### Constructors

* NGEngineControl(int engine)

The parameter engine indicates the respective engine, possible values are ENGINE_0, ENGINE_1, ENGINE_2 and ENGINE_3. The default serialRate is DEFAULTSERIALRATE.

* NGEngineControl(int engine, int serialRate)

The parameter engine indicates the respective engine, possible values are ENGINE_0, ENGINE_1, ENGINE_2 and ENGINE_3.
ENGINE_3 controlled only speed 0(stop) or 255(fullspeed).

#### Methods

* initialize()

This method initialize the engine control. The default speed is NULLSPEED.

* initialize(int speed)

This method initialize the engine control with speed.

* setLogging(bool logging)

This method activate or deactivate the logging.

* setSpeed(int speed)

This method set the speed instantly with interval NULLINTERVAL.

* setSpeed(int speed, int interval)

This method set the speed and the interval in ms.

* run(engineDirection direction)

This method run then engine in direction edNone, edForward and edBackward.

* stop()

This mehod stop the engine with interval NULLINTERVAL.

* stop(int interval)

This mehod stop the engine with interval in ms.

### NGJointControl

The NGJointControl class can controls 3 joints in cooperation with eNGine Shield. A joint consists as an engine and a transducer for giving the radiant.

#### Constructors

* NGJointControl(int joint)

The parameter joint indicates the respective joint, possible values are JOINT_0, JOINT_1 and JOINT_2. The default serialRate is DEFAULTSERIALRATE.

* NGJointControl(int joint, int serialRate)

The parameter joint indicates the respective jointe, possible values are JOINT_0, JOINT_1 and JOINT_2.

#### Methods

* initialize(int minRad, int maxRad, int maxSpeed)

This method initialize the joint control. The default name is NONAME.

* initialize(char* name, int minRad, int maxRad, int maxSpeed)

This method initialize the joint control with a name.

* setMinJointRad(int value)

This method set the minimum joint radiant. This value is given 0 between 1024.

* getMinJointRad()

This method get back the minimum joint radiant.

* setMaxJointRad(int value)

This method set the maximum joint radiant. This value is given 0 between 1024.

* getMaxJointRad()

This method get back the maximum joint radiant.

* setMaxSpeed(int value)

This method set the maximum speed of joint. This value is given 0 between 255.

* getMaxSpeed

This method get back the maximum joint speed.

* setLogging(bool logging)

This method activate or deactivate the logging.

* getName()

This method give back the name of joint.

* read()

This method give back the current radiant of joint.

* move(int targetRad)

This method move the joint to given radiant.

* simulate()

This method move the joint to the minimum or maximum.

## Download

## Install
