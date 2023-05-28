#include <bits/stdc++.h>
using namespace std;

// numarul maxim de noduri
#define NMAX 50005

// valoare mai mare decat orice distanta din graf
#define INF (1 << 30)

// structura folosita pentru a stoca distanta, cat si vectorul de parinti
// folosind algoritmul Dijkstra
struct DijkstraResult {
    vector<int> d;
    vector<int> p;

    DijkstraResult(const vector<int> &d, const vector<int> &p)
        : d(d), p(p) {}
};

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    // n = numar de noduri, m = numar de muchii
    int N, M, K;
    // adj[node] = lista de adiacenta a nodului node
    // perechea (neigh, w) semnifica arc de la node la neigh de cost w
    vector<tuple<int, int, int>> adj[NMAX];
    // vector<tuple<int, int, int>> adj_teleport[NMAX];
    // nodul sursa
    int source = 1;

    void read_input() {
        ifstream fin("teleportare.in");
        fin >> N >> M >> K;
        for (int i = 1, X, Y, T; i <= M; i++) {
            fin >> X >> Y >> T;
            adj[X].push_back({Y, T, 1});
        }
        for (int i = 1, X, Y, P; i <= K; i++) {
            fin >> X >> Y >> P;
            adj[X].push_back({Y, 1, P});
            adj[Y].push_back({X, 1, P});
        }
        fin.close();
    }

    DijkstraResult get_result() {
        return dijkstra(source, N, adj);
    }

    DijkstraResult dijkstra(int source, int nodes,
                            vector<tuple<int, int, int>> adj[NMAX]) {
        // Initializam vectorul de distante cu distante infinite.
        vector<int> d(nodes + 1, INF);
        vector<int> p(nodes + 1, 0);

        // In loc de un priority_queue<> folosim set<>, cu elemente tupluri de
        // tipul (distanta pana la nod, nod). Setul tine elementele ordonate,
        // deci mereu in pq.begin() vom avea tuplul care ii corespunde
        // nodului cu distanta minima.
        set<tuple<int, int>> pq;

        // Inseram nodul de plecare in coada si ii actualizam distanta.
        d[source] = 0;
        pq.insert({d[source], source});

        while (!pq.empty()) {
            // Scoatem top-ul.
            auto top = pq.begin();
            const auto [_, node] = *top;
            pq.erase(top);

            // Ii parcurgem toti vecinii.
            for (const auto &[neigh, T, P] : adj[node]) {
                // Se imbunatateste distanta?
                if (d[node] + T < d[neigh] && d[node] % P == 0) {
                    // Scoatem vechea pereche/distanta din set.
                    pq.erase({d[neigh], neigh});

                    // Actualizam distanta si parintele.
                    d[neigh] = d[node] + T;
                    p[neigh] = node;

                    // Inseram noua distanta.
                    pq.insert({d[neigh], neigh});
                }
            }
        }

        // Toate nodurile catre care distanta este inca INF nu pot fi atinse din
        // nodul source, deci le setam pe -1.
        for (int node = 1; node <= nodes; node++)
            if (d[node] == INF)
                d[node] = -1;

        return {d, p};
    }

    void print_output(const DijkstraResult &result) {
        ofstream fout("teleportare.out");
        const auto &[d, _] = result;

        fout << d[N] << "\n";

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
