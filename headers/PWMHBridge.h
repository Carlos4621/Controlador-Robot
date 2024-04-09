#pragma once
#ifndef PWM_H_BRIDGE_HEADER
#define PWM_H_BRIDGE_HEADER

#include "PWMOutput.h"

namespace My{

    /// @brief Struct con los parámetros de la clase PWMHBridge
    struct PWMHBridgeParams {
        int chipNumber;
        uint8_t RPWMPin;
        uint8_t LPWMPin;
        float frecuency;
    };
    
    /// @brief Clase que permite el manejo de un driver de motores HW-039
    class PWMHBridge {
    public:

        /// @brief Constructor base
        /// @param chipNumber Numero del chip a controlar, se consigue con lgGpiochipOpen(n)
        /// @param RPWMPin Salida que conecta a el pin RPWM
        /// @param LWPMPin Salida que conecta a el pin LPWM
        /// @param frecuency Resolucion del PWM
        PWMHBridge(const int& chipNumber, const uint8_t& RPWMPin,
            const uint8_t& LWPMPin, const float& frecuency);

        /// @brief Constructor con paquete de parámetros
        /// @param params Paquete de los parámetros a usar
        PWMHBridge(const PWMHBridgeParams& params);

        PWMHBridge(const PWMHBridge&) = default;
        PWMHBridge(PWMHBridge&&) noexcept = default;

        virtual ~PWMHBridge() noexcept = default;

        PWMHBridge& operator=(const PWMHBridge&) = default;
        PWMHBridge& operator=(PWMHBridge&&) noexcept = default;

        /// @brief Apaga las dos salidas
        void stopMotor() noexcept;

        /// @brief Envia el porcentaje deseado a el pin RPWM
        /// @param speed Porcentaje del duty cycle
        void setHorary(const float& speed);

        /// @brief Enva el porcentaje deseado a el pin LPWM
        /// @param speed Porcentaje del duty cycle
        void setAntihorary(const float& speed);

        /// @brief Envia el porcentaje deseado al pin PWM siguiendo estas condiciones:
        ///        si x > 0 entonces this->setHorary(x)
        ///        si x < 0 entonces this->setAntihorary(std::abs(x))
        ///        de otra manera this->stopMotors()
        /// @param relativeSpeed 
        void setRelative(const float& relativeSpeed);

    private:

        PWMOutput RPWMPin_m;
        PWMOutput LPWMPin_m;

        void stopHorary() noexcept;
        void stopAntiHorary() noexcept;
    };
}

#endif // !HW039_CONTROLLER_HEADER