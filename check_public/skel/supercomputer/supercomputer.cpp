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
    // numarul maxim de noduri
    static constexpr int NMAX = (int)1e5 + 5; // 10^5 + 5 = 100.005

    // n = numar de noduri, m = numar de muchii/arce
    int N, M;

    vector<int> data_set;
    vector<int> ready1;
    vector<int> ready2;

    // adj[node] = lista de adiacenta a nodului node
    // exemplu: daca adj[node] = {..., neigh, ...} => exista arcul (node, neigh)
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
            ready1[y]++;
            ready2[y]++;
        }

        fin.close();
    }

    int current_data;
    int result_1 = 0;
    int result_2 = 0;

    // vectorul rezultat (in final contine o permutare pentru 1, 2, ..., n)
    vector<int> topsort_start_1;
    vector<int> topsort_start_2;

    queue<int> q1;
    queue<int> q2;

    void solve_dfs()
    {
        // used[node] = 1 daca node a fost deja vizitat, 0 altfel
        // vector<int> used(N + 1, 0);

        create_topsort(q1, q2, topsort_start_1, result_1, ready1);
        create_topsort(q2, q1, topsort_start_2, result_2, ready2);

        // current_data = 1;

        // // pentru fiecare nod
        // for (int node = 1; node <= N; ++node)
        // {
        //     // daca nodul este nevizitat, pornim o parcurgere
        //     if (!used[node] && !ready1[node])
        //     {
        //         dfs(node, used, topsort_start_1, result_1);
        //     }
        // }

        // current_data = 2;

        // // pentru fiecare nod
        // for (int node = 1; node <= N; ++node)
        // {
        //     // daca nodul este nevizitat, pornim o parcurgere
        //     if (!used[node] && !ready1[node])
        //     {
        //         dfs(node, used, topsort_start_2, result_2);
        //     }
        // }
    }

    void create_topsort(queue<int> &first_q, queue<int> &second_q, vector<int> &topsort_start, int &result, vector<int> &ready)
    {
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
            while (!first_q.empty())
            {
                int node = first_q.front();
                first_q.pop();

                topsort_start.push_back(node);

                for (auto &neigh : adj[node])
                {
                    ready[neigh]--;
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

            while (!second_q.empty())
            {
                int node = second_q.front();
                second_q.pop();

                topsort_start.push_back(node);

                for (auto &neigh : adj[node])
                {
                    ready[neigh]--;
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

    // porneste o parcurgere DFS din node
    // foloseste vectorul used pentru a marca nodurile vizitate
    // void dfs(int node, vector<int> &used, vector<int> &topsort_start, int &result)
    // {
    //     used[node] = 1; // marcheze nodul ca fiind vizitat
    //     topsort_start.push_back(node);
    //     int ok1 = 0, ok2 = 0;

    //     // parcurg vecinii
    //     for (auto &neigh : adj[node])
    //     {
    //         if (data_set[neigh] == current_data)
    //         {
    //             if (ready1[neigh] > 0)
    //                 ready1[neigh]--;

    //             if (!used[neigh] && !ready1[neigh])
    //             {
    //                 ok1 = 1;
    //                 dfs(neigh, used, topsort_start, result);
    //             }
    //         }
    //     }

    //     current_data = 3 - current_data;

    //     // parcurg vecinii
    //     for (auto &neigh : adj[node])
    //     {
    //         if (data_set[neigh] == current_data)
    //         {
    //             if (ready1[neigh] > 0)
    //                 ready1[neigh]--;

    //             if (!used[neigh] && !ready1[neigh])
    //             {
    //                 ok2 = 1;
    //                 dfs(neigh, used, topsort_start, result);
    //             }
    //         }
    //     }

    //     current_data = 3 - current_data;

    //     // if (ok1 == 1)
    //     //     result++;
    //     if (ok2 == 1)
    //         result++;
    // }

    void print_output()
    {
        ofstream fout("supercomputer.out");

        if (topsort_start_1.size() < N)
        {
            fout << result_2 << '\n';
            // fout.close();
            // return;
        }

        if (topsort_start_2.size() < N)
        {
            fout << result_1 << '\n';
            // fout.close();
            // return;
        }

        fout << min(result_1, result_2) << '\n';

        fout << "---------------\n";
        fout << "res 1: " << result_1 << '\n';
        fout << "res 2: " << result_2 << '\n';

        for (auto node : topsort_start_1)
        {
            fout << node << ' ';
        }
        fout << '\n';

        for (auto node : topsort_start_2)
        {
            fout << node << ' ';
        }
        fout << '\n';

        if (topsort_start_1.size() < N)
            fout << "Imposibil 1\n";

        if (topsort_start_2.size() < N)
            fout << "Imposibil 2\n";

        fout.close();
    }
};

int main()
{
    auto *task = new (nothrow) Task();
    if (!task)
    {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}