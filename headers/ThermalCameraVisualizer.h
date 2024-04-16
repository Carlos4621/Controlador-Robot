#pragma once
#ifndef THERMAL_CAMERA_VISUALIZER_HEADER
#define THERMAL_CAMERA_VISUALIZER_HEADER

#include <opencv4/opencv2/opencv.hpp>
#include <span>

namespace My {

    /*
        TODO:
        - Eliminar números mágicos del tamaño de la imagen?
    */

    /// @brief Struct con los parámetros de una ThermalCameraVisualizer
    struct ThermalCameraVisualizerParams {
		float horizontalScaleFactor;
		float verticalScaleFactor;
		cv::InterpolationFlags interpolationMode;
    };

    /// @brief Clase encargada de convertir una "imagen" de ThermalCamera a una tipo cv::Mat.
    /// Ideada para trasladar la carga de cómputo a otro dispositivo usando WiFi
    class ThermalCameraVisualizer {
    public:

        /// @brief Constructor base
        /// @param horizontalScaleFactor Factor por el que multiplicará el ancho de la imagen (32)
        /// @param verticalScaleFactor Factor por el que se multiplicará el largo de la imagen (24)
        /// @param interpolationMode Técnica a usar para la interpolación de la imagen
        ThermalCameraVisualizer(const float& horizontalScaleFactor, 
        const float& verticalScaleFactor, const cv::InterpolationFlags& interpolationMode);

		/// @brief Constructor con paquete de parámetros
		/// @param params Paquete con los parámetros a usar
		explicit ThermalCameraVisualizer(const ThermalCameraVisualizerParams& params);

		ThermalCameraVisualizer(const ThermalCameraVisualizer&) = default;
		ThermalCameraVisualizer(ThermalCameraVisualizer&&) noexcept = default;

		virtual ~ThermalCameraVisualizer() noexcept = default;

		ThermalCameraVisualizer& operator=(const ThermalCameraVisualizer&) = default;
		ThermalCameraVisualizer& operator=(ThermalCameraVisualizer&&) noexcept = default;

        /// @brief Convierte el array devuelto por ThermalCamera a un cv::Mat para su obtención con getImage()
        /// @param thermalImage Array con los valores de las temperaturas
        void convertImage(const std::array<float, 768>& thermalImage);

        /// @brief Obtiene la última imagen convertida con convertImage
        /// @return Mat 2d con una imagen que representa zonas de calor
        [[nodiscard]] cv::Mat getImage() const noexcept;

    private:

		ThermalCameraVisualizerParams params_m;

        cv::Mat lastImage_m;
    };
}

#endif // !THERMAL_CAMERA_VISUALIZER_HEADER