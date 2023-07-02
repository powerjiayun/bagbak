LIBPLIST=deps/libplist
LIBCNARY=$(LIBPLIST)/libcnary

SRC_CNARY=$(LIBCNARY)/node{,_list}.c
SRC_PLIST=$(LIBPLIST)/src/*.c

all:
	emcc $(SRC_PLIST) ${SRC_CNARY} \
		-DHAVE_STRNDUP \
		-Ideps/libplist/include -Ideps/libplist/libcnary/include -Ideps/libplist/src \
		plist.c -o plist.cjs

run: all
	node --experimental-wasi-unstable-preview1 --experimental-wasm-modules test.js
