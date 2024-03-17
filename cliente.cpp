//#include <iostream>
//#include "WiFiXbox.h"
//#include "ClientWindow.h"
//
//My::ServerParams svParams{ "192.168.0.3", 50000 };
//My::WindowParams winParam{ sf::VideoMode(1920, 1080), "Cliente" };
//
//int main() {
//	My::ClientWindow win{ winParam };
//	My::WiFiXbox joy{ svParams, 0 };
//
//	joy.startConnection();
//
//	My::XboxControllerData data;
//	while (true) {
//		joy.updateController();
//
//		data = joy.getControllerData();
//
//		win.setLeftStickPoint({ data.leftStick.first, data.leftStick.second });
//		win.setRightStickPoint({ data.rightStick.first, data.rightStick.second });
//
//		win.refreshAndDisplay();
//
//		joy.sendControllerData();
//
//		sf::sleep(sf::milliseconds(100));
//	}
//
//	return 0;
//}

#include "WiFiRobotCameraReceiver.h"
#include "ClientWindow.h"

boost::asio::io_context context;

My::ServerParams svParams{ "sexo", "50000" };
My::WindowParams winParams{ sf::VideoMode(1920, 1080), "Test" };

int main() {
	My::WiFiRobotCameraReceiver rec{ cv::ImreadModes::IMREAD_UNCHANGED, svParams, context };

	rec.waitConnection();

	cv::namedWindow("xxx");
	while (true) {

		try {

			rec.receiveCameraData();

		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;

		} 
		 
		cv::imshow("xxx", rec.getCameraData());
		cv::waitKey(1);
	}
}