#include "WiFiPredictorCameraReceiver.h"

My::WiFiInferencerCameraReceiver::WiFiInferencerCameraReceiver(const cv::ImreadModes& decodeMode, const ServerParams& serverParams,
	boost::asio::io_context& context) :
	WiFiDeserializer{ context, serverParams }, decodeMode_m{ decodeMode } {
}

void My::WiFiInferencerCameraReceiver::receiveCameraData() {
	receiveData(buffer_m);

	originalImage_m = cv::imdecode(buffer_m, decodeMode_m);
}

void My::WiFiInferencerCameraReceiver::receivePredictiedData(const size_t& index) {

	// Se debe mejorar
	if (predictedData_m.size() < index) {
		predictedData_m.resize(index + 1);
	}

	receiveData(predictedData_m[index]);
}

void My::WiFiInferencerCameraReceiver::receiveAllPredictedData() {
	receiveData(predictedData_m);
}

void My::WiFiInferencerCameraReceiver::setBoxesToImage() {

	// Tal vez pueda mejorar esto
	originalImage_m.copyTo(boxedImage_m);
	for (const auto &i : predictedData_m) {
		for (const auto &j : i) {
			cv::rectangle(boxedImage_m, j.bouncingBox, cv::Scalar(255, 0, 255), 2);
		}	
	}
}

cv::Mat My::WiFiInferencerCameraReceiver::getCameraData() noexcept {
	return originalImage_m;
}

std::vector<My::PredictionsData> My::WiFiInferencerCameraReceiver::getPredictedData(const size_t &index) {
    return predictedData_m[index];
}

std::vector<std::vector<My::PredictionsData> > My::WiFiInferencerCameraReceiver::getAllPredictedData() {
    return predictedData_m;
}

cv::Mat My::WiFiInferencerCameraReceiver::getBoxedImage() noexcept {
    return boxedImage_m;
}
