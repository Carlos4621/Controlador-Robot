#include "WiFiXbox.h"

My::WiFiXbox::WiFiXbox(const ServerParams& serverParams, boost::asio::io_context& context, const uint8_t& controllerNumber) :
	XboxController{ controllerNumber }, WiFiSerializer{ context, serverParams } {
}

void My::WiFiXbox::sendControllerData() {
	sendData(getControllerData());
}
