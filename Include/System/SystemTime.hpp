
#ifndef SYSTEM_SYSTEMTIME_HPP_
#define SYSTEM_SYSTEMTIME_HPP_

#include <Types/Time.hpp>

// Function pointers for interfacing with external hw/sw timers
typedef uint32_t (*ReadExternalTimer32Bit_t)();

namespace sys
{
namespace time
{

/*
*============================================================================
* Class
* SystemTime
*============================================================================
*
*static class to read from external timers and calculate sytem time
* - Currently only reads from 32 bit hw / 32 bit sw timer (64 bit timer)
*/
class SystemTime
{
public:

	// Public member functions

	/*
	 *	----------------------------------------------------------------------
	 *	SystemTime::Load
	 *
	 *	Static
	 *	----------------------------------------------------------------------
	 *
	 *	Loads function pointers to read external hw/sw timers and sets all
	 *	time scales
	 *
	 *	INPUTS:
	 *
	 *	OUPUTS:
	 *		void
	 *
	 */
	static void Load(ReadExternalTimer32Bit_t readHwTimer, ReadExternalTimer32Bit_t readSwTimer,
						unsigned long clockFreqInHz);

	/*
	 *	----------------------------------------------------------------------
	 *	SystemTime::GetTime
	 *
	 *	Static
	 *	----------------------------------------------------------------------
	 *
	 *	Returns atomically calculated current system time
	 *
	 *	INPUTS:
	 *		NA
	 *
	 *	OUPUTS:
	 *		types::TimeCount - current system time
	 *
	 */
	static types::TimeCount GetTime();

private:

	// Private member variables

	// function pointer interfacing with external timers
	static ReadExternalTimer32Bit_t mReadHwTimer;
	static ReadExternalTimer32Bit_t mReadSwTimer;

	// Hold information about clock speeds and resolutions
	static types::UnitOfTime mClockResolution;
	static unsigned long mClockFreqInHz;

	// Threshold to de-glitch counts
	static types::TimeCount mDeGlitchThreshold;

	// Private member functions

	/*
	 *	----------------------------------------------------------------------
	 *	SystemTime::GetAtomicTime
	 *
	 *	Static
	 *	----------------------------------------------------------------------
	 *
	 *	Reads from hw/sw timers and calculates current atomic system time
	 *	accounting for any possible glitches
	 *
	 *	INPUTS:
	 *		NA
	 *
	 *	OUPUTS:
	 *		types::TimeCount - current atomic system time
	 *
	 */
	static types::TimeCount GetAtomicTime();

	/*
	 *	----------------------------------------------------------------------
	 *	SystemTime::CalculateClockResolution
	 *
	 *	Static
	 *	----------------------------------------------------------------------
	 *
	 *	Calculates clock resolution based on clock frequency
	 *	- Only call after mClockFreqInHz is set
	 *
	 *	INPUTS:
	 *		NA
	 *
	 *	OUPUTS:
	 *		void
	 *
	 */
	static void CalculateClockResolution();

	/*
	 *	----------------------------------------------------------------------
	 *	SystemTime::DeGlitchCounts
	 *
	 *	Static
	 *	----------------------------------------------------------------------
	 *
	 *	Takes in two successive counts and de-glitches the timer read
	 *
	 *	INPUTS:
	 *		types::TimeCount count1, types::TimeCount coun2
	 *
	 *	OUPUTS:
	 *		types::TimeCount - de-gliched system time
	 *
	 */
	static types::TimeCount DeGlitchCounts(uint64_t count1, uint64_t count2);

};

}
}


#endif /* SYSTEM_SYSTEMTIME_HPP_ */
