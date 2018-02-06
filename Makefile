TARGET = repeats
SOURCE = main.cpp
HEADER = circulararray_template.h

CFLAGS = -std=c++11

$(TARGET): $(SOURCE) $(HEADER)
	g++ $(CFLAGS) -o $(TARGET) $(SOURCE)
	
clean:
	rm -f $(TARGET)
