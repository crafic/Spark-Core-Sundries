/* pulseIn Function for the Spark Core - Version 0.1 (Beta)
 * Copyright (2014) Timothy Brown - See: LICENSE
 *
 * Due to the current timeout issues with Spark Cloud
 * this will return after 10 seconds, even if the
 * input pulse hasn't finished.
 *
 * Input: Trigger Pin, Trigger State
 * Output: Pulse Length in Microseconds (10uS to 1S)
 *
 */

unsigned long pulseIn(uint16_t pin, uint8_t state) {
    
    GPIO_TypeDef* portMask = (PIN_MAP[pin].gpio_peripheral);
    uint16_t pinMask = (PIN_MAP[pin].gpio_pin);
    unsigned long pulseCount = 0;
    unsigned long loopCount = 0;
    unsigned long loopMax = 25000000;
    
    // While the pin is *not* in the target state we make sure the timeout hasn't been reached.
    while (GPIO_ReadInputDataBit(portMask, pinMask) != state) {
        if (loopCount++ == loopMax) {
            return 0;
        }
    }
    
    // When the pin *is* in the target state we bump the counter while still keeping track of the timeout.
    while (GPIO_ReadInputDataBit(portMask, pinMask) == state) {
        if (loopCount++ == loopMax) {
            return 0;
        }
        pulseCount++;
    }
    
    // Return the pulse time in microseconds!
    return pulseCount * 0.405; // Calculated the pulseCount++ loop to be about 0.405uS in length.
}