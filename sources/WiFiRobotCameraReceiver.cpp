#include "WiFiRobotCameraReceiver.h"

My::WiFiRobotCameraReceiver::WiFiRobotCameraReceiver(const cv::ImreadModes& decodeMode, const ServerParams& serverParams,
	boost::asio::io_context& context) :
	WiFiDeserializer{ context, serverParams }, decodeMode_m{ decodeMode } {
}

void My::WiFiRobotCameraReceiver::receiveCameraData() {
	receiveData(buffer_m);

	lastImage_m = cv::imdecode(buffer_m, decodeMode_m);
}

cv::Mat My::WiFiRobotCameraReceiver::getCameraData() noexcept {
	return lastImage_m;
}
