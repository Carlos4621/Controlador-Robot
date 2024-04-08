#include "OutputPin.h"

My::OutputPin::OutputPin(const int &chipNumber, const uint8_t &pin) : chipNumber_m{ chipNumber }, pin_m{ pin } {
    claimOutput();
}

// Tal vez imprimir algo en cerr?
My::OutputPin::~OutputPin() noexcept {
    lgGpioFree(chipNumber_m, pin_m);
}

uint8_t My::OutputPin::getPinNumber() const noexcept {
    return pin_m;
}

int My::OutputPin::getChipNumber() const noexcept {
    return chipNumber_m;
}

void My::OutputPin::claimOutput() {
    if (lgGpioClaimOutput(chipNumber_m, 0, pin_m, LG_LOW) < 0) {
        throw std::runtime_error{ "Unable to claim the output" };
    }
}
