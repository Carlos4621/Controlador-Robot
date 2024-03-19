#pragma once
#ifndef WIFI_ROBOT_CAMERA_RECEIVER
#define WIFI_ROBOT_CAMERA_RECEIVER

#include <opencv2/opencv.hpp>
#include "WiFiDeserializer.h"

namespace My {

	/// @brief Clase que permite una conexi�n TCP y recibir im�genes para su decodificaci�n con cv::imdecode
	class WiFiRobotCameraReceiver : private WiFiDeserializer {
	public:

		/// @brief Constructor base
		/// @param decodeMode Modo de decodificaci�n de la imagen recibida
		/// @param serverParams Par�metros del servidor
		/// @param context Contexto del OS
		WiFiRobotCameraReceiver(const cv::ImreadModes& decodeMode, const ServerParams& serverParams, boost::asio::io_context& context);

		WiFiRobotCameraReceiver(const WiFiRobotCameraReceiver&) = default;
		WiFiRobotCameraReceiver(WiFiRobotCameraReceiver&&) noexcept = default;

		WiFiRobotCameraReceiver& operator=(const WiFiRobotCameraReceiver&) = default;
		WiFiRobotCameraReceiver& operator=(WiFiRobotCameraReceiver&&) noexcept = default;
		
		using WiFiDeserializer::waitConnection;

		/// @brief Recibe la informaci�n enviada para su obtenci�n con getCameraData()
		void receiveCameraData();

		/// @brief Obtiene la �ltima imagen guardada con receiveCameraData()
		/// @return �ltima imagen guardada
		[[nodiscard]] cv::Mat getCameraData() noexcept;

	private:
		std::vector<unsigned char> buffer_m;
		cv::ImreadModes decodeMode_m;

		cv::Mat lastImage_m;
	};
}

#endif // !WIFI_ROBOT_CAMERA_RECEIVER