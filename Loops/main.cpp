#include <iostream>
#include <fstream>
#include <string>
#include "circulararray_template.h"

const char* filename = "test.txt";
const size_t history_buffer_size = 16;

struct LoopInfo
{
	uint64_t streamPosition; //	1-indexed. The first element in the stream should have position 1.
	size_t loopCount;
	size_t loopSize;
};
std::ostream& operator<<(std::ostream& os, const LoopInfo& info)  
{
	os << "Loop @ stream pos: " << info.streamPosition << "\nSize: " << info.loopSize << "\nCount: " << info.loopCount << "\n";
	os << "Count2: " << info.loopCount+2*info.loopSize-1 << "\n";
	return os;
} 

std::string toString(const CircularArray<char>& buffer, size_t startIndex);
size_t DetectLoop(const CircularArray<char>& buffer);

int main(int argc, char* argv[])
{
	std::cout <<  "Loop detection\n" << std::endl;
	
	if(argc>1) filename = argv[1];
	
	uint64_t streamCount(0);
	LoopInfo loopInfo{0,0,0};
	std::ifstream file(filename);
	CircularArray<char> history(history_buffer_size);
	
	size_t detect;
	char c;
	while(file >> c)
	{
		++streamCount;
		
		if(history.Full()) history.PopBack();
		history.PushFront(c);
		
		//Detection report print. //Note: this code looks like it wants to be a state machine.
		if(detect = DetectLoop(history))
		{
			if(detect == loopInfo.loopSize)
			{
				loopInfo.loopCount++;
			}
			else //detected loop size has changed
			{
				if(loopInfo.loopSize) std::cout << loopInfo << "\n"; //print out info for previous loop size
				loopInfo.loopSize = detect;
				loopInfo.loopCount = 1;
				loopInfo.streamPosition = streamCount - loopInfo.loopSize*(loopInfo.loopCount + 1)+1;
			}
		}
		else
		{
			if(loopInfo.loopSize)
			{
				std::cout << loopInfo << "\n"; //print loop info
				loopInfo.loopCount = loopInfo.loopSize = 0;
			}
		}
	}
	//Print out if stream happens to end on a loop
	if(loopInfo.loopSize)
	{
		std::cout << loopInfo << "\n"; //print loop info
		loopInfo.loopCount = loopInfo.loopSize = 0;
	}
	
	return 0;
}

bool StringCompare(const CircularArray<char>& buffer, const size_t s1, const size_t s2, size_t length)
{
	for(size_t i=0; i<length; i++) if(buffer[s1+i] != buffer[s2+i]) return false;
	return true;
}

/**
	Examines the front of the buffer for looping substring
	
	\param buffer 
	\return Length (nr of character) of detected loop. 0 if no loop detected.
*/
size_t DetectLoop(const CircularArray<char>& buffer)
{
	const size_t length = buffer.Size();
	for(size_t i=0; i < length/2; i++)
	{
		if(StringCompare(buffer, 0, i+1, i+1))
		{
			std::cout << toString(buffer, i) << "\n";
			return i+1;
		}
	}
	return 0;
}

std::string toString(const CircularArray<char>& buffer, size_t startIndex)
{
	std::string r;
	do
	{
		r.push_back(buffer[startIndex]);
	}
	while(startIndex--);
	
	return r;
}
