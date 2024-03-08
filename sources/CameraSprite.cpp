#include "CameraSprite.h"

My::CameraSprite::CameraSprite(const sf::Vector2f& position) {
	sprite_m.setPosition(position);
}

void My::CameraSprite::setTexture(const cv::Mat& image) {
	convertToTexture(image);
	sprite_m.setTexture(texture_m);
}

void My::CameraSprite::drawInWindow(sf::RenderWindow& window) const {
	window.draw(sprite_m);
}

void My::CameraSprite::convertToTexture(const cv::Mat& image) {
	cv::Mat tempImage;

	cv::cvtColor(image, tempImage, cv::COLOR_BGR2RGBA);

	sf::Image convertedImage;
	convertedImage.create(tempImage.cols, tempImage.rows, tempImage.ptr());

	texture_m.loadFromImage(convertedImage);
}
