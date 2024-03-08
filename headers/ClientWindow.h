#pragma once
#ifndef CLIENT_WINDOW_HEADER
#define CLIENT_WINDOW_HEADER

#include <SFML/Graphics.hpp>
#include "JoystickCircle.h"
#include <opencv2/opencv.hpp>
#include "CameraSprite.h"

namespace My {

	/*
		TODO:
		- Deber�a hace una clase que contenga todas las figuras a dibujar
	*/

	struct WindowParams {
		sf::VideoMode windowSize;
		sf::String windowTitle;
	};

	/// @brief Clase que representa la ventana del cliente, esta ya est� predise�ada
	class ClientWindow : private sf::RenderWindow {
	public:

		/// @brief Constructor base
		/// @param windowParams Paquete de par�metros de la ventana
		explicit ClientWindow(const WindowParams& windowParams);

		ClientWindow(const ClientWindow&) = default;
		ClientWindow(ClientWindow&&) noexcept = default;

		ClientWindow& operator=(const ClientWindow&) = default;
		ClientWindow& operator=(ClientWindow&&) noexcept = default;

		virtual ~ClientWindow() noexcept = default;

		/// @brief Cambia la posici�n del punto del joystick izquierdo
		/// @param position Posici�n relativa en la que se colocar� el punto
		void setLeftStickPoint(const sf::Vector2f& position);

		/// @brief Cambia la posici�n del punto del joystick derecho
		/// @param position Posici�n relativa en la que se colocar� el punto
		void setRightStickPoint(const sf::Vector2f& position);

		/// @brief Coloca la imagen enviada en el espacio de la primera c�mara
		/// @param image Imagen a colocar
		void setFistCameraImage(const cv::Mat& image);

		/// @brief Coloca la imagen enviada en el espacio de la segunda c�mara
		/// @param image Imagen a colocar 
		void setSecondCameraImage(const cv::Mat& image);

		/// @brief Actualiza la ventana con la nueva informaci�n y la muestra
		void refreshAndDisplay();

		using RenderWindow::pollEvent;

	private:
		static const sf::Color BackgroundColor;

		JoystickCircle leftStickCircle_m;
		JoystickCircle rightStickCircle_m;

		CameraSprite fistCamera_m;
		CameraSprite secondCamera_m;

		void drawShapes();
		void drawCameras();
	};

}

#endif // !CLIENT_WINDOW_HEADER