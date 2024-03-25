#pragma once
#ifndef WIFI_ROBOT_CAMERA_HEADER
#define WIFI_ROBOT_CAMERA_HEADER

#include "WiFiSerializer.h"
#include "InferencerCamera.h"
#include "EncodeParams.h"

namespace My {

	/// @brief Clase que permite una conexi�n TCP y env�a im�genes de una c�mara usando cv::imencode para evitar la
	///        sobrecarga de red
	class WiFiInferencerCamera : public InferencerCamera, private WiFiSerializer {
	public:

		/// @brief Constructor base
		/// @param encodeParams Par�metros para la encodificaci�n de la imagen
		/// @param serverParams Par�metros del servidor
		/// @param context Contexto del OS
		/// @param cameraID ID de la c�mara a usar
		WiFiInferencerCamera(const EncodeParams& encodeParams, const ServerParams& serverParams, boost::asio::io_context& context, 
			const uint8_t& cameraID, std::initializer_list<InferencerParams> Inferences);

		WiFiInferencerCamera(const WiFiInferencerCamera&) = default;
		WiFiInferencerCamera(WiFiInferencerCamera&&) noexcept = default;

		virtual ~WiFiInferencerCamera() noexcept = default;

		WiFiInferencerCamera& operator=(const WiFiInferencerCamera&) = default;
		WiFiInferencerCamera& operator=(WiFiInferencerCamera&&) noexcept = default;

		using WiFiSerializer::startConnection;

		/// @brief Env�a la imagen codificada
		void sendCameraData();

		/// @brief Envía un vector con las inferencias del inferenciador n
		/// @param index Índice del inferenciador a enviar su data
		void sendInferenceData(const size_t& index);

		/// @brief Envía todos los vectores con las inferencias de todos los inferenciadores
		void sendAllInferenceData();

	private:
	
		std::vector<unsigned char> buffer_m;
		EncodeParams params_m;

		void encodeLastImage();
	};
}

#endif // !WIFI_ROBOT_CAMERA_HEADER