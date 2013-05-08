CXXFLAGS = -g
LIBS = 
LDLIBS =
INCLUDES = 


objectsheap = BinaryHeap.o
objectstestheap = BinaryHeapTest.o

objectsgraph = Dijkstra.o Network.o $(objectsheap)
objectstestdijkstra = DijkstraTest.o

objectsproject = RailSchedule.o Project.o $(objectsgraph)
objectstestproject = ProjectTest.o

objectsscenario = Scenario.o $(objectsproject)

# now give target with objects as variable dependencies + command line

all: clean testheap testdijkstra testproject scenario
	
testheap: $(objectsheap) $(objectstestheap) 
	$(CXX) $(CXXFLAGS) -o BinaryHeapTest.exe $(objectsheap) $(objectstestheap) $(INCLUDES)

testdijkstra: $(objectsgraph) $(objectstestdijkstra) 
	$(CXX) $(CXXFLAGS) -o DijkstraTest.exe $(objectsgraph) $(objectstestdijkstra) $(INCLUDES)

testproject: $(objectsproject) $(objectstestproject)
	$(CXX) $(CXXFLAGS) -o ProjectTest.exe $(objectsproject) $(objectstestproject) $(INCLUDES)

scenario: $(objectsscenario)
	$(CXX) $(CXXFLAGS) -o Scenario.exe $(objectsscenario) $(INCLUDES)

# how to build all object files from all dependent source files

	

clean:
	rm -f *.o
	rm -f *.exe
