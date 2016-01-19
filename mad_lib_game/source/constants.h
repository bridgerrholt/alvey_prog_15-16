// A namespace of global constant variables.

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "color_codes.h"
#include "operating_system.h"

namespace constants
{
	const ColorCodes G_COLOR_CODES;

// Windows (32-bit and 64-bit).
#ifdef _WIN32
	const OperatingSystem G_OPERATING_SYSTEM = WINDOWS_32_64;
	// Windows (64-bit only).
	#ifdef _WIN64

	#endif

// Apple devices.
#elif __APPLE__
	// iOS Simulator.
	#if TARGET_IPHONE_SIMULATOR

	// iOS device
	#elif TARGET_OS_IPHONE

	// Other kinds of Mac OS.
	#elif TARGET_OS_MAC
		const OperatingSystem G_OPERATING_SYSTEM = APPLE_MAC;

	// Unkown Apple device.
	#else

	#endif
// Linux devices.
#elif __linux__

// Other Unix devices.
#elif __unix__ // all unices not caught above
// Unix

// POSIX devices.
#elif defined(_POSIX_VERSION)

// Unknown compiler.
#else

#endif
}

#endif