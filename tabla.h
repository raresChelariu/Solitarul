#include "casuta.h"

bool estePozitieInAfaraTablei(PozitieTabla p)
{
    if (p.Lin < 0 || p.Lin > 7 || p.Col < 0 || p.Lin > 7)
        return 0;
    int v[] = {0, 1, 5, 6};
    PozitieTabla pozInvalide[16];
    int k = 0;
    int i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
        {
            pozInvalide[k].Lin = v[i];
            pozInvalide[k].Col = v[j];
        }
    for (i = 0; i < 16; i++)
        if (p.Lin == pozInvalide[i].Lin && p.Col == pozInvalide[i].Col)
            return 0;
    return 1;
}
void citireTabla(const char* numeFisierTabla, Tabla &T)
{
    std::ifstream fin(numeFisierTabla);
    int i, j;
    for (i = 0; i < TABLA_MAX; i++)
        for (j = 0; j < TABLA_MAX; j++)
        {
            fin >> T.M[i][j].Stare;
            T.M[i][j].Pozitie.Lin = i;
            T.M[i][j].Pozitie.Col = j;
        }
    T.EstePiesaSelectata = false;
}
Tabla copiereTabla(Tabla T)
{
    Tabla copie;
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 7; j++)
    {
        copie.M[i][j].Pozitie = T.M[i][j].Pozitie;
        copie.M[i][j].Stare = T.M[i][j].Stare;
    }
    return copie;
}
void desenareTablaJoc(Tabla T)
{
    int i, j;
    for (i = 0; i < TABLA_MAX; i++)
        for (j = 0; j < TABLA_MAX; j++)
            desenareCasuta(i, j, T.M[i][j].Stare);
    if (T.EstePiesaSelectata)
        selectarePiesa(T.PozitieSelectie.Lin, T.PozitieSelectie.Col);
}
bool estePozitieInvalida(PozitieTabla p)
{
    return p.Lin == -1 && p.Col == -1;
}
PozitieTabla PozitieDinCoordonate(int xMouse, int yMouse)
{
    PozitieTabla p;
    if (xMouse == -1 && yMouse == -1)
    {
        std::cout<<"Nu a fost facut click!!!";
        p = {
            .Lin = -1,
            .Col = -1
        };
        return p;
    }
    p.Lin = (yMouse - MARGIN_Y) / DIM_CASUTA;
    p.Col = (xMouse - MARGIN_X) / DIM_CASUTA;
    return p;
}


