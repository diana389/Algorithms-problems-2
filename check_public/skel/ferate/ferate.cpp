#include <bits/stdc++.h>
using namespace std;

class Task
{
public:
    // numarul maxim de noduri
    static constexpr int NMAX = (int)1e5 + 5; // 10^5 + 5 = 100.005
    int N, M, S;
    int nr_comp = 0;
    int index = 0;
    vector<int> adj[NMAX];
    vector<int> visited;
    // vector<int> dfs;
    // vector<int> dfs_nr_compes;

    vector<int> all_sccs;

    void solve()
    {
        ofstream fout("ferate.out");
        read_input();

        visited.resize(N + 1, 0);

        all_sccs.resize(N + 1, -1);

        get_result(fout);
        print_output(fout);

        fout.close();
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
    }

    void get_result(ofstream &fout)
    {
        // all_sccs[S] = nr_comp;
        index = -2;
        DFS_RECURSIVE(S);

        fout << "node: " << S << '\n';
        // print_output(fout);

        for (int i = 1; i <= N; ++i)
        {
            if (all_sccs[i] == -1)
            {
                // all_sccs[i] = nr_comp;
                index = nr_comp;

                DFS_RECURSIVE(i);

                fout << "node: " << i << '\n';
                // print_output(fout);

                if (index == nr_comp)
                    nr_comp++;
            }
        }
    }

    void DFS_RECURSIVE(int node)
    {
        visited[node] = 1;

        for (int neigh : adj[node]) // for each child of the node
        {
            if (visited[neigh] == 0 && all_sccs[neigh] == -1) // if the child is not visited
            {
                visited[neigh] = 1;
                DFS_RECURSIVE(neigh);
            }
            else if (visited[neigh] == 0 && all_sccs[neigh] >= 0)
            {
                // index = all_sccs[neigh];
                visited[neigh] = 1;
                DFS_RECURSIVE(neigh);
            }
        }

        all_sccs[node] = index;
        visited[node] = 0;
    }

    void print_output(ofstream &fout)
    {
        fout << nr_comp << '\n';
        for (int i = 1; i <= N; i++)
        {
            fout << i << ": ";
            fout << all_sccs[i] << ' ';
            fout << "\n\n";
        }
    }
};

int main()
{
    auto *task = new (nothrow) Task(); // hint: cppreference/nothrow
    if (!task)
    {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
