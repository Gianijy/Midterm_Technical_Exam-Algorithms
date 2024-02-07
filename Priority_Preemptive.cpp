/*
    Clemente, Gian Ijy P.
    TN29
    Brute Force - Preemptive Priority Scheduling Algorithm
    - Without file-handling
*/


#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_SIZE = 100;

// Structure to represent a process
struct Process {
    int id;
    int arrivalTime;
    int burstTime; // Original burst time
    int remainingTime; // Remaining time to be executed
    int priority;
    int finishTime;
    int turnaroundTime;
    int waitingTime;
    bool completed;
};

// Function to find the process with the highest priority at a given time
int findHighestPriorityProcess(Process processes[], int n, int currentTime) {
    int highestPriority = -1;
    int selectedProcess = -1;

    for (int i = 0; i < n; ++i) {
        if (!processes[i].completed && processes[i].arrivalTime <= currentTime) {
            if (highestPriority == -1 || processes[i].priority < highestPriority) {
                highestPriority = processes[i].priority;
                selectedProcess = i;
            }
        }
    }
    return selectedProcess;
}


// Function to perform Priority Scheduling - Preemptive
void priorityScheduling(Process processes[], int n) {
    int currentTime = 0;
    int completedProcesses = 0;
    int executedProcess[MAX_SIZE]; // Array to store executed process at each time
    int executionTime[MAX_SIZE];   // Array to store the time at which each process is executed

    // Initialize arrays
    for (int i = 0; i < MAX_SIZE; ++i) {
        executedProcess[i] = -1;
        executionTime[i] = -1;
    }

    // Continue until all processes are completed
    while (completedProcesses < n) {
        int processIndex = findHighestPriorityProcess(processes, n, currentTime);

        if (processIndex != -1) {
            processes[processIndex].remainingTime--;

            if (processes[processIndex].remainingTime == 0) {
                processes[processIndex].completed = true;
                processes[processIndex].finishTime = currentTime + 1;
                processes[processIndex].turnaroundTime = processes[processIndex].finishTime - processes[processIndex].arrivalTime;
                processes[processIndex].waitingTime = processes[processIndex].turnaroundTime - processes[processIndex].burstTime;
                completedProcesses++;
            }

            // Store executed process and execution time
            executedProcess[currentTime] = processIndex;
            executionTime[currentTime] = currentTime;

            // Move to the next time slot
            currentTime++;
        } else {
            // No process to execute, move to the next arrival time
            int nextArrivalTime = INT_MAX;
            for (int i = 0; i < n; ++i) {
                if (!processes[i].completed && processes[i].arrivalTime > currentTime && processes[i].arrivalTime < nextArrivalTime) {
                    nextArrivalTime = processes[i].arrivalTime;
                }
            }
            currentTime = nextArrivalTime;
        }
    }


    // Declare an array to store the time slots
    int timeSlots[MAX_SIZE];

    // Initialize lastExecutionIndex to keep track of the index in the timeSlots array
    int lastExecutionIndex = 0;

    // Display Gantt Chart
    cout << "\nGantt Chart:\n";
    int lastExecutedProcess = -1;  // To keep track of the last executed process
    int lastExecutionTime = -1;  // To keep track of the last execution time
    for (int i = 0; i < MAX_SIZE; ++i) {
        if (executedProcess[i] != -1 && executedProcess[i] != lastExecutedProcess) {
            if (lastExecutionTime != -1) {
                // Store the last execution time in the timeSlots array
                timeSlots[lastExecutionIndex++] = lastExecutionTime;
            }
            cout << "|---P" << processes[executedProcess[i]].id << "---";
            lastExecutedProcess = executedProcess[i];
            lastExecutionTime = i;
        }
    }

    // Store the last execution time in the timeSlots array
    if (lastExecutionTime != -1) {
        timeSlots[lastExecutionIndex++] = lastExecutionTime;
    }

    int lastProcessFinishTime = lastExecutionTime + processes[lastExecutedProcess].burstTime; // Calculate the completion time
    timeSlots[lastExecutionIndex++] = lastProcessFinishTime;

    // Display the processes
    cout << "|" << endl;

    // Display the time slots
    for (int i = 0; i < lastExecutionIndex; ++i) {
        int whiteSpace = timeSlots[i];
        if (whiteSpace < 10) {
            cout << timeSlots[i];
            cout << "        "; // 8 white spaces
        } else if (whiteSpace >= 10) {
            cout << timeSlots[i];
            cout << "       "; // 7 white spaces
        }
    }
    cout << endl;
}

int main() {
    char choice;
    do {
        int n;
        cout << "Enter the number of processes: ";
        cin >> n;

        Process processes[MAX_SIZE];

        // Input the process details
        for (int i = 0; i < n; ++i) {
            processes[i].id = i + 1;
            cout << "Enter arrival time for process P" << processes[i].id << ": ";
            cin >> processes[i].arrivalTime;
            cout << "Enter burst time for process P" << processes[i].id << ": ";
            cin >> processes[i].burstTime;
            processes[i].remainingTime = processes[i].burstTime; // Initialize remaining time
            cout << "Enter priority for process P" << processes[i].id << ": ";
            cin >> processes[i].priority;
            processes[i].completed = false;
        }

        // Sort processes based on arrival time (for Gantt Chart)
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                if (processes[j].arrivalTime > processes[j + 1].arrivalTime) {
                    swap(processes[j], processes[j + 1]);
                }
            }
        }

        // Perform Priority Scheduling - Preemptive
        priorityScheduling(processes, n);

        // Display process details
        cout << "\nProcess Details:\n";
        cout << "+----+---------------+---------------+--------------+-----------------+-------------------+----------------+" << endl;
        cout << "| ID | Arrival Time  |   Burst Time  |   Priority   |   Finish Time   |  Turnaround Time  |  Waiting Time  |\n";
        for (int i = 0; i < n; ++i) {
            cout << "+----+---------------+---------------+--------------+-----------------+-------------------+----------------+" << endl;

            cout << "|  " << processes[i].id << " |       " << processes[i].arrivalTime << "       |       " << processes[i].burstTime 
                 << "\t     |      " << processes[i].priority << "\t    |        " << processes[i].finishTime << "\t      |  \t" 
                 << processes[i].turnaroundTime << "\t  |\t   " << (processes[i].waitingTime < 0 ? 0 : processes[i].waitingTime) << "\t   |" << endl;
        }
        cout << "+----+---------------+---------------+--------------+-----------------+-------------------+----------------+" << endl;

        cout << "Continue (Y/N): ";
        cin >> choice;
    } while (choice == 'Y' || choice == 'y');
    cout << "Terminating..." << endl;
    cout << "Successfuly Terminated" << endl;

    return 0;
}
