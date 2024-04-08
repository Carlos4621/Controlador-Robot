#include "WiFiXboxReceiver.h"
#include <iostream>

int main() {

    // Solo cambiar puerto
    My::ServerParams connectionData{ "ip", "port" };
    boost::asio::io_context context;

    My::WiFiXboxReceiver receiver{ connectionData, context };

    receiver.waitConnection();

    My::XboxControllerData data;
    while (true) {
        receiver.receiveControllerData();

        data = receiver.getControllerData();

        // Imprimir valores a gusto
        std::cout << data.leftStick.first << '|' << data.leftStick.second << '\n';

        cv::waitKey(1);
    }
    
}