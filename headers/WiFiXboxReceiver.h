#pragma once
#ifndef WIFI_XBOX_RECEIVER_HEADER
#define WIFI_XBOX_RECEIVER_HEADER

#include "XboxControllerData.h"
#include "WiFiXbox.h"
#include "WiFiDeserializer.h"

namespace My {

	/*
		TODO:
		- Debo implementar reconexiones
	*/

	/// @brief Clase que permite una coexi�n TCP que recibe datos de un mando de Xbox
	class WiFiXboxReceiver : private WiFiDeserializer {
	public:

		/// @brief Constructor base
		/// @param serverParams Par�metros del servido
		/// @param context Contexto del OS
		WiFiXboxReceiver(const ServerParams& serverParams, boost::asio::io_context& context);

		WiFiXboxReceiver(const WiFiXboxReceiver&) = default;
		WiFiXboxReceiver(WiFiXboxReceiver&&) noexcept = default;

		virtual ~WiFiXboxReceiver() noexcept = default;

		WiFiXboxReceiver& operator=(const WiFiXboxReceiver&) = default;
		WiFiXboxReceiver& operator=(WiFiXboxReceiver&&) noexcept = default;

		bool operator==(const WiFiXboxReceiver& other) const = default;

		using WiFiDeserializer::waitConnection;

		/// @brief Recibe los datos enviados por el cliente y los almacena
		void receiveControllerData();

		/// @brief Obtiene los datos recibidos
		/// @return El �ltimo dato recibido del cliente
		XboxControllerData getControllerData() const;

	private:

		XboxControllerData controllerData_m;
	};
}

#endif // !WIFI_XBOX_RECEIVER_HEADER