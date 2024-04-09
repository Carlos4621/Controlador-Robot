#include "CarController.h"

My::CarController::CarController(const ServerParams &serverParams, 
boost::asio::io_context &ioContext, const PWMHBridgeParams &rightMotor,
 const PWMHBridgeParams &leftMotor) : WiFiXboxReceiver{ serverParams, ioContext },
  rightMotor_m{ rightMotor }, leftMotor_m{ leftMotor } {
}

// TODO: Mejorar esta cosa
void My::CarController::applyChanges() {
  const auto controllerData{ getControllerData() };

  if (controllerData.leftStick.second > 0 || controllerData.leftStick.second > 0) {
    rightMotor_m.setRelative(controllerData.leftStick.second);
    leftMotor_m.setRelative(controllerData.leftStick.second);
  }
  else if (controllerData.RB || controllerData.LB) {
    rightMotor_m.setRelative(65 * (controllerData.RB ? -1 : 1));
    leftMotor_m.setRelative(65 * (controllerData.LB ? 1 : -1));
  }
  else {
    rightMotor_m.stopMotor();
    leftMotor_m.stopMotor();
  }
}
