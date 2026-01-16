# c-tris

## Prerequisites
- Git
- CMake
- Ninja
- LLVM / Clang

## Configure

```sh
mise run config
```
or

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=clang -DCMAKE_C_FLAGS="-std=c23 -march=native -Wall -Wextra -Wpedantic" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
```

## Build

```sh
mise run build
```

or

```sh
cmake --build build
./build/c-tris
```
