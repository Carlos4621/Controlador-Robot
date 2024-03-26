#include "WiFiPredictorCamera.h"

My::WiFiPredictorCamera::WiFiPredictorCamera(const EncodeParams& encodeParams, const ServerParams& serverParams, boost::asio::io_context& context,
	const uint8_t& cameraID, std::initializer_list<YOLOv8ModelParams> modelsParams) : 
	PredictorCamera{ cameraID, modelsParams }, WiFiSerializer{ context, serverParams }, params_m{ encodeParams } {
}

void My::WiFiPredictorCamera::sendCameraData() {
	encodeLastImage();
	sendData(buffer_m);
}

void My::WiFiPredictorCamera::sendPredictedData(const size_t &index) {
	sendData(getPredictions(index));
}

void My::WiFiPredictorCamera::sendAllPredictedData() {
	sendData(getAllPredictions());
}

void My::WiFiPredictorCamera::sendModelsSize() {
	sendData(getModelsSize());
}

void My::WiFiPredictorCamera::encodeLastImage() {
	buffer_m.clear();

	cv::imencode(params_m.fileExtension, getImage(), buffer_m, params_m.flags);
}
