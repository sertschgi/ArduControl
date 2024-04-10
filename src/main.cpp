#include <Arduino.h>
#include "modules/Robot.hpp"
#include "modules/Servo.hpp"
#include "modules/Debug.hpp"

using namespace Impl;

#define BAUD_RATE 19200
#define SERVO_PIN 7

#define DEBUG 1

#ifdef BIGPROTO
    #include "modules/Miller.hpp"
    #include "modules/BigMotor.hpp"

    #define CAMERA_HEIGHT 20
    #define CAMERA_FOV_V 48.8
    #define CAMERA_FOV_H 62.2

    #define MOTOR_L_PIN_A 9
    #define MOTOR_L_PIN_B 10
    #define MOTOR_L_PIN_DC 8
    #define MOTOR_L_PIN_HALL 2

    #define MOTOR_R_PIN_A 12
    #define MOTOR_R_PIN_B 11
    #define MOTOR_R_PIN_DC 13
    #define MOTOR_R_PIN_HALL 3

    #define MOTOR_RESPONSE 100

    #define ROTATION_PULSES 6
    #define WHEEL_CIRCUMFERENCE 30
    #define MOTOR_DISTANCE 50
    #define GEAR_RATIO 1

    #define MILLING_CYCLES 3
    #define MILL_OUT_PERCENT 0.20
    #define SLOW_DOWN_TO 100

    LinearMotor linearMotor(LINEAR_MOTOR_PIN_1, LINEAR_MOTOR_PIN_2, LINEAR_MOTOR_PIN_EXT_TIME);
    MillMotor millMotor(MILL_MOTOR_PIN_1, MILL_MOTOR_PIN_2);

    Miller miller(linearMotor, millMotor);

    SmallMotor motorL(MOTOR_L_PIN_A,
                 MOTOR_L_PIN_DC,
                 MOTOR_L_PIN_HALL,
                 ROTATION_PULSES
    );
    SmallMotor motorR(MOTOR_R_PIN_A,
                 MOTOR_R_PIN_DC,
                 MOTOR_R_PIN_HALL,
                 ROTATION_PULSES
    );

#else
    #include "modules/SmallMotor.hpp"

    #define CAMERA_HEIGHT 20
    #define CAMERA_FOV_V 48.8
    #define CAMERA_FOV_H 62.2

    #define MOTOR_L_PIN_A 9
    #define MOTOR_L_PIN_B 10
    #define MOTOR_L_PIN_DC 8
    #define MOTOR_L_PIN_HALL 2

    #define MOTOR_R_PIN_A 12
    #define MOTOR_R_PIN_B 11
    #define MOTOR_R_PIN_DC 13
    #define MOTOR_R_PIN_HALL 3

    #define MOTOR_RESPONSE 100

    #define ROTATION_PULSES 6
    #define WHEEL_CIRCUMFERENCE 10
    #define MOTOR_DISTANCE 30
    #define GEAR_RATIO 1

    #define SERVO_MIN 544
    #define SERVO_MAX 1100

    SmallMotor motorL(MOTOR_L_PIN_A,
                 MOTOR_L_PIN_B,
                 MOTOR_L_PIN_DC,
                 MOTOR_L_PIN_HALL,
                 ROTATION_PULSES
    );
    SmallMotor motorR(MOTOR_R_PIN_A,
                 MOTOR_R_PIN_B,
                 MOTOR_R_PIN_DC,
                 MOTOR_R_PIN_HALL,
                 ROTATION_PULSES
    );
#endif

Robot robot(motorL, motorR, WHEEL_CIRCUMFERENCE, MOTOR_DISTANCE, GEAR_RATIO);
Servo servo;// servo(7);

void parseArgs(String argv[], String & str)
{
    Serial.write("\nString: ");
    Serial.write(str.c_str());
    Serial.flush();

    int argc = 0;

    size_t lastCut = str.length();

    for (int32_t i = str.length()-1; i > -1; i--)
    {
//        Serial.write("\nArg: ");
//        Serial.write(String(str[i]).c_str());
//        Serial.flush();
        if (str[i] == ';')
        {
            argv[argc++] = str.substring(i+1, lastCut);
            lastCut = i;
        }
    }
}

void caseR(String argStr)
{
    String argv[4];
    parseArgs(argv, argStr);

    uint16_t xmin = argv[3].toInt();
    uint16_t ymin = argv[2].toInt();
    uint16_t height = argv[1].toInt();
    uint16_t width = argv[0].toInt();

    Debug::debug("\nARRAY: ");
    for (const String & i : argv)
    {
        Debug::debug(i);
        Debug::debug(",");
    }

    uint16_t middlePX = xmin + width/2;
    uint16_t middlePY = ymin + height/2;

//    uint16_t middleX = xmin + width/2;
//    uint16_t middleY = ymin + height/2;

//    uint16_t middlePX = middleX*1000/WIDTH;
//    uint16_t middlePY = middleY*1000/HEIGHT;

    int32_t offsetPX = -(50 - middlePX) * 2;
//    int32_t offsetPY = -(50 - middlePY) * 2;

    double distancePictureXBegin = tan((servo.read()-CAMERA_FOV_V/2) * DEG_TO_RAD) * CAMERA_HEIGHT;
    double distancePictureXEnd = tan((servo.read()+CAMERA_FOV_V/2) * DEG_TO_RAD) * CAMERA_HEIGHT;

//    Serial.write("\nServo-Angle: ");
//    Serial.write(String(servo.read()).c_str());
//    Serial.flush();
//
//    Serial.write("\nDPB: ");
//    Serial.write(String(distancePictureXBegin).c_str());
//    Serial.flush();
//
//    Serial.write("\nDPE: ");
//    Serial.write(String(distancePictureXEnd).c_str());
//    Serial.flush();

    double distanceX = middlePY * (distancePictureXEnd-distancePictureXBegin) / 1000 + distancePictureXBegin;
    double distanceZ = offsetPX * tan(CAMERA_FOV_H * DEG_TO_RAD) * distanceX / 1000;

//    Serial.write("\nDX: ");
//    Serial.write(String(distanceX).c_str());
//    Serial.flush();
//
//    Serial.write("\nDZ: ");
//    Serial.write(String(distanceZ).c_str());
//    Serial.flush();

    double distance = sqrt(pow(distanceX, 2) + pow(distanceZ, 2));

    int16_t angle = atan(distanceZ/distanceX) * RAD_TO_DEG;

    int16_t servoAngle = min(90, atan(distanceX/CAMERA_HEIGHT) * RAD_TO_DEG);

    servo.write(servoAngle);
    if (servoAngle < 3) {
//        Serial.write("Milling...");
        #ifdef BIGPROTO
        miller.startMillingSequence(MILLING_CYCLES, MILL_OUT_PERCENT, SLOW_DOWN_TO);
        #endif
        servo.write(90-(int)CAMERA_FOV_V);
    }

    robot.rotate(angle, 100);
//    delay(MOTOR_RESPONSE);
//    Serial.write("\nAngle: ");
//    Serial.write(String(angle).c_str());
    while (robot.driving())
    {
        Debug::debug("\nDriving: ");
        Debug::debug(distance);
    }
    Debug::debug("\nDistance: ");
    Debug::debug(String(distance).c_str());
    robot.driveDistance(distance, 100);
}

void pulse1 ()
{
    motorL.pulseCall();
}

void pulse2 ()
{
    motorR.pulseCall();
}

void MotorTest(Motor & motor)
{
    motor.drive(80);
    delay(1000);
    motor.stop();
}

void ServoTest(Servo & sv)
{
    sv.write(90);
    delay(1000);
    sv.write(0);
    delay(1000);
    sv.write(90-(int)CAMERA_FOV_V);
    delay(1000);
}

void setup()
{
    Debug::setup(BAUD_RATE, DEBUG);
    Serial1.begin(BAUD_RATE);
    servo.attach(SERVO_PIN, SERVO_MIN, SERVO_MAX);
    motorL.setup(pulse1);
    motorR.setup(pulse2);
    delay(1000);
    Debug::debug("\nMotor left test.\n");
    MotorTest(motorL);
    Debug::debug("\nMotor right test.\n");
    MotorTest(motorR);
    Debug::debug("\nServo test.\n");
    ServoTest(servo);
}

void loop()
{
    if (Serial1.available())
    {
        String rawStr = Serial1.readStringUntil('\n');
        if (rawStr.length() > 0)
        {
//        Serial.write("\nRaw: ");
//        Serial.write(rawStr.c_str());
//        Serial.flush();

            char discr = rawStr[0];
            rawStr = rawStr.substring(1);

            Debug::debug("\nRaw: ");
            Debug::debug(rawStr.c_str());



            switch (discr)
            {
                case 'R':
                    caseR(rawStr);
                    break;
                case 'D':
                    for (uint16_t i = 0; i < rawStr.length(); ++i)
                    {
                        if (rawStr[i] == ';')
                        {
                            motorR.drive(rawStr.substring(i + 1).toInt());
                            motorL.drive(rawStr.substring(0, i).toInt());
                            Debug::debug("\nsr1: ");
                            Debug::debug(rawStr.substring(i + 1).toInt());
                            Debug::debug("\nsr2: ");
                            Debug::debug(rawStr.substring(0, i).toInt());
                        }
                    }
                    break;
            }
        }
    }
}