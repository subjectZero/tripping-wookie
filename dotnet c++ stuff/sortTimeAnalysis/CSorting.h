# include <iostream>
# include <fstream>
# include <conio.h>
# include "CStopwatch.h"
using namespace std;

#ifndef __CSorting__
class CSorting {
	public:
		CSorting();
		~CSorting();
		int DisplayArray();
		int LoadArrayFromFile(char*);
		int BubbleSort();
		int SelectionSort();
		int InsertionSort();
		int SortAnalysis(char*);
	private:
		int* pNumbersArray;
		int FileSize;
		StopWatch SortTimer;
};
#endif
