#pragma once
#ifndef WIFI_DESERIALIZER_HEADER
#define WIFI_DESERIALIZER_HEADER

#include "ServerParams.h"
#include <boost/asio.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <iostream>

namespace My {

	/*
		TODO:
		- Manejar desconexiones y reconexiones
		- Manejar asincron�a
	*/

	class WiFiDeserializer {
	public:

		/// @brief Constructor base
		/// @param context Contesto del OS
		/// @param serverParams Par�metros del servidor
		WiFiDeserializer(boost::asio::io_context& context, const ServerParams& serverParams);

		WiFiDeserializer(const WiFiDeserializer&) = default;
		WiFiDeserializer(WiFiDeserializer&&) noexcept = default;

		WiFiDeserializer& operator=(const WiFiDeserializer&) = default;
		WiFiDeserializer& operator=(WiFiDeserializer&&) noexcept = default;

		/// @brief Espera a una petici�n de conexi�n
		void waitConnection();

		/// @brief Recibe data serializada
		/// @tparam T Tipo de dato a recibir
		/// @param toReceive Donde se guardar� la informaci�n desearilizada
		template<typename T>
		void receiveData(T& toReceive);

	private:
		boost::asio::ip::tcp::acceptor acceptor_m;
		boost::asio::ip::tcp::socket socket_m;
		std::vector<char> buffer_m;
		uint32_t receivedDataSize_m{ 0 };

		template<typename T>
		void deserializeData(T& toDeserialize);
	};

	template<typename T>
	inline void WiFiDeserializer::receiveData(T& toReceive) {
		boost::asio::read(socket_m, boost::asio::buffer(&receivedDataSize_m, sizeof(receivedDataSize_m)));

		// Evitamos resize innecesarios
		if (buffer_m.size() < receivedDataSize_m) {
			buffer_m.resize(receivedDataSize_m);
		}

		boost::asio::read(socket_m, boost::asio::buffer(buffer_m, receivedDataSize_m));

		deserializeData(toReceive);
	}

	template<typename T>
	inline void WiFiDeserializer::deserializeData(T& toDeserialize) {

		std::istringstream outputString{ std::string(buffer_m.data(), receivedDataSize_m) };

		boost::archive::text_iarchive binaryArchive{ outputString };

		binaryArchive >> toDeserialize;
	}

}

#endif // !WIFI_DESERIALIZER_HEADER