#include <iostream>
#include <vector>       // For storing the requests
#include <string>       // For handling the "UP" or "DOWN" input
#include <algorithm>    // For sorting the requests
#include <cmath>        // For std::abs()
#include <iomanip>      // For formatting the output table (std::setw)

// Define the disk boundaries as constants
const int MIN_TRACK = 0;
const int MAX_TRACK = 199;

/**
 * @brief Prints the C-SCAN path and calculates the total distance.
 * @param path A vector<int> containing the exact sequence of tracks visited.
 */
void printSimulationTable(const std::vector<int>& path) {
    int totalDistance = 0;

    // Print the table header 
    std::cout << "\n" << std::setw(10) << "Start"
              << std::setw(10) << "Finished"
              << std::setw(20) << "Track Travelled" << std::endl;
    std::cout << "========================================" << std::endl;

    // Loop through the path to calculate and print each step
    for (size_t i = 0; i < path.size() - 1; ++i) {
        int start = path[i];
        int end = path[i + 1];
        int distance = std::abs(end - start);
        totalDistance += distance;

        std::cout << std::setw(10) << start
                  << std::setw(10) << end
                  << std::setw(20) << distance << std::endl;
    }

    // Print the final total 
    std::cout << "========================================" << std::endl;
    std::cout << "Total Track Travelled: " << totalDistance << std::endl;
}

/**
 * @brief Converts a string to uppercase.
 * @param str The string to convert.
 * @return The uppercase version of the string.
 */
std::string toUpper(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

int main() {
    int initialPosition;
    std::string direction;
    std::vector<int> requests;
    std::vector<int> path; // Will store the full sequence of moves

    // 1. Get user inputs 
    std::cout << "Enter the initial arm position (0-199): ";
    std::cin >> initialPosition;

    std::cout << "Enter the arm direction (UP or DOWN): ";
    std::cin >> direction;
    direction = toUpper(direction);

    std::cout << "Enter track requests (e.g., 85 10 37). Enter -1 to finish:" << std::endl;
    int req;
    while (std::cin >> req && req != -1) {
        if (req >= MIN_TRACK && req <= MAX_TRACK) {
            requests.push_back(req);
        } else {
            std::cout << "Ignoring invalid track " << req << ". Must be between 0 and 199." << std::endl;
        }
    }
    


    // 2. Sort the requests in ascending order [cite: 14]
    std::sort(requests.begin(), requests.end());

    // 3. Split requests into two lists: one for "down" and one for "up"
    std::vector<int> downRequests;
    std::vector<int> upRequests;

    for (int r : requests) {
        if (r < initialPosition) {
            downRequests.push_back(r);
        } else {
            upRequests.push_back(r);
        }
    }

    // 4. Start building the movement path
    path.push_back(initialPosition);

    // 5. Simulate the C-SCAN logic based on direction [cite: 15]
    if (direction == "UP") {
        // Service all "up" requests in ascending order
        for (int r : upRequests) {
            path.push_back(r);
        }

        // C-SCAN Logic: Move to the end of the disk 
        path.push_back(MAX_TRACK);
        
        // C-SCAN Logic: "Circulate" back to the beginning 
        path.push_back(MIN_TRACK);

        // Service all "down" requests (which are now "up" from 0)
        for (int r : downRequests) {
            path.push_back(r);
        }
    } 
    else if (direction == "DOWN") {
        // Sort "down" requests in descending order for servicing
        std::sort(downRequests.rbegin(), downRequests.rend());
        
        // Service all "down" requests
        for (int r : downRequests) {
            path.push_back(r);
        }

        // C-SCAN Logic: Move to the beginning of the disk
        path.push_back(MIN_TRACK);

        // C-SCAN Logic: "Circulate" back to the end
        path.push_back(MAX_TRACK);

        // Sort "up" requests in descending order for servicing from the top
        std::sort(upRequests.rbegin(), upRequests.rend());

        // Service all "up" requests
        for (int r : upRequests) {
            path.push_back(r);
        }
    } 
    else {
        std::cout << "Invalid direction. Please enter UP or DOWN." << std::endl;
        return 1; // Exit with an error
    }

    // 6. Print the final results 
    printSimulationTable(path);

    return 0; 
}