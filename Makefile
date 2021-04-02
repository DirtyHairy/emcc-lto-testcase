SOURCE = Chunk.cpp ChunkProbe.cpp Savestate.cpp SavestateProbe.cpp main.cpp
OBJECTS = $(SOURCE:%.cpp=%.o)
BINARY = testcase.js
GARBAGE = $(OBJECTS) $(BINARY:%.js=%.wasm)

CFLAGS = -Werror -Wextra -Wall -Wno-unused-parameter -Wno-pragma-pack -O3 -flto -fno-rtti -std=c++17 -fno-exceptions
LDFLAGS = -O3 -Wno-version-check -flto
CC = emcc

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o : %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(GARBAGE)

.PHONY: clean all
