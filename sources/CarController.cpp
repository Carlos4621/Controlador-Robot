#include "CarController.h"

My::CarController::CarController(const ServerParams &serverParams, 
boost::asio::io_context &ioContext, const HW039ControllerParams &rightMotor,
 const HW039ControllerParams &leftMotor) : WiFiXboxReceiver{ serverParams, ioContext },
  motors_m{ rightMotor, leftMotor } {
}

// TODO: Mejorar esta cosa
void My::CarController::applyChanges() {
    motors_m.first.setRelative(getControllerData().leftStick.first);
    motors_m.second.setRelative(getControllerData().leftStick.first);
}
