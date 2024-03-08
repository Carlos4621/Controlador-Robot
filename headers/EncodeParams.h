#pragma once
#ifndef ENCODE_PARAMS_HEADER
#define ENCODE_PARAMS_HEADER

namespace My {
	struct EncodeParams {
		std::string fileExtension;
		std::vector<int> flags;
	};
}

#endif // !ENCODE_PARAMS_HEADER