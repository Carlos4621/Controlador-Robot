#pragma once
#ifndef OUTPUT_PIN_HEADER
#define OUTPUT_PIN_HEADER

#include <cstdint>
#include <stdexcept>
#include <lgpio.h>

namespace My {

    /*
        TODO:
        - Idea? Al hacer pines que tengan el mismo número de chip o, en el caso de PWMOUtput, también su frecuencia, se está desperdiciando por lo menos
          8 bytes en información duplicada, esto es un problema. Tal vez pueda hacer clases con pines que compartan el mismo chip o, en su dado caso,
          la frecuencia del pulso PWM
    */

    /// @brief Clase que representa un pin de salida genérico, ideado para la gestión automática de pines
    class OutputPin {
    public:

        /// @brief Constructor base
        /// @param chipNumber Número del chip GPIO a controlar
        /// @param pin Pin GPIO a controlar
        OutputPin(const int& chipNumber, const uint8_t& pin);

        OutputPin(const OutputPin&) = default;
        OutputPin(OutputPin&&) noexcept = default;

        virtual ~OutputPin() noexcept;

        OutputPin& operator=(const OutputPin&) = default;
        OutputPin& operator=(OutputPin&&) noexcept = default;

        /// @brief Obtiene el número del pin manejado
        /// @return Número del pin manejado
        [[nodiscard]] uint8_t getPinNumber() const noexcept;

        /// @brief Obtiene el número del chip GPIO que se está usando
        /// @return Número del chip GPIO en uso
        [[nodiscard]] int getChipNumber() const noexcept;

    private:

        int chipNumber_m;
        uint8_t pin_m;

        void claimOutput();
    };
}

#endif // !OUTPUT_PIN_HEADER