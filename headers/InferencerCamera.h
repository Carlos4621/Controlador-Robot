#pragma once
#ifndef ROBOT_CAMERA_HEADER
#define ROBOT_CAMERA_HEADER

#include <opencv2/opencv.hpp>
#include <vector>
#include <string_view>
#include "Inferencer.h"

namespace My {

	/*
		TODO:
		- Agregar funcionamiento de reconocimiento
	*/

	/// @brief Clase que representa una c�mara que ofrece funciones de reconocimiento
	class InferencerCamera {
	public:

		/// @brief Constructor base
		/// @param cameraID ID de la c�mara a usar
		explicit InferencerCamera(const uint8_t& cameraID);

		InferencerCamera(const InferencerCamera&) = default;
		InferencerCamera(InferencerCamera&&) noexcept = default;

		virtual ~InferencerCamera() noexcept = default;

		InferencerCamera& operator=(const InferencerCamera&) = default;
		InferencerCamera& operator=(InferencerCamera&&) noexcept = default;

		/// @brief Toma un frame de la c�mara
		void updateCamara();

		/// @brief Obtiene la �ltima imagen guardada con updateCamara()
		/// @return La �ltima imagen guardada
		[[nodiscard]] cv::Mat getLastImage() const noexcept;

	private:
	
		cv::VideoCapture camera_m;
		cv::Mat lastImage_m;

	};
}

#endif // !ROBOT_CAMERA_HEADER