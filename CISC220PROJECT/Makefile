CXXFLAGS = -g
LIBS = 
LDLIBS =
INCLUDES = 


objectsheap = BinaryHeap.o
objectstestheap = BinaryHeapTest.o

objectsgraph = Dijkstra.o Network.o 
objectstestdijkstra = DijkstraTest.o

objectsproject = RailSchedule.o Project.o
objectstestproject = ProjectTest.o


# now give target with objects as variable dependencies + command line

all: clean testheap testdijkstra testproject
	
testheap: $(objectsheap) $(objectstestheap) 
	$(CXX) $(CXXFLAGS) -o BinaryHeapTest.exe $(objectsheap) $(objectstestheap) $(INCLUDES)

testdijkstra: $(objectsheap) $(objectsgraph) $(objectstestdijkstra) 
	$(CXX) $(CXXFLAGS) -o DijkstraTest.exe $(objectsheap) $(objectsgraph) $(objectstestdijkstra) $(INCLUDES)

testproject: $(objectsheap) $(objectsgraph) $(objectsproject) $(objectstestproject)
	$(CXX) $(CXXFLAGS) -o ProjectTest.exe $(objectsheap) $(objectsgraph) $(objectsproject) $(objectstestproject) $(INCLUDES)

# how to build all object files from all dependent source files

	

clean:
	rm -f *.o
	rm -f *.exe
