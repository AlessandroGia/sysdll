CONFIG ?= Debug

BUILD_CRT := build-crt
BUILD_NOCRT := build-nocrt

OUT_DIR := out
CRT_EXE := $(OUT_DIR)\crt\Syscalls.exe
NOCRT_DLL := $(OUT_DIR)\nocrt\Syscalls.dll

.PHONY: all crt nocrt run-crt run-nocrt rebuild-crt rebuild-nocrt clean clean-build clean-out imports-crt imports-nocrt

all: crt nocrt

crt:
	cmake -S . -B $(BUILD_CRT) -DBUILD_NO_CRT=OFF
	cmake --build $(BUILD_CRT)

nocrt:
	cmake -S . -B $(BUILD_NOCRT) -DBUILD_NO_CRT=ON
	cmake --build $(BUILD_NOCRT)

run-crt: crt
	$(CRT_EXE)

run-nocrt: nocrt
	$(NOCRT_DLL)

clean: clean-build clean-out

clean-build:
	@if exist $(BUILD_CRT) rmdir /s /q $(BUILD_CRT)
	@if exist $(BUILD_NOCRT) rmdir /s /q $(BUILD_NOCRT)

clean-out:
	@if exist $(OUT_DIR) rmdir /s /q $(OUT_DIR)

imports-crt: crt
	dumpbin /imports $(CRT_EXE)

imports-nocrt: nocrt
	dumpbin /imports $(NOCRT_EXE)
