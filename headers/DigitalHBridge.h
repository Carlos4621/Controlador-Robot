#pragma once
#ifndef DIGITAL_H_BRIDGE_HEADER
#define DIGITAL_H_BRIDGE_HEADER

#include "DigitalOutput.h"

namespace My {

    struct DigitalHBridgeParams {
        int chipNumber;
        uint8_t horaryPin;
        uint8_t antihoraryPin;
    };
    

    /// @brief Clase que permite el control de un puente H de forma digital (sin control de velocidad)
    class DigitalHBridge {
    public:

        /// @brief Constructor base
        /// @param chipNumber Número del chip GPIO a utilizar
        /// @param horaryPin Pin que activa el giro horario
        /// @param antihoraryPin Pin que activa el giro antihorario
        DigitalHBridge(const int& chipNumber, const uint8_t& horaryPin, const uint8_t& antihoraryPin);

        /// @brief Contructor con paquete de parámetros
        /// @param params Parámetros con los que se inicializará el puente H
        DigitalHBridge(const DigitalHBridgeParams& params);

        DigitalHBridge(const DigitalHBridge&) = default;
        DigitalHBridge(DigitalHBridge&&) noexcept = default;

        virtual ~DigitalHBridge() noexcept = default;

        DigitalHBridge& operator=(const DigitalHBridge&) = default;
        DigitalHBridge& operator=(DigitalHBridge&&) noexcept = default;

        /// @brief Detiene el motor
        void stopMotor() noexcept;

        /// @brief Activa el horaryPin para establecer un giro horario del motor
        void setHorary() noexcept;

        /// @brief Activa el antihoraryPin para establecer un giro antihorario del motor
        void setAntihorary() noexcept;

    private:

        DigitalOutput horaryPin_m;
        DigitalOutput antihoraryPin_m;

        void stopHorary() noexcept;
        void stopAntihorary() noexcept;
    };
}

#endif DIGITAL_H_BRIDGE_HEADER