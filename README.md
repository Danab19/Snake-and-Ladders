# 🐍🎲 Snake and Ladders Game (C++)

This is a **console-based implementation** of the classic *Snakes and Ladders* game in C++. The game supports **two-player (PvP)** and **player vs computer (PvC)** modes. It includes dice rolling, a visual board, snakes and ladders behavior, and score saving.

---

## 📋 Features

* Player vs. Player and Player vs. Computer modes
* Rolling dice mechanic with "roll again if 6"
* Board visualization with player tokens
* Snakes and ladders altering player positions
* Win condition requiring exact roll to reach square 100
* Score logging to a `Scores.txt` file
* View last game's dice rolls and stats

---

## ▶️ How to Run

1. **Compile** the program:

   ```bash
   g++ -o SnakeAndLadders SnakeAndLadders.cpp
   ```

2. **Run** the game:

   ```bash
   ./SnakeAndLadders
   ```

---

## 🕹️ Gameplay Instructions

* Choose from the main menu:

  * **1. How to Play** – View rules
  * **2. Play** – Start a new game
  * **3. Last Game Dice Rolls** – View dice rolls from the previous game
  * **4. Quit** – Exit the program

* **Roll the dice** by pressing `Enter`.

* If you **roll a 6**, you get another turn.

* You **must roll the exact number** to land on the 100th square and win.

* Ladders move you **up**, and snakes move you **down**:

  | Ladders | Snakes  |
  | ------- | ------- |
  | 4 → 14  | 36 → 6  |
  | 8 → 30  | 48 → 26 |
  | 21 → 42 | 62 → 18 |
  | 28 → 76 | 88 → 24 |
  | 50 → 67 | 95 → 56 |
  | 71 → 92 |         |

---

## 📁 File Overview

* `SnakeAndLadders.cpp` — Main source code
* `Scores.txt` — Output file containing last game statistics

---

## 🧠 Code Structure

### Main Components:

* **`main()`** – Game loop and menu handler
* **`Play()`** – Launches game logic based on selected mode
* **`SnakesOrLadders(int &position)`** – Modifies position based on game rules
* **`GameBoard()`** – Renders board and player positions
* **`RollDice()`** – Simulates dice roll using `rand()`
* **`DiceDraw(int)`** – Displays rolled number in ASCII-art style
* **`SaveScores()`** – Saves game statistics to `Scores.txt`

---

## 💡 Notes

* The random seed is initialized with `time(0)` each time the dice is rolled, which may not be ideal. For better randomness, consider initializing `srand()` **once** in `main()` instead.
* The code uses characters to represent players on the board.

