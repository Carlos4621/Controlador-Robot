#pragma once
#ifndef WIFI_XBOX_HEADER
#define WIFI_XBOX_HEADER

#include "XboxController.h"
#include "WiFiSerializer.h"

namespace My {

	/*
		TODO:
		- Deber�a manejar reconexiones de red y mando
	*/

	/// @brief Clase que permite una comunicaci�n TCP que env�a datos de un mando de Xbox
	class WiFiXbox : public XboxController, private WiFiSerializer {
	public:

		/// @brief Constructor base
		/// @param serverParams Par�metros del servidor
		/// @param context Contexto del OS
		/// @param controllerNumber N�mero del control a usar
		WiFiXbox(const ServerParams& serverParams, boost::asio::io_context& context, const uint8_t& controllerNumber);

		WiFiXbox(const WiFiXbox&) = default;
		WiFiXbox(WiFiXbox&&) noexcept = default;

		virtual ~WiFiXbox() noexcept = default;

		WiFiXbox& operator=(const WiFiXbox&) = default;
		WiFiXbox& operator=(WiFiXbox&&) noexcept = default;

		bool operator==(const WiFiXbox&) const noexcept = default;

		using WiFiSerializer::startConnection;

		/// @brief Env�a la informaci�n del mando, usa la �ltima informaci�n guardada con updateController()
		void sendControllerData();

	};
}

#endif // !WIFI_XBOX_HEADER