//
//  NGMotionSequenceDefinitions.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 14.10.21.
//

#ifndef NGMotionSequenceDefinitions_h
#define NGMotionSequenceDefinitions_h

#define DEF_MOTION_SEQUENCE_START byte MotionSequence = -1

#define DEF_MOTION_SEQUENCE_BEGIN_STRAIGHT(unitMotion) MotionSequence = unitMotion.registerMotionSequence(mskStraight)
#define DEF_MOTION_SEQUENCE_END_STRAIGHT MotionSequence = -1
#define DEF_MOTION_SEQUENCE_BEGIN_BACK(unitMotion) MotionSequence = unitMotion.registerMotionSequence(mskBack)
#define DEF_MOTION_SEQUENCE_END_BACK MotionSequence = -1
#define DEF_MOTION_SEQUENCE_BEGIN_LEFT(unitMotion) MotionSequence = unitMotion.registerMotionSequence(mskLeft)
#define DEF_MOTION_SEQUENCE_END_LEFT MotionSequence = -1
#define DEF_MOTION_SEQUENCE_BEGIN_RIGHT(unitMotion) MotionSequence = unitMotion.registerMotionSequence(mskRight)
#define DEF_MOTION_SEQUENCE_END_RIGHT MotionSequence = -1
#define DEF_MOTION_SEQUENCE_BEGIN_STOP(unitMotion) MotionSequence = unitMotion.registerMotionSequence(mskStop)
#define DEF_MOTION_SEQUENCE_END_STOP MotionSequence = -1
#define DEF_MOTION_SEQUENCE_BEGIN_FULLTURN(unitMotion) MotionSequence = unitMotion.registerMotionSequence(mskFullTurn)
#define DEF_MOTION_SEQUENCE_END_FULLTURN MotionSequence = -1

// Foward
#define DEF_MOTION_SEQUENCE_FORWARD(unitMotion, Speed, Time) unitMotion.addMotionSequenceItem(MotionSequence, Speed, edForward, tdNone, Time)
#define DEF_MOTION_SEQUENCE_FORWARD_WITH_LIGHTLEFT(unitMotion, Speed, Time) unitMotion.addMotionSequenceItem(MotionSequence, Speed, edForward, tdNone, Time, flsLeft);
#define DEF_MOTION_SEQUENCE_FORWARD_WITH_LIGHTRIGHT(unitMotion, Speed, Time) unitMotion.addMotionSequenceItem(MotionSequence, Speed, edForward, tdNone, Time, flsRight);
#define DEF_MOTION_SEQUENCE_FORWARD_WITH_BRAKE(unitMotion, Speed, Time) unitMotion.addMotionSequenceItem(MotionSequence, Speed, edForward, tdNone, Time, flsBrake);

#define DEF_MOTION_SEQUENCE_FORWARD_LEFT_WITH_LIGHT(unitMotion, Speed, Time) unitMotion.addMotionSequenceItem(MotionSequence, Speed, edForward, tdLeftSoft, Time, flsLeft);
#define DEF_MOTION_SEQUENCE_FORWARD_LEFT2_WITH_LIGHT(unitMotion, Speed, Time) unitMotion.addMotionSequenceItem(MotionSequence, Speed, edForward, tdLeft, Time, flsLeft);
#define DEF_MOTION_SEQUENCE_FORWARD_RIGHT_WITH_LIGHT(unitMotion, Speed, Time) unitMotion.addMotionSequenceItem(MotionSequence, Speed, edForward, tdRightSoft, Time, flsRight);
#define DEF_MOTION_SEQUENCE_FORWARD_RIGHT2_WITH_LIGHT(unitMotion, Speed, Time) unitMotion.addMotionSequenceItem(MotionSequence, Speed, edForward, tdRight, Time, flsRight);

// Backward
#define DEF_MOTION_SEQUENCE_BACKWARD(unitMotion, Speed, Time) unitMotion.addMotionSequenceItem(MotionSequence, Speed, edBackward, tdNone, Time)
#define DEF_MOTION_SEQUENCE_BACKWARD_WITH_LIGHTLEFT(unitMotion, Speed, Time) unitMotion.addMotionSequenceItem(MotionSequence, Speed, edBackward, tdNone, Time, flsLeft);
#define DEF_MOTION_SEQUENCE_BACKWARD_WITH_LIGHTRIGHT(unitMotion, Speed, Time) unitMotion.addMotionSequenceItem(MotionSequence, Speed, edBackward, tdNone, Time, flsRight);
#define DEF_MOTION_SEQUENCE_BACKWARD_WITH_BRAKE(unitMotion, Speed, Time) unitMotion.addMotionSequenceItem(MotionSequence, Speed, edBackward, tdNone, Time, flsBrake);

#define DEF_MOTION_SEQUENCE_BACKWARD_LEFT_WITH_LIGHT(Speed, Time) unitMotion.addMotionSequenceItem(MotionSequence, Speed, edBackward, tdLeftSoft, Time, flsLeft);
#define DEF_MOTION_SEQUENCE_BACKWARD_LEFT2_WITH_LIGHT(Speed, Time) unitMotion.addMotionSequenceItem(MotionSequence, Speed, edBackward, tdLeft, Time, flsLeft);
#define DEF_MOTION_SEQUENCE_BACKWARD_RIGHT_WITH_LIGHT(Speed, Time) unitMotion.addMotionSequenceItem(MotionSequence, Speed, edBackward, tdRightSoft, Time, flsRight);
#define DEF_MOTION_SEQUENCE_BACKWARD_RIGHT2_WITH_LIGHT(Speed, Time) unitMotion.addMotionSequenceItem(MotionSequence, Speed, edBackward, tdRight, Time, flsRight);

// Stop
#define DEF_MOTION_SEQUENCE_STOP(unitMotion, Time) unitMotion.addMotionSequenceItemStop(MotionSequence, Time)
#define DEF_MOTION_SEQUENCE_STOP_WITH_BRAKE(unitMotion, Time) unitMotion.addMotionSequenceItemStop(MotionSequence, Time, flsBrake)
#define DEF_MOTION_SEQUENCE_STOP_NONE(unitMotion, Time) unitMotion.addMotionSequenceItemStop(MotionSequence, Time, flsNone)

// FullTurn
#define DEF_MOTION_SEQUENCE_FULLTURN(unitMotion, Speed, Time) unitMotion.addMotionSequenceItem(MotionSequence, Speed, edForward, tdRight, Time, flsNone);

#endif /* NGMotionSequenceDefinitions_h */
