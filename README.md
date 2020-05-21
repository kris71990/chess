# Chess Game

## About
This is a two-player chess implementation in C++. All chess rules apply except castling. 


## Use
Clone repository to compile, build, and play in the command line.


### Build with CMake

1. `mkdir build`
2. `cd build` -> 
3. `cmake ..`
3. `cmake --build .`
5. `./chess`


### Basic Guide
1. The chess board is displayed as a grid - columns are lettered `a-h` and rows are numbered `1-8`.
2. To play, enter a square containing a piece `ex. e2`
3. Then enter a square you want to move the piece to `ex. e4`
4. If it is a valid move, the updated board will re-print and the other player will be prompted to move

* Enable help mode with the `-h` suffix during step 2 for a list of possible moves for the selected piece
* Help mode will remain on until turned off - turn off help mode during step 3 or 4 with the `-hx` suffix
* All moves are logged - to view the log for the current game, type `l` at any time. 

* To quit, type `q` at any time. 