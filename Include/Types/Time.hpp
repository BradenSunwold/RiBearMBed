
#ifndef TYPES_TIME_HPP_
#define TYPES_TIME_HPP_

#include "StdTypeDefs.hpp"

namespace types
{

typedef unsigned long long TimeCount;

/*
 * 	ENUM
 * 	types::UnitOfTime - clock resolutions
 */
typedef enum
{
	eNanoSecond		= 1,
	eMicroSecond	= 2,
	eMilliSecond	= 3
}UnitOfTime;

}


#endif /* TYPES_TIME_HPP_ */
