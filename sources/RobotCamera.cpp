#include "RobotCamera.h"

My::RobotCamera::RobotCamera(const uint8_t& cameraID) : camera_m(cameraID) {
	if (!camera_m.isOpened()) {
		throw std::runtime_error{ "No se ha podido abrir la cámara" };
	}
}

void My::RobotCamera::updateCamara() {
	camera_m >> lastImage_m;
}

cv::Mat My::RobotCamera::getLastImage() const noexcept {
	return lastImage_m;
}