#include <bits/stdc++.h>
using namespace std;

class Task
{
public:
    void solve()
    {
        read_input();
        solve_dfs();
        print_output();
    }

private:
    // maximum number of nodes
    static constexpr int NMAX = (int)1e5 + 5; // 10^5 + 5 = 100.005

    // N = number of nodes, M = number of edges
    int N, M;

    vector<int> data_set; // stores data set for each node
    vector<int> ready1;   // check if node is ready to be processed
    vector<int> ready2;   // check if node is ready to be processed (copy of ready1)

    int result_1 = 0; // result for topological sort starting with data set 1
    int result_2 = 0; // result for topological sort starting with data set 2

    queue<int> q1; // queue for data set 1
    queue<int> q2; // queue for data set 2

    // adjacency list
    vector<int> adj[NMAX];

    void read_input()
    {
        ifstream fin("supercomputer.in");
        fin >> N >> M;

        data_set.resize(N + 1);
        for (int i = 1; i <= N; i++)
            fin >> data_set[i];

        ready1.resize(N + 1, 0);
        ready2.resize(N + 1, 0);

        for (int i = 1, x, y; i <= M; i++)
        {
            fin >> x >> y; // arc (x, y)
            adj[x].push_back(y);
            ready1[y]++; // increase the number of arcs entering in y
            ready2[y]++; // increase the number of arcs entering in y
        }

        fin.close();
    }

    void solve_dfs()
    {
        // topological sort starting with data set 1
        create_topsort(q1, q2, result_1, ready1);

        // topological sort starting with data set 2
        create_topsort(q2, q1, result_2, ready2);
    }

    void create_topsort(queue<int> &first_q, queue<int> &second_q, int &result, vector<int> &ready)
    {
        // push in queue all nodes that are ready to be processed
        for (int i = 1; i <= N; ++i)
        {
            if (ready[i] == 0)
            {
                if (data_set[i] == 1)
                    q1.push(i);
                else
                    q2.push(i);
            }
        }

        while (!first_q.empty() || !second_q.empty())
        {
            // process all nodes that are ready to be processed
            // with the current data set

            while (!first_q.empty())
            {
                int node = first_q.front();
                first_q.pop();

                for (auto &neigh : adj[node])
                {
                    ready[neigh]--; // decrease the number of arcs entering in neigh

                    // push in queue all nodes that are ready to be processed
                    if (ready[neigh] == 0)
                    {
                        if (data_set[neigh] == 2)
                            q2.push(neigh);
                        else
                            q1.push(neigh);
                    }
                }
            }

            if (!second_q.empty())
                result++;

            // process all nodes that are ready to be processed
            // with the other data set

            while (!second_q.empty())
            {
                int node = second_q.front();
                second_q.pop();

                for (auto &neigh : adj[node])
                {
                    ready[neigh]--; // decrease the number of arcs entering in neigh

                    // push in queue all nodes that are ready to be processed
                    if (ready[neigh] == 0)
                    {
                        if (data_set[neigh] == 2)
                            q2.push(neigh);
                        else
                            q1.push(neigh);
                    }
                }
            }

            if (!first_q.empty())
                result++;
        }
    }

    void print_output()
    {
        ofstream fout("supercomputer.out");
        fout << min(result_1, result_2) << '\n'; // print the result
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