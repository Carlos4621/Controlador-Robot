#include "WiFiThermalCameraReceiver.h"

boost::asio::io_context context;

int main() {
    My::ServerParams sv{ "ip", "port" };

    My::WiFiThermalCameraReceiver vis{ context, sv, {7, 7, cv::INTER_CUBIC} };

    vis.waitConnection();

    cv::Mat frame;
    cv::namedWindow("xxx");
    while (true) {
        vis.receiveThermalImage();

        frame = vis.getImage();

        cv::imshow("xxx", frame);

        cv::waitKey(1);
    }
}