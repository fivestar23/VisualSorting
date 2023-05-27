#include "olcConsoleGameEngine.h"
#include "sortAlgorithms.h"

#include <iostream>
#include <cstdlib>	// For rand() and srand()
#include <ctime>	// For rand seed = srand(time)

using namespace std;

class Sort : public olcConsoleGameEngine, public sortAlgorithms

{
public:
	// record final time to sort and display
	float holdSortTime;		float lastTickTime;
	float totalSortTime = 0.0;		float totalTickTime = 0.0;
	bool totalSortTimeFlag = true;  bool totalTickTimeFlag = true;

	int index = 0;								// initialize 1st layer of sorting alg. externally
	int numberSamples;		int v[200];			// numberSamples must be less than 200
	int sortSelected;		bool dirSortSelected;	

	int windowWidth;		int windowHeight;
	int xLL;				int xRL;

	// Check number of samples in array do not exceed the windows width
	void setup(const int width, const int height, const int length, int sel, bool dir)
	{
		// Setup Window : Pass main functions parameters to the Class
		windowWidth = width;
		windowHeight = height;
		numberSamples = length;
		sortSelected = sel;
		dirSortSelected = dir;
		// x-axis centered on window given number of samples less than the window width
		xLL = (windowWidth / 2) - (numberSamples / 2);
		xRL = (windowWidth / 2) + (numberSamples / 2); // iterate Left to Right
		// generate random time-based seed
		genRandArray();		
	}	
	void genRandArray()
	{
		srand(time(0));
		const int maxVal = 100;		const int minVal = 1;
		for (int i = 0; i < numberSamples; i++)
		{
			v[i] = (rand() % (maxVal - minVal + 1) + minVal);
		}
	}	
protected:
	virtual bool OnUserCreate()
	{
		return true;
	}
	virtual bool OnUserUpdate(float fElaspedTime)
	{		
		
		controlTime(fElaspedTime);			
		controlBuffer();
		controlSpeed();

		return true;
	}	
	void controlSpeed()
	{
		if (m_keys[VK_NUMPAD0].bHeld)
			holdSortTime = 0.0;
		else if (m_keys[VK_NUMPAD1].bHeld)
			holdSortTime = 0.5;
		else if (m_keys[VK_NUMPAD2].bHeld)
			holdSortTime = 1.0;
		else if (m_keys[VK_NUMPAD3].bHeld)
			holdSortTime = 2.0;
	}
	void controlTime(float m_fElaspedTime)
	{				
		lastTickTime = m_fElaspedTime;
		totalTickTime = (totalTickTimeFlag == true) ? totalTickTime + lastTickTime : 0;
		totalTickTimeFlag = (totalTickTime >= holdSortTime) ? true : false;		
		totalSortTime = (totalSortTimeFlag == true) ? totalSortTime + totalTickTime : totalSortTime;				
	}
	void controlBuffer()
	{
		// Iterate one sort		
		if (index < numberSamples-1 && totalTickTimeFlag == true)
		{
			sortArray();	index++;					
			Fill(0, 0, windowWidth, windowHeight, 0x2588, 0);	//clear screen
		}
		if (index == numberSamples - 1)		
			totalSortTimeFlag = false;	//done sorting

		// Draw text overlay
		

		// Load Buffer 			
		for (int i = xLL; i < xRL; i++)
		{				
			DrawLine(i, windowHeight, i, windowHeight - *(v + i - xLL), 0x2588, 0x000F);
		}
	}	
	void sortArray()
	{
		switch (dirSortSelected) 
		{
		case false:
			switch (sortSelected)
			{
			case 1:
				selectionSort(&v[0], numberSamples, index, ascending); break;
			case 2:
				insertionSort(&v[0], numberSamples, index, ascending); break;
			case 3:
				bubbleSort(&v[0], numberSamples, index, ascending);	break;
			}
			break;
		case true:
			switch (sortSelected)
			{
			case 1:
				selectionSort(&v[0], numberSamples, index, descending); break;
			case 2:
				insertionSort(&v[0], numberSamples, index, descending); break;
			case 3:
				bubbleSort(&v[0], numberSamples, index, descending); break;
			}
		}
	}
};
int main()
{
	// Hardcoded for now, could prompt user and link to #samples
	const int w_Width = 140;	const int w_Height = 110;
	const int w_numSamples = 100;
	int selectSort; // 0:disabled 1:selection 2:insert 3: bubble
	bool dirSort;	// 0:ascending 1:descending

	cout << "Select the sort Algorithm" << endl;
	cout << "\t0:disabled  1:selection  2:insertion  3:bubble" << endl;
	cin >> selectSort;
	cout << "Select the sort Direction" << endl;
	cout << "\t0:ascending  1:descending" << endl;
	cin >> dirSort;

	Sort render;	
	render.setup(w_Width, w_Height, w_numSamples, selectSort, dirSort);
	render.ConstructConsole(render.windowWidth, render.windowHeight, 8, 8);
	render.Start();
}

