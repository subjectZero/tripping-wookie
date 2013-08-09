# include <iostream>
# include <iomanip>
# include <time.h>
using namespace std;

# ifndef __STOPWATCH__
# define __STOPWATCH__

class 
StopWatch
{
	public:
		StopWatch();
		bool Start();
		bool Stop();
		bool DisplayTimerInfo();
		bool Reset();
		enum WatchState {TICKING, STOPPED};

	protected:
		// GETTERS
		clock_t _getBeginTime();
		clock_t _getEndTime();
		clock_t _getElapsedTime(); 
		double _getSecondsElapsed();
		double _getMilsElapsed();
		StopWatch::WatchState _getMode();

		// SETTERS
		void _setBeginTime(clock_t);
		void _setEndTime(clock_t);
		void _setElapsedTime(clock_t);
		void _setSecondsElapsed(double);
		void _setMilsElapsed(double);
		void _setMode(StopWatch::WatchState);
	private:
		WatchState __mode;
		clock_t __beginTime;
		clock_t __endTime;
		clock_t __elapsedTime;
		double __secondsElapsed;
		double __milsElapsed;
};
# endif

