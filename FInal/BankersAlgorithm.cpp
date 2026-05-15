#include <iostream>
using namespace std;

int main()
{
    int n, m;

    // Input number of processes and resources
    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter number of resource types: ";
    cin >> m;

    int allocation[10][10];
    int maxm[10][10];
    int need[10][10];
    int available[10];

    // Input Allocation Matrix
    cout << "\nEnter Allocation Matrix:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> allocation[i][j];
        }
    }

    // Input Max Matrix
    cout << "\nEnter Max Matrix:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> maxm[i][j];
        }
    }

    // Input Available Resources
    cout << "\nEnter Available Resources:\n";
    for (int i = 0; i < m; i++)
    {
        cin >> available[i];
    }

    // Calculate Need Matrix
    cout << "\nNeed Matrix:\n";

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = maxm[i][j] - allocation[i][j];
            cout << need[i][j] << " ";
        }
        cout << endl;
    }

    bool finish[10] = {false};
    int safeSequence[10];
    int work[10];

    // Copy available to work
    for (int i = 0; i < m; i++)
    {
        work[i] = available[i];
    }

    int count = 0;

    while (count < n)
    {
        bool found = false;

        for (int p = 0; p < n; p++)
        {
            if (!finish[p])
            {
                bool possible = true;

                // Check Need <= Available
                for (int j = 0; j < m; j++)
                {
                    if (need[p][j] > work[j])
                    {
                        possible = false;
                        break;
                    }
                }

                if (possible)
                {
                    // Release resources after execution
                    for (int j = 0; j < m; j++)
                    {
                        work[j] += allocation[p][j];
                    }

                    safeSequence[count] = p;
                    count++;
                    finish[p] = true;
                    found = true;
                }
            }
        }

        // Unsafe state
        if (!found)
        {
            cout << "\nSystem is NOT in safe state.\n";
            return 0;
        }
    }

    // Safe State
    cout << "\nSystem is in SAFE state.\n";

    cout << "Safe Sequence: ";
    for (int i = 0; i < n; i++)
    {
        cout << "T" << safeSequence[i];

        if (i != n - 1)
            cout << " -> ";
    }

    cout << endl;

    return 0;
}