#include "WiFiPredictorCameraReceiver.h"

int main() {

    // Cambiar
    My::ServerParams connectionData{ "ip", "port" };

    boost::asio::io_context context;

    My::WiFiPredictorCameraReceiver receiver{ cv::IMREAD_UNCHANGED, connectionData, context };

    receiver.waitConnection();
    receiver.receiveModelSize();

    cv::namedWindow("Hazmat");
    while (true) {
        receiver.receiveCameraData();
        receiver.receiveAllPredictedData();
        receiver.setBoxesToImage();

        cv::imshow("Hazmat", receiver.getCameraData());

        cv::waitKey(1);
    }
}