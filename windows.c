// Include libraries
#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include "windows.h"
#include "Game.h"
#include "common.h"


// GameOfLife

void initColors() {
    // Charge predifined colors
    start_color();

    // Initialize color pairs (foreground, background)
    init_pair(1, COLOR_BLACK, COLOR_RED);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    init_pair(4, COLOR_WHITE, COLOR_BLACK);
    init_pair(5, COLOR_RED, COLOR_YELLOW);
}

void plotGeneration(array_cells *lifeList, WINDOW *win, int offsetX, int offsetY, unsigned int color) {
    // Clean window
    werase(win);

    // Create box arround the window
    box(win, 0, 0);

    // Starts attributes of colors
    wattron(win, COLOR_PAIR(color));

    // For each element in the list
    for (unsigned int x = 0; x < lifeList->array_length; x++) {
        // Plot a square in the position defined by the offsets
        mvwaddch(win, offsetY + lifeList->array[x].y, offsetX + lifeList->array[x].x, ' ');
    }

    // Finish the color attibutes
    wattroff(win, COLOR_PAIR(color));

    // Update the window
    wrefresh(win);
}

void chargeInfo(){
    // Create the window of information
    WINDOW *winInfo = newwin(Y_BORDER, X_BORDER, 0, 0);

    // Create box arround the window
    box(winInfo, 0, 0);

    // Plot the information
    wattron(winInfo, COLOR_PAIR(2) | A_UNDERLINE);
    mvwprintw(winInfo, 1, 9, "Game of life" );
    wattroff(winInfo, COLOR_PAIR(2) | A_UNDERLINE);
    mvwprintw(winInfo, 2, 1, " ");
    wattron(winInfo, COLOR_PAIR(4) | A_UNDERLINE);
    mvwprintw(winInfo, 3, 1, "Information" );
    wattroff(winInfo, A_UNDERLINE);
    mvwprintw(winInfo, 4, 2, "Select pattern using UP/DOWN");
    mvwprintw(winInfo, 5, 2, "Control initial position:");
    mvwprintw(winInfo, 6, 3, "+ To move up pulse Y");
    mvwprintw(winInfo, 7, 3, "+ To move down pulse B");
    mvwprintw(winInfo, 8, 3, "+ To move right pulse J");
    mvwprintw(winInfo, 9, 3, "+ To move left pulse G");
    mvwprintw(winInfo, 10, 2, "To input pattern pulse ENTER");
    mvwprintw(winInfo, 11, 2, "Control speed using LEFT/RIGHT");
    mvwprintw(winInfo, 12, 2, "To pause the expansion pulse P");
    mvwprintw(winInfo, 13, 2, "To make an step pulse S");
    mvwprintw(winInfo, 14, 2, "To reset pulse R");
    mvwprintw(winInfo, 15, 2, "To exit pulse ESC");
    wattroff(winInfo, COLOR_PAIR(2));

    // Update the window
    wrefresh(winInfo);
}

void choosePattern(int Highlight, array_cells *lifeList){
  cell cell_i = {.x = 1, .y = 2, .alive_neighbor = 0};
  freeMemory(lifeList);
  
  // For no pattern selection
  if (Highlight == 0){
      // Charge the live cells
      cell_i.x = 1; cell_i.y = 1;
  }

  // For the pattern 1
  if (Highlight == 1){
      // Charge the live cells
      cell_i.x = 1; cell_i.y = 2;
      addCellToArray(lifeList, cell_i);
      cell_i.x = 2; cell_i.y = 1;
      addCellToArray(lifeList, cell_i);
      cell_i.x = 2; cell_i.y = 2;
      addCellToArray(lifeList, cell_i);
      cell_i.x = 2; cell_i.y = 3;
      addCellToArray(lifeList, cell_i);
      cell_i.x = 3; cell_i.y = 1;
      addCellToArray(lifeList, cell_i);
  }

  // For pattern 2
  else if (Highlight == 2){
      cell_i.x = 1; cell_i.y = 2;
      addCellToArray(lifeList, cell_i);
      cell_i.x = 2; cell_i.y = 2;
      addCellToArray(lifeList, cell_i);
      cell_i.x = 2; cell_i.y = 3;
      addCellToArray(lifeList, cell_i);
      cell_i.x = 7; cell_i.y = 1;
      addCellToArray(lifeList, cell_i);
      cell_i.x = 6; cell_i.y = 3;
      addCellToArray(lifeList, cell_i);
      cell_i.x = 7; cell_i.y = 3;
      addCellToArray(lifeList, cell_i);
      cell_i.x = 8; cell_i.y = 3;
      addCellToArray(lifeList, cell_i);
  }

  // For pattern 3
  else if (Highlight == 3){
      cell_i.x = 1; cell_i.y = 3;
      addCellToArray(lifeList, cell_i);
      cell_i.x = 2; cell_i.y = 3;
      addCellToArray(lifeList, cell_i);
      cell_i.x = 2; cell_i.y = 1;
      addCellToArray(lifeList, cell_i);
      cell_i.x = 4; cell_i.y = 2;
      addCellToArray(lifeList, cell_i);
      cell_i.x = 5; cell_i.y = 3;
      addCellToArray(lifeList, cell_i);
      cell_i.x = 6; cell_i.y = 3;
      addCellToArray(lifeList, cell_i);
      cell_i.x = 7; cell_i.y = 3;
      addCellToArray(lifeList, cell_i);
  }
}

void restart (array_cells *lifeList, array_cells *deadList, array_cells *newGenList){
  freeMemory(deadList);
  freeMemory(newGenList);
  freeMemory(lifeList);
}

int main() {
    // Initialize ncurses
    initscr();
    // Disable input echoing
    noecho();
    // Hide cursor
    curs_set(0);
    // Call initColors() function
    initColors();
    // Disable line buffering
    cbreak();

    // Obtain terminal size
    getmaxyx(stdscr, yWinMax, xWinMax);

    // Divide the terminal in subwindows
    winGame = newwin(yWinMax, xWinMax - X_BORDER, 0, X_BORDER);
    winSettings = newwin(yWinMax- Y_BORDER, X_BORDER, Y_BORDER, 0);
    winPrev = newwin(yWinMax - Y_BORDER - 14, X_BORDER - 10, Y_BORDER + 7, 5);

    // In the window settings add some titles and a box
    wattron(winSettings,  A_UNDERLINE);
    mvwprintw(winSettings, 6, 9, "Selected pattern" );
    mvwprintw(winSettings, 1, 1, "Pattern selection" );
    wattroff(winSettings, A_UNDERLINE);
    wrefresh(winSettings);
    box(winSettings, 0, 0);

    // Call chargeInfo() function
    chargeInfo();

    // Read the keyboard of the computer
    nodelay(winSettings, true);
    keypad(winSettings, true);

    // Define the predefined patterns
    char *choices[] = {"-----------",
                       "R-pentomino",
                       "Diehard    ",
                       "Acorn      "};


    unsigned int choice = 0;        // Index of the selected pattern (changes with ENTER)
    unsigned int Highlight = 0;     // Index of the menu of selection (changes with UP/DOWN)
    unsigned int speed = 1;         // Index of speed (changes with LEFT/RIGHT)
    unsigned int rate = 1;          // Final delay time
    ite = 0;                        // Number of iterations
    bool stop = true;               // Variable to indicate to pause the program
    bool step = true;               // Variable to enable 1 step when paused program
    int xDirOffset = 0;             // Initial position offset in X
    int yDirOffset = 0;             // Initial position offset in Y
    unsigned int i  = 1;
    // Prelocation of lists
    lifeList = initCellArray();
    deadList = initCellArray();
    newGenList = initCellArray();

    choosePattern(0, &lifeList);
    // Call the plotGeneration() function to previsualize the pattern in the previsualization windows
    plotGeneration(&lifeList, winPrev, 0, 0, 3);

    // Main Loop
    while (1) {
        // For each defined pattern
        for (i = 1; i < 4; i++) {
            // The background color of the selected pattern is highlightened
            if (i == Highlight) {
                wattron(winSettings, COLOR_PAIR(3));
            }
            // The rest are set to normal style
            else {
                wattron(winSettings, COLOR_PAIR(4));
            }
            // Plot the patterns
            mvwprintw(winSettings, i + 1, 1, "%s", choices[i]);

            // Finish the style of the choices
            wattroff(winSettings, COLOR_PAIR(3) | COLOR_PAIR(4));
        }

        // Show pattern choice and configured speed
        mvwprintw(winSettings, yWinMax-Y_BORDER - 6, 1, "Running: %s", choices[choice]);
        mvwprintw(winSettings, yWinMax-Y_BORDER - 5, 1, "Speed: %d", speed);
        mvwprintw(winSettings, yWinMax-Y_BORDER - 4, 1, "Num ite: %d", ite);
        wrefresh(winSettings);

        // Get information from the keyboard
        unsigned int input = wgetch(winSettings);

        // Depending on the input do...
        switch (input) {
           // Choose pattern
            case KEY_UP: // If UP is pulsed
                // Move the cursor 1 space down
                Highlight--;

                // If at top, limit the scroll
                if (Highlight <= 0){
                    Highlight = 1;
                }

                // Reset when new pattern is selected
                if (ite != 0){
                    restart (&lifeList, &deadList, &newGenList);
                    choice = 0; ite = 0;
                    mvwprintw(winSettings, yWinMax-Y_BORDER - 4, 1, "Num ite: %d      ", ite);
                    mvwprintw(winSettings, yWinMax-Y_BORDER - 3, 1, "Num cells alive: %ld            ", lifeList.array_length);
                }

                // Charge pattern
                choosePattern(Highlight, &lifeList);

                // Call the plotGeneration() function to previsualize the pattern in the previsualization window
                plotGeneration(&lifeList, winPrev, 0, 0, 3);
                break;

            case KEY_DOWN: // If DOWN is pulsed
                // Move the cursor 1 space ip
                Highlight++;

                // If at bottom, limit the scroll
                if (Highlight >= 4){
                    Highlight = 3;
                }
                // Reset when new pattern is selected
                if (ite != 0){
                    restart (&lifeList, &deadList, &newGenList);
                    choice = 0; ite = 0;
                    mvwprintw(winSettings, yWinMax-Y_BORDER - 4, 1, "Num ite: %d      ", ite);
                    mvwprintw(winSettings, yWinMax-Y_BORDER - 3, 1, "Num cells alive: %ld            ", lifeList.array_length);
                }

                // Charge pattern
                choosePattern(Highlight, &lifeList);
                
                // Call the plotGeneration() function to previsualize the pattern in the previsualization window
                plotGeneration(&lifeList, winPrev, 0, 0, 3);
                break;

            //Choose starting point
            case 121: // If Y is pulsed (offset up)
                // If choice not done yet, move the initial position up
                if (choice == 0){
                    yDirOffset--;
                }
                break;
            case 98: // If B is pulsed (offset down)
                // If choice not done yet, move the initial position down
                if (choice == 0){
                    yDirOffset++;
                }
                break;
            case 103: // If G is pulsed (offset left)
                // If choice not done yet, move the initial position left
                if (choice == 0){
                    xDirOffset--;
                }
                break;
            case 106:  // If J is pulsed (offset right)
                // If choice not done yet, move the initial position right
                if (choice == 0){
                    xDirOffset++;
                }
                break;

            // Choose simulation speed
            case KEY_RIGHT: // If RIGHT is pulsed
                // Increase the speed factor
                speed++;
                // If at top, limit the speed
                if (speed > 5){
                    speed = 5;
                }
                break;
            case KEY_LEFT: // If LEFT is pulsed
                // Decrease the speed factor
                speed--;
                // If at bottom, limit the speed
                if (speed == 0){
                    speed = 1;
                }
                break;

            case 112: // If P is pulsed (pause)
                // Active pause
                stop = !stop;
                break;

            case 115: // If S is pulsed (step)
                // Active step
                step = !step;
                choice = Highlight;
                if (stop){
                    stop = !stop;
                }
                break;

            case 10: // If ENTER is pulsed
                // Select the pattern as the one in highlight
                choice = Highlight;
                break;

            case 27: // If ESC is pulsed, end everything
                endwin();
                freeMemory(&deadList);
                freeMemory(&newGenList);
                freeMemory(&lifeList);
                return 0;

            case 114: // If R is pulsed, reset simulation
                if (ite != 0){
                  restart (&lifeList, &deadList, &newGenList);
                  choice = 0; ite = 0;
                  mvwprintw(winSettings, yWinMax-Y_BORDER - 4, 1, "Num ite: %d      ", ite);
                  mvwprintw(winSettings, yWinMax-Y_BORDER - 3, 1, "Num cells alive: %ld            ", lifeList.array_length);
                }
                choosePattern(Highlight, &lifeList);

            default:
                break;
        }

        // Compute delay based on the speed factor
        rate = (6-speed) * 100000;

        // Previsualize the pattern in the game grid
        if (choice == 0) {
          plotGeneration(&lifeList, winGame, xDirOffset, yDirOffset, 1);
        }

        // If choice is done, not stop or stepped
        if (choice != 0 && (stop || step)) {
            // Plot the live cells in white
            plotGeneration(&lifeList, winGame, xDirOffset, yDirOffset, 3);

            // Inform of the number of alive cells
            mvwprintw(winSettings, yWinMax-Y_BORDER - 3, 1, "Num cells alive: %ld            ", lifeList.array_length);

            // If liveList is empty
            if (lifeList.array_length == 0){
                // Allow new selection
                choice = 0;

                // Advice all cells are dead
                wattron(winSettings, COLOR_PAIR(5));
                mvwprintw(winSettings, yWinMax-Y_BORDER - 3, 1, "   ***ALL CELLS ARE DEAD***   ");
                wattroff(winSettings, COLOR_PAIR(5));

                // Restart the game variables
                restart (&lifeList, &deadList, &newGenList);
            }

            // Delay based on the rate factor
            usleep(rate);
            
            // Disable step
            step = !step;

            // GameOfLife
            game(&lifeList, &deadList, &newGenList);

            // Adapt old and new generations variables
            freeMemory(&lifeList);
            for (i = 0; i < newGenList.array_length; i++){
              addCellToArray(&lifeList, newGenList.array[i]);
            }
            freeMemory(&deadList);
            freeMemory(&newGenList);

            ite++;
        }
    }

    // Clean up ncurses
    endwin();
    return 0;
}
