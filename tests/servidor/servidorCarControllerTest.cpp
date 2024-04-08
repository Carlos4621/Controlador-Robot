#include "CarController.h"
#include <iostream>

int main() {

    //Cambiar
    My::ServerParams connectionData{ "ip", "port" };

    boost::asio::io_context context;

    auto chip{ lgGpiochipOpen(4) };

    if (chip < 0) {
        std::cout << "Unable to open the GPIO chip" << std::endl;
        return chip;
    }

    // Cambiar
    My::HW039ControllerParams rightMotor{ chip, 17, 27, 10000 };
    My::HW039ControllerParams leftMotor{ chip, 23, 24, 10000 };

    My::CarController controller{ connectionData, context, rightMotor, leftMotor };

    controller.waitConnection();

    while (true) {
        controller.receiveControllerData();
        controller.applyChanges();

        cv::waitKey(1);
    }
    
}