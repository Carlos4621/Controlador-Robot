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

	/// @brief Clase que permite una conexión TCP que recibe datos de un mando de Xbox, también implementa una zona muerta
	class WiFiXboxReceiver : private WiFiDeserializer {
	public:

		/// @brief Constructor base
		/// @param serverParams Parámetros del servido
		/// @param context Contexto del E/S
		/// @param XAxisDeadZone Zona muerta en el XAxis, si no se supera, se asigna 0. Por defecto = 0
		/// @param YAxisDeadZone Zona muerta en el YAxis, si no se supera, se asigna 0. Por defecto = 0
		WiFiXboxReceiver(const ServerParams& serverParams, boost::asio::io_context& context, const float& XAxisDeadZone = 0, const float& YAxisDeadZone = 0);

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
		/// @return El último dato recibido del cliente
		[[nodiscard]] XboxControllerData getControllerData() const noexcept;

	private:

		XboxControllerData controllerData_m;
		std::pair<float, float> deadZone_m;

		void verifyDeadZone();

		void applyDeadZone(std::pair<float, float>& stick) noexcept;
	};
}

#endif // !WIFI_XBOX_RECEIVER_HEADER