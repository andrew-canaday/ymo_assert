.PHONY: clean check

all: check

example: example.c ymo_assert.h
	$(CC) -DYMO_ASSERT_VERBOSE=1 example.c -o example

clean:
	rm -f example

check: example
	@./example
