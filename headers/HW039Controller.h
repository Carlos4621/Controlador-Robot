#pragma once
#ifndef HW039_CONTROLLER_HEADER
#define HW039_CONTROLLER_HEADER

#include "PWMOutput.h"

namespace My{

    /// @brief Struct con los parámetros de la clase HW039Controller
    struct HW039ControllerParams {
        int chipNumber;
        uint8_t RPWMPin;
        uint8_t LPWMPin;
        float frecuency;
    };
    
    /// @brief Clase que permite el manejo de un driver de motores HW-039
    class HW039Controller {
    public:

        /// @brief Constructor base
        /// @param chipNumber Numero del chip a controlar, se consigue con lgGpiochipOpen(n)
        /// @param RPWMPin Salida que conecta a el pin RPWM
        /// @param LWPMPin Salida que conecta a el pin LPWM
        /// @param frecuency Resolucion del PWM
        HW039Controller(const int& chipNumber, const uint8_t& RPWMPin,
            const uint8_t& LWPMPin, const float& frecuency);

        /// @brief Constructor con paquete de parámetros
        /// @param params Paquete de los parámetros a usar
        HW039Controller(const HW039ControllerParams& params);

        HW039Controller(const HW039Controller&) = default;
        HW039Controller(HW039Controller&&) noexcept = default;

        virtual ~HW039Controller() noexcept = default;

        HW039Controller& operator=(const HW039Controller&) = default;
        HW039Controller& operator=(HW039Controller&&) noexcept = default;

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