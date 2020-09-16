#include <iostream>
#include <stdlib.h>

using namespace std;

void ImprimirMatriz(const char[][] m){

    for (int i = 0; i < NumeroAnillo; i++)
    {
        for (int j = 0; j < tam2; j++)
        {
            cout << arr1[i][j];
        }
        cout << endl;
    }
    cout << "------------------------------"; 
}

void ImprimirSalida(int Num, int Torre_a, int Torre_b, int Torre_c){
    Prueba(int Num, int Torre_a, int Torre_b);
    cout << "A: "; 
    ImprimirMatriz(arr1); 
    cout << "B: "; 
    ImprimirMatriz(arr2); 
    cout << "C: "; 
    ImprimirMatriz(arr3); 
}

void Prueba(int Num, int Torre_a, int Torre_b){
    char[][] temp; 
    switch (Torre_a)
    {
    case 1:
        if (Torre_b == 2){
            temp = arr1; 
            for (int i = 0; i < tam2; i++)
            {
                temp[Num][i] = arr2[Num][i]; 
                arr1[Num][i] = ' '; 
            }
            
        } else {
            temp = arr1; 
            for (int i = 0; i < tam2; i++)
            {
                temp[Num][i] = arr3[Num][i]; 
                arr1[Num][i] = ' '; 
            }
            
        }
        break;
    case 2:
        if (Torre_b == 1){
            temp = arr2; 
            for (int i = 0; i < tam2; i++)
            {
                temp[Num][i] = arr1[Num][i]; 
                arr2[Num][i] = ' '; 
            }
            
        } else {
            temp = arr2; 
            for (int i = 0; i < tam2; i++)
            {
                temp[Num][i] = arr3[Num][i]; 
                arr2[Num][i] = ' '; 
            }
            
        }   
        break;
    case 3:
        if (Torre_b == 1){
            temp = arr3; 
            for (int i = 0; i < tam2; i++)
            {
                temp[Num][i] = arr1[Num][i]; 
                arr3[Num][i] = ' '; 
            }
            
        } else {
            temp = arr3; 
            for (int i = 0; i < tam2; i++)
            {
                temp[Num][i] = arr2[Num][i]; 
                arr3[Num][i] = ' '; 
            }
            
        }
        break;
    }
}

void TorresHanoi(int Num, int Torre_a, int Torre_b, int Torre_c)
{

    if (Num > 0)
    {
        TorresHanoi(Num - 1, Torre_a, Torre_c, Torre_b);
        ImprimirMatriz(Num, Torre_a, Torre_c, Torre_b);
        TorresHanoi(Num - 1, Torre_c, Torre_b, Torre_a);
    }
}

int NumeroAnillo = 0, tam2 = 0;
char arr1[][], arr2[][], arr3[][]; 

int main()
{
    int carac = 254;
    cout << "Numeros de discos: ";
    cin >> NumeroAnillo;
    tam2 = NumeroAnillo*2;

    char arr1[NumeroAnillo][tam2],
    arr2[NumeroAnillo][tam2],
    arr3[NumeroAnillo][tam2];
    for (int i = 0; i < NumeroAnillo; i++)
    {
        for (int j = 0; j < tam2; j++)
        {
            if ((i + j) >= NumeroAnillo && (j - i) <= NumeroAnillo)
            {
                arr1[i][j] = (char) carac;
            }
            else
            {
                arr1[i][j] = ' ';
            }
        }
    }

    for (int i = 0; i < NumeroAnillo; i++)
    {
        for (int j = 0; j < tam2; j++)
        {
            arr2[i][j] = ' ';
            arr3[i][j] = ' ';
        }
    }

    cout << "Aguja -> Aguja \n";

    TorresHanoi(NumeroAnillo, 1, 3, 2);

    return 0;
}