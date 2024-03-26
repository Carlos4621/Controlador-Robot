#include "WiFiPredictorCameraReceiver.h"

My::WiFiPredictorCameraReceiver::WiFiPredictorCameraReceiver(const cv::ImreadModes& decodeMode, const ServerParams& serverParams,
	boost::asio::io_context& context) :
	WiFiDeserializer{ context, serverParams }, decodeMode_m{ decodeMode } {
}

void My::WiFiPredictorCameraReceiver::receiveCameraData() {
	receiveData(buffer_m);

	originalImage_m = cv::imdecode(buffer_m, decodeMode_m);
}

void My::WiFiPredictorCameraReceiver::receivePredictiedData(const size_t& index) {
	receiveData(predictedData_m[index]);
}

void My::WiFiPredictorCameraReceiver::receiveAllPredictedData() {
	receiveData(predictedData_m);
}

void My::WiFiPredictorCameraReceiver::receiveModelSize() {
	size_t newSize;
	receiveData(newSize);
	predictedData_m.resize(newSize);
}

void My::WiFiPredictorCameraReceiver::setBoxesToImage() {

	// Tal vez pueda mejorar esto
	originalImage_m.copyTo(boxedImage_m);
	for (const auto &i : predictedData_m) {
		for (const auto &j : i) {
			cv::rectangle(boxedImage_m, j.bouncingBox, cv::Scalar(255, 0, 255), 2);
		}	
	}
}

cv::Mat My::WiFiPredictorCameraReceiver::getCameraData() noexcept {
	return originalImage_m;
}

std::vector<My::PredictionsData> My::WiFiPredictorCameraReceiver::getPredictedData(const size_t &index) {
    return predictedData_m[index];
}

std::vector<std::vector<My::PredictionsData> > My::WiFiPredictorCameraReceiver::getAllPredictedData() {
    return predictedData_m;
}

cv::Mat My::WiFiPredictorCameraReceiver::getBoxedImage() noexcept {
    return boxedImage_m;
}
