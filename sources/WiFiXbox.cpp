#include "WiFiXbox.h"
#include <boost/archive/binary_oarchive.hpp>
#include <sstream>

My::WiFiXbox::WiFiXbox(const ServerParams& serverParams, boost::asio::io_context& context, const uint8_t& controllerNumber) :
	XboxController{ controllerNumber }, WiFiSerializer{ context, serverParams } {
}

void My::WiFiXbox::sendControllerData() {
	return sendData(getControllerData());
}
