NAME := gridgraph

DEPENDENCIES_FILE := dep.d

SOURCES := $(wildcard *.c)
OBJECTS := $(SOURCES:%.c=%.o)



all: dependencies compile clean_after_compile



dependencies:
	cc -MM $(SOURCES) > $(DEPENDENCIES_FILE)

-include $(DEPENDENCIES_FILE)

compile: $(OBJECTS)
	cc -o $(NAME) $(OBJECTS)

clean_after_compile:
	rm $(OBJECTS) $(DEPENDENCIES_FILE)



clean:
	rm $(NAME) $(OBJECTS) $(DEPENDENCIES_FILE)



test: all
	./gridgraph -w -xh 6 -xw 6 -Wmin 0.5 -Wmax 0.9 -Cmin 1 -Cmax 3