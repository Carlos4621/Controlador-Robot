#pragma once
#ifndef WIFI_THERMAL_CAMERA_RECEIVER_HEADER
#define WIFI_THERMAL_CAMERA_RECEIVER_HEADER

#include "ThermalCameraVisualizer.h"
#include "WiFiDeserializer.h"

namespace My {
    class WiFiThermalCameraReceiver : private ThermalCameraVisualizer, private WiFiDeserializer {
    public:

        WiFiThermalCameraReceiver(boost::asio::io_context& context, 
            const ServerParams& serverParams, const ThermalCameraVisualizerParams& thermalCameraVisualizerParams);

        using WiFiDeserializer::waitConnection;
        using ThermalCameraVisualizer::getImage;

        void receiveThermalImage();
    };
}

#endif // !WIFI_THERMAL_CAMERA_RECEIVER_HEADER