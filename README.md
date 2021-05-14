#  NGEngineControl

NGEngineControl is an [Arduino](http://arduino.cc) library for [eNGine Shield](https://github.com/bart4223/NGEngineControl/wiki/Engine-Control).
The code only works with eNGine Shield.

## Documentation

### NGEngineControl

#### Constructor

* NGEngineControl(int engine)

The parameter engine indicates the respective engine, possible values are ENGINE_0, ENGINE_1 and ENGINE_2. The default serialRate is DEFAULTSERIALRATE.

* NGEngineControl(int engine, int serialRate)

The parameter engine indicates the respective engine, possible values are ENGINE_0, ENGINE_1 and ENGINE_2.

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

#### Constructor

#### Methods

## Download

## Install
