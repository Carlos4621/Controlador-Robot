#include "DigitalOutput.h"

My::DigitalOutput::DigitalOutput(const int & chipNumber, const uint8_t & pin) : 
    OutputPin{ chipNumber, pin } {
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
    if (lgGpioWrite(getChipNumber(), getPinNumber(), newState) != LG_OKAY) {
        throw std::runtime_error{ "Unable to manage the pin" };
    }
    
    state_m = newState;
}

bool My::DigitalOutput::isActivated() const noexcept {
    return state_m;
}
