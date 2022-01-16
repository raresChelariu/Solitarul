#include "actiuni.h"

void ecranStart();
void ecranJoc();

void ecranStart()
{
    initwindow (DIM_ECRAN_WIDTH, DIM_ECRAN_HEIGHT, "Solitarul");
    readimagefile(POZA_ECRAN_START, 0, 0, DIM_ECRAN_WIDTH, DIM_ECRAN_HEIGHT);

    // ASTEPT SA FIE APASATA ORICE TASTA PT A TRECE MAI DEPARTE
    while (!kbhit())
    {

    }
    ecranJoc();
}
void ecranJoc()
{
    initwindow (DIM_ECRAN_WIDTH, DIM_ECRAN_HEIGHT, "Solitarul");

    ButoaneJoc Btns;
    adaugaButon(Btns, 20, 20, BUTON_TEXT_MUTA);
    adaugaButon(Btns, 20, 140, BUTON_TEXT_ANULARE);
    adaugaButon(Btns, 20, 280, BUTON_TEXT_FA_MUTAREA);
    Btns.Butoane[0].Visibil = 1;
    Btns.Butoane[1].Visibil = 0;
    Btns.Butoane[2].Visibil = 0;

    desenareButoane(Btns);

    Tabla T;
    citireTabla("tablaInitiala.txt", T);

    desenareTablaJoc(T);

    SetMutari SM;

    while (1)
    {
        actiuneJucator(T, Btns, SM);
        if (esteJocCastigat(T))
        {
            afisareTabla(T);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
            outtextxy(WINNER_TEXT_X, WINNER_TEXT_Y, WINNER_TEXT);

            getch(); // apas orice tasta pt inchiderea jocului
            exit(0); // inchid tot programul
        }
    }
    getch();
    closegraph();
}
