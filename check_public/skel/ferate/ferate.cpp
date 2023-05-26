#include <iostream>
#include <cstdint>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream fin("ferate.in");
    ofstream fout("ferate.out");

    int N, M, S, x, y;

    fin >> N >> M >> S;

    for (int i = 0; i < M; i++)
    {
        fin >> x >> y;
    }

    fout << 0;

    return 0;
}
