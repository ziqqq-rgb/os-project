#include <iostream>
#include <vector>       
#include <string>       
#include <algorithm>    
#include <cmath>       
#include <iomanip>      

const int MIN_TRACK = 0;
const int MAX_TRACK = 199;

/**
 * @brief 
 * @param path 
 */
void printSimulationTable(const std::vector<int>& path) {
    int totalDistance = 0;

    // print the table 
    std::cout << "\n" << std::setw(10) << "Start"
              << std::setw(10) << "Finished"
              << std::setw(20) << "Track Travelled" << std::endl;
    std::cout << "========================================" << std::endl;

    
    for (size_t i = 0; i < path.size() - 1; ++i) {
        int start = path[i];
        int end = path[i + 1];
        int distance = std::abs(end - start);
        totalDistance += distance;

        std::cout << std::setw(10) << start
                  << std::setw(10) << end
                  << std::setw(20) << distance << std::endl;
    }

    // print final total 
    std::cout << "========================================" << std::endl;
    std::cout << "Total Track Travelled: " << totalDistance << std::endl;
}

/**
 * @brief 
 * @param str 
 * @return 
 */
std::string toUpper(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

int main() {
    int initialPosition;
    std::string direction;
    std::vector<int> requests;
    std::vector<int> path; 

    // user inputs 
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
    


    // sort requests in ascending order
    std::sort(requests.begin(), requests.end());

    // split requests into "down" or"up"
    std::vector<int> downRequests;
    std::vector<int> upRequests;

    for (int r : requests) {
        if (r < initialPosition) {
            downRequests.push_back(r);
        } else {
            upRequests.push_back(r);
        }
    }

    path.push_back(initialPosition);

    // c-scan logic 
    if (direction == "UP") {
        
        for (int r : upRequests) {
            path.push_back(r);
        }

        path.push_back(MAX_TRACK);
        

        path.push_back(MIN_TRACK);


        for (int r : downRequests) {
            path.push_back(r);
        }
    } 
    else if (direction == "DOWN") {
        
        std::sort(downRequests.rbegin(), downRequests.rend());
        
        
        for (int r : downRequests) {
            path.push_back(r);
        }

       
        path.push_back(MIN_TRACK);

       
        path.push_back(MAX_TRACK);

       
        std::sort(upRequests.rbegin(), upRequests.rend());

       
        for (int r : upRequests) {
            path.push_back(r);
        }
    } 
    else {
        std::cout << "Invalid direction. Please enter UP or DOWN." << std::endl;
        return 1; 
    }

    // print final results
    printSimulationTable(path);

    return 0; 
}