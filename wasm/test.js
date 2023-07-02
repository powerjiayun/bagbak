import { readFile } from 'fs/promises';

(async () => {
  const wasmImports = {
    __assert_fail(condition, filename, line, func) {
      throw new Error('__assert_fail not implemented');
    },
    emscripten_memcpy_big(dest, src, num) {
      throw new Error('emscripten_memcpy_big not implemented');
    },
    emscripten_resize_heap(requestedSize) {
      throw new Error('emscripten_resize_heap');
    },
    fd_write(fd, iov, iovcnt, pnum) {
      throw new Error('fd_write');
    }
  };

  const wasm = await WebAssembly.compile(await readFile('./plist.wasm'));
  const instance = await WebAssembly.instantiate(wasm, {
    'env': wasmImports,
    'wasi_snapshot_preview1': wasmImports,
  });

  console.log(instance.exports);
})();
