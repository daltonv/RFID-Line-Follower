/*
 * linefollower.cpp
 *
 *  Created on: Jan 19, 2017
 *      Author: dalto
 */


#include <LineSensor.h>

static uint16_t resultsBuffer[8];

LineSensor::LineSensor() {
    /* Initializing ADC (MCLK/1/1) */
    MAP_ADC14_enableModule();
    MAP_ADC14_initModule(ADC_CLOCKSOURCE_MCLK, ADC_PREDIVIDER_1, ADC_DIVIDER_1,0);

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
LineSensor::~LineSensor() {

}

void LineSensor::irOn() {
    MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P9, GPIO_PIN1);
}

void LineSensor::irOff() {
    MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P9, GPIO_PIN1);
}

/* this has to be placed around interrupt vectors for them to work in C++ files*/
extern "C" {
    /* ADC Interrupt Handler. This handler is called whenever there is a conversion
     * that is finished for ADC_MEM0.
     */
    void ADC14_IRQHandler(void)
    {
        uint64_t status = MAP_ADC14_getEnabledInterruptStatus();
        MAP_ADC14_clearInterruptFlag(status);

        if (ADC_INT7 & status)
        {
            MAP_ADC14_getMultiSequenceResult(resultsBuffer);

            //curADCResult = MAP_ADC14_getResult(ADC_MEM0);
            //normalizedADCRes = (curADCResult * 3.3) / 16384;

            //printf(EUSCI_A0_BASE, "ADCResult:   %i\r\n", curADCResult);

            MAP_ADC14_toggleConversionTrigger();
        }
    }
}
