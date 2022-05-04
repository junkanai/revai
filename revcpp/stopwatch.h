#pragma once

#include <iostream>
#include <ctime>

class StopWatch {
private:
	clock_t currentTime, startTime, lastLapTime;
	bool isWorking;
public:
	StopWatch(bool isStart=true);
	void start();
	void stop();
	void reset();
	void restart();
	void print();
	void lap();
	~StopWatch();
};
