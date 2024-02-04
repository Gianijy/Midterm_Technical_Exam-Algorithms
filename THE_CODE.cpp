//This program uses BRUTH FORCE ALGORITHM for a CPU scheduler (Priority - Preemptive)

#include <iostream>
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
void priorityScheduling(Process processes[], int n, int currentTime, int completedProcesses = 0) {
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

        // Recursively call the function for the next time slot
        priorityScheduling(processes, n, currentTime + 1, completedProcesses);
    } else {
        // No process to execute, move to the next time slot
        currentTime++;

        // Check if all processes are completed
        if (completedProcesses == n) {
            return;
        }

        // Continue scheduling for the next time slot
        priorityScheduling(processes, n, currentTime, completedProcesses);
    }
}

int main() {
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
    cout << "\nGantt Chart:\n";
    priorityScheduling(processes, n, 0);

    // Display process details
    cout << "\nProcess Details:\n";
    cout << "+----+---------------+---------------+--------------+-----------------+-------------------+----------------+" << endl;
    cout << "| ID | Arrival Time  |   Burst Time  |   Priority   |   Finish Time   |  Turnaround Time  |  Waiting Time  |\n";
    for (int i = 0; i < n; ++i) {
        cout << "+----+---------------+---------------+--------------+-----------------+-------------------+----------------+" << endl;

        cout << "| " << processes[i].id << "  |       " << processes[i].arrivalTime << "       |       " << processes[i].burstTime 
        << "       |      " << processes[i].priority << "       |        " << processes[i].finishTime << "\t      |\t        " 
        << processes[i].turnaroundTime << "\t  |\t  " << (processes[i].waitingTime < 0 ? 0 : processes[i].waitingTime) << "\t   |" << endl;
    }
    cout << "+----+---------------+---------------+--------------+-----------------+-------------------+----------------+" << endl;
    return 0;
}

