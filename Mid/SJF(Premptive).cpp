#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    string pid[n];
    int at[n], bt[n], rt[n];
    int ct[n], wt[n], tat[n];

    for (int i = 0; i < n; i++) {
        cin >> pid[i] >> at[i] >> bt[i];
        rt[i] = bt[i]; // remaining time
    }

    int complete = 0, time = 0, min_bt, shortest = -1;
    bool found;

    // For Gantt Chart
    string gantt[1000];
    int gindex = 0;

    while (complete < n) {
        min_bt = 1e9;
        found = false;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0 && rt[i] < min_bt) {
                min_bt = rt[i];
                shortest = i;
                found = true;
            }
        }

        if (!found) {
            time++;
            continue;
        }

        // Execute 1 unit
        rt[shortest]--;
        gantt[gindex++] = pid[shortest];
        time++;

        // If finished
        if (rt[shortest] == 0) {
            complete++;
            ct[shortest] = time;
        }
    }

    // TAT & WT
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    // -------- GANTT CHART (compressed) --------
    cout << "\nGantt Chart:\n| ";
    cout << gantt[0] << " | ";

    for (int i = 1; i < gindex; i++) {
        if (gantt[i] != gantt[i - 1]) {
            cout << gantt[i] << " | ";
        }
    }

    // Time line
    cout << "\n0";
    int currentTime = 0;

    for (int i = 1; i < gindex; i++) {
        if (gantt[i] != gantt[i - 1]) {
            cout << "\t" << i;
        }
    }
    cout << "\t" << gindex;

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
p1 3 1
p2 1 4
p3 4 2
p4 0 6
p5 2 3

*/