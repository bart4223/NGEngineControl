//
//  NGMotionSequenceDefinitions.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 14.10.21.
//

#ifndef NGMotionSequenceDefinitions_h
#define NGMotionSequenceDefinitions_h

#define DEF_MOTION_SEQUENCE_START byte MotionSequence = -1

#define DEF_MOTION_SEQUENCE_BEGIN_STRAIGHT MotionSequence = unitMotion.registerMotionSequence(mskStraight)
#define DEF_MOTION_SEQUENCE_END_STRAIGHT MotionSequence = -1
#define DEF_MOTION_SEQUENCE_BEGIN_BACK MotionSequence = unitMotion.registerMotionSequence(mskBack)
#define DEF_MOTION_SEQUENCE_END_BACK MotionSequence = -1
#define DEF_MOTION_SEQUENCE_BEGIN_LEFT MotionSequence = unitMotion.registerMotionSequence(mskLeft)
#define DEF_MOTION_SEQUENCE_END_LEFT MotionSequence = -1
#define DEF_MOTION_SEQUENCE_BEGIN_RIGHT MotionSequence = unitMotion.registerMotionSequence(mskRight)
#define DEF_MOTION_SEQUENCE_END_RIGHT MotionSequence = -1
#define DEF_MOTION_SEQUENCE_BEGIN_STOP MotionSequence = unitMotion.registerMotionSequence(mskStop)
#define DEF_MOTION_SEQUENCE_END_STOP MotionSequence = -1

// Foward
#define DEF_MOTION_SEQUENCE_FORWARD(Speed, Time) unitMotion.addMotionSequenceItem(MotionSequence, Speed, edForward, tdNone, Time)
#define DEF_MOTION_SEQUENCE_FORWARD_WITH_LIGHTLEFT(Speed, Time) unitMotion.addMotionSequenceItem(MotionSequence, Speed, edForward, tdNone, Time, flsLeft);
#define DEF_MOTION_SEQUENCE_FORWARD_WITH_LIGHTRIGHT(Speed, Time) unitMotion.addMotionSequenceItem(MotionSequence, Speed, edForward, tdNone, Time, flsRight);
#define DEF_MOTION_SEQUENCE_FORWARD_WITH_BRAKE(Speed, Time) unitMotion.addMotionSequenceItem(MotionSequence, Speed, edForward, tdNone, Time, flsBrake);

#define DEF_MOTION_SEQUENCE_FORWARD_LEFT_WITH_LIGHT(Speed, Time) unitMotion.addMotionSequenceItem(MotionSequence, Speed, edForward, tdLeftSoft, Time, flsLeft);
#define DEF_MOTION_SEQUENCE_FORWARD_LEFT2_WITH_LIGHT(Speed, Time) unitMotion.addMotionSequenceItem(MotionSequence, Speed, edForward, tdLeft, Time, flsLeft);
#define DEF_MOTION_SEQUENCE_FORWARD_RIGHT_WITH_LIGHT(Speed, Time) unitMotion.addMotionSequenceItem(MotionSequence, Speed, edForward, tdRightSoft, Time, flsRight);
#define DEF_MOTION_SEQUENCE_FORWARD_RIGHT2_WITH_LIGHT(Speed, Time) unitMotion.addMotionSequenceItem(MotionSequence, Speed, edForward, tdRight, Time, flsRight);

// Backward
#define DEF_MOTION_SEQUENCE_BACKWARD(Speed, Time) unitMotion.addMotionSequenceItem(MotionSequence, Speed, edBackward, tdNone, Time)
#define DEF_MOTION_SEQUENCE_BACKWARD_WITH_LIGHTLEFT(Speed, Time) unitMotion.addMotionSequenceItem(MotionSequence, Speed, edBackward, tdNone, Time, flsLeft);
#define DEF_MOTION_SEQUENCE_BACKWARD_WITH_LIGHTRIGHT(Speed, Time) unitMotion.addMotionSequenceItem(MotionSequence, Speed, edBackward, tdNone, Time, flsRight);
#define DEF_MOTION_SEQUENCE_BACKWARD_WITH_BRAKE(Speed, Time) unitMotion.addMotionSequenceItem(MotionSequence, Speed, edBackward, tdNone, Time, flsBrake);

#define DEF_MOTION_SEQUENCE_BACKWARD_LEFT_WITH_LIGHT(Speed, Time) unitMotion.addMotionSequenceItem(MotionSequence, Speed, edBackward, tdLeftSoft, Time, flsLeft);
#define DEF_MOTION_SEQUENCE_BACKWARD_LEFT2_WITH_LIGHT(Speed, Time) unitMotion.addMotionSequenceItem(MotionSequence, Speed, edBackward, tdLeft, Time, flsLeft);
#define DEF_MOTION_SEQUENCE_BACKWARD_RIGHT_WITH_LIGHT(Speed, Time) unitMotion.addMotionSequenceItem(MotionSequence, Speed, edBackward, tdRightSoft, Time, flsRight);
#define DEF_MOTION_SEQUENCE_BACKWARD_RIGHT2_WITH_LIGHT(Speed, Time) unitMotion.addMotionSequenceItem(MotionSequence, Speed, edBackward, tdRight, Time, flsRight);

// Stop
#define DEF_MOTION_SEQUENCE_STOP(Time) unitMotion.addMotionSequenceItemStop(MotionSequence, Time)
#define DEF_MOTION_SEQUENCE_STOP_WITH_BRAKE(Time) unitMotion.addMotionSequenceItemStop(MotionSequence, Time, flsBrake)
#define DEF_MOTION_SEQUENCE_STOP_NONE(Time) unitMotion.addMotionSequenceItemStop(MotionSequence, Time, flsNone)

#endif /* NGMotionSequenceDefinitions_h */
