#include <bits/stdc++.h>
using namespace std;

// numarul maxim de noduri
static constexpr int NMAX = (int)1e5 + 5; // 10^5 + 5 = 100.005

class Task
{
public:
	int N; // N = numar de noduri
	int Q; // Q = numar de intrebari
	vector<int> adj[NMAX];

	void solve()
	{
		ifstream fin("magazin.in");
		fin >> N >> Q;

		// std::vector<int> p(N + 1, -1); // Parent array

		for (int i = 2; i <= N; ++i)
		{
			int x;
			fin >> x;
			adj[x].push_back(i);
		}

		std::vector<int> dfs(N + 1, -1); // dfs array, initially set to -1
		std::vector<int> dfs_invers(N + 1, -1);
		std::vector<int> start(N + 1);	// Start time array
		std::vector<int> finish(N + 1); // Finish time array

		DFS(N, dfs, dfs_invers, start, finish);
		ofstream fout("magazin.out");
		// for (int i = 1; i < N; ++i)
		// {
		// 	fout << dfs[i] << " ";
		// }
		// fout << '\n';
		// fout.close();

		for (int i = 0; i < Q; ++i)
		{
			int D; // D = nodul de start
			int E; // E = numarul de expedieri consecutive
			fin >> D >> E;

			int pos_D = -1;

			int D_children = (finish[D] - start[D] - 1) / 2;
			if (D_children < E)
			{
				fout << -1 << '\n';
				continue;
			}

			pos_D = dfs_invers[D];

			// for (int i = 1; i <= N; ++i)
			// {
			// 	if (dfs[i] == D)
			// 	{
			// 		pos_D = i;
			// 		break;
			// 	}
			// }

			// if (pos_D == -1)
			// {
			// 	fout << "error" << '\n';
			// 	continue;
			// }

			int pos = pos_D + E;

			fout << dfs[pos] << '\n';
		}

		fout.close();
		fin.close();
	}

private:
	int index = 2;

	void DFS_RECURSIVE(int node, int N, std::vector<int> &visited,
					   std::vector<int> &dfs, std::vector<int> &dfs_invers, std::vector<int> &start, std::vector<int> &finish, int &timestamp)
	{
		start[node] = ++timestamp;
		for (int neigh : adj[node])
		{
			if (visited[neigh] == -1)
			{
				dfs_invers[neigh] = index;
				dfs[index++] = neigh;
				visited[neigh] = 1;
				DFS_RECURSIVE(neigh, N, visited, dfs, dfs_invers, start, finish, timestamp);
			}
		}
		finish[node] = ++timestamp;
	}

	void DFS(int N, std::vector<int> &dfs, std::vector<int> &dfs_invers,
			 std::vector<int> &start, std::vector<int> &finish)
	{
		std::vector<int> visited(N + 1, -1); // visited array, initially set to -1

		int timestamp = 0;
		dfs[1] = 1;
		dfs_invers[1] = 1;

		for (int node = 1; node <= N; ++node)
		{
			if (visited[node] == -1)
			{
				DFS_RECURSIVE(node, N, visited, dfs, dfs_invers, start, finish, timestamp);
			}
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