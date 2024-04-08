#include "WiFiPredictorCamera.h"

int main() {

    // Cambiar
    My::ServerParams connectionData{ "ip", "port" };

    boost::asio::io_context context;

    My::EncodeParams encodeParams{ "jpg", {} };
    My::YOLOv8ModelParams hazmatModel{ "/home/carlos4621/Escritorio/Controlador-Robot/resources/hazmatModel.onnx",
        cv::Size{640, 640}, "/home/carlos4621/Escritorio/Controlador-Robot/resources/hazmatClasses.txt",
        false };

    My::WiFiPredictorCamera camera{encodeParams, connectionData, context, 0, {hazmatModel}};

    camera.startConnection();
    camera.sendModelsSize();

    while (true) {
        camera.updateCamara();
        camera.applyAllModels();
        camera.sendCameraData();
        camera.sendAllPredictedData();

        cv::waitKey(1);
    }
     

}