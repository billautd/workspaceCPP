#include "UtilsGeneral.h"
#include <chrono>

unsigned int UtilsGeneral::RandomInt() {
	//Ms since 1/1/70
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

	return static_cast<unsigned int>(ms.count()) % INT32_MAX;
}
