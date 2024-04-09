#pragma once
#ifndef CAR_CONTROLLER_HEADER
#define CAR_CONTROLLER_HEADER

#include "WiFiXboxReceiver.h"
#include "PWMHBridge.h"

namespace My {

    /// @brief Clase que permite que cualquier control de Xbox controle dos modulos HW-039
    class CarController : public WiFiXboxReceiver {
    public:
        
        /// @brief Constructor base
        /// @param serverParams Paquete de parametros para el servidor
        /// @param ioContext Contexto de E/S
        /// @param rightMotor Paquete de parametros para el motor derecho
        /// @param leftMotor Paquete de parametros para el motor izquierdo
        CarController(const ServerParams& serverParams, boost::asio::io_context& ioContext, 
        const PWMHBridgeParams& rightMotor, const PWMHBridgeParams& leftMotor);

        CarController(const CarController&) = default;
        CarController(CarController&&) noexcept = default;

        virtual ~CarController() noexcept = default;

        /// @brief Aplica los ultimos valores leidos de receiveControllerData()
        void applyChanges();

    private:

        PWMHBridge rightMotor_m;
        PWMHBridge leftMotor_m;
        
    };

}

#endif //!CAR_CONTROLLER_HEADER