/******************************************************************************
Trabajo 1         : Estructuras de datos
Estudiante        : Víctor Gutiérrez
Profesor          : Yuri Cáceres Hernández
IDE               : VisualStudio Code
Compilador        : g++ (Debian 10.2.1-6) 10.2.1 20210110
Sistema operativo : Debian GNU/Linux 11 (bullseye) (WSL2)
Fecha             : 23/11/2023

Descripción de la solución:

Se crea un archivo binario a partir de un CSV con un formato particular, luego
se extrae la información del binario para llenar una lista enlazada con información
de palabras, la que posee dos sublistas enlazadas por nodo para guardar la
información de sus sinónimos y antónimos (de acuerdo a una dinámica ficticia en que
manejamos datos de una encuesta de lenguaje).

*******************************************************************************/
#include <iostream>
// Importamos librerías propias
#include "Binario.h"
#include "ListaPrincipal.h"
#include "ListaSecundaria.h"

using namespace std;

int main()
{
    // Struct que organiza los datos de un binario
    info_binario info;
    // Lista principal con información de palabras (contiene listas secundarias)
    ListaPrincipal lista_principal;
    // Objeto "Binario" que permite manejar un archivo binario
    Binario bin;

    // Función para construir un archivo binario a partir de un CSV "palabras.csv"
    // que posee cierto formato (ver archivo adjunto)
    // bin.construir();

    // Extraemos los datos del binario "palabras.dat" hacia el struct
    info = bin.extraerDatos();
    // Llenamos la lista con los datos del binario
    lista_principal.llenarConBinario(info);
    // Mostramos la lista de palabras (con sus sinónimos y antónimos)
    lista_principal.mostrar();
    return 0;
}
