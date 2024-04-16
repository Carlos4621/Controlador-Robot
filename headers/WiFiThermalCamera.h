#pragma once
#ifndef WIFI_THERMAL_CAMERA_HEADER
#define WIFI_THERMAL_CAMERA_HEADER

#include "WiFiSerializer.h"
#include "ThermalCamera.h"

namespace My {

    /// @brief Clase que permite una conexión TCP para la transmisión de una imagen térmica
    class WiFiThermalCamera : public ThermalCamera, private WiFiSerializer {
    public:

        /// @brief Constructor base
        /// @param context Contexto de E/S
        /// @param serverParams Parámetros del servidor a conectar
        /// @param slaveAddress Dirección I2C de la cámara térmica
        WiFiThermalCamera(boost::asio::io_context& context, const ServerParams& serverParams, 
            const uint8_t& slaveAddress);

        WiFiThermalCamera(const WiFiThermalCamera&) = default;
        WiFiThermalCamera(WiFiThermalCamera&&) noexcept = default;

        virtual ~WiFiThermalCamera() noexcept = default;

        WiFiThermalCamera& operator=(const WiFiThermalCamera&) = default;
        WiFiThermalCamera& operator=(WiFiThermalCamera&&) noexcept = default;

        using WiFiSerializer::startConnection;

        /// @brief Envía la última imagen guardada con updateCamera()
        void sendThermalImageData();
    };
}

#endif // !WIFI_THERMAL_CAMERA_HEADER