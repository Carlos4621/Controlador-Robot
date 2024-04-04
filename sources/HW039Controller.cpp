#include "HW039Controller.h"
#include <stdexcept>

My::HW039Controller::HW039Controller(const int &chipNumnber, const uint8_t &RPWMPin,
 const uint8_t &LPWMPin, const float &frecuency) : 
    RPWMPin_m{ chipNumnber, RPWMPin, frecuency }, LPWMPin_m{ chipNumnber, LPWMPin, frecuency } {
}

My::HW039Controller::HW039Controller(const HW039ControllerParams &params) : 
    HW039Controller{ params.chipNumber, params.RPWMPin, params.LPWMPin, params.frecuency } {
}

void My::HW039Controller::stopMotor() noexcept {
    stopHorary();
    stopAntiHorary();
}

void My::HW039Controller::setHorary(const float& speed) {
    stopAntiHorary();
    RPWMPin_m.set(speed);
}

void My::HW039Controller::setAntihorary(const float& speed) {
    stopHorary();
    LPWMPin_m.set(speed);
}

void My::HW039Controller::setRelative(const float &relativeSpeed) {
    if (relativeSpeed > 0) {
        setHorary(relativeSpeed);
    }
    else if (relativeSpeed < 0) {
        setAntihorary(std::abs(relativeSpeed));
    }
    else {
        stopMotor();
    }
}

void My::HW039Controller::stopHorary() noexcept {
    RPWMPin_m.desactivate();
}

void My::HW039Controller::stopAntiHorary() noexcept {
    LPWMPin_m.desactivate();
}
