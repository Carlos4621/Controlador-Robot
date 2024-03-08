#include "WiFiSerializer.h"

My::WiFiSerializer::WiFiSerializer(boost::asio::io_context& context, const ServerParams& serverParams) :
	socket_m{ context } {

	boost::asio::ip::tcp::resolver resolver{ context };
	endPoints_m = resolver.resolve(serverParams.ip, serverParams.port);
}

void My::WiFiSerializer::startConnection() {
	boost::asio::connect(socket_m, endPoints_m);
}
