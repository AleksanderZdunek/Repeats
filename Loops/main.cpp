#include <iostream>
#include <fstream>
#include "circulararray_template.h"

const char* filename = "test.txt";
const size_t history_buffer_size = 16;

std::string toString(const CircularArray<char>& buffer, size_t startIndex);
bool DetectLoop(const CircularArray<char>& buffer);

int main(int argc, char* argv[])
{
	std::cout <<  "Loop detection" << std::endl;
	
	std::ifstream file(filename);
	CircularArray<char> history(history_buffer_size);
	
	char c;
	while(file >> c)
	{
		if(history.Full()) history.PopBack();
		history.PushFront(c);
		DetectLoop(history);
	}
	
	return 0;
}

bool StringCompare(const CircularArray<char>& buffer, const size_t s1, const size_t s2, size_t length)
{
	for(size_t i=0; i<length; i++) if(buffer[s1+i] != buffer[s2+i]) return false;
	return true;
}

bool DetectLoop(const CircularArray<char>& buffer)
{
	const size_t length = buffer.Size();
	for(size_t i=0; i < length/2; i++)
	{
		if(StringCompare(buffer, 0, i+1, i+1))
		{
			std::cout << toString(buffer, i) << "\n";
			return true;
		}
	}
	return false;
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
