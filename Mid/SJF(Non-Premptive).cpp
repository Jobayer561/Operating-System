#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    string pid[n];
    int at[n], bt[n], ct[n], wt[n], tat[n];
    bool done[n] = {false};

    // Input
    for (int i = 0; i < n; i++) {
        cin >> pid[i] >> at[i] >> bt[i];
    }

    int completed = 0, time = 0;

    string gantt[100];
    int gtime[100];
    int gindex = 0;

    while (completed < n) {
        int idx = -1;
        int min_bt = 1e9;

        // Find shortest job among arrived
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && !done[i] && bt[i] < min_bt) {
                min_bt = bt[i];
                idx = i;
            }
        }

        // If no process available → CPU idle
        if (idx == -1) {
            time++;
            continue;
        }

        // Store for Gantt
        gantt[gindex] = pid[idx];
        gtime[gindex] = time;
        gindex++;

        // Execute fully (non-preemptive)
        time += bt[idx];
        ct[idx] = time;

        done[idx] = true;
        completed++;
    }

    gtime[gindex] = time;

    // TAT & WT
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    // -------- GANTT CHART --------
    cout << "\nGantt Chart:\n| ";
    for (int i = 0; i < gindex; i++) {
        cout << gantt[i] << " | ";
    }

    cout << "\n" << gtime[0];
    for (int i = 1; i <= gindex; i++) {
        cout << "\t" << gtime[i];
    }

    // -------- TABLE --------
    cout << "\n\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << pid[i] << "\t" << at[i] << "\t" << bt[i] << "\t"
             << ct[i] << "\t" << tat[i] << "\t" << wt[i] << endl;
    }

    // -------- AVERAGES --------
    float avgWT = 0, avgTAT = 0;
    for (int i = 0; i < n; i++) {
        avgWT += wt[i];
        avgTAT += tat[i];
    }

    cout << "\nAverage Waiting Time: " << avgWT / n;
    cout << "\nAverage Turnaround Time: " << avgTAT / n;

    return 0;
}


/*
5
P1 0 7
P2 2 4
P3 4 1
P4 5 4
P5 6 2
*/