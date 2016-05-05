
EXE = average_and_stddev.exe

all: dirtree
	$(CXX) -std=c++11 -o bin/$(EXE) average_and_stddev/ave_stddev.cpp

dirtree:
	mkdir -p bin
	mkdir -p obj

clean:
	rm -rf *.sdf bin/*.ilk bin/*.pdb obj/*.log obj/*.idb obj/*.pdb

cleanall:
	rm -rf *.sdf bin obj


