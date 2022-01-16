#include "predefinite.h"
#include "constante.h"
#include "structuriJoc.h"

void getCoordCasuta(int lin, int col,
                    int &X_stanga_sus, int &Y_stanga_sus, int &X_dreapta_jos, int &Y_dreapta_jos)
{
    X_stanga_sus  = col*DIM_CASUTA + MARGIN_X;
    Y_stanga_sus  = lin*DIM_CASUTA + MARGIN_Y;
    X_dreapta_jos = (col+1)*DIM_CASUTA + MARGIN_X;
    Y_dreapta_jos = (lin + 1)*DIM_CASUTA + MARGIN_Y;
}
void desenarePiesa(int lin, int col, int culoarePiesa = CULOARE_PIESA)
{
    int X_centru_cerc = col*DIM_CASUTA + DIM_CASUTA/2 + MARGIN_X;
    int Y_centru_cerc = lin*DIM_CASUTA + DIM_CASUTA/2 + MARGIN_Y;

    setfillstyle(SOLID_FILL, culoarePiesa);
    setcolor(culoarePiesa);

    fillellipse(X_centru_cerc, Y_centru_cerc, DIM_PIESA_CERC, DIM_PIESA_CERC);
    circle(X_centru_cerc, Y_centru_cerc, DIM_PIESA_CERC);
}
void selectarePiesa(int lin, int col)
{
    desenarePiesa(lin, col, CULOARE_SELECTARE_PIESA);
}
void selectareCasuta(int lin, int col, int casutaContinePiesa)
{
    int X_stanga_sus, Y_stanga_sus, X_dreapta_jos, Y_dreapta_jos;
    getCoordCasuta(lin, col, X_stanga_sus, Y_stanga_sus,
                   X_dreapta_jos, Y_dreapta_jos);
    setcolor(CULOARE_SELECTARE_PIESA);
    rectangle(X_stanga_sus, Y_stanga_sus,
              X_dreapta_jos, Y_dreapta_jos);
    if (casutaContinePiesa)
        desenarePiesa(lin, col);
}
void desenareCasuta(int lin, int col, int stare)
{
    int X_stanga_sus, Y_stanga_sus, X_dreapta_jos, Y_dreapta_jos;
    getCoordCasuta(lin, col, X_stanga_sus, Y_stanga_sus,
                   X_dreapta_jos, Y_dreapta_jos);

    switch (stare)
    {
    case NON_CASUTA:
        break;
    case CASUTA_GOALA:
        setcolor(CULOARE_TABLA_MARGINE);
        rectangle(X_stanga_sus, Y_stanga_sus,
                  X_dreapta_jos, Y_dreapta_jos);
        break;
    case CASUTA_CU_PIESA:
        setcolor(CULOARE_TABLA_MARGINE);
        rectangle(X_stanga_sus, Y_stanga_sus,
                  X_dreapta_jos, Y_dreapta_jos);
        desenarePiesa(lin, col);
        break;
    default:
        std::cout<<"La coord "<<lin<<","<<col<<"nu pot desena starea "<<stare<<std::endl;
    }
}
