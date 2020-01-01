build:
	mkdir -p build && cd build && cmake -DCMAKE_INSTALL_PREFIX=. .. && make

install:
	cd build && make install

clean:
	rm -rf build

.PHONY: build install clean
