#pragma once
#ifndef DIGITAL_OUTPUT_HEADER
#define DIGITAL_OUTPUT_HEADER

#include "OutputPin.h"

namespace My {

    /// @brief Clase que se encarga de manejar un pin de salidas digitales
    class DigitalOutput : public OutputPin {
    public:

        /// @brief Contructor base
        /// @param chipNumber Número del chip GPIO a controlar, se consigue con (...)
        /// @param pin Número del pin GPIO a controlar
        DigitalOutput(const int& chipNumber, const uint8_t& pin);

        DigitalOutput(const DigitalOutput&) = default;
        DigitalOutput(DigitalOutput&&) noexcept = default;

        virtual ~DigitalOutput() noexcept = default;

        DigitalOutput& operator=(const DigitalOutput&) = default;
        DigitalOutput& operator=(DigitalOutput&&) noexcept = default;

        /// @brief Activa el pin en uso
        void activate();

        /// @brief Desactiva el pin en uso
        void desactivate();

        /// @brief Si el pin está activado, lo desactiva y viceversa
        void toggle();

        /// @brief Coloca el pin en el estado deseado: true = activado, false = desactivado
        /// @param newState Estado a colocar
        void set(const bool& newState);

        /// @brief Determina si el pin está actualmente activo
        /// @return Estado actual del pin
        bool isActivated() const noexcept;

    private:

        bool state_m{ false };
    };
}

#endif // !DIGITAL_OUTPUT_HEADER