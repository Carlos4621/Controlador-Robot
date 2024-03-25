#pragma once
#ifndef INFERENCER_HEADER
#define INFERENCER_HEADER

#include <fstream>
#include <vector>
#include <string>
#include <string_view>
#include <opencv2/opencv.hpp>
#include "InferenceData.h"

namespace My {

    struct InferencerParams {
        std::string modelPath;
        cv::Size modelInputSize;
        std::string classNamesPath;
        bool runWithCUDA;
    };
    
    /// @brief Clase que permite el uso de modelos YOLOv8 exportados a .onnx
    class Inferencer {
    public:

        /// @brief Constructor base
        /// @param onnxModelPath Ruta al modelo .onnx
        /// @param modelInputShape Tamaño de las imágenes de entrada del modelo
        /// @param classNamesPath Ruta a los nombres de las classes dependiendo su ID
        /// @param runWithCuda Decidir si usar CUDA. Default = true
        Inferencer(std::string_view onnxModelPath, const cv::Size& modelInputShape, std::string_view classNamesPath, const bool& runWithCuda = true);

        /// @brief Constructor con paquete de parámetros
        /// @param params Paquete de parámetros del inferenciador
        explicit Inferencer(const InferencerParams& params);

        Inferencer(const Inferencer&) = default;
        Inferencer(Inferencer&&) noexcept = default;

        virtual ~Inferencer() noexcept = default;

        Inferencer& operator=(const Inferencer&) = default;
        Inferencer& operator=(Inferencer&&) noexcept = default;

        /// @brief Aplica el modelo a la imagen proporcionada y devuelve las inferencias
        /// @param inputImage Imagen a usar
        /// @param modelConfidenceThreshold Threshold de la confidencia. Default = 0.25
        /// @param modelScoreThreshold Threshold del score. Default = 0.45
        /// @param modelNMSThreshold Threshold del NMS. Default = 0.5
        /// @return Vector con los datos de las inferencias
        [[nodiscard]] std::vector<InferenceData> getInferences(const cv::Mat& inputImage, const double& modelConfidenceThreshold = 0.25f,
            const double& modelScoreThreshold = 0.45f, const double& modelNMSThreshold = 0.5f);

    private:

        std::vector<std::string> classNames_m;

        const cv::Size2f modelInputSize_m;

        cv::dnn::Net network_m;

        void loadClasses(std::string_view path);
        void loadOnnxNetwork(std::string_view path, const bool& cudaEnabled);
    };
}
#endif // INFERENCE_H