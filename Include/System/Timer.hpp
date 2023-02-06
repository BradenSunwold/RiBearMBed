
#ifndef INCLUDE_SYSTEM_TIMER_HPP_
#define INCLUDE_SYSTEM_TIMER_HPP_

#include <Types/Time/Time.hpp>
#include <System/SystemTime.hpp>

namespace sys
{
namespace time
{

/*
*============================================================================
* Class
* Timer
*============================================================================
*
* static class to create one shot and periodic timers based off the system clock
* - Can pass in any time unit between milliseconds - nanoseconds
*
*/
class Timer
{
public:

	Timer();

	/*
	 *	----------------------------------------------------------------------
	 *	Timer::CreatePeriodicTimer()
	 *
	 *	Static
	 *	----------------------------------------------------------------------
	 *
	 *	Creates a periodic timer based on the current clock resolution.
	 *	Static function for ease of creating timer instances
	 *
	 *	INPUTS:
	 *		- int period
	 *	OUPUTS:
	 *		Timer instance
	 *
	 */
	static Timer CreatePeriodicTimer(int period, types::UnitOfTime resolution);

	/*
	 *	----------------------------------------------------------------------
	 *	Timer::CreateOneShotTimer
	 *
	 *	Static
	 *	----------------------------------------------------------------------
	 *
	 *	Creates one shot timer based on current clock resolution of system timer.
	 *	Static and returns instance of new timer for ease of creating new timers
	 *
	 *	INPUTS:
	 *		- int period
	 *	OUPUTS:
	 *		Timer instance
	 *
	 */
	static Timer CreateOneShotTimer(int period, types::UnitOfTime resolution);

	/*
	 *	----------------------------------------------------------------------
	 *	Timer::TimedOut()
	 *
	 *	Static
	 *	----------------------------------------------------------------------
	 *
	 *	Function to check if current timer instance has timed out
	 *
	 *	INPUTS:
	 *		void
	 *	OUPUTS:
	 *		bool - has timed out
	 *
	 */
	bool TimedOut();


private:
	// Private member variables
	bool mIsPeriodic;
	uint32_t mPeriod;
	uint32_t mNextTimeout;
	types::UnitOfTime mClockResolution;

	// Private member functions

	// Helper function to convert passed in period to correct clock resolution
	int CalculatePeriod(int period, types::UnitOfTime resolution);

};

}
}



#endif /* INCLUDE_SYSTEM_TIMER_HPP_ */
