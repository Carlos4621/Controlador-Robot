#include "HW039Controller.h"
#include <stdexcept>

My::HW039Controller::HW039Controller(const int &chipNumnber, const uint8_t &RPWMPin,
 const uint8_t &LWPMPin, const uint16_t &frecuency) : chipNumber_m{chipNumnber},
 RPWMPin_m{RPWMPin}, LPWMPin_m{LWPMPin}, freuency_m{frecuency} {
    claimOutputs();
}

void My::HW039Controller::stopMotor() const noexcept {
    stopHorary();
    stopAntiHorary();
}

void My::HW039Controller::setHorary(const std::uint8_t &speed) {
    stopAntiHorary();
    motorHelper(true, speed);
}

void My::HW039Controller::setAntihorary(const std::uint8_t &speed) {
    stopHorary();
    motorHelper(false, speed);
}

void My::HW039Controller::claimOutputs() {
    for(const auto& i : {RPWMPin_m, LPWMPin_m}) {
        if (lgGpioClaimOutput(chipNumber_m, 0, i, 0) != LG_OKAY) {
            throw std::runtime_error{"Unable to claim the outputs"};
        }
    }
}

void My::HW039Controller::stopHorary() const noexcept {
    motorHelper(true, 0);
}

void My::HW039Controller::stopAntiHorary() const noexcept {
    motorHelper(false, 0);
}

void My::HW039Controller::motorHelper(const bool &horary, const uint8_t& speed) const noexcept {
    if (lgTxPwm(chipNumber_m, (horary ? RPWMPin_m : LPWMPin_m), 
            (speed == 0 ? 0 : freuency_m), speed, 0, 0) != LG_OKAY) {
        std::runtime_error{"Unable to manage the motor"};
    }
}