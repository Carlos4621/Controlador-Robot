#pragma once
#ifndef WIFI_ROBOT_CAMERA_RECEIVER
#define WIFI_ROBOT_CAMERA_RECEIVER

#include <opencv2/opencv.hpp>
#include "WiFiDeserializer.h"

namespace My {

	/// @brief Clase que permite una conexión TCP y recibir imágenes para su decodificación con cv::imdecode
	class WiFiRobotCameraReceiver : private WiFiDeserializer {
	public:

		/// @brief Constructor base
		/// @param decodeMode Modo de decodificación de la imagen recibida
		/// @param serverParams Parámetros del servidor
		/// @param context Contexto del OS
		WiFiRobotCameraReceiver(const cv::ImreadModes& decodeMode, const ServerParams& serverParams, boost::asio::io_context& context);

		WiFiRobotCameraReceiver(const WiFiRobotCameraReceiver&) = default;
		WiFiRobotCameraReceiver(WiFiRobotCameraReceiver&&) noexcept = default;

		WiFiRobotCameraReceiver& operator=(const WiFiRobotCameraReceiver&) = default;
		WiFiRobotCameraReceiver& operator=(WiFiRobotCameraReceiver&&) noexcept = default;
		
		using WiFiDeserializer::waitConnection;

		/// @brief Recibe la información enviada para su obtención con getCameraData()
		void receiveCameraData();

		/// @brief Obtiene la última imagen guardada con receiveCameraData()
		/// @return Última imagen guardada
		cv::Mat getCameraData() noexcept;

	private:
		std::vector<unsigned char> buffer_m;
		cv::ImreadModes decodeMode_m;

		cv::Mat lastImage_m;
	};
}

#endif // !WIFI_ROBOT_CAMERA_RECEIVER