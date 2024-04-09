#include "WiFiXbox.h"

int main() {

    // Cambiar dependiendo a conexión
    My::ServerParams connectionData{ "10.100.105.75", "50000" };

    boost::asio::io_context context;

    My::WiFiXbox controller{connectionData, context, 0};

    controller.startConnection();

    while (true) {
        controller.updateController();
        controller.sendControllerData();

        cv::waitKey(1);
    }
    
}