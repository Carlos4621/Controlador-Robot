#include "XboxController.h"

enum XboxButtons {
	A = 0, B, X, Y, LB, RB, Back, start, L, R
};

My::XboxController::XboxController(const uint8_t& controllerNumber) : controllerNumber_m{ controllerNumber } {
}

bool My::XboxController::operator==(const XboxController& other) const noexcept {
	return controllerNumber_m == other.controllerNumber_m;
}

void My::XboxController::updateController() {
	sf::Joystick::update();
	readButtons();
	readAxis();
}

My::XboxControllerData My::XboxController::getControllerData() const noexcept {
	return controllerData_m;
}

bool My::XboxController::isConnected() const noexcept {
	return sf::Joystick::isConnected(controllerNumber_m);
}

void My::XboxController::readButtons() {
	static const auto getButton{ [this](const auto& button) { return sf::Joystick::isButtonPressed(controllerNumber_m, button); } };

	controllerData_m.A = getButton(A);
	controllerData_m.B = getButton(B);
	controllerData_m.X = getButton(X);
	controllerData_m.Y = getButton(Y);

	controllerData_m.RB = getButton(RB);
	controllerData_m.LB = getButton(LB);

	controllerData_m.R = getButton(R);
	controllerData_m.L = getButton(L);
}

void My::XboxController::readAxis() {
	static const auto getAxis{ [this](const auto& axis) { return sf::Joystick::getAxisPosition(controllerNumber_m, axis); } };

	controllerData_m.rightStick.first = getAxis(sf::Joystick::Axis::U);
	controllerData_m.rightStick.second = getAxis(sf::Joystick::Axis::Y);

	controllerData_m.leftStick.first = getAxis(sf::Joystick::Axis::X);
	controllerData_m.leftStick.second = getAxis(sf::Joystick::Axis::Y);
}
