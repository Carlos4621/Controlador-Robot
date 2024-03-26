#pragma once
#ifndef WIFI_ROBOT_CAMERA_HEADER
#define WIFI_ROBOT_CAMERA_HEADER

#include "WiFiSerializer.h"
#include "PredictorCamera.h"
#include "EncodeParams.h"

namespace My {

	/// @brief Clase que permite una conexión TCP y envía imágenes de una cámara con sus respectivas predicciones usando cv::imencode para evitar la
	///        sobrecarga de red
	class WiFiPredictorCamera : public PredictorCamera, private WiFiSerializer {
	public:

		/// @brief Constructor base
		/// @param encodeParams Parámetros para la encodificación de la imagen
		/// @param serverParams Parámetros del servidor
		/// @param context Contexto del OS
		/// @param cameraID ID de la cámara a usar
		/// @param modelParams Lista con los paquetes de parámetros a usar por los modelos
		WiFiPredictorCamera(const EncodeParams& encodeParams, const ServerParams& serverParams, boost::asio::io_context& context, 
			const uint8_t& cameraID, std::initializer_list<YOLOv8ModelParams> modelsParams);

		WiFiPredictorCamera(const WiFiPredictorCamera&) = default;
		WiFiPredictorCamera(WiFiPredictorCamera&&) noexcept = default;

		virtual ~WiFiPredictorCamera() noexcept = default;

		WiFiPredictorCamera& operator=(const WiFiPredictorCamera&) = default;
		WiFiPredictorCamera& operator=(WiFiPredictorCamera&&) noexcept = default;

		using WiFiSerializer::startConnection;

		/// @brief Envía la imagen codificada
		void sendCameraData();

		/// @brief Envía un vector con las predicciones del modelo n
		/// @param index Índice del modelo a enviar su data
		void sendPredictedData(const size_t& index);

		/// @brief Envía todos los vectores con las predicciones de todos los modelos
		void sendAllPredictedData();

	private:
	
		std::vector<unsigned char> buffer_m;
		EncodeParams params_m;

		void encodeLastImage();
	};
}

#endif // !WIFI_ROBOT_CAMERA_HEADER