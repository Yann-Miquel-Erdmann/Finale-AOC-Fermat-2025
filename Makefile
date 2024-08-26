SOURCES = $(shell find src -type f -name '*.c')
HEADERS = $(shell find src -type f -name '*.h')
OBJECTS = $(patsubst %.c,%.o,$(SOURCES))
CFLAGS = -g -Wall -Wextra -O0 

build_: $(OBJECTS)
	gcc -o build/interpreter $^ -lm

build/%.o: src/%.c $(HEADERS)
	mkdir -p $(@D)
	gcc $(CFLAGS) -c $< -o $@

fast:
	make build_ CFLAGS='-Ofast -g'

clean:
	rm -f $(OBJECTS) 
test_suite:
	python3 ./testing/test_suite.py

test:
	valgrind ./build/interpreter ./testing/test.FC
