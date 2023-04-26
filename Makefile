CPPFLAGS=-Werror -Wall -pedantic -std=gnu++98 -ggdb3
PROGS=path-step1 #path-step2 path-step3 path-step4
all: $(PROGS)

path-step1: path-step1.o point.o graph.o
	g++ -o $@ $^
# path-step2: test-step2.o myode.o euler.o
# 	g++ -o $@ $^
# num_sim: num_sim.o myode.o euler.o
# 	g++ -o $@ $^

%.o: %.cpp
	g++ $(CPPFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *~ *.o $(PROGS)

point.o: point.hpp
graph.o: graph.hpp
