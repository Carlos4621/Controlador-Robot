#pragma once
#ifndef WIFI_ROBOT_CAMERA_HEADER
#define WIFI_ROBOT_CAMERA_HEADER

#include "WiFiSerializer.h"
#include "RobotCamera.h"
#include "EncodeParams.h"

namespace My {

	/// @brief Clase que permite una conexi�n TCP y env�a im�genes de una c�mara usando cv::imencode para evitar la
	///        sobrecarga de red
	class WiFiRobotCamera : public RobotCamera, private WiFiSerializer {
	public:

		/// @brief Constructor base
		/// @param encodeParams Par�metros para la encodificaci�n de la imagen
		/// @param serverParams Par�metros del servidor
		/// @param context Contexto del OS
		/// @param cameraID ID de la c�mara a usar
		WiFiRobotCamera(const EncodeParams& encodeParams, const ServerParams& serverParams, boost::asio::io_context& context, 
			const uint8_t& cameraID);

		WiFiRobotCamera(const WiFiRobotCamera&) = default;
		WiFiRobotCamera(WiFiRobotCamera&&) noexcept = default;

		WiFiRobotCamera& operator=(const WiFiRobotCamera&) = default;
		WiFiRobotCamera& operator=(WiFiRobotCamera&&) noexcept = default;

		using WiFiSerializer::startConnection;

		/// @brief Env�a la imagen codificada
		void sendCameraData();

	private:
		std::vector<unsigned char> buffer_m;
		EncodeParams params_m;

		void encodeLastImage();
	};
}

#endif // !WIFI_ROBOT_CAMERA_HEADER