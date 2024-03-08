#pragma once
#ifndef XBOX_CONTROLLER_HEADER
#define XBOX_CONTROLLER_HEADER

#include "XboxControllerData.h"
#include <SFML/Graphics.hpp>

namespace My {

	/// @brief Clase que representa un control de Xbox
	class XboxController {
	public:

		/// @brief Constructor base
		/// @param controllerNumber N�mero del mando
		explicit XboxController(const uint8_t& controllerNumber);

		XboxController(const XboxController&) = default;
		XboxController(XboxController&&) = default;

		XboxController& operator=(const XboxController&) = default;
		XboxController& operator=(XboxController&&) noexcept = default;

		bool operator==(const XboxController&) const noexcept;

		/// @brief Actualiza la informaci�n del mando
		void updateController();

		/// @brief Obtiene la �ltima informaci�n guardada con updateController()
		/// @return Data del mando
		XboxControllerData getControllerData() const noexcept;

		/// @brief Verifica si el mando est� conectado
		/// @return True si el mando est� conectado, False sino
		bool isConnected() const noexcept;

	private:
		uint8_t controllerNumber_m;
		XboxControllerData controllerData_m;

		void readButtons();
		void readAxis();
	};
}

#endif // !XBOX_CONTROLLER_HEADER