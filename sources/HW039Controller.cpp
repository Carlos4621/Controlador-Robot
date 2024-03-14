#include "HW039Controller.h"
#include <stdexcept>

My::HW039Controller::HW039Controller(const int &chipNumnber, const uint8_t &RPWMPin,
 const uint8_t &LWPMPin, const float &frecuency) : chipNumber_m{chipNumnber},
 RPWMPin_m{RPWMPin}, LPWMPin_m{LWPMPin}, freuency_m{frecuency} {
    claimOutputs();
}

My::HW039Controller::~HW039Controller() noexcept {
    for (const auto &i : {RPWMPin_m, LPWMPin_m}) {
        lgGpioFree(chipNumber_m, i);
    }
}

void My::HW039Controller::stopMotor() const noexcept {
    stopHorary();
    stopAntiHorary();
}

void My::HW039Controller::setHorary(const float& speed) {
    stopAntiHorary();
    motorHelper(true, speed);
}

void My::HW039Controller::setAntihorary(const float& speed) {
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
    motorHelper(true, 0.f);
}

void My::HW039Controller::stopAntiHorary() const noexcept {
    motorHelper(false, 0.f);
}

void My::HW039Controller::motorHelper(const bool &horary, const float& speed) const noexcept {
    if (lgTxPwm(chipNumber_m, (horary ? RPWMPin_m : LPWMPin_m), 
            (speed == 0.f ? 1.f : freuency_m), speed, 0, 0) != LG_OKAY) {
        std::runtime_error{"Unable to manage the motor"};
    }
}
