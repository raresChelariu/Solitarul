#include "predefinite.h"

void stergeButoane(ButoaneJoc& Btns)
{
    Btns.NrButoane = 0;
}
void adaugaButon(ButoaneJoc &listaButoane, int X, int Y, const char* Text, int CuloareFundal = RED, int CuloareText = BLUE)
{
    listaButoane.Butoane[listaButoane.NrButoane].X = X;
    listaButoane.Butoane[listaButoane.NrButoane].Y = Y;
    strcpy(listaButoane.Butoane[listaButoane.NrButoane].Text, Text);
    listaButoane.Butoane[listaButoane.NrButoane].CuloareFundal = CuloareFundal;
    listaButoane.Butoane[listaButoane.NrButoane].CuloareText = CuloareText;
    listaButoane.NrButoane++;
}
void desenareButon(Buton b)
{
    if (b.Visibil == 0)
        return;
    int textWidth = textwidth(b.Text);
    int textHeight = textheight(b.Text);

    // daca am setat latimea si lungimea mai mici ca textul
    // atunci le setez a.i. sa incapa textul + sa am padding de jur imprejur
    // padding initializat mai jos

    int textMinPadding = 10;
    if (b.Width < textWidth + textMinPadding * 2)
        b.Width = textWidth + textMinPadding * 2;
    if (b.Height < textHeight + textMinPadding * 2)
        b.Height = textHeight + textMinPadding * 2;

    // desenez dreptunghiul umplut pt buton
    setfillstyle(SOLID_FILL, b.CuloareFundal);
    bar(b.X, b.Y, b.X + b.Width, b.Y + b.Height);
    // desenez textul pt buton
    outtextxy(b.X + (b.Width - textWidth)/2,
              b.Y + (b.Height - textHeight)/2,
              b.Text);
}

void desenareButoane(ButoaneJoc btns)
{
    int i;
    for (i = 0; i < btns.NrButoane; i++)
        if (btns.Butoane[i].Visibil)
            desenareButon(btns.Butoane[i]);
}
bool esteClickPeButon(Buton b, int x, int y)
{
    if (b.Visibil == 0)
        return 0;
    return b.X <= x &&
           x <= b.X + b.Width &&
           b.Y <= y &&
           y <= b.Y + b.Height;
}
