#include "tabla.h"
#include "buton.h"

void reDesenare(Tabla &T, ButoaneJoc &btns)
{
    clearviewport();
    desenareButoane(btns);
    desenareTablaJoc(T);
}
void afisareTabla(Tabla T)
{
    int i, j;
    for (i = 0; i < 7; i++, std::cout << '\n')
        for (j = 0; j < 7; j++)
        {
            std::cout<<T.M[i][j].Stare << ' ';
        }
}
bool esteJocCastigat(Tabla T)
{
    if (T.M[3][3].Stare != CASUTA_CU_PIESA)
        return 0;
    int i, j;
    for (i = 0; i < 7; i++)
        for (j = 0; j < 7; j++)
        {
            // am gasit piesa ce nu e in centru
            if (T.M[i][j].Stare == CASUTA_CU_PIESA
                    && !(i == 3 && j == 3))
                return 0;
        }
    return 1;
}
void mutarePiese(Tabla &T, PozitieTabla a, PozitieTabla b)
{
    PozitieTabla intreAB;
    intreAB.Lin = (a.Lin + b.Lin)/2;
    intreAB.Col = (a.Col + b.Col)/2;

    T.M[a.Lin][a.Col].Stare = CASUTA_GOALA;
    T.M[intreAB.Lin][intreAB.Col].Stare = CASUTA_GOALA;
    T.M[b.Lin][b.Col].Stare = CASUTA_CU_PIESA;
}
bool validarePerecheMutare(Tabla &T, PozitieTabla a, PozitieTabla b)
{
    std::cout << "VALIDARE\n";
    std::cout << a.Lin << ' ' << a.Col << ' ' << b.Lin << ' ' << b.Col << '\n';
    afisareTabla(T);
    if (T.M[a.Lin][a.Col].Stare != CASUTA_CU_PIESA)
        return 0;
    if (T.M[b.Lin][b.Col].Stare != CASUTA_GOALA)
        return 0;
    std::cout << "Stari valide\n";
    int dLin[] = {-2, 0, 2, 0};
    int dCol[] = { 0, 2, 0,-2};
    int i, nrDir = 4;
    bool esteLaDistDe2 = 0;
    for (i = 0; i < nrDir && esteLaDistDe2 == 0; i++)
    {
        std::cout << "DIR" << i << '\n';
        if (a.Lin + dLin[i] == b.Lin &&
                a.Col + dCol[i] == b.Col)
        {
            esteLaDistDe2 = 1;
        }
    }
    if (0 == esteLaDistDe2)
        return 0;
    std::cout << "este la 2\n";
    // calculez coord pt casuta dintre
    PozitieTabla intreAB;
    intreAB.Lin = (a.Lin + b.Lin)/2;
    intreAB.Col = (a.Col + b.Col)/2;
    std::cout << "Pozitia dintre : " << intreAB.Lin << " " << intreAB.Col << '\n';
    std::cout << "Stare dintre : " << T.M[intreAB.Lin][intreAB.Col].Stare << '\n';
    //
    if (T.M[intreAB.Lin][intreAB.Col].Stare != CASUTA_CU_PIESA)
        return 0;
    return 1;
}
bool validareSetMutari(Tabla T, SetMutari S)
{
    int i;
    Tabla copieTabla = T;

    for (i = 1; i < S.NrMutari; i++)
    {
        if (0 == validarePerecheMutare(copieTabla, S.Mutari[i-1], S.Mutari[i]))
            return 0;
        mutarePiese(copieTabla, S.Mutari[i-1], S.Mutari[i]);
    }
    return 1;
}
void resetMutari(SetMutari &SM)
{
    int i;
    PozitieTabla PozGoala;
    PozGoala.Lin = 0;
    PozGoala.Col = 0;
    for (i = 0; i < SM.NrMutari; i++)
        SM.Mutari[i] = PozGoala;
    SM.NrMutari = 0;
}

void adaugaMutare(SetMutari &SM, PozitieTabla poz)
{
    SM.Mutari[SM.NrMutari++] = poz;
}
int indexMutareInSM(SetMutari SM, PozitieTabla poz)
{
    int i;
    for (i = 0; i < SM.NrMutari; i++)
        if (SM.Mutari[i].Lin == poz.Lin && SM.Mutari[i].Col == poz.Col)
            return i;
    return -1;
}
void actiuneButonMuta(Tabla &T, ButoaneJoc &btns, SetMutari &SM)
{
    resetMutari(SM);
    btns.Butoane[0].Visibil = 0;
    btns.Butoane[1].Visibil = 1;
    btns.Butoane[2].Visibil = 1;
    reDesenare(T, btns);
}
void actiuneButonFaMutare(Tabla &T, ButoaneJoc &btns, SetMutari &SM)
{
    int i;
    if (validareSetMutari(T, SM) == 0)
    {
        std::cout << "Mutare invalida\n";
        for (i = 0; i < SM.NrMutari; i++)
        {
            std::cout << SM.Mutari[i].Lin << ' ' << SM.Mutari[i].Col << '\n';
        }
        return;
    }

    for (i = 1; i < SM.NrMutari; i++)
        mutarePiese(T, SM.Mutari[i-1], SM.Mutari[i]);

    btns.Butoane[0].Visibil = 1;
    btns.Butoane[1].Visibil = 0;
    btns.Butoane[2].Visibil = 0;
    reDesenare(T, btns);
}
void actiuneButonAnulare(Tabla &T, ButoaneJoc &btns, SetMutari &SM)
{
    resetMutari(SM);
    btns.Butoane[0].Visibil = 1;
    btns.Butoane[1].Visibil = 0;
    btns.Butoane[2].Visibil = 0;
    reDesenare(T, btns);
}
// returneaza 1 daca este click pe unul dintre butoane
// 0, daca nu
bool actiuniButoane(Tabla &T, ButoaneJoc &btns, SetMutari &SM, int xMouse, int yMouse)
{
    int i;
    for (i = 0; i < btns.NrButoane; i++)
    {
        if (esteClickPeButon(btns.Butoane[i], xMouse, yMouse))
        {
            if (0 == strcmp(btns.Butoane[i].Text, BUTON_TEXT_MUTA))
            {
                actiuneButonMuta(T, btns, SM);
                return 1;
            }
            if (0 == strcmp(btns.Butoane[i].Text, BUTON_TEXT_FA_MUTAREA))
            {
                actiuneButonFaMutare(T, btns, SM);
                return 1;
            }
            if (0 == strcmp(btns.Butoane[i].Text, BUTON_TEXT_ANULARE))
            {
                actiuneButonAnulare(T, btns, SM);
                return 1;
            }
        }
    }
    return 0;
}
void actiuneJucator(Tabla &T, ButoaneJoc &btns, SetMutari &SM)
{
    bool isClicked = false;
    int xMouse, yMouse;
    while (!isClicked)
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            isClicked = true;
            getmouseclick(WM_LBUTTONDOWN, xMouse, yMouse);
            std::cout << "Click la :" << xMouse << " " << yMouse;

            if (actiuniButoane(T, btns, SM, xMouse, yMouse))
            {
                return;
            }
            PozitieTabla poz = PozitieDinCoordonate(xMouse, yMouse);
            if (estePozitieInvalida(poz))
            {
                return;
            }
            // buton Fa Mutare visibil
            if (btns.Butoane[2].Visibil)
            {
                // mutarea nu este in setul de mutari
                // (pt a evita sa punem din greseala aceiasi mutare de 2 ori)
                if (indexMutareInSM(SM, poz) == -1)
                {
                    // facem selectia casutei si adaugarea mutarii la setul de mutari
                    // doar daca mutarea se afla in casutele desenate
                    //if (estePozitieInAfaraTablei(poz) == 0)
                    //{
                        std::cout << poz.Lin << " " << poz.Col << '@';

                        bool continePiesa = T.M[poz.Lin][poz.Col].Stare == CASUTA_CU_PIESA;
                        selectareCasuta(poz.Lin, poz.Col, continePiesa);
                        adaugaMutare(SM, poz);
                    //}

                }
            }
        }
    }
}
