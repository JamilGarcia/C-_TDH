#include <curses.h>
#include "Disco.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;
WINDOW *ventana;
int movimiento = -1;

bool intento(int MaxX, int MaxY, WINDOW *ventanaPalo1, WINDOW *ventanaPalo2, WINDOW *ventanaPalo3, vector<Disco *> listaA, vector<Disco *> listaB, vector<Disco *> listaC, int Num, WINDOW *ventanaPaloBajo)
{
    wrefresh(ventanaPaloBajo);
    movimiento++;
    int tecla = getch();
    if (tecla == 27)
    {
        return false;
    }
    if (movimiento > 9)
    {
        mvwprintw(ventana, 4, MaxX / 2.5 + 15, "0");
        mvwprintw(ventana, 4, MaxX / 2.5 + 15, "%d", movimiento);
    }
    else if (movimiento > 99)
    {
        mvwprintw(ventana, 4, MaxX / 2.5 + 14, "%d", movimiento);
    }
    else
    {
        mvwprintw(ventana, 4, MaxX / 2.5 + 14, "00");
        mvwprintw(ventana, 4, MaxX / 2.5 + 16, "%d", movimiento);
    }

    wattron(ventana, A_REVERSE);

    for (int i = 0; i < listaA.size(); i++)
    {
        if (listaA[i] != nullptr)
        {
            int x1 = listaA.at(i)->getPosX(),
                y = listaA.at(i)->getPosY(),
                x2 = listaA.at(i)->getPosY() * 2;
            for (int j = 1; j <= listaA.at(i)->getNDisco() + 1; j++)
            {
                mvwprintw(ventana, x1 - j + 1, x2 - j + 1, "   ");
            }
        }
    }
    for (int i = 0; i < listaB.size(); i++)
    {
        if (listaB[i] != nullptr)
        {
            int x1 = listaB.at(i)->getPosX(),
                y = listaB.at(i)->getPosY(),
                x2 = (MaxY / 1.1 + i) * 2;
            for (int j = 1; j <= listaB.at(i)->getNDisco() + 1; j++)
            {

                mvwprintw(ventana, x1 - j + 1, x2 - j + 1, "   ");
            }
        }
    }
    for (int i = 0; i < listaC.size(); i++)
    {
        if (listaC[i] != nullptr)
        {
            int x1 = listaC.at(i)->getPosX(),
                y = listaC.at(i)->getPosY(),
                x2 = (MaxY / 0.65 + i) * 2;
            for (int j = 1; j <= listaC.at(i)->getNDisco() + 1; j++)
            {
                mvwprintw(ventana, x1 - j + 1, x2 - j + 1, "   ");
            }
        }
    }
    wattroff(ventana, A_REVERSE);
    touchwin(ventanaPaloBajo);
    touchwin(ventana);
    wrefresh(ventana);
    wrefresh(ventanaPaloBajo);

    if (Num > 0)
    {
        for (int i = 0; i < listaA.size(); i++)
        {
            if (listaC[i] != nullptr)
            {

                Disco *temp = listaB[i];
                listaB[i] = listaC[i];
                listaC[i] = temp;
                wrefresh(ventanaPaloBajo);
                intento(MaxX, MaxY, ventanaPalo1, ventanaPalo2, ventanaPalo3, listaA, listaB, listaC, Num - 1, ventanaPaloBajo);
                break;
            }

            if (listaA[i] != nullptr)
            {
                Disco *temp = listaA[i],
                      *temp2 = listaC[i];

                listaA[i] = temp2;

                listaC[i] = temp;
                wrefresh(ventanaPaloBajo);
                intento(MaxX, MaxY, ventanaPalo1, ventanaPalo2, ventanaPalo3, listaA, listaB, listaC, Num - 1, ventanaPaloBajo);
                break;
            }
        }
    }

    touchwin(ventanaPalo1);
    wrefresh(ventanaPalo1);
    touchwin(ventanaPalo2);
    wrefresh(ventanaPalo2);

    touchwin(ventanaPalo3);
    wrefresh(ventanaPalo3);
    wrefresh(ventanaPaloBajo);
    touchwin(ventana);
    touchwin(ventanaPaloBajo);
    wrefresh(ventana);
    refresh();
    return false;
}

int getNum(int n)
{
    if (n == 1)
        return 1;
    else
        return 2 * getNum(n - 1) + 1;
}

int main()
{
    int MaxX, MaxY;
    initscr();
    getmaxyx(stdscr, MaxY, MaxX);
    if (!has_colors())
    {
        endwin();
        return 1;
    }
    cbreak();
    noecho();
    nonl();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_WHITE);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    ventana = newwin(MaxY, MaxX, 0, 0);
    WINDOW *ventanaPalo1 = newwin(MaxY / 2.5, 1, MaxY / 4.5, MaxX * 1 / 4);
    WINDOW *ventanaPalo2 = newwin(MaxY / 2.5, 1, MaxY / 4.5, MaxX * 2 / 4);
    WINDOW *ventanaPalo3 = newwin(MaxY / 2.5, 1, MaxY / 4.5, MaxX * 3 / 4);
    WINDOW *ventanaPaloBajo = newwin(1, MaxX * 6 / 8, (MaxY / 4.5 + MaxY / 2.5), MaxX * 1 / 8);
    wbkgd(ventana, COLOR_PAIR(1));
    wbkgd(ventanaPalo1, COLOR_PAIR(2));
    wbkgd(ventanaPalo2, COLOR_PAIR(2));
    wbkgd(ventanaPalo3, COLOR_PAIR(2));
    wbkgd(ventanaPaloBajo, COLOR_PAIR(3));
    box(ventana, ACS_VLINE, ACS_HLINE);
    box(ventanaPalo1, ACS_VLINE, ACS_HLINE);
    box(ventanaPalo2, ACS_VLINE, ACS_HLINE);
    box(ventanaPalo3, ACS_VLINE, ACS_HLINE);
    box(ventanaPaloBajo, ' ', ' ');

    const char CMovimiento[15] = " MOVIMIENTO # ";

    mvwprintw(ventana, 0, MaxX / 3, "  T  O  R  R  E  S   D  E   H  A  N  O  I  ");
    mvwprintw(ventana, MaxY - 1, MaxX / 2.75, "  P R O G R A M A C I O N    I I I  ");
    mvwprintw(ventana, MaxY - 4, MaxX / 2.8, "Desarrolador por Jamil Garcia (11911053)");
    mvwprintw(ventana, 4, MaxX / 2.5, CMovimiento);
    wrefresh(ventana);
    wattron(ventana, A_REVERSE);
    mvwprintw(ventana, MaxY - 5, MaxX / 4.3, " Presione cualquier tecla para continuar o presione ESC para finalizar ");
    mvwprintw(ventana, 3, MaxX / 3.5, " MUESTRA  DE  MOVIMIENTOS  NECESARIOS  PASO  A  PASO ");
    wattroff(ventana, A_REVERSE);
    wrefresh(ventana);
    mvwprintw(ventana, 4, MaxX / 2.5, CMovimiento + movimiento);
    mvwprintw(ventanaPaloBajo, 0, MaxX * 1 / 8, "1");
    mvwprintw(ventanaPaloBajo, 0, MaxX * 3 / 8, "2");
    mvwprintw(ventanaPaloBajo, 0, MaxX * 5 / 8, "3");

    //get Numero de discos
    printw("Ingrese la cantidad de discos: ");
    int nDiscos = getch();
    nDiscos = nDiscos - 48;
    cout << nDiscos << endl;

    while (nDiscos > 7 || nDiscos <= 0)
    {
        printw("\n Error Saliendo del programa... Valor no soportado \n");
        exit(1);
        getch();
    }

    vector<Disco *> listaA;
    vector<Disco *> listaB;
    vector<Disco *> listaC;
    int contNDisc = 0;

    for (int i = 0; i < nDiscos; i++)
    {
        listaB.push_back(nullptr);
        listaC.push_back(nullptr);
        listaA.push_back(new Disco(contNDisc, MaxX / 7, MaxY / 2.5 + i));
        //listaA.push_back(new Disco(contNDisc, MaxX / 7, MaxY/1.1 + i));
        //listaA.push_back(new Disco(contNDisc, MaxX / 7, MaxY/0.65 + i));
        contNDisc++;
    }

    wattron(ventana, A_REVERSE);

    for (int i = 0; i < listaA.size(); i++)
    {
        listaB.push_back(nullptr);
        listaC.push_back(nullptr);
        int x1 = listaA.at(i)->getPosX(),
            y = listaA.at(i)->getPosY(),
            x2 = listaA.at(i)->getPosY() * 2;
        for (int j = 1; j <= listaA.at(i)->getNDisco() + 1; j++)
        {
            mvwprintw(ventana, x1 - j + 1, x2 - j + 1, "   ");
        }
    }
    wattroff(ventana, A_REVERSE);

    touchwin(ventanaPaloBajo);
    touchwin(ventanaPalo1);
    touchwin(ventanaPalo2);
    touchwin(ventanaPalo3);
    touchwin(ventana);
    wrefresh(ventana);
    wrefresh(ventanaPaloBajo);
    wrefresh(ventanaPalo1);
    wrefresh(ventanaPalo2);
    wrefresh(ventanaPalo3);
    refresh();
    bool running = true;
    while (running)
    {
        int num = getNum(nDiscos);
        running = intento(MaxX, MaxY, ventanaPalo1, ventanaPalo2, ventanaPalo3, listaA, listaB, listaC, num, ventanaPaloBajo);
        touchwin(ventana);
        wrefresh(ventana);
        refresh();
    }
    getchar();
    endwin();
    return 0;
}
