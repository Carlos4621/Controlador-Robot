#include "WiFiDeserializer.h"

My::WiFiDeserializer::WiFiDeserializer(boost::asio::io_context& context, const ServerParams& serverParams) :
	socket_m{ context }, acceptor_m{ context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), std::stoi(serverParams.port)) },
	buffer_m{} {
}

void My::WiFiDeserializer::waitConnection() {
	acceptor_m.accept(socket_m);
}
