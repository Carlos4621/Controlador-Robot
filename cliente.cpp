// #include <iostream>
// #include "WiFiXbox.h"
// #include "ClientWindow.h"

// My::ServerParams svParams{ "10.100.105.62", "50000" };

// boost::asio::io_context context;

// int main() {
// 	My::WiFiXbox joy{ svParams, context, 0  };

// 	joy.startConnection();

// 	My::XboxControllerData data;
// 	while (true) {
// 		joy.updateController();

// 		joy.sendControllerData();

// 		sf::sleep(sf::milliseconds(100));
// 	}

// 	return 0;
// }

#include "WiFiPredictorCameraReceiver.h"
#include "ClientWindow.h"

boost::asio::io_context context;

My::ServerParams svParams{ "sexo", "50000" };
My::WindowParams winParams{ sf::VideoMode(1920, 1080), "Test" };

int main() {
	My::WiFiPredictorCameraReceiver rec{ cv::ImreadModes::IMREAD_UNCHANGED, svParams, context };

	rec.waitConnection();
	rec.receiveModelSize();

	cv::namedWindow("xxx");
	while (true) {

		try {

			rec.receiveCameraData();
			rec.receiveAllPredictedData();
			rec.setBoxesToImage();

		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;

		} 
		 
		cv::imshow("xxx", rec.getCameraData());
		cv::imshow("det", rec.getBoxedImage());
		cv::waitKey(1);
	}
}