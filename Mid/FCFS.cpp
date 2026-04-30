#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    string pid[n];
    int at[n], bt[n], ct[n], tat[n], wt[n];

    // Input
    for (int i = 0; i < n; i++) {
        cin >> pid[i] >> at[i] >> bt[i];
    }

    // Sort by Arrival Time (FCFS rule)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1]) {
                swap(at[j], at[j + 1]);
                swap(bt[j], bt[j + 1]);
                swap(pid[j], pid[j + 1]);
            }
        }
    }

    int time = 0;

    // ---------- GANTT CHART ----------
    cout << "\nGantt Chart:\n| ";

    for (int i = 0; i < n; i++) {

        // CPU IDLE condition
        if (time < at[i]) {
            cout << "IDLE | ";
            time = at[i];
        }

        cout << pid[i] << " | ";
        time += bt[i];
        ct[i] = time;
    }

    // ---------- TIME LINE ----------
    cout << "\n0";
    time = 0;

    for (int i = 0; i < n; i++) {

        if (time < at[i]) {
            cout << "\t" << at[i];
            time = at[i];
        }

        time += bt[i];
        cout << "\t" << time;
    }

    // ---------- CALCULATIONS ----------
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    // ---------- TABLE ----------
    cout << "\n\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << pid[i] << "\t" << at[i] << "\t" << bt[i] << "\t"
             << ct[i] << "\t" << tat[i] << "\t" << wt[i] << endl;
    }

    // ---------- AVERAGES ----------
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
p1 3 4
p2 5 3
p3 0 2
p4 5 1
p5 4 3

*/