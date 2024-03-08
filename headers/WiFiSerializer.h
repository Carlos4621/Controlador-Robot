#pragma once
#ifndef WIFI_SERIALIZER_HEADER
#define WIFI_SERIALIZER_HEADER

#include "ServerParams.h"
#include <boost/asio.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <opencv2/opencv.hpp>

namespace My {

	/// @brief Clase que permite una conexión TCP y el envío de datos serializados
	class WiFiSerializer {
	public:

		/// @brief Constructor base
		/// @param context Contexto del OS
		/// @param serverParams Parámetros del servidor a conectar
		WiFiSerializer(boost::asio::io_context& context, const ServerParams& serverParams);

		WiFiSerializer(const WiFiSerializer&) = default;
		WiFiSerializer(WiFiSerializer&&) noexcept = default;

		WiFiSerializer& operator=(const WiFiSerializer&) = default;
		WiFiSerializer& operator=(WiFiSerializer&&) noexcept = default;

		/// @brief Inicia la conexión con otro socket
		void startConnection();

		/// @brief Envía data a otro socket
		/// @tparam T Tipo de dato a enviar
		/// @param toSend Data a enviar
		template<typename T>
		void sendData(const T& toSend);

	private:
		boost::asio::ip::tcp::resolver::results_type endPoints_m;
		boost::asio::ip::tcp::socket socket_m;

		template<typename T>
		std::string serializeData(const T& toSerialize);

	};

	template<typename T>
	inline std::string WiFiSerializer::serializeData(const T& toSerialize) {
		std::ostringstream inputString;

		boost::archive::binary_oarchive binaryArchive{ inputString };

		binaryArchive << toSerialize;

		return inputString.str();
	}

	template<typename T>
	inline void WiFiSerializer::sendData(const T& toSend) {
		const auto serializedData{ serializeData(toSend) };
		const auto sizeOfData{ static_cast<uint32_t>(serializedData.size()) };

		boost::asio::write(socket_m, boost::asio::buffer(&sizeOfData, sizeof(sizeOfData)));
	
		boost::asio::write(socket_m, boost::asio::buffer(serializedData));

	}

}
#endif // !WIFI_SERIALIZER_HEADER