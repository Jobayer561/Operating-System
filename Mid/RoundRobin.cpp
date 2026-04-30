#include <iostream>
#include <queue>
using namespace std;

int main() {
    int n, tq;
    cin >> n;

    string pid[n];
    int at[n], bt[n], rt[n], ct[n];

    for (int i = 0; i < n; i++) {
        cin >> pid[i] >> at[i] >> bt[i];
        rt[i] = bt[i];
    }

    cin >> tq;

    queue<int> q;
    bool inQueue[n] = {false};

    int time = 0, completed = 0;

    // Gantt
    string gantt[1000];
    int gtime[1000];
    int gindex = 0;

    q.push(0);
    inQueue[0] = true;

    while (!q.empty()) {
        int i = q.front();
        q.pop();

        // store gantt
        gantt[gindex] = pid[i];
        gtime[gindex] = time;
        gindex++;

        if (rt[i] > tq) {
            time += tq;
            rt[i] -= tq;
        } else {
            time += rt[i];
            rt[i] = 0;
            ct[i] = time;
            completed++;
        }

        // add new arrivals
        for (int j = 0; j < n; j++) {
            if (at[j] <= time && !inQueue[j] && rt[j] > 0) {
                q.push(j);
                inQueue[j] = true;
            }
        }

        // re-add current
        if (rt[i] > 0) {
            q.push(i);
        }
    }

    gtime[gindex] = time;

    // TAT & WT
    int tat[n], wt[n];
    float avgWT = 0, avgTAT = 0;

    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        avgWT += wt[i];
        avgTAT += tat[i];
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
    cout << "\nAverage Waiting Time: " << avgWT / n;
    cout << "\nAverage Turnaround Time: " << avgTAT / n;

    return 0;
}

// 6
// p1 0 4
// p2 1 5
// p3 2 2
// p4 3 1
// p5 4 6
// p6 6 3
// 2