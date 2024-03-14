#include "HW039Controller.h"
#include <stdexcept>

My::HW039Controller::HW039Controller(const int &chipNumnber, const uint8_t &RPWMPin,
 const uint8_t &LWPMPin, const float &frecuency) : 
    params_m{chipNumnber, RPWMPin, LWPMPin, frecuency} {
    claimOutputs();
}

My::HW039Controller::HW039Controller(const HW039ControllerParams &params) {

}

My::HW039Controller::~HW039Controller() noexcept {
    for (const auto &i : {params_m.RPWMPin, params_m.LPWMPin}) {
        lgGpioFree(params_m.chipNumber, i);
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
    for(const auto& i : {params_m.RPWMPin, params_m.LPWMPin}) {
        if (lgGpioClaimOutput(params_m.chipNumber, 0, i, 0) != LG_OKAY) {
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
    if (lgTxPwm(params_m.chipNumber, (horary ? params_m.RPWMPin : params_m.LPWMPin), 
            (speed == 0.f ? 1.f : params_m.frecuency), speed, 0, 0) != LG_OKAY) {
        std::runtime_error{"Unable to manage the motor"};
    }
}
