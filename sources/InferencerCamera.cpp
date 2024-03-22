#include "InferencerCamera.h"

My::InferencerCamera::InferencerCamera(const uint8_t& cameraID) : camera_m(cameraID) {
	if (!camera_m.isOpened()) {
		throw std::runtime_error{ "No se ha podido abrir la c�mara" };
	}
}

void My::InferencerCamera::updateCamara() {
	camera_m >> lastImage_m;
}

cv::Mat My::InferencerCamera::getLastImage() const noexcept {
	return lastImage_m;
}