#include "WiFiThermalCamera.h"

My::WiFiThermalCamera::WiFiThermalCamera(boost::asio::io_context &context, 
    const ServerParams &serverParams, const uint8_t &slaveAddress) : 
    ThermalCamera{ slaveAddress }, WiFiSerializer{ context, serverParams } {
}

void My::WiFiThermalCamera::sendThermalImageData() {
    sendData(this->getImage());
}