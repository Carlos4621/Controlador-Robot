#pragma once
#ifndef JOYSTICK_CIRCLE_HEADER
#define JOYSTICK_CIRCLE_HEADER

#include <SFML/Graphics.hpp>

namespace My {

	/// @brief Clase que representa un círculo y un punto que representa la posición actual del joystick
	class JoystickCircle {
	public:

		/// @brief Constructor base
		/// @param position Posición del círculo
		explicit JoystickCircle(const sf::Vector2f& position);

		/// @brief Dibuja la figura en una ventana
		/// @param window Ventana en la que se va a dibujar la figura
		void drawInWindow(sf::RenderWindow& window) const;

		/// @brief Dibuja un punto dentro del círculo. El origen de las coordenadas será el centro del círculo, 
		/// si el punto sale del rango del círculo se lanzará una excepción
		/// @param position Posición relativa en donde se dibujará el punto
		void drawPoint(const sf::Vector2f& position);

	private:
		static const uint8_t CircleRadius{ 100 };
		static const uint8_t PointRadius{ 10 };

		sf::CircleShape circle_m{ CircleRadius, 50 };
		sf::CircleShape point_m{ PointRadius };
	};
}

#endif // !JOYSTICK_CIRCLE_HEADER