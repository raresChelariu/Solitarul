#include "structuriJoc.h"

bool validarePerecheMutare(Tabla &T, PozitieTabla a, PozitieTabla b)
{
    if (T.M[a.Lin][a.Col].Stare != CASUTA_CU_PIESA)
        return 0;
    if (T.M[b.Lin][a.Col].Stare != CASUTA_GOALA)
        return 0;
    int dLin[] = {-2, 0, 2, 0};
    int dCol[] = { 0, 2, 0,-2};
    int i, nrDir = 4;
    bool esteLaDistDe2 = false;
    for (i = 0; i < nrDir && esteLaDistDe2 == false; i++)
    {
        if (a.Lin + dLin[i] == b.Lin &&
                a.Col + dCol[i] == b.Col)
        {
            esteLaDistDe2 = 1;
        }
    }
    if (0 == esteLaDistDe2)
        return 0;
    // calculez coord pt casuta dintre
    PozitieTabla intreAB;
    intreAB.Lin = a.Lin + dLin[i]/2;
    intreAB.Col = a.Col + dCol[i]/2;
    //
    if (T.M[intreAB.Lin][intreAB.Col].Stare != CASUTA_CU_PIESA)
        return 0;
    return 1;
}
bool validareSetMutari(Tabla T, SetMutari S)
{
    int i;
    for (i = 1; i < S.NrMutari; i++)
    {
        if (0 == validarePerecheMutare(T, S.Mutari[i-1], S.Mutari[i]))
            return 0;
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
void mutarePiese(Tabla &T, PozitieTabla a, PozitieTabla b)
{
    PozitieTabla intreAB;
    intreAB.Lin = (a.Lin + b.Lin)/2;
    intreAB.Col = (a.Col + b.Col)/2;

    T.M[a.Lin][a.Col].Stare = CASUTA_GOALA;
    T.M[intreAB.Lin][intreAB.Col].Stare = CASUTA_GOALA;
    T.M[b.Lin][b.Col].Stare = CASUTA_CU_PIESA;
}


