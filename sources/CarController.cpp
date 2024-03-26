#include "CarController.h"

My::CarController::CarController(const ServerParams &serverParams, 
boost::asio::io_context &ioContext, const HW039ControllerParams &rightMotor,
 const HW039ControllerParams &leftMotor) : WiFiXboxReceiver{ serverParams, ioContext },
  motors_m{ rightMotor, leftMotor } {
}

// TODO: Mejorar esta cosa
void My::CarController::applyChanges() {
  const auto controllerData{getControllerData()};

  if (controllerData.leftStick.first > 5 || controllerData.leftStick.first < -5) {
    motors_m.first.setRelative(getControllerData().leftStick.first);
    motors_m.second.setRelative(getControllerData().leftStick.first);
  }
  else if (controllerData.leftStick.second > 5 || controllerData.leftStick.second < -5) {
    motors_m.first.setRelative(controllerData.leftStick.second * (controllerData.leftStick.second < -5 ? -1 : 1));
    motors_m.second.setRelative(controllerData.leftStick.second * (controllerData.leftStick.second > 5 ? -1 : 1));
  }
}
