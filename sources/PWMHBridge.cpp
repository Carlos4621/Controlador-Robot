#include "PWMHBridge.h"
#include <stdexcept>

My::PWMHBridge::PWMHBridge(const int &chipNumnber, const uint8_t &RPWMPin,
    const uint8_t &LPWMPin, const float &frecuency) : 
    RPWMPin_m{ chipNumnber, RPWMPin, frecuency }, LPWMPin_m{ chipNumnber, LPWMPin, frecuency } {
}

My::PWMHBridge::PWMHBridge(const PWMHBridgeParams &params) : 
    PWMHBridge{ params.chipNumber, params.RPWMPin, params.LPWMPin, params.frecuency } {
}

void My::PWMHBridge::stopMotor() noexcept {
    stopHorary();
    stopAntiHorary();
}

void My::PWMHBridge::setHorary(const float& speed) {
    stopAntiHorary();
    RPWMPin_m.set(speed);
}

void My::PWMHBridge::setAntihorary(const float& speed) {
    stopHorary();
    LPWMPin_m.set(speed);
}

void My::PWMHBridge::setRelative(const float &relativeSpeed) {
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

void My::PWMHBridge::stopHorary() noexcept {
    RPWMPin_m.desactivate();
}

void My::PWMHBridge::stopAntiHorary() noexcept {
    LPWMPin_m.desactivate();
}
