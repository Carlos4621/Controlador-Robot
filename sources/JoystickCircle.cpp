#include "JoystickCircle.h"

My::JoystickCircle::JoystickCircle(const sf::Vector2f& position) {
	circle_m.setPosition(position);
	point_m.setOrigin(PointRadius, PointRadius);
	point_m.setPosition(position.x + CircleRadius, position.y + CircleRadius);
	point_m.setFillColor(sf::Color::Black);
}

void My::JoystickCircle::drawInWindow(sf::RenderWindow& window) const {
	window.draw(circle_m);
	window.draw(point_m);
}

void My::JoystickCircle::drawPoint(const sf::Vector2f& position) {
	const auto circleCenter{ circle_m.getPosition() + sf::Vector2f{CircleRadius, CircleRadius} };

	const sf::Vector2f objetive{ circleCenter.x + position.x,  circleCenter.y + position.y };

	if (!circle_m.getGlobalBounds().contains(objetive)) {
		throw std::invalid_argument{ "Las coordenadas salen del círculo" };
	}

	point_m.setPosition(objetive);
}
