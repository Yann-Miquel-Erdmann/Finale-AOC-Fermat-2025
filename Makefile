SOURCES = $(shell find src -type f -name '*.c')
HEADERS = $(shell find src -type f -name '*.h')
OBJECTS = $(patsubst %.c,%.o,$(SOURCES))
CFLAGS = -g -O0 
build/interpreter: $(OBJECTS)
	gcc -o $@ $^ -lm
%.o: %.c $(SOURCES)
	gcc $(CFLAGS) -c -o $@ $<
clean:
	rm -f $(OBJECTS) 
test:
	python3 ./testing/test_suite.py
