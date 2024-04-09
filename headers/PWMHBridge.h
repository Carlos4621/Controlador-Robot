#pragma once
#ifndef PWM_H_BRIDGE_HEADER
#define PWM_H_BRIDGE_HEADER

#include "PWMOutput.h"

namespace My{

    /// @brief Struct con los parámetros de la clase PWMHBridge
    struct PWMHBridgeParams {
        int chipNumber;
        uint8_t horaryPin;
        uint8_t antihoraryPin;
        float frecuency;
    };
    
    /// @brief Clase que permite el manejo de un puente H de forma analógica (con control de velocidad de motor)
    class PWMHBridge {
    public:

        /// @brief Constructor base
        /// @param chipNumber Numero del chip a controlar, se consigue con lgGpiochipOpen(n)
        /// @param horaryPin Número del pin GPIO que conecta a el pin que controla el giro horario
        /// @param antihoraryPin Número del pin GPIO que conecta a el pin que controla el giro antihorario
        /// @param frecuency Resolucion del PWM
        PWMHBridge(const int& chipNumber, const uint8_t& horaryPin,
            const uint8_t& antihoraryPin, const float& frecuency);

        /// @brief Constructor con paquete de parámetros
        /// @param params Paquete de los parámetros a usar
        PWMHBridge(const PWMHBridgeParams& params);

        PWMHBridge(const PWMHBridge&) = default;
        PWMHBridge(PWMHBridge&&) noexcept = default;

        virtual ~PWMHBridge() noexcept = default;

        PWMHBridge& operator=(const PWMHBridge&) = default;
        PWMHBridge& operator=(PWMHBridge&&) noexcept = default;

        /// @brief Detiene al motor
        void stopMotor() noexcept;

        /// @brief Establece el duty cycle del PWM para el giro horario, esto se traduce en velocidad del motor
        /// @param speed Porcentaje del duty cycle a establecer
        void setHorary(const float& speed);

        /// @brief Establece el duty cycle del PWM para el giro antihorario, esto se traduce en velocidad del motor
        /// @param speed Porcentaje del duty cycle a establecer
        void setAntihorary(const float& speed);

        /// @brief Envia el porcentaje deseado al pin horario o antihorario siguiendo estas condiciones:
        ///        si x > 0 entonces this->setHorary(x)
        ///        si x < 0 entonces this->setAntihorary(std::abs(x))
        ///        de otra manera this->stopMotors()
        /// @param relativeSpeed Número que representa el porcentaje del duty cycle y lo aplica según las condiciones establecidas
        void setRelative(const float& relativeSpeed);

    private:

        PWMOutput horaryPin_m;
        PWMOutput antihoraryPin_m;

        void stopHorary() noexcept;
        void stopAntiHorary() noexcept;
    };
}

#endif // !PWM_H_BRIDGE_HEADER