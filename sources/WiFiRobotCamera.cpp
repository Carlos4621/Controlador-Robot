#include "WiFiRobotCamera.h"
#include "WiFiRobotCamera.h"

My::WiFiRobotCamera::WiFiRobotCamera(const EncodeParams& encodeParams, const ServerParams& serverParams, boost::asio::io_context& context,
	const uint8_t& cameraID) : RobotCamera{ cameraID }, WiFiSerializer{ context, serverParams }, params_m{ encodeParams } {
}

void My::WiFiRobotCamera::sendCameraData() {
	encodeLastImage();
	return sendData(buffer_m);
}

void My::WiFiRobotCamera::encodeLastImage() {
	buffer_m.clear();

	cv::imencode(params_m.fileExtension, getLastImage(), buffer_m, params_m.flags);
}
