# Arduino-Dino-Runner-Game-For-University-college-embedded-systems
# 🦖 Arduino Dino Runner Game on 16x2 LCD

![Platform](https://img.shields.io/badge/Platform-Arduino_IDE-blue.svg)
![Hardware](https://img.shields.io/badge/Board-Arduino_Uno-green.svg)
![Display](https://img.shields.io/badge/Display-16x2_LCD-yellow.svg)
![Language](https://img.shields.io/badge/Language-Arduino_C-orange.svg)

A fully playable **Chrome Dinosaur-style game** recreated on an **Arduino Uno** with a 16x2 LCD. Control the dino using a physical button, jump over moving obstacles, and enjoy animations and sounds in real-time , It was for ES university project.  
🧪 Simulated on both **real hardware** and **Tinkercad simulation** for full testability.

[▶️ Watch the Project Demo on YouTube](https://youtu.be/tK4FDF1B7fw) <!-- Replace with your YouTube link -->

---

## 📦 Overview

- 🦕 LCD-rendered dino animation (stand, run, jump)
- 🌵 Random obstacles: cacti, branches, flying birds
- 🎵 Sound effects for jumps, collisions, and milestones
- 🕹️ Physical button control for jumping
- 🧠 State machine for clear game structure
- 📈 Difficulty increases as obstacles speed up
- ✅ Works in real hardware **and** on **Tinkercad circuits**

---

## 🔌 Hardware Configuration

| Component   | Arduino Pin      | Description         |
|------------|------------------|---------------------|
| LCD (16x2) | RS → 9           | Register Select     |
|            | E  → 8           | Enable              |
|            | D4 → 5           | Data Line           |
|            | D5 → 4           | Data Line           |
|            | D6 → 3           | Data Line           |
|            | D7 → 2           | Data Line           |
| Button     | 11               | Player jump button  |
| Buzzer     | 10               | Sound output        |

---

## 🧠 Game States

| State             | Description                           |
|------------------|---------------------------------------|
| `STATE_WELCOME`  | Welcome screen with scrolling text and melody |
| `STATE_PLAYING`  | Game is active                        |
| `STATE_GAME_OVER`| Collision → game over screen + sound  |

---

## 🦕 Custom Characters (8 Total)

The LCD allows 8 custom characters. These are used efficiently to simulate animation:

- **Dino Animation (6 characters)**  
  - Standing (2 parts)  
  - Running – Left/Right foot (2 frames × 2 parts)

- **Obstacles (2 characters)**  
  - Ground cacti/branches  
  - Flying bird with 2-frame wing animation  

---

## 🎮 Gameplay Mechanics

### 🏃 Dino Animation
- Alternates between running frames using `millis()` timing
- Non-blocking for smooth animation

### 🌵 Obstacle System
- Randomly chooses one of three types:  
  - Two ground-based (row 1)  
  - One flying (row 0)
- Moves from column 13 to 0
- Increases speed over time by reducing interval (`periodo2`)

### ⬆️ Jumping
- Press button to jump to top row
- Variables `b`, `c`, `d` handle jump logic and collision disabling

### ☠️ Collision Detection
- Ground: check if obstacle overlaps with dino on row 1
- Air: check if dino jumps into flying bird on row 0

### 🧮 Scoring
- Score increases over time (`periodo3`)
- Two-digit score using `puntos` (units) and `punto2` (hundreds)
- Special sound plays every 100 points

---

## 🎵 Sound Effects

| Event         | Sound                                  |
|---------------|-----------------------------------------|
| Start screen  | Ascending notes: C5, E5, G5, C6         |
| Jump          | Single tone at 600Hz                   |
| Collision     | Two descending tones                   |
| 100-point mark| 800Hz and 900Hz tones in sequence      |

---

## 🔁 Game Flow

1. Shows welcome screen + melody  
2. Wait for button press  
3. Dino starts running  
4. Obstacles move from right to left  
5. Player presses button to jump over them  
6. Collision triggers game over screen + sound  
7. Button press restarts game  

---

## 🧰 Functions Summary

| Function              | Description                                  |
|-----------------------|----------------------------------------------|
| `setup()`             | Initializes pins, LCD, and custom chars      |
| `loop()`              | Controls game state transitions              |
| `showWelcomeScreen()` | Displays scrolling welcome + melody          |
| `playGame()`          | Main loop with animation, input, scoring     |
| `resetGame()`         | Resets obstacle, speed, score, and states    |
| `handleGameOver()`    | Displays “Game Over” and plays defeat sound  |

---

## ⚙️ Technical Details

- **Platform**: Arduino IDE  
- **Microcontroller**: Arduino Uno  
- **Display**: 16x2 LCD in 4-bit mode  
- **Simulation**: ✔ Real Hardware & ✔ Tinkercad Simulation  
- **Timing System**: Uses `millis()` for smooth multitasking  
- **Memory Use**: Optimized character slots & integer math  
- **Obstacle Speed**: Dynamically adjusted based on progress

---

## 📂 Project Files

- `DinoRunner.ino` → Main game logic  
- `custom_chars.h` (optional) → Character map definitions  
- `simulation.tinkercad` (optional) → Tinkercad circuit simulation  
- `Fritzing_Diagram.fzz` (optional) → Wiring diagram  

---

## 📬 Contact

Have feedback, ideas, or questions?

- Telegram: [@Kz_u4](https://t.me/Kz_u4)  
- YouTube: [@0xkimson](https://www.youtube.com/@0xkimson)

---

## 📄 License

Licensed under the [MIT License](LICENSE)

---

> ⚡ A fun and challenging way to bring arcade-style gaming into embedded systems. Built using low-cost hardware, clever timing, and pixel-level LCD control — enjoy and extend it your way!
