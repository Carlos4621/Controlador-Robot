#include "WiFiXboxReceiver.h"

My::WiFiXboxReceiver::WiFiXboxReceiver(const ServerParams& serverParams, boost::asio::io_context& context) :
	WiFiDeserializer{ context, serverParams } {
}

void My::WiFiXboxReceiver::receiveControllerData() {
	receiveData(controllerData_m);
}

My::XboxControllerData My::WiFiXboxReceiver::getControllerData() const {
	return controllerData_m;
}