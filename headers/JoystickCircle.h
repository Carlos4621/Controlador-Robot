#pragma once
#ifndef JOYSTICK_CIRCLE_HEADER
#define JOYSTICK_CIRCLE_HEADER

#include <SFML/Graphics.hpp>
#include <cstdint>

namespace My {

	/// @brief Clase que representa un c�rculo y un punto que representa la posici�n actual del joystick
	class JoystickCircle {
	public:

		/// @brief Constructor base
		/// @param position Posici�n del c�rculo
		explicit JoystickCircle(const sf::Vector2f& position);

		/// @brief Dibuja la figura en una ventana
		/// @param window Ventana en la que se va a dibujar la figura
		void drawInWindow(sf::RenderWindow& window) const;

		/// @brief Dibuja un punto dentro del c�rculo. El origen de las coordenadas ser� el centro del c�rculo, 
		/// si el punto sale del rango del c�rculo se lanzar� una excepci�n
		/// @param position Posici�n relativa en donde se dibujar� el punto
		void drawPoint(const sf::Vector2f& position);

	private:
		static const uint8_t CircleRadius{ 100 };
		static const uint8_t PointRadius{ 10 };

		sf::CircleShape circle_m{ CircleRadius, 50 };
		sf::CircleShape point_m{ PointRadius };
	};
}

#endif // !JOYSTICK_CIRCLE_HEADER