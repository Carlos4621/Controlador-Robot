#include "WiFiInferencerCamera.h"

My::WiFiInferencerCamera::WiFiInferencerCamera(const EncodeParams& encodeParams, const ServerParams& serverParams, boost::asio::io_context& context,
	const uint8_t& cameraID) : InferencerCamera{ cameraID }, WiFiSerializer{ context, serverParams }, params_m{ encodeParams } {
}

void My::WiFiInferencerCamera::sendCameraData() {
	encodeLastImage();
	sendData(buffer_m);
}

void My::WiFiInferencerCamera::encodeLastImage() {
	buffer_m.clear();

	cv::imencode(params_m.fileExtension, getLastImage(), buffer_m, params_m.flags);
}
