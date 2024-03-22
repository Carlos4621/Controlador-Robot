#include "WiFiInferencerCameraReceiver.h"

My::WiFiInferencerCameraReceiver::WiFiInferencerCameraReceiver(const cv::ImreadModes& decodeMode, const ServerParams& serverParams,
	boost::asio::io_context& context) :
	WiFiDeserializer{ context, serverParams }, decodeMode_m{ decodeMode } {
}

void My::WiFiInferencerCameraReceiver::receiveCameraData() {
	receiveData(buffer_m);

	lastImage_m = cv::imdecode(buffer_m, decodeMode_m);
}

cv::Mat My::WiFiInferencerCameraReceiver::getCameraData() noexcept {
	return lastImage_m;
}
