#include "PWMHBridge.h"
#include <stdexcept>

My::PWMHBridge::PWMHBridge(const int &chipNumnber, const uint8_t &horaryPin,
    const uint8_t &antihoraryPin, const float &frecuency) : 
    horaryPin_m{ chipNumnber, horaryPin, frecuency }, antihoraryPin_m{ chipNumnber, antihoraryPin, frecuency } {
}

My::PWMHBridge::PWMHBridge(const PWMHBridgeParams &params) : 
    PWMHBridge{ params.chipNumber, params.horaryPin, params.antihoraryPin, params.frecuency } {
}

void My::PWMHBridge::stopMotor() noexcept {
    stopHorary();
    stopAntiHorary();
}

void My::PWMHBridge::setHorary(const float& speed) {
    stopAntiHorary();
    horaryPin_m.set(speed);
}

void My::PWMHBridge::setAntihorary(const float& speed) {
    stopHorary();
    antihoraryPin_m.set(speed);
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
    horaryPin_m.desactivate();
}

void My::PWMHBridge::stopAntiHorary() noexcept {
    antihoraryPin_m.desactivate();
}
