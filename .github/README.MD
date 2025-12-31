# c-tris

## Prerequisites

### Windows (MSVC)
- Visual Studio 2022 Build Tools (MSVC + Windows SDK)
- CMake
- Git

### macOS
- Xcode Command Line Tools (Apple Clang)
- CMake
- Ninja
- pkg-config
- Git

## Build

### Windows

```sh
cmake --preset=windows
cmake --build build
```

### macOS

```sh
cmake --preset=macos
cmake --build build
```

## Run

### Windows
```sh
.\build\Debug\c-tris.exe
```

### macOS
```sh
./build/c-tris
```
