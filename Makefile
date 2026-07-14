.PHONY: build run test clean fresh

build:
	cmake -S . -B build && cmake --build build

run: build
	./build/lib_manager

test:
	cmake -S . -B build -DBUILD_TESTING=ON && cmake --build build
	ctest --test-dir build --output-on-failure

fresh:
	rm -rf build && cmake -S . -B build && cmake --build build

clean:
	rm -rf build
