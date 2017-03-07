
EXE = average_and_stddev.exe

all: dirtree
	$(CXX) -std=c++11 -o bin/$(EXE) src/ave_stddev.cpp

dirtree:
	mkdir -p bin
	mkdir -p obj

clean:
	rm -f *.sdf bin/* obj/*

cleanall:
	rm -rf *.sdf bin obj


