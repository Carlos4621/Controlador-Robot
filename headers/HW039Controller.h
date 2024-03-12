#pragma once
#ifndef HW039_CONTROLLER_HEADER
#define HW039_CONTROLLER_HEADER

#include <lgpio.h>
#include <cstdint>

namespace My{

    /// @brief Clase que permite el manejo de un driver de motores HW-039
    class HW039Controller {
    public:

        /// @brief Constructor base
        /// @param chipNumnber Numero del chip a controlar, se consigue con lgGpiochipOpen(n)
        /// @param RPWMPin Salida que conecta a el pin RPWM
        /// @param LWPMPin Salida que conecta a el pin LPWM
        /// @param frecuency Resolucion del PWM
        HW039Controller(const int& chipNumnber, const uint8_t& RPWMPin,
            const uint8_t& LWPMPin, const uint16_t& frecuency);

        HW039Controller(const HW039Controller&) = default;
        HW039Controller(HW039Controller&&) noexcept = default;

        virtual ~HW039Controller() noexcept = default;

        HW039Controller& operator=(const HW039Controller&) = default;
        HW039Controller& operator=(HW039Controller&&) noexcept = default;

        /// @brief Apaga las dos salidas
        void stopMotor() const noexcept;

        /// @brief Envia el porcentaje deseado a el pin RPWM
        /// @param speed Porcentaje del duty cycle
        void setHorary(const std::uint8_t& speed);

        /// @brief Enva el porcentaje deseado a el pin LPWM
        /// @param speed Porcentaje del duty cycle
        void setAntihorary(const std::uint8_t& speed);

    private:
        uint8_t RPWMPin_m;
        uint8_t LPWMPin_m;
        uint16_t freuency_m;
        int chipNumber_m;

        void claimOutputs();

        void stopHorary() const noexcept;
        void stopAntiHorary() const noexcept;

        void motorHelper(const bool&, const uint8_t&) const noexcept;
    };
}

#endif // !HW039_CONTROLLER_HEADER