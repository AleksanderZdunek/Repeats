/**
	Find repeating substrings in an element stream.
	Searches for repeating subtrings within a limited element window, or history buffer.
*/
#include <iostream>
#include <fstream>
#include "circulararray_template.h"

const char* filename = "alpha.txt";
const size_t history_buffer_size = 16;

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
		for(int i=0; i<history.Size(); i++)
		{
			std::cout<<history[i];
		}
		std::cout << std::endl;
	}
	
	return 0;
}
