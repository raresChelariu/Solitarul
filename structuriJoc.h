struct PozitieTabla {
    int Lin, Col;
};
struct Casuta
{
    int Stare;
    PozitieTabla Pozitie;
};
struct Buton
{
    int X, Y, Width = 100, Height = 100;
    int CuloareFundal = RED;
    int CuloareText = BLUE;
    char Text[256];
    bool Visibil = 0;
};
struct ButoaneJoc
{
    Buton Butoane[10];
    int NrButoane = 0;
};
struct SetMutari
{
    int NrMutari = 0;
    PozitieTabla Mutari[100];
};
struct Tabla
{
    Casuta M[TABLA_MAX][TABLA_MAX];
    bool EstePiesaSelectata;
    PozitieTabla PozitieSelectie;
};
