CC = g++
CFLAGS = -std=c++11 -Wall -Wextra -Wpedantic -Weffc++ -O3 -march=native
OBJFILES = $(patsubst %.cc, %.o, $(wildcard *.cc))

%.o: %.cc
	-@mkdir -p ../build
	$(CC) $(CFLAGS) -o ../build/$@ -c $^

.PHONY: clean all

all: $(OBJFILES)

clean:
	-@rm -rfv ../build/*.o
