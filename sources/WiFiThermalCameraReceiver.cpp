#include "WiFiThermalCameraReceiver.h"

My::WiFiThermalCameraReceiver::WiFiThermalCameraReceiver(boost::asio::io_context &context, 
    const ServerParams &serverParams, const ThermalCameraVisualizerParams &thermalCameraVisualizerParams) :
    ThermalCameraVisualizer{ thermalCameraVisualizerParams }, WiFiDeserializer{ context, serverParams } {
}

void My::WiFiThermalCameraReceiver::receiveThermalImage() {
    std::array<float, 768> image;
    receiveData(image);

    convertImage(image);
}