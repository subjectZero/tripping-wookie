# include "CStopwatch.h"

// PUBLIC METHODS
// CTOR // --------------------------------------------------------------------
StopWatch::StopWatch()
{
	__mode = STOPPED;
	__beginTime = 0;
	__endTime = 0;
	__elapsedTime = 0;
	__secondsElapsed = 0;
	__milsElapsed = 0;
} // end Constructor

bool // -----------------------------------------------------------------------
StopWatch::Start()
{
	// ensure that the clock actually needs to be started
	if(this->_getMode() == TICKING)
		return EXIT_FAILURE;

	this->_setBeginTime(clock());
	this->_setMode(TICKING);
	return EXIT_SUCCESS;
} // end StopWatch::Start()

bool // -----------------------------------------------------------------------
StopWatch::Stop()
{
	// declare some time variables
	long endTime, startTime, elapsedTime;
	double secElapsed, milElapsed;

	// verify that the clock actually needs to be stopped
	if(this->_getMode() == STOPPED)
		return EXIT_FAILURE;

	// record the end time
	this->_setEndTime(clock());
	this->_setMode(STOPPED);

	// get the elapsed time
	endTime = this->_getEndTime();
	startTime = this->_getBeginTime();
	elapsedTime = endTime - startTime;
	this->_setElapsedTime(elapsedTime);

	// convert to seconds, mils
	secElapsed = ((double)elapsedTime) / ((double)CLOCKS_PER_SEC);
	this->_setSecondsElapsed(secElapsed);
	milElapsed = ((double)elapsedTime) / (((double)CLOCKS_PER_SEC) / (1000.0000));
	this->_setMilsElapsed(milElapsed);

	return EXIT_SUCCESS;
} // end StopWatch::Stop()

bool // -----------------------------------------------------------------------
StopWatch::Reset()
{
	// we wouldn't want to reset a ticking clock... bad things might happen
	if(this->_getMode() == TICKING)
		return EXIT_FAILURE;

	// reset time data members
	this->_setBeginTime(0);
	this->_setEndTime(0);
	this->_setElapsedTime(0);
	this->_setSecondsElapsed(0);
	this->_setMilsElapsed(0);

	return EXIT_FAILURE;
} // end StopWatch::Reset()

bool // -----------------------------------------------------------------------
StopWatch::DisplayTimerInfo()
{
	if(this->_getMode() == TICKING)
		return EXIT_FAILURE;

	cout << "Elapsed Time: " << this->_getMilsElapsed() <<  " miliseconds.\n";

	return EXIT_SUCCESS;
} // end StopWatch::DisplayTimerInfo()

// PROTECTED METHODS

// GETTERS --------------------------------------------------------------------
clock_t StopWatch::_getBeginTime() {return this->__beginTime;}
clock_t StopWatch::_getEndTime() {return this->__endTime;}
clock_t StopWatch::_getElapsedTime() {return this->__elapsedTime;}
double StopWatch::_getSecondsElapsed() {return this->__secondsElapsed;}
double StopWatch::_getMilsElapsed() {return this->__milsElapsed;}
StopWatch::WatchState StopWatch::_getMode() {return this->__mode;}

// SETTERS --------------------------------------------------------------------
void StopWatch::_setBeginTime(clock_t time) {this->__beginTime = time;}
void StopWatch::_setEndTime(clock_t time) {this->__endTime = time;}
void StopWatch::_setElapsedTime(clock_t time) {this->__elapsedTime = time;}
void StopWatch::_setSecondsElapsed(double secs){this->__secondsElapsed = secs;}
void StopWatch::_setMilsElapsed(double mils) {this->__milsElapsed = mils;}
void StopWatch::_setMode(StopWatch::WatchState state) {this->__mode = state;}