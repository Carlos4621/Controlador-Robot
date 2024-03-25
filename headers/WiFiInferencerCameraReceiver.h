#pragma once
#ifndef WIFI_ROBOT_CAMERA_RECEIVER
#define WIFI_ROBOT_CAMERA_RECEIVER

#include <opencv2/opencv.hpp>
#include "WiFiDeserializer.h"
#include "InferenceData.h"

namespace My {

	/// @brief Clase que permite una conexi�n TCP y recibir im�genes para su decodificaci�n con cv::imdecode
	class WiFiInferencerCameraReceiver : private WiFiDeserializer {
	public:

		/// @brief Constructor base
		/// @param decodeMode Modo de decodificaci�n de la imagen recibida
		/// @param serverParams Par�metros del servidor
		/// @param context Contexto del OS
		WiFiInferencerCameraReceiver(const cv::ImreadModes& decodeMode, const ServerParams& serverParams, boost::asio::io_context& context);

		WiFiInferencerCameraReceiver(const WiFiInferencerCameraReceiver&) = default;
		WiFiInferencerCameraReceiver(WiFiInferencerCameraReceiver&&) noexcept = default;

		virtual ~WiFiInferencerCameraReceiver() noexcept = default;

		WiFiInferencerCameraReceiver& operator=(const WiFiInferencerCameraReceiver&) = default;
		WiFiInferencerCameraReceiver& operator=(WiFiInferencerCameraReceiver&&) noexcept = default;
		
		using WiFiDeserializer::waitConnection;

		/// @brief Recibe la informaci�n enviada para su obtenci�n con getCameraData()
		void receiveCameraData();

		/// @brief Recibe la información de un conjunto de inferencias, se debe usar en conjunto con
		///		   sendInferenceData(size_t)
		/// @param index Índice en el cual se guardarán los datos
		void receiveInferencesData(const size_t& index);

		/// @brief Recibe todas las inferencias hechas, se debe usar en conjunto con sendAllInferencesData()
		void receiveAllInferencesData();

		/// @brief Modifica la imagen para la inclusión de las bouncing boxes con ella, para obtener la imagen usa getBoxedImage();
		void setBoxesToImage();

		/// @brief Obtiene la �ltima imagen guardada con receiveCameraData()
		/// @return �ltima imagen guardada
		[[nodiscard]] cv::Mat getCameraData() noexcept;

		/// @brief Obtiene los datos del vector en el índice n
		/// @param index Índice del vector a obtener
		/// @return Vector con las inferencias
		[[nodiscard]] std::vector<InferenceData> getInferencesData(const size_t& index);

		/// @brief Obtiene todos los datos de las inferencias
		/// @return Vector de vectores con todas las inferencias de todos los inferenciadores
		[[nodiscard]] std::vector<std::vector<InferenceData> > getAllInferencesData();

		/// @brief Obtiene la última imagen con las bouncing boxes aplicadas
		/// @return Imagen con bouncing boxes
		[[nodiscard]] cv::Mat getBoxedImage() noexcept;

	private:

		std::vector<unsigned char> buffer_m;
		std::vector<std::vector<InferenceData> > inferencesData_m;
		cv::ImreadModes decodeMode_m;

		cv::Mat lastOriginalImage_m;
		cv::Mat lastModifiedImage_m;
	};
}

#endif // !WIFI_ROBOT_CAMERA_RECEIVER