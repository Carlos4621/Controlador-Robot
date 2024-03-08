#include "ClientWindow.h"

const sf::Color My::ClientWindow::BackgroundColor{ 69,63,63 };

My::ClientWindow::ClientWindow(const WindowParams& windowParams) :
	RenderWindow{ windowParams.windowSize, windowParams.windowTitle },
	leftStickCircle_m{ {980, 560} }, rightStickCircle_m{ {1270, 560} }, fistCamera_m{ {20, 20} }, secondCamera_m{ {1000, 1000} } {
}

void My::ClientWindow::setLeftStickPoint(const sf::Vector2f& position) {
	leftStickCircle_m.drawPoint(position);
}

void My::ClientWindow::setRightStickPoint(const sf::Vector2f& position) {
	rightStickCircle_m.drawPoint(position);
}

void My::ClientWindow::setFistCameraImage(const cv::Mat& image) {
	fistCamera_m.setTexture(image);
}

void My::ClientWindow::drawShapes() {
	rightStickCircle_m.drawInWindow(*this);
	leftStickCircle_m.drawInWindow(*this);
}

void My::ClientWindow::drawCameras() {
	fistCamera_m.drawInWindow(*this);
	secondCamera_m.drawInWindow(*this);
}

void My::ClientWindow::setSecondCameraImage(const cv::Mat& image) {
	secondCamera_m.setTexture(image);
}

void My::ClientWindow::refreshAndDisplay() {
	clear(BackgroundColor);
	drawShapes();
	drawCameras();
	display();
}
