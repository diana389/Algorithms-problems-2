#include <bits/stdc++.h>
using namespace std;

class Task {
 public:
    void solve() {
        read_input();
        print_output(tarjan_scc());
    }

 private:
    // maximum number of nodes
    static constexpr int NMAX = (int)1e5 + 5;  // 10^5 + 5 = 100.005

    // N = number of nodes, M = number of edges, S = source node
    int N, M, S;

    // adj[node] = adjacency list of node
    vector<int> adj[NMAX];

    // adj_int[node] = adj mirrored
    // stores the nodes that have an edge going to node
    vector<int> adj_int[NMAX];

    // parent[node] = parent of node in the DFS traversal
    vector<int> parent;

    // found[node] = the timestamp when node was found
    // (when started to visit its subtree)
    // The global timestamp is incremented everytime a node is found.
    vector<int> found;

    // the minimum accessible timestamp that node can see/access
    // low_link[node] =  min { found[x] | x is node OR x in ancestors(node)
    // OR x in descendants(node) };
    vector<int> low_link;

    // visiting stack: nodes are pushed into the stack in visiting order
    stack<int> nodes_stack;

    // in_stack[node] = true, if node is in stack false, otherwise
    vector<bool> in_stack;

    void read_input() {
        ifstream fin("ferate.in");
        fin >> N >> M >> S;
        for (int i = 1, x, y; i <= M; i++) {
            fin >> x >> y;
            adj[x].push_back(y);  // edge from x to y

            // there is an edge from x to y, adj[y] stores x
            adj_int[y].push_back(x);
        }
        fin.close();
    }

    vector<vector<int>> tarjan_scc() {
        // initialize results
        parent = vector<int>(N + 1, -1);
        found = vector<int>(N + 1, -1);
        low_link = vector<int>(N + 1, -1);
        in_stack = vector<bool>(N + 1, false);

        // visit all nodes
        vector<vector<int>> all_sccs;
        int timestamp = 0;  // global timestamp
        for (int node = 1; node <= N; ++node) {
            // node not visited
            if (parent[node] == -1) {
                // convention: the parent of the root is actually the root
                parent[node] = node;

                // start a new DFS traversal this subtree
                dfs(node, timestamp, all_sccs);
            }
        }

        return all_sccs;
    }

    void dfs(int node, int &timestamp, vector<vector<int>> &all_sccs) {
        // a new node is visited - increment the timestamp
        found[node] = ++timestamp;     // the timestamp when node was found
        low_link[node] = found[node];  // node only knows its timestamp
        nodes_stack.push(node);        // add node to the visiting stack
        in_stack[node] = true;

        // visit each neighbour
        for (auto neigh : adj[node]) {
            // check if neigh is already visited
            if (parent[neigh] != -1) {
                // update low_link[node] with information gained through neigh
                // note: neigh is in the same SCC with node only if it's in the
                // visiting stack;
                // otherwise, neigh is from other SCC, so it should be ignored
                if (in_stack[neigh]) {
                    low_link[node] = min(low_link[node], found[neigh]);
                }
                continue;
            }

            // save parent
            parent[neigh] = node;

            // recursively visit the child subree
            dfs(neigh, timestamp, all_sccs);

            // update low_link[node] with information gained through neigh
            low_link[node] = min(low_link[node], low_link[neigh]);
        }

        // node is root in a SCC if low_link[node] == found[node]
        // (there is no edge from a descendant to an ancestor)
        if (low_link[node] == found[node]) {
            // pop all elements above node from stack
            // => extract the SCC where node is root
            vector<int> scc;
            do {
                auto x = nodes_stack.top();
                nodes_stack.pop();
                in_stack[x] = false;

                scc.push_back(x);

                // stop when node was popped from the stack
            } while (scc.back() != node);

            // save SCC
            all_sccs.push_back(scc);
        }
    }

    void print_output(const vector<vector<int>> &all_sccs) {
        ofstream fout("ferate.out");

        int size = all_sccs.size();  // number of SCCs

        for (const auto &scc : all_sccs) {
            int found = 0;

            // remove the SCC if it contains the source node
            if (find(scc.begin(), scc.end(), S) != scc.end()) {
                size--;
                continue;
            }

            // find the SCCs containing a node x that has an edge coming from
            // a node y that is not in the SCC
            // -> remove the SCC from the total number of SCCs
            for (auto node : scc) {
                for (int neigh : adj_int[node])
                    if (find(scc.begin(), scc.end(), neigh) == scc.end()) {
                        found = 1;
                        break;
                    }

                if (found)
                    break;
            }

            if (found)
                size--;
        }

        // print the number of edges that need to be added
        fout << size;
        fout.close();
    }
};

int main() {
    auto *task = new (nothrow) Task();
    if (!task) {
        cerr << "Failed!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
