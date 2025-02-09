# 🐍 Snake Game in C++ 🎮

## Description
This is a console-based **Snake** game implemented in C++. The game features a customizable difficulty level, a snake that grows as it eats food, and a border collision detection system. The game runs in the terminal with user-friendly controls and visual effects. 🐍🍏

## Features
- **Snake Movement**: Control the snake using the keyboard (W, A, S, D). ⬆️⬇️⬅️➡️
- **Food**: The snake can eat food 🍏, which causes it to grow longer.
- **Difficulty Levels**: The game has four difficulty levels (Easy, Medium, Hard, Expert).
- **Game Over Conditions**: The game ends if the snake collides with the wall 🧱 or its own body 🐍💥.
- **Visual Effects**: Uses ASCII characters for rendering the game, including snake 🐍 and food 🍏. The terminal cursor is hidden for a better visual experience.

## Controls
- **W**: Move Up ⬆️
- **S**: Move Down ⬇️
- **A**: Move Left ⬅️
- **D**: Move Right ➡️

## Instructions
1. **Run the Game**: 
    - Compile the program using a C++ compiler.
    - Execute the program.

2. **Starting the Game**: 
    - Enter your name when prompted. ✍️
    - Select a difficulty level (1-4). 🎮

3. **Gameplay**:
    - Use W, A, S, D to control the snake. 🐍
    - The snake moves automatically and can grow longer by eating the food (`#`). 🍏
    - Avoid hitting the borders 🧱 or the snake's own body! 💥
    - The game ends if either condition occurs. 🚫

4. **Ending the Game**:
    - Once the game is over, the score will be displayed along with your name. 🏆

## Code Structure
The code consists of the following main sections:

### 1. **Header Files**:
The program includes standard libraries such as `iostream`, `unistd.h`, and `termios.h` for controlling terminal input and output.

### 2. **Functions**:
- **`Sleep(int a)`**: Pauses the game for a specified time ⏳.
- **`get()` & `set()`**: Functions to get and reset terminal attributes. 🖥️
- **`userInput(SnakeDirection direction)`**: Handles user input for controlling snake direction. 🎮
- **`HideCursor()` & `ShowCursor()`**: Hides and shows the terminal cursor during gameplay. 🕵️‍♂️
- **`getTerminalSize(int &width, int &height)`**: Gets the size of the terminal window. 📏
- **`setSize()`**: Adjusts the size of the game board. 🛠️
- **`setColor(int color)`**: Changes text color in the terminal. 🎨
- **`resetchange()`**: Resets text formatting. 🔄
- **`setbold()`**: Makes text bold. 💪

### 3. **Classes**:
#### **Snake Class**:
Represents the snake and its functionality:
- Tracks the snake's body, length, and direction. 🐍
- Updates the snake’s position based on user input. 🎮
- Checks for body collisions and grows the snake when it eats food. 🍏

#### **food Class**:
Represents the food:
- Randomly generates coordinates for food 🍏 within the game board.
- Prints the food on the screen. 🖥️

### 4. **Game Logic**:
- The game logic handles player input, snake movement, food consumption, and collision detection. ⚙️
- The game continues running until either the snake collides with the border or itself. 🚧

### 5. **Main Function**:
The `main()` function is the entry point of the game, which:
- Takes player input for the name and difficulty. 🎮
- Initializes the game environment, including the snake 🐍 and food 🍏 objects.
- Handles the game loop, checking for collisions and updating the game state. 🔄

## Compilation and Execution

### To Compile:
1. Use a C++ compiler like `g++`:
   ```bash
   g++ -o snake_game snake_game.cpp
   ```

### To Run:
2. Execute the compiled program:
   ```bash
   ./snake_game
   ```

## Difficulty Levels
1. **Easy**: Slower game speed 🐢.
2. **Medium**: Moderate game speed 🐍.
3. **Hard**: Faster game speed 🐇.
4. **Expert**: Very fast game speed 🦁.

## Example

```bash
Enter Your Name: John
Enter number to adjust difficulty level:
1. Easy
2. Medium
3. Hard
4. Expert
Difficulty level: 3
```

After the game ends, your score will be displayed:
```bash
John, you scored: 100 🏆
```

## Notes
- This game is designed to be run in a terminal that supports ANSI escape sequences for cursor movement and text formatting. 💻
- The game uses non-blocking input to allow for real-time player control without waiting for the player to press a key. ⏳

## Contributing
Feel free to fork and improve the game! Contributions are always welcome. 🙌

## License
This project is open-source and available under the MIT License. 🎉

---

Enjoy the game! 🐍🍏🎮
