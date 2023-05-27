#pragma once
#include <iostream>]
using namespace std;

class sortAlgorithms
{
public:    
    void selectionSort(int* const v, const int length, const int entryIndex, bool (*compare)(int* const, int* const))
    {
        int sortedIndex = entryIndex;
        for (int i = entryIndex + 1; i < length; i++)
        {
            if ((*compare)(v + sortedIndex, v + i))            
                sortedIndex = i;
        }
        swapValues(v + entryIndex, v + sortedIndex);      
    }
    void insertionSort(int* const v, const int length, const int entryIndex, bool (*compare)(int* const, int* const))
    {
            int i = entryIndex;
            do
            {
                if ((*compare)(v + i, v + i + 1))
                {
                    swapValues(v + i, v + i + 1);
                    i--;
                }
            } while (i >= 0 && (*compare)(v + i, v + i + 1));
    }
    void bubbleSort(int* const v, const int length, const int entryIndex, bool (*compare)(int* const, int* const))
    {
            for (int i = 0; i < length - 1; i++)
            {
                if ((*compare)(v + i, v + i + 1))                
                    swapValues(v + i, v + i + 1);                
            }        
    }
    void swapValues(int* const leftVal, int* const rightVal)
    {   // Left-Shift
        int tempVal = *leftVal;
        *leftVal = *rightVal;
        *rightVal = tempVal;
    }
    static bool ascending(int* const leftVal, int* const rightVal)
    {
        return (*leftVal > *rightVal) ? true : false;
    }

    static bool descending(int* const leftVal, int* const rightVal)
    {
        return (*leftVal < *rightVal) ? true : false;
    }
    void printArray(int* const v, const int length)
    {
        for (int i = 0; i < length; i++)
            cout << *(v + i) << " ";
        cout << endl;
    }
};