# CMake owns its generated Makefile. Keep plain make usable from a fresh checkout.
ifneq ($(wildcard CMakeCache.txt),)
include Makefile
else
CMAKE ?= cmake

.PHONY: all
all: build/Makefile
	$(MAKE) -C build

build/Makefile:
	$(CMAKE) -S . -B build -G "Unix Makefiles"
endif
