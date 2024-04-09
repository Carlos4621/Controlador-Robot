#include "DigitalHBridge.h"

My::DigitalHBridge::DigitalHBridge(const int &chipNumber, const uint8_t &horaryPin, const uint8_t &antihoraryPin) :
    horaryPin_m{ chipNumber, horaryPin }, antihoraryPin_m{ chipNumber, antihoraryPin } {
}

void My::DigitalHBridge::stopMotor() noexcept {
    stopHorary();
    stopAntihorary();
}

void My::DigitalHBridge::setHorary() noexcept {
    stopAntihorary();
    horaryPin_m.activate();
}

void My::DigitalHBridge::setAntihorary() noexcept {
    stopHorary();
    horaryPin_m.activate();
}

void My::DigitalHBridge::stopHorary() noexcept {
    horaryPin_m.desactivate();
}

void My::DigitalHBridge::stopAntihorary() noexcept {
    antihoraryPin_m.desactivate();
}
