#pragma once
#ifndef XBOX_CONTROLLER_DATA
#define XBOX_CONTROLLER_DATA

#include <utility>
#include <boost/serialization/utility.hpp>

namespace My {

	struct XboxControllerData {
		bool A;
		bool B;
		bool X;
		bool Y;
		bool RB;
		bool LB;
		bool Back;
		bool Start;
		bool L;
		bool R;

		std::pair<float, float> rightStick;
		std::pair<float, float> leftStick;

		std::pair<float, float> DPad;

		float trigger;

		// Para Boost::Serializer
		template <class Archive>
		void serialize(Archive& ar, const unsigned int version) {
			ar& A;
			ar& B;
			ar& X;
			ar& Y;
			ar& RB;
			ar& LB;
			ar& Back;
			ar& Start;
			ar& L;
			ar& R;

			ar& rightStick;
			ar& leftStick;

			ar& DPad;

			ar& trigger;
		}
	};

}

#endif // !XBOX_CONTROLLER_DATA