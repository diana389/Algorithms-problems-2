#include <bits/stdc++.h>
using namespace std;

class Task
{
public:
    // n = numar de noduri, m = numar de muchii/arce
    int N, M, S;

    // numarul maxim de noduri
    static constexpr int NMAX = (int)1e5 + 5; // 10^5 + 5 = 100.005

    // adj[node] = lista de adiacenta a nodului node
    // exemplu: daca adj[node] = {..., neigh, ...} => exista arcul (node, neigh)
    vector<int> adj[NMAX];
    vector<int> nodes;
    int current_node = 1;

    void solve()
    {
        read_input();
        // print_output(adj);

        while (current_node <= N)
        {
            solve_task(current_node);
            current_node++;
        }

        print_output();
    }

private:
    void read_input()
    {
        ifstream fin("ferate.in");
        fin >> N >> M >> S;
        for (int i = 1, x, y; i <= M; i++)
        {
            fin >> x >> y;
            adj[x].push_back(y); // arc (x, y)
        }
        fin.close();

        for (int i = 1; i <= N; i++)
            nodes.push_back(i);
    }

    void solve_task(int node)
    {
        vector<int> neighbors = adj[node]; // Make a copy of the adjacency list

        for (int neigh : neighbors)
        {
            // Find the element in the adjacency list
            vector<int>::iterator new_end;
            new_end = remove(adj[node].begin(), adj[node].end(), neigh);
            adj[node].erase(new_end, adj[node].end());

            solve_task(neigh);

            if (neigh != current_node)
            {
                new_end = remove(nodes.begin(), nodes.end(), neigh);
                nodes.erase(new_end, nodes.end());
            }
        }
    }

    void print_output()
    {
        ofstream fout("ferate.out");
        for (int i = 1; i <= N; i++)
        {
            fout << i << ": ";
            for (int neigh : adj[i])
            {
                fout << neigh << " ";
            }
            fout << "\n";
        }

        for (int node : nodes)
            fout << node << " ";

        fout.close();
    }
};

int main()
{
    auto *task = new (nothrow) Task();
    if (!task)
    {
        cerr << "Failed!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
