#include "CarController.h"
#include <iostream>

int main() {

    //Cambiar
    My::ServerParams connectionData{ "ip", "50000" };

    boost::asio::io_context context;

    auto chip{ lgGpiochipOpen(4) };

    if (chip < 0) {
        std::cout << "Unable to open the GPIO chip" << std::endl;
        return chip;
    }

    // Cambiar
    My::PWMHBridgeParams rightMotor{ chip, 17, 27, 10000 };
    My::PWMHBridgeParams leftMotor{ chip, 23, 24, 10000 };

    My::CarController controller{ connectionData, context, rightMotor, leftMotor };

    controller.waitConnection();

    while (true) {
        controller.receiveControllerData();
        controller.applyChanges();

        cv::waitKey(1);
    }
    
}