#pragma once
#ifndef PWM_OUTPUT_HEADER
#define PWM_OUTPUT_HEADER

#include "OutputPin.h"

namespace My {

    /// @brief Clase que se encarga de manjerar salidas PWM
    class PWMOutput : public OutputPin {
    public:

        /// @brief Constructor base
        /// @param chipNumber Número del chip GPIO a utlizar
        /// @param pin Número del pin GPIO a utilizar
        /// @param frecuency Frecuencia del pulso PWM
        PWMOutput(const int& chipNumber, const uint8_t& pin, const float& frecuency);

        PWMOutput(const PWMOutput&) = default;
        PWMOutput(PWMOutput&&) noexcept = default; 

        virtual ~PWMOutput() noexcept = default;

        PWMOutput& operator=(const PWMOutput&) = default;
        PWMOutput& operator=(PWMOutput&&) noexcept = default;

        /// @brief Establece el duty cycle del pulso PWM
        /// @param dutyCycle valor en porcentaje que representa el duty cycle
        void set(const float& dutyCycle);

        /// @brief Establece en 0% el duty cycle
        void desactivate();

    private:

        float frecuency_m;

        void writeHelper(const float& dutyCycle);
    };
}

#endif // !PWM_OUTPUT_HEADER