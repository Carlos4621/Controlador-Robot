#pragma once
#ifndef WIFI_ROBOT_CAMERA_RECEIVER
#define WIFI_ROBOT_CAMERA_RECEIVER

#include <opencv2/opencv.hpp>
#include "WiFiDeserializer.h"
#include "PredictionsData.h"

namespace My {

	/// @brief Clase que permite una conexión TCP y recibir imágenes para su decodificación con cv::imdecode, al igual que los datos de las predicciones hechas
	class WiFiPredictorCameraReceiver : private WiFiDeserializer {
	public:

		/// @brief Constructor base
		/// @param decodeMode Modo de decodificación de la imagen recibida
		/// @param serverParams Parámetros del servidor
		/// @param context Contexto del OS
		WiFiPredictorCameraReceiver(const cv::ImreadModes& decodeMode, const ServerParams& serverParams, boost::asio::io_context& context);

		WiFiPredictorCameraReceiver(const WiFiPredictorCameraReceiver&) = default;
		WiFiPredictorCameraReceiver(WiFiPredictorCameraReceiver&&) noexcept = default;

		virtual ~WiFiPredictorCameraReceiver() noexcept = default;

		WiFiPredictorCameraReceiver& operator=(const WiFiPredictorCameraReceiver&) = default;
		WiFiPredictorCameraReceiver& operator=(WiFiPredictorCameraReceiver&&) noexcept = default;
		
		using WiFiDeserializer::waitConnection;

		/// @brief Recibe la información enviada para su obtención con getCameraData()
		void receiveCameraData();

		/// @brief Recibe un conjunto de predicciones, se debe usar en conjunto con
		///		   sendPredictionData(size_t)
		/// @param index Índice en el cual se guardarán los datos
		void receivePredictiedData(const size_t& index);

		/// @brief Recibe todas las predicciones hechas, se debe usar en conjunto con sendAllPredictedData()
		void receiveAllPredictedData();

		/// @brief Modifica la imagen para la inclusión de las bouncing boxes recibidas de las predicciones en la imagen,
		///		   para obtener la imagen usa getBoxedImage();
		void setBoxesToImage();

		/// @brief Obtiene la última imagen guardada con receiveCameraData()
		/// @return última imagen guardada
		[[nodiscard]] cv::Mat getCameraData() noexcept;

		/// @brief Obtiene los datos de la predicción del modelo n
		/// @param index Índice del modelo a obtener
		/// @return Vector con las predicciones
		[[nodiscard]] std::vector<PredictionsData> getPredictedData(const size_t& index);

		/// @brief Obtiene todos los datos de las predicciones
		/// @return Vector de vectores con todas las predicciones de todos los modelos
		[[nodiscard]] std::vector<std::vector<PredictionsData> > getAllPredictedData();

		/// @brief Obtiene la última imagen con las bouncing boxes aplicadas
		/// @return Imagen con bouncing boxes
		[[nodiscard]] cv::Mat getBoxedImage() noexcept;

	private:

		std::vector<unsigned char> buffer_m;
		std::vector<std::vector<PredictionsData> > predictedData_m;
		cv::ImreadModes decodeMode_m;

		cv::Mat originalImage_m;
		cv::Mat boxedImage_m;
	};
}

#endif // !WIFI_ROBOT_CAMERA_RECEIVER