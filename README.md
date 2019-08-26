# cmake_entangled_libs

Show you how to build entangled libraries with CMake on Linux.

## Compiling CClient Application  

```shell
git clone https://github.com/oopsmonk/cmake_entangled_libs.git
cd cmake_entangled_libs/cclient
mkdir build && cd $_
cmake ..
make -j8
```

For build your application you just need to change the source in `add_executable`.

```cmake
add_executable(${PROJECT_NAME} test_cclient.c)
```

## Compiling MAM Application  

**TODO**
