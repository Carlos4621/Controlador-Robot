#include "ThermalCameraVisualizer.h"

My::ThermalCameraVisualizer::ThermalCameraVisualizer(const float &horizontalScaleFactor,
    const float &verticalScaleFactor, const cv::InterpolationFlags &interpolationMode) :
    params_m{horizontalScaleFactor, verticalScaleFactor, interpolationMode} {
}

My::ThermalCameraVisualizer::ThermalCameraVisualizer(const ThermalCameraVisualizerParams &params) : 
    params_m{ params } {
}

void My::ThermalCameraVisualizer::convertImage(const std::array<float, 768> &thermalImage)
{
    cv::Mat temperatura_mat(24, 32, CV_8UC1);

    for (int i = 0; i < 24; ++i) {
        for (int j = 0; j < 32; ++j) {
            temperatura_mat.at<uint8_t>(i, j) = static_cast<uint8_t>(thermalImage[i * 32 + j]);
        }
    }

    cv::normalize(temperatura_mat, temperatura_mat, 0, 255, cv::NORM_MINMAX);
    cv::applyColorMap(temperatura_mat, temperatura_mat, cv::COLORMAP_JET);

    cv::resize(temperatura_mat, temperatura_mat, cv::Size(), params_m.horizontalScaleFactor,
        params_m.verticalScaleFactor, cv::INTER_CUBIC);

    lastImage_m = temperatura_mat;
}

cv::Mat My::ThermalCameraVisualizer::getImage() const noexcept {
    return lastImage_m;
}