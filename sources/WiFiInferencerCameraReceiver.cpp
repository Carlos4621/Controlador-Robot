#include "WiFiInferencerCameraReceiver.h"

My::WiFiInferencerCameraReceiver::WiFiInferencerCameraReceiver(const cv::ImreadModes& decodeMode, const ServerParams& serverParams,
	boost::asio::io_context& context) :
	WiFiDeserializer{ context, serverParams }, decodeMode_m{ decodeMode } {
}

void My::WiFiInferencerCameraReceiver::receiveCameraData() {
	receiveData(buffer_m);

	lastOriginalImage_m = cv::imdecode(buffer_m, decodeMode_m);
}

void My::WiFiInferencerCameraReceiver::receiveInferencesData(const size_t& index) {
	if (inferencesData_m.size() < index) {
		inferencesData_m.resize(index + 1);
	}

	receiveData(inferencesData_m[index]);
}

void My::WiFiInferencerCameraReceiver::receiveAllInferencesData() {
	receiveData(inferencesData_m);
}

void My::WiFiInferencerCameraReceiver::setBoxesToImage() {
	lastOriginalImage_m.copyTo(lastModifiedImage_m);
	for (const auto &i : inferencesData_m) {
		for (const auto &j : i) {
			cv::rectangle(lastModifiedImage_m, j.bouncingBox, cv::Scalar(255, 0, 255), 2);
		}	
	}
}

cv::Mat My::WiFiInferencerCameraReceiver::getCameraData() noexcept {
	return lastOriginalImage_m;
}

std::vector<My::InferenceData> My::WiFiInferencerCameraReceiver::getInferencesData(const size_t &index) {
    return inferencesData_m[index];
}

std::vector<std::vector<My::InferenceData> > My::WiFiInferencerCameraReceiver::getAllInferencesData() {
    return inferencesData_m;
}

cv::Mat My::WiFiInferencerCameraReceiver::getBoxedImage() noexcept {
    return lastModifiedImage_m;
}
