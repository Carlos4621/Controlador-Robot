#include "PredictorCamera.h"

My::PredictorCamera::PredictorCamera(const uint8_t& cameraID, std::initializer_list<YOLOv8ModelParams> modelsParams) : camera_m(cameraID) {
	if (!camera_m.isOpened()) {
		throw std::runtime_error{ "No se ha podido abrir la c�mara" };
	}

	for (const auto& i : modelsParams) {
		models_m.emplace_back(i);
	}

	PredictionsData_m.resize(models_m.size());
}

void My::PredictorCamera::updateCamara() {
	camera_m >> image_m;
}

void My::PredictorCamera::applyModel(const size_t &index, const double &modelConfidenceThreshold, const double &modelScoreThreshold, 
const double &modelNMSThreshold) {

	PredictionsData_m[index] = std::move(models_m[index].getPredictions(image_m, modelConfidenceThreshold, modelScoreThreshold, modelNMSThreshold));
}

void My::PredictorCamera::applyAllModels(const double &modelConfidenceThreshold, const double &modelScoreThreshold, const double &modelNMSThreshold) {

	for (size_t i{ 0 }; i < models_m.size(); ++i) {
		applyModel(i, modelConfidenceThreshold, modelScoreThreshold, modelNMSThreshold);
	}
}

std::vector<My::PredictionsData> My::PredictorCamera::getPredictions(const size_t &index) const {
    return PredictionsData_m[index];
}

std::vector<std::vector<My::PredictionsData> > My::PredictorCamera::getAllPredictions() const noexcept {
    return PredictionsData_m;
}

size_t My::PredictorCamera::getModelsSize() const noexcept {
    return models_m.size();
}

cv::Mat My::PredictorCamera::getImage() const noexcept {
    return image_m;
}