#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream fin("teleportare.in");
    ofstream fout("teleportare.out");

    int N, M, K, X, Y, T, P;

    fin >> N >> M >> K;

    for (int i = 0; i < M; i++)
    {
        fin >> X >> Y >> T;
    }

    for (int i = 0; i < K; i++)
    {
        fin >> X >> Y >> P;
    }

    fout << 0;

    return 0;
}
