#include "PWMOutput.h"

My::PWMOutput::PWMOutput(const int &chipNumber, const uint8_t &pin, const float &frecuency) : 
    chipNumber_m{ chipNumber }, pin_m{ pin }, frecuency_m{ frecuency } {
    claimOutput();
}

My::PWMOutput::~PWMOutput() noexcept {
    lgGpioFree(chipNumber_m, pin_m);
}

void My::PWMOutput::set(const float &dutyCycle) {
    writeHelper(dutyCycle);
}

void My::PWMOutput::desactivate() {
    writeHelper(0);
}

void My::PWMOutput::claimOutput() {
    if (lgGpioClaimOutput(chipNumber_m, 0, pin_m, 0) != LG_OKAY) {
        throw std::runtime_error{ "Unable to claim the output" };
    }
}

void My::PWMOutput::writeHelper(const float& dutyCycle) {
    if (lgTxPwm(chipNumber_m, pin_m, frecuency_m, dutyCycle, 0, 0) != LG_OKAY) {
        throw std::runtime_error{ "Unable to manage the output" };
    }   
}
