CXX=g++
CXXFLAGS=-I/usr/local/include
LDFLAGS=-L/usr/local/lib -lmapnik2 -licuuc
OBJS=test.o renderer.o

agg_test:	$(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o run

clean:
	rm -f run
	rm -f $(OBJS)

test.o: test.cpp
renderer.o: renderer.cpp
