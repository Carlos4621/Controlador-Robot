#include "WiFiXboxReceiver.h"

My::WiFiXboxReceiver::WiFiXboxReceiver(const ServerParams& serverParams, boost::asio::io_context& context, const float& XAxisDeadZone,
	const float& YAxisDeadZone) : 
	WiFiDeserializer{ context, serverParams }, deadZone_m{ XAxisDeadZone, YAxisDeadZone } {
}

void My::WiFiXboxReceiver::receiveControllerData() {
	receiveData(controllerData_m);

	verifyDeadZone();
}

My::XboxControllerData My::WiFiXboxReceiver::getControllerData() const noexcept {
	return controllerData_m;
}

void My::WiFiXboxReceiver::verifyDeadZone() {
	applyDeadZone(controllerData_m.leftStick);
	applyDeadZone(controllerData_m.rightStick);
}

void My::WiFiXboxReceiver::applyDeadZone(std::pair<float, float> &stick) noexcept {
	if (std::abs(stick.first) < deadZone_m.first) {
		stick.first = 0;
	}

	if (std::abs(stick.second) < deadZone_m.second) {
		stick.second = 0;
	}
}
