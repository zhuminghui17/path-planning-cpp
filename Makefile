CPPFLAGS=-Werror -Wall -pedantic -std=gnu++98 -ggdb3
PROGS=path-step1 path-step2 path-step3 path-step4
all: $(PROGS)

path-step1: path-step1.o node.o graph.o edge.o
	g++ -o $@ $^
path-step2: path-step2.o node.o graph.o edge.o
	g++ -o $@ $^
path-step3: path-step3.o node.o graph.o	edge.o
	g++ -o $@ $^
path-step4: path-step4.o node.o graph.o edge.o
	g++ -o $@ $^


%.o: %.cpp
	g++ $(CPPFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *~ *.o $(PROGS)

node.o: node.hpp
graph.o: graph.hpp
edge.o: edge.hpp
