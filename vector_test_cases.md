### 1. Vertical Win (Player 1)
All chips are in Column 0. Since index 0 is the bottom, the chips occupy indices 0, 1, 2, and 3.
```cpp
std::vector<std::vector<int>> verticalWin = {
    {1, 1, 1, 1, 0, 0}, // Column 0: Four 1s stacked from bottom
    {0, 0, 0, 0, 0, 0}, // Column 1
    {0, 0, 0, 0, 0, 0}, // Column 2
    {0, 0, 0, 0, 0, 0}, // Column 3
    {0, 0, 0, 0, 0, 0}, // Column 4
    {0, 0, 0, 0, 0, 0}, // Column 5
    {0, 0, 0, 0, 0, 0}  // Column 6
};
```

### 2. Horizontal Win (Player 2)
The win spans across Columns 0, 1, 2, and 3, all at the bottom-most row (index 0).
```cpp
std::vector<std::vector<int>> horizontalWin = {
    {2, 0, 0, 0, 0, 0}, // Col 0
    {2, 0, 0, 0, 0, 0}, // Col 1
    {2, 0, 0, 0, 0, 0}, // Col 2
    {2, 0, 0, 0, 0, 0}, // Col 3
    {1, 0, 0, 0, 0, 0}, // Col 4
    {1, 0, 0, 0, 0, 0}, // Col 5
    {1, 0, 0, 0, 0, 0}  // Col 6
};
```

### 3. Ascending Diagonal Win (Player 1)
The win starts at (Col 0, Row 0) and climbs to (Col 3, Row 3). Note how "padding" chips are needed to support the diagonal chips.
```cpp
std::vector<std::vector<int>> diagonalAscending = {
    {1, 0, 0, 0, 0, 0}, // Col 0: (0,0) is '1'
    {2, 1, 0, 0, 0, 0}, // Col 1: (1,1) is '1'
    {2, 2, 1, 0, 0, 0}, // Col 2: (2,2) is '1'
    {2, 1, 2, 1, 0, 0}, // Col 3: (3,3) is '1'
    {0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0}
};
```

### 4. Descending Diagonal Win (Player 2)
The win starts at a height (Col 0, Row 3) and drops to (Col 3, Row 0).
```cpp
std::vector<std::vector<int>> diagonalDescending = {
    {1, 2, 1, 2, 0, 0}, // Col 0: (0,3) is '2'
    {1, 1, 2, 0, 0, 0}, // Col 1: (1,2) is '2'
    {1, 2, 0, 0, 0, 0}, // Col 2: (2,1) is '2'
    {2, 0, 0, 0, 0, 0}, // Col 3: (3,0) is '2'
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0}
};
```

### 5. Top-of-Board Horizontal Block (Mixed)
This tests the highest possible indices. Players have filled columns until a win occurs at the very top (Row 5).
```cpp
std::vector<std::vector<int>> topRowStruggle = {
    {1, 2, 1, 2, 1, 2}, // Col 0: Full
    {2, 1, 2, 1, 2, 1}, // Col 1: Full
    {1, 2, 1, 2, 1, 2}, // Col 2: Full
    {2, 1, 2, 1, 2, 2}, // Col 3: Full, Player 2 wins at (3,5)? 
    {0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0}
};
```

### 6. Far-Right Vertical Win (Player 2)
This tests the boundary of the very last column (index 6) and the highest possible rows.
```cpp
std::vector<std::vector<int>> rightEdgeVertical = {
    {0, 0, 0, 0, 0, 0}, // Col 0
    {0, 0, 0, 0, 0, 0}, // Col 1
    {0, 0, 0, 0, 0, 0}, // Col 2
    {0, 0, 0, 0, 0, 0}, // Col 3
    {0, 0, 0, 0, 0, 0}, // Col 4
    {0, 0, 0, 0, 0, 0}, // Col 5
    {1, 1, 2, 2, 2, 2}  // Col 6: Win at indices 2, 3, 4, 5
};
```

### 7. "Floating" Horizontal Win (Player 1)
A horizontal win that doesn't touch the floor. This ensures your logic doesn't only check `row 0`.
```cpp
std::vector<std::vector<int>> midAirHorizontal = {
    {2, 1, 0, 0, 0, 0}, // Col 0
    {2, 1, 0, 0, 0, 0}, // Col 1
    {2, 1, 0, 0, 0, 0}, // Col 2
    {1, 1, 0, 0, 0, 0}, // Col 3: Win for Player 1 at row index 1
    {0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0}
};
```

### 8. Offset Ascending Diagonal (Player 2)
An ascending diagonal win that starts in the middle of the board rather than the corner. This tests if your diagonal loops are flexible with starting coordinates.
```cpp
std::vector<std::vector<int>> midBoardDiagonalAsc = {
    {0, 0, 0, 0, 0, 0}, 
    {1, 0, 0, 0, 0, 0}, 
    {1, 2, 0, 0, 0, 0}, // Win starts here (Col 2, Row 1)
    {2, 1, 2, 0, 0, 0}, // (3, 2)
    {1, 2, 1, 2, 0, 0}, // (4, 3)
    {2, 1, 2, 1, 2, 0}, // (5, 4)
    {0, 0, 0, 0, 0, 0}
};
```

### 9. Wrapped Descending Diagonal (Player 1)
A descending diagonal win that ends at the very bottom-right corner of the board.
```cpp
std::vector<std::vector<int>> cornerDiagonalDesc = {
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {2, 2, 2, 1, 0, 0}, // (3, 3) - Start
    {2, 2, 1, 0, 0, 0}, // (4, 2)
    {2, 1, 0, 0, 0, 0}, // (5, 1)
    {1, 0, 0, 0, 0, 0}  // (6, 0) - End
};
```

### 10. The "Overlapping" Win
A case where Player 1 has 5 chips in a row horizontally. Some algorithms fail if they strictly look for exactly 4; this ensures "4 or more" is handled correctly.
```cpp
std::vector<std::vector<int>> fiveInARow = {
    {1, 0, 0, 0, 0, 0}, // Col 0
    {1, 0, 0, 0, 0, 0}, // Col 1
    {1, 0, 0, 0, 0, 0}, // Col 2
    {1, 0, 0, 0, 0, 0}, // Col 3
    {1, 0, 0, 0, 0, 0}, // Col 4
    {2, 2, 0, 0, 0, 0}, // Col 5
    {2, 0, 0, 0, 0, 0}  // Col 6
};
```

---

### Logic Tip for Column-Major
When checking for wins in this format, your iteration limits change slightly:
* **Vertical:** Only check rows $0$ to $2$ (since a win starting at row 3 would go out of bounds). 
* **Horizontal:** Only check columns $0$ to $3$.
* **Diagonal:** Ensure your nested loops stay within `grid[0...6]` and `grid[col][0...5]`.