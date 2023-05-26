#include <bits/stdc++.h>
using namespace std;

// numarul maxim de noduri
static constexpr int NMAX = (int)1e5 + 5; // 10^5 + 5 = 100.005

class Task
{
public:
	int N;				   // N = number of nodes
	int Q;				   // Q = number of questions
	vector<int> adj[NMAX]; // adj = adjacency list

	void solve()
	{
		ifstream fin("magazin.in");
		fin >> N >> Q;

		for (int i = 2; i <= N; ++i)
		{
			int x; // x = parent of i
			fin >> x;
			adj[x].push_back(i); // complete the adjacency list
		}

		vector<int> dfs(N + 1, -1);			// dfs array, initially set to -1
		vector<int> dfs_indexes(N + 1, -1); // array of indexes in dfs array, initially set to -1
		vector<int> start(N + 1);			// start time array
		vector<int> finish(N + 1);			// finish time array
		vector<int> visited(N + 1, -1);		// visited array, initially set to -1

		int timestamp = 0;
		dfs[1] = 1;
		dfs_indexes[1] = 1;

		DFS_RECURSIVE(1, visited, dfs, dfs_indexes, start, finish, timestamp);

		ofstream fout("magazin.out");

		for (int i = 0; i < Q; ++i)
		{
			int D; // D = nodul de start
			int E; // E = numarul de expedieri consecutive
			fin >> D >> E;

			int D_children = (finish[D] - start[D] - 1) / 2;
			if (D_children < E)
			{
				fout << -1 << '\n';
				continue;
			}

			int pos = dfs_indexes[D] + E;

			fout << dfs[pos] << '\n';
		}

		fout.close();
		fin.close();
	}

private:
	int index = 2;

	void DFS_RECURSIVE(int node, std::vector<int> &visited,
					   std::vector<int> &dfs, std::vector<int> &dfs_indexes, std::vector<int> &start, std::vector<int> &finish, int &timestamp)
	{
		start[node] = ++timestamp;
		for (int neigh : adj[node])
		{
			if (visited[neigh] == -1)
			{
				dfs_indexes[neigh] = index;
				dfs[index++] = neigh;
				visited[neigh] = 1;
				DFS_RECURSIVE(neigh, visited, dfs, dfs_indexes, start, finish, timestamp);
			}
		}
		finish[node] = ++timestamp;
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