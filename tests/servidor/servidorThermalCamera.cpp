#include "WiFiThermalCamera.h"

boost::asio::io_context context;

int main() {
    My::ServerParams sv{ "ip", "port" };

    My::WiFiThermalCamera cam{ context, sv, 0x33 };

    cam.startConnection();

    while(true) {
        cam.updateCamera();
        cam.sendThermalImageData();

        cv::waitKey(1);
    }
}