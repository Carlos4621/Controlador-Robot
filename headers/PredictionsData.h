#pragma once
#ifndef INFERENCES_DATA_HEADER
#define INFERENCES_DATA_HEADER

#include <cstdint>
#include <string>
#include <opencv4/opencv2/opencv.hpp>
#include <boost/serialization/string.hpp>

namespace My {

    /// @brief Struct que contiene los datos de las predicciones
    struct PredictionsData {

        uint16_t classID;
        std::string className;
        double confidence;
        cv::Rect bouncingBox;

        // Para Boost::Serialize
        template <class Archive>
		void serialize(Archive& ar, const unsigned int version) {
            ar & classID;
            ar & className;
            ar & confidence;

            ar & bouncingBox.x;
            ar & bouncingBox.y;

            ar & bouncingBox.width;
            ar & bouncingBox.height;
        }
    };
}

#endif //!INFERENCES_DATA_HEADER