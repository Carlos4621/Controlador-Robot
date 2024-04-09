#include "DigitalOutput.h"

void My::DigitalOutput::activate() {
    this->set(true);
    state_m = true;
}

void My::DigitalOutput::desactivate() {
    this->set(false);
    state_m = false;
}

void My::DigitalOutput::toggle() {
    state_m ? desactivate() : activate();
}

void My::DigitalOutput::set(const bool &newState) {
    if (lgGpioWrite(getChipNumber(), getPinNumber(), newState) < 0) {
        throw std::runtime_error{ "Unable to manage the pin" };
    }
    
    state_m = newState;
}

bool My::DigitalOutput::isActivated() const noexcept {
    return state_m;
}
