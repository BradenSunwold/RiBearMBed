
#ifndef COMPONENTS_SPEEDSENSOR_HPP_
#define COMPONENTS_SPEEDSENSOR_HPP_

#include <System/SystemTime.hpp>

/*
 * CLASS: SpeedSensor
 *
 *		class to interact with Acewell S-type speed sensor.
 *		Dynamically calculates speed every time speed sensor
 *		passes magnet on wheel.
 *
 * NOTE
 * 		- Wheel circumference is passed in inches
 * 		- TODO: Make odem and trip non-volatile
 */
class SpeedSensor
{

public:
	SpeedSensor();
	SpeedSensor(float wspd, uint32_t trip, uint32_t odom);
	SpeedSensor( float wheelCircum, int numSensors, types::TimeCount previousTime,
					uint32_t totalTicks, bool dataInMiles, float wspd, uint32_t trip,
					uint32_t odom);

	void UpdateInstrumentData(types::TimeCount currentTime);

	float GetWspd();
	int GetTrip();
	int GetOdom();

private:

	// Private member variables
	float mWheelCircum;
	int mNumSensors;
	int mDistanceUnitInTicks;
	float mDistanceUnitInInches;
	float mPreviousDistance;
	types::TimeCount mPreviousTime;
	uint32_t mTotalTicks;

	bool mDataInMiles;

	float mWspd;
	uint32_t mTrip;
	uint32_t mOdom;

	// Private member functions
	void CalculateDistanceInTicks();

};

#endif /* COMPONENTS_SPEEDSENSOR_HPP_ */
