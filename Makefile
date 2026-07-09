.PHONY: build run clean fresh

build:
	cmake -S . -B build && cmake --build build

run: build
	./build/lib_manager

fresh:
	rm -rf build && cmake -S . -B build && cmake --build build

clean:
	rm -rf build
