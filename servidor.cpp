//#include "../Cliente/XboxControllerData.h"
//#include <iostream>
//#include <SFML/Graphics.hpp>
//#include <SFML/Network.hpp>
//#include "WiFiXboxReceiver.h"
//#include "WiFiInferencerCamera.h"
//
//using namespace std;
//
//const My::ServerParams sv{ sf::IpAddress::Any, 50000 };
//
//int main() {
//
//	My::WiFiXboxReceiver cont{ sv, 300 };
//
//	cont.waitConnection();
//
//	My::XboxControllerData data;
//
//	while (true) {
//
//		cont.receiveControllerData();
//
//		data = cont.getControllerData();
//
//		cout << data.leftStick.first << '\n';
//		cout << data.leftStick.second << '\n';
//		cout << "---------------------\n";
//
//	}
//
//	return 0;
//}

#include "WiFiPredictorCamera.h"

//const My::ServerParams sv{ "192.168.0.172", "50000" };
const My::ServerParams sv{ "127.0.0.1", "50000" };

//const My::ServerParams sv{ "192.168.203.85", "50000" };

boost::asio::io_context context;

const My::EncodeParams enpar{ ".jpg", {} };
const My::YOLOv8ModelParams inp{"/home/carlos4621/Controlador-Robot/resources/hazmatModel.onnx", cv::Size(640, 640), 
	"/home/carlos4621/Controlador-Robot/resources/hazmatClasses.txt" , false };

int main() {
	My::WiFiInferencerCamera cc{ enpar, sv, context, 0, {inp} };

	cc.startConnection();

	while (true) {
		cc.updateCamara();
		cc.applyAllModels();
		
		cc.sendCameraData();
		cc.sendAllPredictedData();

		cv::waitKey(1);
	}
}

//#include <opencv2/opencv.hpp>
//#include <vector>
//using namespace std;
//
//int main() {
//
//	cv::QRCodeDetector det;
//
//	cv::VideoCapture cam(0);
//	cv::Mat image;
//	vector<cv::Point> points;
//	cv::namedWindow("test");
//	while (true) {
//		cam >> image;
//
//		det.detect(image, points);
//
//		if (!points.empty())
//		{
//			auto texto{ det.decode(image, points) };
//			cv::imshow("test", image);
//			cout << texto << endl;
//		}
//
//		cv::waitKey(100);
//	}
//
//	
//
//	cv::waitKey();
//}