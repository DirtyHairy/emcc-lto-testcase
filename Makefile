LLVM_PREFIX ?= ~/git/llvm-project/prefix/bin
LLVM_SYSROOT ?= /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk

CXXFLAGS = -O3 -flto -fno-rtti -fno-exceptions -I./include
LDFLAGS = -O3 -flto

OBJECTS_LIBC = algorithm.o new.o
OBJECTS = test.o

BINARY = test

bin: $(BINARY)

$(OBJECTS) : %.o : %.cpp
	$(LLVM_PREFIX)/clang++ $(CXXFLAGS) -isysroot $(LLVM_SYSROOT) -c $<

$(OBJECTS_LIBC) : %.o : src/%.cpp
	$(LLVM_PREFIX)/clang++ $(CXXFLAGS) -isysroot $(LLVM_SYSROOT) -c $<

$(BINARY) : $(OBJECTS) $(OBJECTS_LIBC)
	$(LLVM_PREFIX)/clang $(LDFLAGS) -isysroot $(LLVM_SYSROOT) -o $@ $^

clean:
	-rm -f $(OBJECTS) $(OBJECTS_LIBC) $(BIN)

.PHONY: clean bin
