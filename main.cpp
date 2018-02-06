/**
	Find repeating substrings in an element stream.
	Searches for repeating subtrings within a limited element window, or history buffer.
*/
//compile: g++ -std=c++11 main.cpp
//Improvement: implement max distance between detected repeats?
//Improvement: take advantage of fact that history buffer changes slowly, to not detect same repeat multiple times?
//Improvement: use better string search algorithm? currently uses brute force
#include <iostream>
#include <fstream>
#include "circulararray_template.h"

const char* filename = "alpha.txt";
const size_t history_buffer_size = 16;

const size_t min = 1;					//minimum length of repeat to detect
const size_t max = history_buffer_size;	//maximum length of repeat to detect

int DetectRepeats(CircularArray<char>& buffer);

int main(int argc, char* argv[])
{
	std::cout  << "Repeating substring search demo" << std::endl;
	
	std::ifstream file(filename);
	CircularArray<char> history(history_buffer_size);
	
	char c;
	while(file >> c)
	{
		if(history.Full()) history.PopFront();
		history.PushBack(c);
		DetectRepeats(history);
	}
	
	return 0;
}

bool StringCompare(const CircularArray<char>& buffer, const size_t s1, const size_t s2, size_t length)
{
	for(int i=0; i<length; i++) if(buffer[s1+i] != buffer[s2+i]) return false;
	return true;
}

bool FindString(const CircularArray<char>& buffer, const size_t patternStartIndex, const size_t patternEndIndex, const size_t stringStartIndex, const size_t stringEndIndex)
{
	for(size_t i=stringStartIndex; i<=stringEndIndex+patternStartIndex-patternEndIndex; i++)
	{
		if(StringCompare(buffer, patternStartIndex, i, patternEndIndex-patternStartIndex+1)) return true;
	}
	return false;
}

int DetectRepeats(CircularArray<char>& buffer)
{
	int count = 0;
	
	const size_t length = buffer.Size();
	for(int i=0; i<length-min; i++)
	{
		for(int j=i+min-1; j<std::min((length+i)/2, i+max); j++)
		{
			if(FindString(buffer, i, j, j+1, length-1))
			{
				count++;
				//print detected pattern
				for(size_t k=i; k<=j; k++) std::cout<<buffer[k];
				std::cout << std::endl;
			};
		}
	}
	
	return count;
}
