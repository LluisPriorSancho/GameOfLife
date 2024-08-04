# GameOfLife
Game of life devolepd in CThe Game of life is a popular simulation game developed by the mathematician John Conway in 1970. The game of life was presented as, what is called now, cellular automaton. With simple rules, the game yields non-trial, complex patterns that evolve overtime. 
The game consists of a discrete time, infinite two dimensional orthogonal grid of square cells. Each cell can be in one of two states, live or dead. Every cell interacts with its eight neighbours(horizontal, vertical and diagonal adjacent) and according to a fixed set of rules, the state of the next step will be decided. The rules are 4:

  1. Any live cell with fewer than two live cells in their neighbourhood dies, as if caused by underpopulation.
  2. Any live cell with two or three live cells in their neighbourhood lives on the next generation. 
  3. Any live cell with more than three live cells in their neighbourhood dies, as if by overpopulation.
  4. Any dead cell with exactly three live cells in their neighbourhood revives, as if by reproduction.
    
## Usage of the Game
  1. To compile and launch the game:
     
    $ make init

  3. To run the game and check memory metrics:

    $ make memoryCheck

  4. To generate a file that checks the time management of the last launch of the game. It is mandatory to run the code first at least 1 time.

    $ make times

  5. To generate a file called ‘metrics.png’ that visually plots the relation between functions and times it function was called. It is mandatory to run the code first at least 1 time.

    $ make connect

  6. To clean multiples files of the compilation or metrics:

    $ make clean
    
## User interface
The user interface is a graphical screen that allows the user to configure multiple parameters and control the flow of the program. When the system is launched, the graphical interface appears on top of the terminal. To be sure that the screen works properly, it is mandatory to run the code in a full screen terminal (minimum resolution of 153x39). Launching the program in another window size may not ensure the correct functionality of all the characteristics implemented such as the previsualization of the pattern, even though the program will work some assets might not be seen.
Once the game is launched, the first appearance is the following:

![image](https://github.com/user-attachments/assets/415f2eee-02dc-44f7-b398-b7b6d4389239)
We can visualise 3 main areas. Occupying the majority of the screen is the game window. Here the different generations will be displayed as white squares. In the bottom left part of the screen is displayed the pattern selector, more details of this window will be given later. In the top left part is displayed multiple information regarding the controls of the interface:

  1. To **select the initial pattern** we can use the *up and down* arrows. The selection will appear in the pattern selection box.
  2. To **control the initial position of the pattern**, it will be plotted in red in the game window. Using *Y and B* we can control the vertical axis and with *G and J* we can control the horizontal axis. These controls are only available as long as the pattern is not selected and the simulation has not started.
  3. We can **start the simulation** by pressing *enter*. This action will take the selected pattern, place it in the desired initial position and will start the simulation. The selected pattern is displayed at the bottom of the selection window.
  4. We can **control the speed** at which the simulation plots the different generations by using the *left and right* arrow keys. The speed has 5 different levels that correspond to 10Hz, 5Hz, 3.34Hz, 2.5Hz and 2Hz where 1 corresponds to the slower rate and 5 the highest one. The actual speed level is displayed at the bottom of the selection windows.
  5. In order to *stop the simulation* at any moment by pressing the letter *P*. To start the simulation again it is enough to pulse it again.
  6. The simulation can be **controlled step by step** pressing the letter *S*. 
  7. To **restart the simulation** the letter *R* can be pressed. This will allow us to select a new pattern and to place it in a new initial position. It erases all the previous simulation.
  8. To **exit** and close the user interface and finalise the program, the button *ESC* can be pressed.
    
More information about the pattern selection part. The most interesting elements are:

  1. The selection menu will highlight the option the cursor is in.
  
  2. A small previsualization of the pattern can be seen in the selected pattern window.
  
  3. Once the simulation has started, at the bottom it can be seen which pattern the simulation has started with.
  
  4. More useful information such as the speed level, the current iteration number and the actual number of alive cells is displayed at the bottom.
  
  <img src="https://github.com/user-attachments/assets/79ca4cb9-912a-458d-a52b-5057bb99fc61" width=300> <img src="https://github.com/user-attachments/assets/946f06bb-43c6-40d2-ab6c-16c48d194579" width=300> <img src="https://github.com/user-attachments/assets/12a4547b-f3e7-4bc5-a79a-bf3ffdc136ec" width=300>

  5. When a simulation reaches a state where there are no more alive cells it automatically stops and plots a warning message.
    
<img src="https://github.com/user-attachments/assets/c98913e4-4001-4c67-aadb-2be232b87849" width=300>
