.PHONY: clean check doc

all: check

example: example.c ymo_assert.h
	$(CC) -DYMO_ASSERT_VERBOSE=1 example.c -o example

clean:
	rm -vf example

doc:
	pomd4c ./ymo_assert.h > ./README.md
	pomd4c ./example.c >> ./README.md

check: example
	./example
