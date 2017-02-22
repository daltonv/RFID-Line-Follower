/*
 * MotorControl.cpp
 *
 *  Created on: Jan 26, 2017
 *      Author: dalto
 */

#include <MotorControl.h>

MotorControl::MotorControl() : leftMotor(TIMER_A_CAPTURECOMPARE_REGISTER_1, TIMER_A_CAPTURECOMPARE_REGISTER_2),
                               rightMotor(TIMER_A_CAPTURECOMPARE_REGISTER_3, TIMER_A_CAPTURECOMPARE_REGISTER_4)
{
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN5 + GPIO_PIN4 + GPIO_PIN6 + GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);
}

MotorControl::~MotorControl()
{
    // TODO Auto-generated destructor stub
}

void MotorControl::straight(int speed) {
    this->leftMotor.setSpeed(speed);
    this->rightMotor.setSpeed(speed);
}

void MotorControl::turnLeftHard(int speed) {
    this->leftMotor.setSpeed(speed);
    this->rightMotor.setSpeed(0);
}

void MotorControl::turnRightHard(int speed) {
    this->leftMotor.setSpeed(0);
    this->rightMotor.setSpeed(speed);
}

void MotorControl::stop() {
    this->leftMotor.setSpeed(0);
    this->rightMotor.setSpeed(0);
}
