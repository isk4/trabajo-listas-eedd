/******************************************************************************
Trabajo 1         : Estructuras de datos
Estudiante        : Víctor Gutierrez
Profesor          : Yuri Cáceres Hernández
IDE               : VisualStudio Code
Compilador        : g++ (Debian 10.2.1-6) 10.2.1 20210110
Sistema operativo : Debian GNU/Linux 11 (bullseye) (WSL2)
Fecha             : XX/XX/2023

Descripción de la solución:

*******************************************************************************/
#include <iostream>
#include "Binario.h"
#include "ListaPrincipal.h"
#include "ListaSecundaria.h"

using namespace std;

int main()
{
    info_binario info;
    ListaPrincipal lista_principal;
    Binario bin;
    //bin.construir();
    info = bin.extraerDatos();
    lista_principal.llenarConBinario(info);
    lista_principal.mostrar();
    return 0;
}
