#include "CarController.h"

My::CarController::CarController(const ServerParams &serverParams, 
boost::asio::io_context &ioContext, const HW039ControllerParams &rightMotor,
 const HW039ControllerParams &leftMotor) : WiFiXboxReceiver{ serverParams, ioContext },
  rightMotor_m{ rightMotor }, leftMotor_m{ leftMotor } {
}

// TODO: Mejorar esta cosa
void My::CarController::applyChanges() {
  const auto controllerData{ getControllerData() };

  if (controllerData.leftStick.second > 5 || controllerData.leftStick.second < -5) {
    rightMotor_m.setRelative(controllerData.leftStick.second);
    leftMotor_m.setRelative(controllerData.leftStick.second);
  }
  else if (controllerData.leftStick.first > 5 || controllerData.leftStick.first < -5) {
    rightMotor_m.setRelative(controllerData.leftStick.first * (controllerData.leftStick.first < -5 ? -1 : 1));
    leftMotor_m.setRelative(controllerData.leftStick.first * (controllerData.leftStick.first > 5 ? -1 : 1));
  }
  else {
    rightMotor_m.stopMotor();
    leftMotor_m.stopMotor();
  }
}
