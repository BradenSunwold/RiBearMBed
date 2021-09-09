
#ifndef COMPONENTS_SPEEDSENSOR_HPP_
#define COMPONENTS_SPEEDSENSOR_HPP_

class SpeedSensor
{

public:
	SpeedSensor();
	SpeedSensor(float wspd, int trip, int odom);
	SpeedSensor(float wspd, int trip, int odom, int frameTime, float wheelCircum, int numSensors, int mileInTicks);

	void UpdateInstrumentData(int ticks);

	float GetWspd();
	int GetTrip();
	int GetOdom();

	void SetFrameTime(int frameTime);

private:
	int mPrevDistance;
	int mCurrentDistance;
	int mFrameTime;
	float mWheelCircum;
	int mNumSensors;
	int mMileInTicks;

	float mWspd;
	int mTrip;
	int mOdom;

};

#endif /* COMPONENTS_SPEEDSENSOR_HPP_ */
