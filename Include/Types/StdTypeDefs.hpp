
#ifndef INCLUDE_TYPES_STDTYPEDEFS_HPP_
#define INCLUDE_TYPES_STDTYPEDEFS_HPP_

#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>

namespace types
{

// To ensure cross-platform compatibility, forward is defined as the default system endianess and
// reverse is the opposite
typedef enum endian_t
{
	eForward = 0,
	eReverse = 1
} endian_t;

#define CM_TO_KM 100000
#define CM_TO_MILES 160934

template <typename T>
void InsertToByteArray(T data, endian_t endianType, char* buffer, int index, size_t dataSize)
{
	char* bytes = (char*)&data;

	if(endianType == eForward)
	{
		for(int i = 0; i < dataSize; i++)
		{
			buffer[index + i] = bytes[i];
			char currByte = buffer[index + i];
			int test = 1;
			test++;
		}
	}
	else
	{
		for(int i = 0; i < dataSize; i++)
		{
			buffer[index + i] = bytes[dataSize - 1 - i];
		}
	}
}

}

#endif /* INCLUDE_TYPES_STDTYPEDEFS_HPP_ */
