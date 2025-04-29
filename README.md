# Reaction time with C++/Raylib

A simple reaction time measurement game I made for practice.

## Building from Source

### Prerequisites

- a C++ compiler, i guess
- [Raylib](https://www.raylib.com/)

### Compilation

#### Linux/macOS:
```bash
g++ -o build t.cpp -lraylib -lm -lpthread -ldl -lX11
```

#### Windows (MinGW):
```bash
g++ -o build.exe t.cpp -lraylib -lopengl32 -lgdi32 -lwinmm
```

## License

This project is available under the MIT License - see the LICENSE file for details.

## Stuff

- Built with [Raylib](https://www.raylib.com/)
- Inspired by sleep deprivation
