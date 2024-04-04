#pragma once
#ifndef PWM_OUTPUT_HEADER
#define PWM_OUTPUT_HEADER

#include <cstdint>
#include <lgpio.h>
#include <stdexcept>

namespace My {

    /*
        TODO:
        - Si el problema del delay persiste, cambiar a hardware PWM
        - Tal vez pueda hacer una abstracción de una clase llamada OutputPin para ahorrar código duplicado
    */

    /// @brief Clase que se encarga de manjerar salidas PWM, tiene un retraso de aplicación, tener en cuenta
    class PWMOutput {
    public:

        /// @brief Constructor base
        /// @param chipNumber Número del chip GPIO a utlizar
        /// @param pin Número del pin GPIO a utilizar
        /// @param frecuency Frecuencia del pulso PWM
        PWMOutput(const int& chipNumber, const uint8_t& pin, const float& frecuency);

        PWMOutput(const PWMOutput&) = default;
        PWMOutput(PWMOutput&&) noexcept = default; 

        virtual ~PWMOutput() noexcept;

        PWMOutput& operator=(const PWMOutput&) = default;
        PWMOutput& operator=(PWMOutput&&) noexcept = default;

        /// @brief Establece el duty cycle del pulso PWM
        /// @param dutyCycle valor en porcentaje que representa el duty cycle
        void set(const float& dutyCycle);

        /// @brief Establece en 0% el duty cycle
        void desactivate();

    private:

        int chipNumber_m;
        uint8_t pin_m;
        float frecuency_m;

        void claimOutput();
        void writeHelper(const float& dutyCycle);
    }
}

#endif // !PWM_OUTPUT_HEADER