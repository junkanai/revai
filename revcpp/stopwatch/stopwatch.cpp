#include "stopwatch.h"

#define NC "\e[0m"
#define YEL "\e[0;33m"

StopWatch::StopWatch(bool isStart) {
	reset();
	if (isStart) start();
}

StopWatch::~StopWatch() {
	print();
}

void StopWatch::start() {
	if (isWorking) return;
	startTime = std::clock();
	lastLapTime = startTime;
	isWorking = true;
}

void StopWatch::stop() {
	if (!isWorking) return;
	currentTime += std::clock() - startTime;
	isWorking = false;
}

void StopWatch::reset() {
	currentTime = 0;
	startTime = 0;
	isWorking = false;
}

void StopWatch::restart() {
	reset();
	start();
}

void StopWatch::print() {
	stop();
	auto elapsed = (double)currentTime / CLOCKS_PER_SEC;
	printf(YEL "Total Time: %4.4f seconds.\n" NC, elapsed);
}

void StopWatch::lap() {
	auto lap = (double)(std::clock() - lastLapTime) / CLOCKS_PER_SEC;
	auto elapsed = (double)(std::clock() - startTime) / CLOCKS_PER_SEC;
	printf("Lap Time: %4.4f seconds.(Total Time: %4.4f seconds.)\n", lap, elapsed);
	lastLapTime = std::clock();
}
