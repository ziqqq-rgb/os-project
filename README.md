# os-project

This is a C++ code demonstrating the **C-SCAN (Circular SCAN) disk scheduling algorithm** for a disk with 200 tracks (0-199). The code is for the TDB2043 Operating Systems course.

## Group Members
- Muhammad Raziq Bin Sufian (24006626)
- Hazieq Danial Bin Roshihan Annuar (24006633)
- Ibrahim Bin Ahmad Jaafar Sadzik (24006396)
- Muhammad Aiman (22011708)
- Mohamed Ennaceur (24004285)

## Instructions to Compile and Run
1. **Prerequisites:** You require a C++ compiler with Standard Library (like g++).

2. **Compilation:** Execute terminal in the directory of the project and execute the command:
```bash
g++ -o disk_scheduler main.cpp
```
3. **Execution:**  Execute the produced executable.
```bash
./disk_scheduler
```
4. **Program Instructions:** After the execution of the program, you will be prompted to enter the primary head position, the track requests, and the direction.

## Project Structure

- `main.cpp` - The main source code for C-SCAN simulator.
- `OS Report.pdf` - The complete project report.
- `Presentation.pdf` - The project Slides.

## Code Explanation:

Variable Declaration : The program declares variables for initial head position (initialPos), number of requests (n), direction (direction), and a vector to store track requests.

Input Collection : Ask the user to enter the initial arm position (0-199), the direction (UP or DOWN), the number of track requests, and then all the track request numbers.

Direction Normalization : The direction string is converted to uppercase using transform() to handle both "up"/"UP" and "down"/"DOWN" inputs consistently.

Sorting Requests : All track requests are sorted in ascending order using sort(), which is essential for the C-SCAN algorithm to work efficiently.

Display Sorted Requests : The program displays the sorted request sequence to show the order before processing begins.

Output Header Setup : It prints a formatted header showing the initial arm position, direction, and column headers (Start, Finished, Track Travelled).

UP Direction Logic - Part 1 : If direction is "UP", the algorithm first services all requests that are greater than or equal to the current head position, moving upward through the disk.

Move to End (199) : After servicing all requests above the initial position, the head moves to track 199 (the outer edge of the disk) if it's not already there.

Circular Jump (UP) : The head then jumps from track 199 back to track 0. This jump distance of 199 tracks IS counted in the total movement, which is a key characteristic of C-SCAN.

UP Direction - Part 2 : After jumping to track 0, the algorithm services all remaining requests (those below the initial head position) in ascending order from 0 upward.

DOWN Direction Logic - Part 1 : If direction is "DOWN", the algorithm services all requests less than or equal to the current head position in descending order (moving toward track 0).

Move to Start (0) : After servicing all requests below the initial position, the head moves to track 0 (the inner edge) if not already there.

Circular Jump (DOWN) : The head jumps from track 0 to track 199. This 199-track jump IS counted in total movement, maintaining C-SCAN's circular nature.

DOWN Direction - Part 2 : After jumping to track 199, the algorithm services remaining requests (those above initial position) in descending order from 199 downward.


Track Movement Calculation : For each movement, the program calculates the absolute distance traveled, displays it, and adds it to the totalTrackTravelled counter, ensuring accurate total distance calculation including the circular jump. 





