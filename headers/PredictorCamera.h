#pragma once
#ifndef ROBOT_CAMERA_HEADER
#define ROBOT_CAMERA_HEADER

#include <opencv2/opencv.hpp>
#include <vector>
#include "YOLOv8Model.h"
#include "PredictionsData.h"

namespace My {

	/// @brief Clase que representa una cámara que ofrece funciones de reconocimiento
	class PredictorCamera {
	public:

		/// @brief Constructor base
		/// @param cameraID ID de la cámara a usar
		/// @param modelsParams Lista de parámetros para los modelos a usar
		PredictorCamera(const uint8_t& cameraID, std::initializer_list<YOLOv8ModelParams> modelsParams);

		PredictorCamera(const PredictorCamera&) = default;
		PredictorCamera(PredictorCamera&&) noexcept = default;

		virtual ~PredictorCamera() noexcept = default;

		PredictorCamera& operator=(const PredictorCamera&) = default;
		PredictorCamera& operator=(PredictorCamera&&) noexcept = default;

		/// @brief Toma un frame de la cámara
		void updateCamara();

		/// @brief Aplica el modelo n a la última imagen tomada
		/// @param index Índice del modelo a usar
		/// @param modelConfidenceThreshold Threshold de la confidencia. Default = 0.25
        /// @param modelScoreThreshold Threshold del score. Default = 0.45
        /// @param modelNMSThreshold Threshold del NMS. Default = 0.5
		void applyModel(const size_t& index, const double& modelConfidenceThreshold = 0.25f, const double& modelScoreThreshold = 0.45f, 
			const double& modelNMSThreshold = 0.5f);

		/// @brief Aplica todos los modelos a la última imagen tomada
		/// @param modelConfidenceThreshold Threshold de la confidencia. Default = 0.25
        /// @param modelScoreThreshold Threshold del score. Default = 0.45
        /// @param modelNMSThreshold Threshold del NMS. Default = 0.5
		void applyAllModels(const double& modelConfidenceThreshold = 0.25f, const double& modelScoreThreshold = 0.45f, const double& modelNMSThreshold = 0.5f);

		/// @brief Obtiene el vector con los datos de las predicciones
		/// @param index Índice del modelo cuyos datos se quieren obtener
		/// @return Vector con todas las predicciones hechas
		[[nodiscard]] std::vector<PredictionsData> getPredictions(const size_t& index) const;

		/// @brief Obtiene todos las predicciones de todos los modelos
		/// @return Vector de vectores con todas las predicciones por modelo
		[[nodiscard]] std::vector<std::vector<PredictionsData> > getAllPredictions() const noexcept;

		/// @brief Obtiene el número de modelos guardados
		/// @return El número de modelos
		[[nodiscard]] size_t getModelsSize() const noexcept;

		/// @brief Obtiene la última imagen guardada con updateCamara()
		/// @return La última imagen guardada
		[[nodiscard]] cv::Mat getImage() const noexcept;

	private:
	
		cv::VideoCapture camera_m;
		cv::Mat image_m;
		std::vector<YOLOv8Model> models_m;
		std::vector<std::vector<PredictionsData> > PredictionsData_m;

	};
}

#endif // !ROBOT_CAMERA_HEADER