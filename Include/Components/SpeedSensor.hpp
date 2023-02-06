
#ifndef COMPONENTS_SPEEDSENSOR_HPP_
#define COMPONENTS_SPEEDSENSOR_HPP_

#include <System/SystemTime.hpp>

/*
 * CLASS: SpeedSensor
 *
 *		class to hold instrument cluster data - works with Acewell S-type
 *		speed sensor. Calculates speed on set configurable timer interrupt.
 *		Stores speed, trip and odometer data to send off to IPC
 *
 * NOTE
 * 		- Wheel circumference is passed in cm
 * 		- kph default, mph otherwise
 * 		- TODO: Make odem and trip non-volatile
 */
class SpeedSensor
{

public:
	SpeedSensor();
	SpeedSensor(float wspd, uint32_t trip, uint32_t odom);
	SpeedSensor( float wheelCircum, int numSensors, uint32_t totalTicks,
									bool dataInKm, uint32_t timerRateHz, float wspd,
									uint32_t trip, uint32_t odom);

	// Function to update cluster parameters on timer callback
	void UpdateInstrumentData();

	// Function to update speed ticks on GPIO interrupt callback
	void IncrementSpeedTicks();

	// Getters for data items
	float GetWspd();
	int GetTrip();
	int GetOdom();
	bool GetDataRdy();

	// Setters for sensor / wheel parameters
	void SetWheelCircum(float newWheelCircum);
	void SetSensorNum(uint16_t newSensorNum);
	void SetDataInKm(bool dataInKm);
	void ClearDataRdy();

private:

	// Private member variables
	float mWheelCircum;					// Wheel circumference in cm
	uint16_t mNumSensors;				// Number of magnets on wheel (default = 1)
	bool mDataInKm;						// Default to data in kph, otherwise assumed mph

	uint32_t mSensorTicks;				// Track how many sensor ticks
	uint32_t mTickOverflow;				// Value to track ticks between timer interrupts if necessary
	uint32_t mTimerRateInHz;			// Rate of timer interrupt for speed calculation

	float mLastDistance;
	bool mDataRdy;

	float mWspd;
	uint32_t mTrip;
	uint32_t mOdom;

};

#endif /* COMPONENTS_SPEEDSENSOR_HPP_ */
