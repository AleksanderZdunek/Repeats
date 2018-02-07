//20180205-1440
//edit@ 20180207-1415
#pragma once

#include <memory>

template<typename T>
class CircularArray
{
public:
	CircularArray(const size_t capacity = 16);
	bool Empty() const;
	bool Full() const;
	size_t Capacity() const;
	size_t Size() const;
	T* PushBack(const T e);
	T* PushFront(const T e);
	T* PopBack();
	T* PopFront();
	T& operator[](size_t i) const;

	template<typename U>
	friend void DebugPrint(const CircularArray<U>& arr);

private:
	std::unique_ptr<T[]> data;
	const size_t capacity;
	size_t i_begin;
	size_t i_end;
};

template<typename T>
CircularArray<T>::CircularArray(const size_t capacity): capacity(capacity), data(new T[capacity]), i_begin(0), i_end(capacity)
{
}

template<typename T>
bool CircularArray<T>::Empty() const
{
	//let i_end == capacity indicate empty list, since this is a value i_end should normally never attain. Remember that max(i_end) == capacity - 1.
	return capacity == i_end;
}

template<typename T>
bool CircularArray<T>::Full() const
{
	if(Empty()) return false;
	return (i_end+1)%capacity == i_begin;
}

template<typename T>
size_t CircularArray<T>::Capacity() const
{
	return capacity;
}

template<typename T>
size_t CircularArray<T>::Size() const
{
	if(Empty()) return 0;

	//calculate circular index of last element, and add 1
	return (i_end+capacity-i_begin)%capacity + 1;
}

template<typename T>
T* CircularArray<T>::PushBack(const T e)
{
	if(Full()) return nullptr;
	if(Empty()) data[i_end = i_begin] = e;
	else data[i_end = (i_end+1)%capacity] = e;

	return data.get() + i_end;
}

template<typename T>
T* CircularArray<T>::PushFront(const T e)
{
	if(Full()) return nullptr;
	if(Empty()) data[i_end = i_begin] = e;
	else data[i_begin = (i_begin-1)%capacity] = e;

	return data.get() + i_begin;
}

template<typename T>
T* CircularArray<T>::PopBack()
{
	if(Empty()) return nullptr;

	T* pPopped = data.get() + i_end;
	if(1==Size()) i_end = capacity; //mark array as empty
	else i_end = (i_end-1)%capacity;
	return pPopped;
}

template<typename T>
T* CircularArray<T>::PopFront()
{
	if(Empty()) return nullptr;

	T* pPopped = data.get() + i_begin;
	if(1==Size()) i_end = capacity;	//mark array as empty
	i_begin = (i_begin+1)%capacity; //note the lack of symetry of this line compared the to corresponding line in PopBack(), where the line is else conditional
	return pPopped;
}

template<typename T>
T& CircularArray<T>::operator[](size_t i) const
{
	return data[(i_begin+i)%capacity];
}
