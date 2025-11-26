#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

// Validation function that returns true if valid
bool validateInput(int value, int min, int max, const string& fieldName) {
    if (value < min || value > max) {
        cout << "Error: " << fieldName << " must be between " << min << " and " << max << endl;
        return false;
    }
    return true;
}

int main() {
    int initialPos, n;
    string direction;
    vector<int> requests;

    // Get initial arm position with validation and retry
    while (true) {
        cout << "Enter initial arm position (0-199): ";
        cin >> initialPos;
        
        if (validateInput(initialPos, 0, 199, "Initial arm position")) {
            break; // Valid input, exit loop
        }
        cout << "Please try again.\n";
    }

    // Get direction with validation and retry
    while (true) {
        cout << "Enter direction (UP/DOWN): ";
        cin >> direction;
        transform(direction.begin(), direction.end(), direction.begin(), ::toupper);
        
        if (direction == "UP" || direction == "DOWN") {
            break; // Valid input, exit loop
        }
        cout << "Error: Direction must be UP or DOWN\n";
        cout << "Please try again.\n";
    }

    // Get number of requests with validation and retry
    while (true) {
        cout << "Enter number of track requests: ";
        cin >> n;
        
        if (validateInput(n, 1, 100, "Number of requests")) {
            break; // Valid input, exit loop
        }
        cout << "Please try again.\n";
    }

    // Get track requests with validation
    cout << "Enter track requests: ";
    int i = 0;
    while (i < n) {
        int track;
        cin >> track;
        
        if (!validateInput(track, 0, 199, "Track request")) {
            cout << "Please enter a valid track number: ";
            continue; // Ask for this track again
        }
        
        // Check for duplicates
        if (find(requests.begin(), requests.end(), track) != requests.end()) {
            cout << "Warning: Duplicate track " << track << " ignored. Enter another: ";
            continue; // Ask for another track
        }
        
        requests.push_back(track);
        i++; // Only increment when we successfully add a track
    }


    sort(requests.begin(), requests.end());
    // After removing duplicates, display the number of unique requests.
    cout << "Processing " << requests.size() << " unique track requests.\n";
    cout << "\nSorted requests: ";
    for (int req : requests) cout << req << " ";
    cout << "\n\n";

    cout << "=========================================\n";
    cout << "Initial Arm position: " << initialPos << "\tDirection: " << direction << "\n";
    cout << "=========================================\n\n";

    cout << left << setw(10) << "Start" << setw(15) << "Finished" << "Track Travelled\n";
    cout << "-------------------------------------------\n";

    int currentPos = initialPos;
    int totalTrackTravelled = 0;
    vector<int> serviceOrder;

    if (direction == "UP") {
        // service requests >= head
        for (int req : requests) {
            if (req >= currentPos) {
                int travel = abs(req - currentPos);
                cout << left << setw(10) << currentPos << setw(15) << req << travel << "\n";
                totalTrackTravelled += travel;
                currentPos = req;
                serviceOrder.push_back(req);
            }
        }

        // move to 199
        if (currentPos != 199) {
            int travel = 199 - currentPos;
            cout << left << setw(10) << currentPos << setw(15) << 199 << travel << "\n";
            totalTrackTravelled += travel;
            currentPos = 199;
        }

        // Jump to 0 (counted )
        int jumpDist = 199;
        cout << left << setw(10) << currentPos << setw(15) << 0 << jumpDist << "\n";
        totalTrackTravelled += jumpDist;
        currentPos = 0;

        // service remaining (less than head)
        for (int req : requests) {
            if (req < initialPos) {
                int travel = abs(req - currentPos);
                cout << left << setw(10) << currentPos << setw(15) << req << travel << "\n";
                totalTrackTravelled += travel;
                currentPos = req;
                serviceOrder.push_back(req);
            }
        }

    } else { // DOWN
        // service requests <= head (descending)
        for (int i = requests.size() - 1; i >= 0; i--) {
            if (requests[i] <= currentPos) {
                int travel = abs(currentPos - requests[i]);
                cout << left << setw(10) << currentPos << setw(15) << requests[i] << travel << "\n";
                totalTrackTravelled += travel;
                currentPos = requests[i];
                serviceOrder.push_back(requests[i]);
            }
        }

        // move to 0
        if (currentPos != 0) {
            int travel = currentPos;
            cout << left << setw(10) << currentPos << setw(15) << 0 << travel << "\n";
            totalTrackTravelled += travel;
            currentPos = 0;
        }

        // Jump to 199 (counted)
        int jumpDist = 199;
        cout << left << setw(10) << currentPos << setw(15) << 199 << jumpDist << "\n";
        totalTrackTravelled += jumpDist;
        currentPos = 199;

        // service remaining (greater than head)
        for (int i = requests.size() - 1; i >= 0; i--) {
            if (requests[i] > initialPos) {
                int travel = abs(currentPos - requests[i]);
                cout << left << setw(10) << currentPos << setw(15) << requests[i] << travel << "\n";
                totalTrackTravelled += travel;
                currentPos = requests[i];
                serviceOrder.push_back(requests[i]);
            }
        }
    }

    cout << "\nTotal Track Travelled: " << totalTrackTravelled << "\n\n";
    cout << "Service Order: ";
    for (int track : serviceOrder) cout << track << " ";
    cout << "\n";

    return 0;
}
