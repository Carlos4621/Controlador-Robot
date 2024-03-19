#include <iostream>
#include "Inferencer.h"

using namespace std;
using namespace cv;

int main() {
    
    const std::string modelPath{ "/home/carlos4621/Escritorio/Controlador-Robot/resources/hazmatModel.onnx" };
    const std::string classesPath{ "/home/carlos4621/Escritorio/Controlador-Robot/resources/hazmatClasses.txt" };

    My::Inferencer inf{ modelPath, cv::Size(640, 640), classesPath, false };

    std::vector<std::string> imageNames;
    imageNames.emplace_back("/home/carlos4621/Escritorio/Controlador-Robot/resources/hazmatTest1.jpg");
    imageNames.emplace_back("/home/carlos4621/Escritorio/Controlador-Robot/resources/hazmatTest2.jpg");
    imageNames.emplace_back("/home/carlos4621/Escritorio/Controlador-Robot/resources/nothing.jpg");

    cv::Scalar boxColor{ 255, 0, 255 };
    for (const auto& i : imageNames) {

        auto frame{ cv::imread(i) };

        auto inferences{ inf.getInferences(frame) };

        std::cout << "Detecciones:" << inferences.size() << std::endl;

        for (const auto& j : inferences) {

            cv::rectangle(frame, j.bouncingBox, boxColor, 2);

            const auto classString{ j.className + ' ' + std::to_string(j.confidence).substr(0, 4) };
            const auto textSize{ cv::getTextSize(classString, cv::FONT_HERSHEY_DUPLEX, 1, 2, 0) };
            cv::Rect textBox{ j.bouncingBox.x, j.bouncingBox.y - 40, textSize.width + 10, textSize.height + 20 };

            cv::rectangle(frame, textBox, boxColor, cv::FILLED);
            cv::putText(frame, classString, cv::Point{ j.bouncingBox.x + 5, j.bouncingBox.y - 10 }, cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar{ 0, 0, 0 }, 2, 0);
        }

        cv::imshow("Inference", frame);

        cv::waitKey();
    }
}
