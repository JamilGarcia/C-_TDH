#include <iostream>
#include <stdlib.h>

using namespace std;

void TorresHanoi(int Num, int Torre_a, int Torre_b, int Torre_c)
{

    if (Num > 0)
    {
        TorresHanoi(Num - 1, Torre_a, Torre_c, Torre_b);
        cout << Torre_a << " -> " << Torre_b << endl;
        TorresHanoi(Num - 1, Torre_c, Torre_b, Torre_a);
    }
}

int main()
{
    int NumeroAnillo, carac = 220;
    cout << "Numeros de discos: ";
    cin >> NumeroAnillo;

    cout << "Aguja -> Aguja \n";

    TorresHanoi(NumeroAnillo, 1, 3, 2);

    return 0;
}