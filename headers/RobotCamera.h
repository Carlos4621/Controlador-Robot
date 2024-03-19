#pragma once
#ifndef ROBOT_CAMERA_HEADER
#define ROBOT_CAMERA_HEADER

#include <opencv2/opencv.hpp>
#include <vector>
#include <string_view>

namespace My {

	/*
		TODO:
		- Agregar funcionamiento de reconocimiento
	*/

	/// @brief Clase que representa una c�mara que ofrece funciones de reconocimiento
	class RobotCamera {
	public:

		/// @brief Constructor base
		/// @param cameraID ID de la c�mara a usar
		explicit RobotCamera(const uint8_t& cameraID);

		RobotCamera(const RobotCamera&) = default;
		RobotCamera(RobotCamera&&) noexcept = default;

		RobotCamera& operator=(const RobotCamera&) = default;
		RobotCamera& operator=(RobotCamera&&) noexcept = default;

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