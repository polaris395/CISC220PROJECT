LIBS =
LDLIBS =
INCLUDES = 

# first name a variable objects for all object files

objectsheap = BinaryHeap.o
objectstestheap = BinaryHeapTest.o

# name a variable sources for all source files

sourcesheap = BinaryHeap.cpp
sourcestestheap = BinaryHeapTest.cpp
# now give target with objects as variable dependencies + command line

all: clean testheap

testheap: $(objectsheap) $(objectstestheap) 
	$(CXX) -o BinaryHeapTest.exe $(objectsheap) $(objectstestheap)
# how to build all object files from all dependent source files

$(objectsheap): $(sourcesheap)
	$(CXX) -c $(sourcesheap) $(INCLUDES)

$(objectstestheap): $(sourcestestheap)
	$(CXX) -c $(sourcestestheap) $(INCLUDES)

clean:
	rm -f *.o
	rm -f *.exe
