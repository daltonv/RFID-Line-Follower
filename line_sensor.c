/*
 * linefollower.cpp
 *
 *  Created on: Jan 19, 2017
 *      Author: dalto
 */


#include "line_sensor.h"

static uint16_t resultsBuffer[8];
static uint16_t irBuffer[8];

void line_sensor_init() {
    /* Initializing ADC (MCLK/1/1) */
    MAP_ADC14_enableModule();
    MAP_ADC14_initModule(ADC_CLOCKSOURCE_MCLK, ADC_PREDIVIDER_1, ADC_DIVIDER_4,0);

    /* Configuring GPIOs for Analog In */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5,
            GPIO_PIN5 | GPIO_PIN4 | GPIO_PIN3 | GPIO_PIN2 | GPIO_PIN1
                    | GPIO_PIN0, GPIO_TERTIARY_MODULE_FUNCTION);
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4,
            GPIO_PIN7 | GPIO_PIN6, GPIO_TERTIARY_MODULE_FUNCTION);

    /* Configuring ADC Memory (ADC_MEM0 - ADC_MEM7 (A0 - A7)  with repeat)
         * with internal 3.3v reference */
    MAP_ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM7, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM0,
            ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A0, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM1,
            ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A1, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM2,
            ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A2, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM3,
            ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A3, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM4,
            ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A4, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM5,
            ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A5, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM6,
            ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A6, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM7,
            ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A7, false);

    /* enable IR LED switch as output */
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P9, GPIO_PIN1);

    MAP_GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3 | GPIO_PIN4 | GPIO_PIN5);
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P6, GPIO_PIN0 | GPIO_PIN1);

    /* Configuring Sample Timer */
    MAP_ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);

    /* Enabling/Toggling Conversion */
    MAP_ADC14_enableConversion();
    MAP_ADC14_toggleConversionTrigger();

    /* Enabling interrupts */
    MAP_ADC14_enableInterrupt(ADC_INT7);
    MAP_Interrupt_enableInterrupt(INT_ADC14);
    MAP_Interrupt_enableMaster();
}


void irOn() {
    MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P9, GPIO_PIN1);
}

void irOff() {
    MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P9, GPIO_PIN1);
}

float readLineAvg() {
    int lineSum = irBuffer[0] + irBuffer[1]*2 + irBuffer[2]*3 + irBuffer[3]*4 + irBuffer[4]*5 + irBuffer[5]*6 + irBuffer[6]*7 + irBuffer[7]*8;
    float lineAvg = 0;

    if (lineSum != 0) {
        lineAvg = (float)lineSum/(irBuffer[0] + irBuffer[1] + irBuffer[2] + irBuffer[3] + irBuffer[4] + irBuffer[5] + irBuffer[6] + irBuffer[7]);
    }

    return lineAvg;
}

int detectEdge() {
    if(irBuffer[0] == 1 && irBuffer[1] == 1 && irBuffer[2] == 1 && irBuffer[3] == 1 && irBuffer[4] == 1 && irBuffer[5] == 0 && irBuffer[6] == 0 && irBuffer[7] == 0) {
        return EDGE_LEFT;
    }
    else if(irBuffer[0] == 0 && irBuffer[1] == 0 && irBuffer[2] == 0 && irBuffer[3] == 1 && irBuffer[4] == 1 && irBuffer[5] == 1 && irBuffer[6] == 1 && irBuffer[7] == 1) {
        return EDGE_RIGHT;
    }
    else if(irBuffer[0] == 1 && irBuffer[1] == 1 && irBuffer[2] == 1 && irBuffer[3] == 1 && irBuffer[4] == 1 && irBuffer[5] == 1 && irBuffer[6] == 1 && irBuffer[7] == 1) {
        return EDGE_BOTH;
    }
    else {
        return EDGE_NONE;
    }
}

/* ADC Interrupt Handler. This handler is called whenever there is a conversion
 * that is finished for ADC_MEM7.
 */
void ADC14_IRQHandler(void)
{
    uint64_t status = MAP_ADC14_getEnabledInterruptStatus();
    MAP_ADC14_clearInterruptFlag(status);

    if (ADC_INT7 & status)
    {
        MAP_ADC14_getMultiSequenceResult(resultsBuffer);

        if(resultsBuffer[0] < 3000) {
            MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN5);
            irBuffer[0] = 1;
        }
        else{
            MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN5);
            irBuffer[0] = 0;
        }

        if(resultsBuffer[1] < 4500) {
            MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN4);
            irBuffer[1] = 1;
        }
        else{
            MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);
            irBuffer[1] = 0;
        }
        if(resultsBuffer[2] < 5000) {
            MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN3);
            irBuffer[2] = 1;
        }
        else{
            MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
            irBuffer[2] = 0;
        }

        if(resultsBuffer[3] < 6000) {
            MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN2);
            irBuffer[3] = 1;
        }
        else{
            MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
            irBuffer[3] = 0;
        }
        if(resultsBuffer[4] < 7500) {
            MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN1);
            irBuffer[4] = 1;
        }
        else{
            MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN1);
            irBuffer[4] = 0;
        }
        if(resultsBuffer[5] < 7500) {
            MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN0);
            irBuffer[5] = 1;
        }
        else{
            MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0);
            irBuffer[5] = 0;
        }
        if(resultsBuffer[6] < 6000) {
            MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN1);
            irBuffer[6] = 1;
        }
        else{
            MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN1);
            irBuffer[6] = 0;
        }
        if(resultsBuffer[7] < 3000) {
            MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN0);
            irBuffer[7] = 1;
        }
        else{
            MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0);
            irBuffer[7] = 0;
        }


        MAP_ADC14_toggleConversionTrigger();
    }
}
