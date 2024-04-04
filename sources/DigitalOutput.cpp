#include "DigitalOutput.h"

My::DigitalOutput::DigitalOutput(const int & chipNumber, const uint8_t & pin, const bool & initialState) : 
    chipNumber_m{ chipNumber }, pin_m{ pin }, state_m{ initialState } {
    claimOutput();
}

My::DigitalOutput::~DigitalOutput() noexcept {
    lgGpioFree(chipNumber_m, pin_m);
}

void My::DigitalOutput::activate() {
    this->set(true);
}

void My::DigitalOutput::desactivate() {
    this->set(false);
}

void My::DigitalOutput::toggle() {
    state_m ? desactivate() : activate();
}

void My::DigitalOutput::set(const bool &newState) {
    if (lgGpioWrite(chipNumber_m, pin_m, newState) != LG_OKAY) {
        throw std::runtime_error{ "Unable to manage the pin" };
    }
    
    state_m = newState;
}

bool My::DigitalOutput::isActivated() const noexcept {
    return state_m;
}

void My::DigitalOutput::claimOutput() {
    if (lgGpioClaimOutput(chipNumber_m, 0, pin_m, state_m) != LG_OKAY) {
        throw std::runtime_error{ "Unable to claim the output" };
    }
}
