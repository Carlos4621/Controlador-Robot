#pragma once
#ifndef DIGITAL_OUTPUT_HEADER
#define DIGITAL_OUTPUT_HEADER

#include <cstdint>
#include <stdexcept>
#include <lgpio.h>

namespace My {

    /// @brief Clase que se encarga de manejar un pin de salidas digitales
    class DigitalOutput {
    public:

        /// @brief Contructor base
        /// @param chipNumber Número del chip GPIO a controlar, se consigue con (...)
        /// @param pin Número del pin GPIO a controlar
        DigitalOutput(const int& chipNumber, const uint8_t& pin, const bool& initialState = false);

        DigitalOutput(const DigitalOutput&) = default;
        DigitalOutput(DigitalOutput&&) noexcept = default;

        virtual ~DigitalOutput() noexcept;

        DigitalOutput& operator=(const DigitalOutput&) = default;
        DigitalOutput& operator=(DigitalOutput&&) noexcept = default;


        /// @brief Activa el pin almacenado
        void activate();

        /// @brief Desactiva el pin almacenado
        void desactivate();

        /// @brief Si el pin está activado, lo desactiva y viceversa
        void toggle();

        /// @brief Escribe el valor deseado en la salida
        /// @param newState Estado a escribir
        void set(const bool& newState);

        /// @brief Determina si el pin está actualmente activo
        /// @return Estado actual del pin
        bool isActivated() const noexcept;

    private:

        int chipNumber_m;
        uint8_t pin_m;
        bool state_m;

        void claimOutput();
    };
}

#endif // !DIGITAL_OUTPUT_HEADER