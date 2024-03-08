#pragma once
#ifndef CAMERA_SPRITE_HEADER
#define CAMERA_SPRITE_HEADER

#include <opencv2/opencv.hpp>
#include <SFML/Graphics.hpp>

namespace My {

	/// @brief Clase que permite convertir un cv::Mat en un sf::Sprite para su f�cil display
	class CameraSprite {
	public:

		/// @brief Constructor base
		/// @param position Posici�n en donde se dibujar� el sprite
		CameraSprite(const sf::Vector2f& position);

		CameraSprite(const CameraSprite&) = default;
		CameraSprite(CameraSprite&&) noexcept = default;

		CameraSprite& operator=(const CameraSprite&) = default;
		CameraSprite& operator=(CameraSprite&&) noexcept = default;

		virtual ~CameraSprite() noexcept = default;

		/// @brief Hace que el sprite tome la textura de la imagen
		/// @param image Imagen a colocar
		void setTexture(const cv::Mat& image);

		/// @brief Dibuja el sprite, debe ser llamado para actualizar la imagen
		/// @param window Ventana en donde se va a dibujar
		void drawInWindow(sf::RenderWindow& window) const;

	private:
		sf::Sprite sprite_m;
		sf::Texture texture_m;

		void convertToTexture(const cv::Mat& image);
	};
}

#endif // !CAMERA_SPRITE_HEADER