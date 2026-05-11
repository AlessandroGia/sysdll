CONFIG ?= Debug

BUILD_CRT := build-crt
BUILD_NOCRT := build-nocrt

OUT_DIR := out
EXE := $(OUT_DIR)\debug\Syscalls.exe
DLL := $(OUT_DIR)\release\Syscalls.dll

.PHONY: all debug build clean clean-build clean-out

all: debug build

debug:
	cmake -S . -B $(BUILD_CRT) -DBUILD_NO_CRT=OFF
	cmake --build $(BUILD_CRT)

build:
	cmake -S . -B $(BUILD_NOCRT) -DBUILD_NO_CRT=ON
	cmake --build $(BUILD_NOCRT)

clean: clean-build clean-out

clean-build:
	@if exist $(BUILD_CRT) rmdir /s /q $(BUILD_CRT)
	@if exist $(BUILD_NOCRT) rmdir /s /q $(BUILD_NOCRT)

clean-out:
	@if exist $(OUT_DIR) rmdir /s /q $(OUT_DIR)
