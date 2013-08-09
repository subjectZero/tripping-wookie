# include "CSorting.h"

// CTOR & DTOR ----------------------------------------------------------------
CSorting::CSorting() { this->pNumbersArray = NULL;}
CSorting::~CSorting() {	delete [] pNumbersArray;}

int // ------------------------------------------------------------------------
CSorting::LoadArrayFromFile(char* FileToLoad)
{
	ifstream inHandle(FileToLoad, ios::in);

	if (!(inHandle.is_open()))
	{
		cout << "Unable to open file: \n"
				<< FileToLoad << "\n";
		return EXIT_FAILURE;
	}
	else if(pNumbersArray != NULL)
	{
		delete [] pNumbersArray;
		pNumbersArray = NULL;
	}
	
	// count the number of integers in the file
	int lineCount = 0;
	int holder;
	while( !(inHandle.eof()))
	{
		inHandle >> holder;
		lineCount++;
	}
	inHandle.clear();
	inHandle.seekg(0,ios::beg);

	// determine size of memory allocation
	this->FileSize = lineCount;
	
	// allocate memory from the heap
	pNumbersArray = new (nothrow) int[lineCount];
	if (pNumbersArray == NULL)
	{	
		cout << "Error: memory could not be allocated.\n"
				<< "Unable to load array.\n";
		return EXIT_FAILURE;
	}
	int i = 0;
	while( i < lineCount )
	{
		inHandle >> *(pNumbersArray + i);
		++i;
	};

	// close the input file
	inHandle.close();

	return EXIT_SUCCESS;
} // end CSorting::LoadArray()

int // ------------------------------------------------------------------------
CSorting::DisplayArray()
{
	if (this->pNumbersArray == NULL)
	{
		cout << "No array has been loaded." << endl;
		return EXIT_FAILURE;
	}
	else
	{
		for(int i = 0; i < FileSize; ++i)
		{
			cout << *(this->pNumbersArray + i);
			if(i != FileSize - 1)
				cout << ", ";
		}
		cout << endl;
	};
	return EXIT_SUCCESS;
} // end CSorting::DisplayArray()


int // ------------------------------------------------------------------------
CSorting::BubbleSort()
{   // this is the part where we ensure that there's actually something to sort
	if (pNumbersArray == NULL)
	{
		cout << "No array has been loaded.\n"
				<< "Please load an array before attempting to sort.\n";
		return EXIT_FAILURE;
	};
	// reset the clock then start it
	this->SortTimer.Reset();
	this->SortTimer.Start();
	// start sorting
	int temp;
	bool swap = true;
	while(swap == true)
	{
		swap = false;
		for(int i = 0; i <= (this->FileSize) - 2; i++) 
		{
			int j = i + 1;
			if(pNumbersArray[i] > pNumbersArray[j])
			{
				int temp = pNumbersArray[j];
				pNumbersArray[j] = pNumbersArray[i];
				pNumbersArray[i] = temp;
				swap = true;
			}
		}
	}
	// get the end time so that we calculate the time it took to finish thesort
	this->SortTimer.Stop();
	return EXIT_SUCCESS;
} // end CSorting::BubbleSort()

int // ------------------------------------------------------------------------
CSorting::SelectionSort()
{   // make sure we're not about to 'sort' a NULL pointer
	if (pNumbersArray == NULL)
	{
		cout << "No array has been loaded.\n"
				<< "Please load an array before attempting to sort.\n";
		return EXIT_FAILURE;
	}

	// reset and start the clock
	this->SortTimer.Reset();
	this->SortTimer.Start();

	// and we're off! the sort begins
	for(int i = 0; i < (this->FileSize) - 1; i++) {

		int currentMin = i;

		for(int j = i + 1; j < (this->FileSize); j++)
		{
			if(pNumbersArray[j] < pNumbersArray[currentMin])
				currentMin = j;
		}

		int tempNum = pNumbersArray[i];
		pNumbersArray[i] = pNumbersArray[currentMin];
		pNumbersArray[currentMin] = tempNum;
	}

	// get the end time
	this->SortTimer.Stop();
	return EXIT_SUCCESS;
} // end CSorting::SelectionSort()

int // ------------------------------------------------------------------------
CSorting::InsertionSort()
{   // did we actually remember to load a file into the driver code...
	if (pNumbersArray == NULL)
	{
		cout << "No array has been loaded.\n"
				<< "Please load an array before attempting to sort.\n";
		return EXIT_FAILURE;
	}
	// reset and start the clock
	this->SortTimer.Reset();
	this->SortTimer.Start();

	// the sorting begins, the green flag drops!
	int currentValue;
	for(int i = 1; i < (this->FileSize); i++)
	{
		int j = i - 1;
		currentValue = pNumbersArray[i];
		while(pNumbersArray[j] > currentValue && j >= 0)
		{
			pNumbersArray[j + 1] = pNumbersArray[j];
			j--;
		}
		pNumbersArray[j + 1] = currentValue;
	}
	// stop the clock and record the results
	this->SortTimer.Stop();
	return EXIT_SUCCESS;
} // end CSorting::InsertionSort()

int // ------------------------------------------------------------------------
CSorting::SortAnalysis(char* FileName)
{   // it's like nascar, but at 4 in the morning and with your GPA on the line
	cout << "Preparing array...\n";
	if(this->LoadArrayFromFile(FileName))
		return EXIT_FAILURE;
	cout << "\nARRAY SIZE: " << this->FileSize;
	
	// good thing i have an outrageously fast processor
	cout << "\nBubble Sort.... START!\n";
	this->BubbleSort();
	this->SortTimer.DisplayTimerInfo();

	// bubble sort is kind of a slowpoke
	cout << "\nPreparing array...\n";
	if(this->LoadArrayFromFile(FileName))
		return EXIT_FAILURE;

	// so slow that i initially thought my code was completely fubar...
	cout << "Selection Sort.... START!\n";
	this->SelectionSort();
	this->SortTimer.DisplayTimerInfo();

	// ... turned out to be a user error
	cout << "\nPreparing array...\n";
	if(this->LoadArrayFromFile(FileName))
		return EXIT_FAILURE;

	cout << "Insertion Sort.... START!\n";
	this->InsertionSort();
	this->SortTimer.DisplayTimerInfo();

	return EXIT_SUCCESS;
} // end CSorting::SortAnalysis()