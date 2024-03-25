#pragma once
#ifndef ROBOT_CAMERA_HEADER
#define ROBOT_CAMERA_HEADER

#include <opencv2/opencv.hpp>
#include <vector>
#include <string_view>
#include "Inferencer.h"
#include "InferenceData.h"

namespace My {

	/*
		TODO:
		- Agregar funcionamiento de reconocimiento
	*/

	/// @brief Clase que representa una c�mara que ofrece funciones de reconocimiento
	class InferencerCamera {
	public:

		/// @brief Constructor base
		/// @param cameraID ID de la cámara a usar
		/// @param inferencers Lista de parámetros para los inferenciadores a usar
		explicit InferencerCamera(const uint8_t& cameraID, std::initializer_list<InferencerParams> inferencers);

		InferencerCamera(const InferencerCamera&) = default;
		InferencerCamera(InferencerCamera&&) noexcept = default;

		virtual ~InferencerCamera() noexcept = default;

		InferencerCamera& operator=(const InferencerCamera&) = default;
		InferencerCamera& operator=(InferencerCamera&&) noexcept = default;

		/// @brief Toma un frame de la cámara
		void updateCamara();

		/// @brief Aplica el inferenciador n a la última imagen tomada
		/// @param index Índice del inferenciador a usar
		/// @param modelConfidenceThreshold Threshold de la confidencia. Default = 0.25
        /// @param modelScoreThreshold Threshold del score. Default = 0.45
        /// @param modelNMSThreshold Threshold del NMS. Default = 0.5
		void applyInferencer(const size_t& index, const double& modelConfidenceThreshold = 0.25f, const double& modelScoreThreshold = 0.45f, 
			const double& modelNMSThreshold = 0.5f);

		/// @brief Aplica todos los inferenciadores a la última imagen tomada
		/// @param modelConfidenceThreshold Threshold de la confidencia. Default = 0.25
        /// @param modelScoreThreshold Threshold del score. Default = 0.45
        /// @param modelNMSThreshold Threshold del NMS. Default = 0.5
		void applyAllInferencers(const double& modelConfidenceThreshold = 0.25f, const double& modelScoreThreshold = 0.45f, const double& modelNMSThreshold = 0.5f);

		/// @brief Obtiene el conjunto de datos inferidos por el inferenciador n
		/// @param index Índice del inferenciador cuyos datos se quieren obtener
		/// @return Vector con todas las inferencias hechas
		[[nodiscard]] std::vector<InferenceData> getInferences(const size_t& index) const;

		/// @brief Obtiene todos las inferencias de todos los inferenciadores
		/// @return Vector de vectores con todas las inferenciaciones por inferenciador
		[[nodiscard]] std::vector<std::vector<InferenceData> > getAllInferences() const noexcept;

		/// @brief Obtiene el número de inferenciadores guardados
		/// @return El número de inferenciadores
		[[nodiscard]] size_t getInferencersSize() const noexcept;

		/// @brief Obtiene la �ltima imagen guardada con updateCamara()
		/// @return La �ltima imagen guardada
		[[nodiscard]] cv::Mat getLastImage() const noexcept;

	private:
	
		cv::VideoCapture camera_m;
		cv::Mat lastOriginalImage_m;
		std::vector<Inferencer> inferencers_m;
		std::vector<std::vector<InferenceData> > inferencesData_m;

	};
}

#endif // !ROBOT_CAMERA_HEADER