#pragma once
#ifndef SERVER_PARAMS_HEADER
#define SERVER_PARAMS_HEADER

#include <string>

namespace My {
	struct ServerParams {
		std::string ip;
		std::string port;
	};
}

#endif // !SERVER_PARAMS_HEADER