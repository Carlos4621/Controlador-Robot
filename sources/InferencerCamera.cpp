#include "InferencerCamera.h"

My::InferencerCamera::InferencerCamera(const uint8_t& cameraID, std::initializer_list<InferencerParams> inferencers) : camera_m(cameraID) {
	if (!camera_m.isOpened()) {
		throw std::runtime_error{ "No se ha podido abrir la c�mara" };
	}

	for (const auto& i : inferencers) {
		inferencers_m.emplace_back(i);
	}

	inferencesData_m.resize(inferencers_m.size());
}

void My::InferencerCamera::updateCamara() {
	camera_m >> lastOriginalImage_m;
}

void My::InferencerCamera::applyInferencer(const size_t &index, const double &modelConfidenceThreshold, const double &modelScoreThreshold, 
const double &modelNMSThreshold) {

	inferencesData_m[index] = std::move(inferencers_m[index].getInferences(lastOriginalImage_m, modelConfidenceThreshold, modelScoreThreshold, modelNMSThreshold));
}

void My::InferencerCamera::applyAllInferencers(const double &modelConfidenceThreshold, const double &modelScoreThreshold, const double &modelNMSThreshold) {

	for (size_t i{ 0 }; i < inferencers_m.size(); ++i) {
		applyInferencer(i, modelConfidenceThreshold, modelScoreThreshold, modelNMSThreshold);
	}
}

std::vector<My::InferenceData> My::InferencerCamera::getInferences(const size_t &index) const {
    return inferencesData_m[index];
}

std::vector<std::vector<My::InferenceData> > My::InferencerCamera::getAllInferences() const noexcept {
    return inferencesData_m;
}

size_t My::InferencerCamera::getInferencersSize() const noexcept {
    return inferencers_m.size();
}

cv::Mat My::InferencerCamera::getLastImage() const noexcept {
    return lastOriginalImage_m;
}