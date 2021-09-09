
#ifndef INCLUDE_TYPES_STDTYPEDEFS_HPP_
#define INCLUDE_TYPES_STDTYPEDEFS_HPP_

#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>

namespace types
{

typedef enum endian_t
{
	little = 0,
	big = 1
} endian_t;

void FloatToBytes(float wspd, endian_t endianType, char* buffer, int index);
}

#endif /* INCLUDE_TYPES_STDTYPEDEFS_HPP_ */
