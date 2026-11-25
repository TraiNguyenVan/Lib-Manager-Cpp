.PHONY: build run clean fresh test

build:
	cmake -S . -B build && cmake --build build

run: build
	./build/lib_manager

test: build
	cd build && ctest --output-on-failure

fresh:
	rm -rf build && cmake -S . -B build && cmake --build build

clean:
	rm -rf build
