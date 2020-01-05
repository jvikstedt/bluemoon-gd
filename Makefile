build:
	mkdir -p build && cd build && cmake -DCMAKE_INSTALL_PREFIX=. .. && make

install: build
	cd build && make install

clean:
	rm -rf build

run-server: install
	./build/bluemoon-server

run-client: install
	./build/bluemoon-client

compile-commands: build
	cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=YES

.PHONY: build install clean run-server run-client compile-commands
