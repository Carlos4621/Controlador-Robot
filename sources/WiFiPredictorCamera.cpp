#include "WiFiPredictorCamera.h"

My::WiFiInferencerCamera::WiFiInferencerCamera(const EncodeParams& encodeParams, const ServerParams& serverParams, boost::asio::io_context& context,
	const uint8_t& cameraID, std::initializer_list<YOLOv8ModelParams> modelsParams) : 
	InferencerCamera{ cameraID, modelsParams }, WiFiSerializer{ context, serverParams }, params_m{ encodeParams } {
}

void My::WiFiInferencerCamera::sendCameraData() {
	encodeLastImage();
	sendData(buffer_m);
}

void My::WiFiInferencerCamera::sendPredictedData(const size_t &index) {
	sendData(getPredictions(index));
}

void My::WiFiInferencerCamera::sendAllPredictedData() {
	sendData(getAllPredictions());
}

void My::WiFiInferencerCamera::encodeLastImage() {
	buffer_m.clear();

	cv::imencode(params_m.fileExtension, getImage(), buffer_m, params_m.flags);
}
