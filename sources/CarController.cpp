#include "CarController.h"

My::CarController::CarController(const ServerParams &serverParams, 
boost::asio::io_context &ioContext, const HW039ControllerParams &rightMotor,
 const HW039ControllerParams &leftMotor) : WiFiXboxReceiver{ serverParams, ioContext },
  rightMotor_m{ rightMotor }, leftMotor_m{ leftMotor } {
}

// TODO: Mejorar esta cosa
void My::CarController::applyChanges() {
  const auto controllerData{getControllerData()};

  if (controllerData.leftStick.first > 5 || controllerData.leftStick.first < -5) {
    rightMotor_m.setRelative(getControllerData().leftStick.first);
    leftMotor_m.setRelative(getControllerData().leftStick.first);
  }
  else if (controllerData.leftStick.second > 5 || controllerData.leftStick.second < -5) {
    rightMotor_m.setRelative(controllerData.leftStick.second * (controllerData.leftStick.second < -5 ? -1 : 1));
    leftMotor_m.setRelative(controllerData.leftStick.second * (controllerData.leftStick.second > 5 ? -1 : 1));
  }
}
