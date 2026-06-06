# In the Abyss

> [🇨🇳 中文版本](README_CN.md)

This game was wrote by me as a middle-school freshman, which was inspired by Kenzaburō Ōe's *The Silent Cry* (*万延元年のフットボール*). I was a big fan of text adventure games at that moment.

This is a text adventure game where players traverse between the city of the dead and hell, exploring the mysteries between life and death. The game is known for its unique narrative style and rich literary atmosphere.

## Game Overview

The game tells the story of an ordinary office worker who, after accidentally encountering the mysterious game "In the Abyss", begins to travel between the real world and hell. The game features multiple storylines and character-switching mechanics, allowing players to experience different perspectives across three chapters. The narrative alternates between mundane office life and surreal hellscapes, gradually revealing the connections between the two realms.

## Story Flow

```
                    ┌──────────────┐
                    │  Main Menu   │
                    │ A: Chapter 1 │
                    │ B: Chapter 2 │
                    │ C: Chapter 3 │
                    │ D: Exit      │
                    └──────┬───────┘
                           │
              ┌────────────┴────────────┐
              │  Chapter 1              │
              │  City of the Dead       │
              │  Streets / Office       │
              └────────────┬────────────┘
                           │
              ┌────────────┴────────────┐
              │  Chapter 2              │
              │  Office · Staircase     │
              │  Office work /          │
              │  Stairwell minigame     │
              └────────────┬────────────┘
                           │
              ┌────────────┴────────────┐
              │  Chapter 3              │
              │  Hell's Dull Fire       │
              │  ┌─────────────────┐    │
              │  │ Press Z to      │    │
              │  │ switch between  │    │
              │  │ the two worlds  │    │
              │  └─────────────────┘    │
              │  Explore hell,          │
              │  uncover the truth      │
              └─────────────────────────┘
```

## Project Structure

```
├── include/                # Headers (12)
│   ├── platform.h          #   Cross-platform (Win/Linux)
│   ├── common_vars.h       #   Global var declarations
│   ├── functions.h         #   Utility functions
│   ├── print.h             #   ASCII art
│   ├── story.h             #   Story declarations
│   ├── game_state.h        #   State registry
│   ├── room_registry.h     #   Room definitions
│   ├── scene_registry.h    #   Scene registry
│   ├── dialogue_tree.h     #   Dialogue engine
│   ├── ending_tracker.h    #   Endings tracker
│   ├── save_load.h         #   Save/Load
│   └── random_event.h      #   Random events
├── src/
│   ├── main.cpp            #   Entry point, menu
│   ├── globals.cpp         #   Global variables
│   ├── functions.cpp       #   Utility implementations
│   ├── chapter1.cpp        #   Chapter 1
│   ├── chapter2.cpp        #   Chapter 2
│   ├── chapter3.cpp        #   Chapter 3 (hell)
│   ├── game_state.cpp
│   ├── room_registry.cpp
│   ├── scene_registry.cpp
│   ├── dialogue_tree.cpp
│   ├── ending_tracker.cpp
│   ├── save_load.cpp
│   └── random_event.cpp
├── Makefile
├── README.md               # This file
└── README_CN.md            # Chinese version
```

## Compilation and Running

### Unix (Linux / macOS)

```bash
make          # Build (release)
make run      # Build & run
make debug    # Build (debug, -O0 -g)
make clean    # Remove build artifacts
```

Or compile directly:

```bash
g++ -o Abyss -Iinclude src/*.cpp -std=c++17
./Abyss
```

### Windows

Using MinGW/g++:
```cmd
g++ -o Abyss.exe -Iinclude src/*.cpp -std=c++17
Abyss.exe
```

## Build Targets

| Target | Command | Description |
|--------|---------|-------------|
| Release | `make` | `-O2 -Wall -Wextra` |
| Debug | `make debug` | `-O0 -g -DDEBUG` |
| Run | `make run` | Build & run release |
| Run (Debug) | `make run-debug` | Build & run debug |
| Clean | `make clean` | Remove obj/ & binaries |

## Controls

| Key | Action |
|-----|--------|
| N / S / W / E | Move North / South / West / East |
| ↑ / ↓ | Confirm / Cancel |
| Z | Switch character (Chapter 3) |
| A-E | Select menu options |

## Extension Systems

The project includes pluggable extension frameworks for future content:

- **GameState** — Centralized state tracker with flags, visit counters, and inventory
- **Room registry** — Room graph with exits and scene hooks
- **Scene registry** — Runtime scene registration and dispatch
- **Dialogue tree** — Branching conversations with conditions and flags
- **Ending tracker** — Multiple ending condition evaluation
- **Save/Load** — Serialization skeleton
- **Random events** — Probabilistic events with cooldowns

## License

MIT
