#include "PWMOutput.h"

My::PWMOutput::PWMOutput(const int &chipNumber, const uint8_t &pin, const float &frecuency) : 
    OutputPin{ chipNumber, pin }, frecuency_m{ frecuency } {
}

void My::PWMOutput::set(const float &dutyCycle) {
    writeHelper(dutyCycle);
}

void My::PWMOutput::desactivate() {
    writeHelper(0);
}

void My::PWMOutput::writeHelper(const float& dutyCycle) {
    if (lgTxPwm(getChipNumber(), getPinNumber(), frecuency_m, dutyCycle, 0, 0) < 0) {
        throw std::runtime_error{ "Unable to manage the output" };
    }
}
