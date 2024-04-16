#pragma once
#ifndef THERMAL_CAMERA_HEADER
#define THERMAL_CAMERA_HEADER

#include "MLX90640_API.h"
#include <array>

namespace My {

    /*
        TODO:
        - La clase transmitirá (y pesará) por lo menos 768 * sizeof(float), lo cual es un montón, tal vez debería redondear
          sus datos al tipo short o char
        - Muchos números constantes y poca personalización del usuario, por mejorar
    */

    /// @brief Clase que representa una cámara térmica MLX90640, su imagen es representada por un array de float con valores
    /// que representan temperatura ,para su mejor representación visual se recomienda usar la clase (...) en conjunto a esta
    class ThermalCamera {
    public:

        /// @brief Constructor base
        /// @param slaveAddress Dirección IC2 de la cámara térmica
        ThermalCamera(const uint8_t& slaveAddress);

        ThermalCamera(const ThermalCamera&) = default;
        ThermalCamera(ThermalCamera&&) noexcept = default;

        virtual ~ThermalCamera() noexcept = default;

        ThermalCamera& operator=(const ThermalCamera&) = default;
        ThermalCamera& operator=(ThermalCamera&&) noexcept = default;
        
        /// @brief Toma un frame de la cámara para su obtención con getImage()
        void updateCamera();

        /// @brief Obtiene el último array con las temperaturas recogidas
        /// @return Array con las últimas temperaturas leídas
        [[nodiscard]] std::array<float, 768> getImage() const noexcept;

    private:
    
        static constexpr float emissivity{ 0.95 };
        const uint8_t shift{ 8 };

        uint8_t slaveAddress_m;
        std::array<float, 768> lastImage_m;
    };

}

#endif // !THERMAL_CAMERA_HEADER