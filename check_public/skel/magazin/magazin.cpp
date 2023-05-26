#include <bits/stdc++.h>
using namespace std;

static constexpr int NMAX = (int)1e5 + 5; // 10^5 + 5 = 100.005
vector<int> dfs(((int)1e5 + 5), -1);
vector<int> dfs_indexes(((int)1e5 + 5), -1); // array of indexes in dfs array, initially set to -1
vector<int> start(((int)1e5 + 5));			 // start time array
vector<int> finish(((int)1e5 + 5));			 // finish time array
vector<int> visited(((int)1e5 + 5), -1);	 // visited array, initially set to -1

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

		dfs[1] = 1;
		dfs_indexes[1] = 1;

		DFS_RECURSIVE(1);

		ofstream fout("magazin.out");

		for (int i = 0; i < Q; ++i)
		{
			int D; // D = nodul de start
			int E; // E = numarul de expedieri consecutive
			fin >> D >> E;

			int D_children = (finish[D] - start[D] - 1) / 2; // number of children of D
			if (D_children < E)
			{
				fout << -1 << '\n';
				continue;
			}

			int pos = dfs_indexes[D] + E;

			fout << dfs[pos] << '\n'; // print the answer
		}

		fout.close();
		fin.close();
	}

private:
	int index = 2;
	int timestamp = 0;

	void DFS_RECURSIVE(int node)
	{
		start[node] = ++timestamp;	// set the start time of the node
		for (int neigh : adj[node]) // for each child of the node
		{
			if (visited[neigh] == -1) // if the child is not visited
			{
				dfs_indexes[neigh] = index;
				dfs[index++] = neigh;
				visited[neigh] = 1;
				DFS_RECURSIVE(neigh);
			}
		}
		finish[node] = ++timestamp; // set the finish time of the node
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