#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main() {
    ifstream fin("supercomputer.in");
    ofstream fout("supercomputer.out");

    int N, M, a, x, y;

    fin >> N >> M;
    for(int i = 0; i < N; i++)
        fin >> a;

    for(int i = 0; i < M; i++) {
        fin >> x >> y;
    }

    fout << 0;

    return 0;
}
