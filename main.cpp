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

void iniciar_menu(ListaPrincipal* lista_principal);

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

    // Iniciando menu
    iniciar_menu(&lista_principal);

    cout << "Adiós.\n";

    // Ejemplo de eliminación de palabra
    // char palabra_a_eliminar[] = "vocablo";
    // lista_principal.eliminar(palabra_a_eliminar);
    
    return 0;
}

void iniciar_menu(ListaPrincipal* lista_principal)
{
    // Booleano que controla si el menú continuará mostrándose o no
    bool continuar = true;
    // String que recibe input del usuario
    string input_usuario;
    // Opción del menú elegida
    int opcion_menu;
    while (continuar)
    {
        cout << "\nMenú principal"
            << "\n------------------------------------------------\n"
            << "\n1. Mostrar todas las palabras disponibles y sus detalles\n"
            << "2. Mostrar palabras más y menos usadas\n"
            << "3. Mostrar palabras sin sinónimos o antónimos\n"
            << "4. Mostrar palabras con más sinónimos\n"
            << "5. Mostrar palabras con más antónimos\n"
            << "6. Mostrar palabras por tipo\n"
            << "7. Mostrar sinónimo que más se repite entre las palabras\n"
            << "8. Mostrar antónimo que más se repite entre las palabras\n"
            << "9. Buscar palabra\n"
            << "10. Mostrar todos los sinónimos y antónimos disponibles\n"
            << "0. Salir\n\nIngrese una opción: ";
        getline(cin, input_usuario);

        // Verificamos si el input es correcto
        try
        {
            opcion_menu = stoi(input_usuario);
            if (opcion_menu < 0 || opcion_menu > 10) throw;
        }
        // Atajamos cualquier error y asignamos valor aleatorio en caso de haberlo
        catch (...) { opcion_menu = -1; }

        cout << endl << endl;
        switch (opcion_menu)
        {
            case 1:
                // Mostramos la lista de palabras (con sus sinónimos y antónimos)
                lista_principal->mostrar();
                break;
            case 2:
                // Mostramos las palabras más y menos usadas
                lista_principal->mostrarMayorMenorFreq();
                break;
            case 3:
                // Mostramos las palabras sin sinónimos ni antónimos
                lista_principal->mostrarSinSecundarias();
                break;
            case 4:
                // Mostramos las palabras sin sinónimos ni antónimos
                lista_principal->mostrarMasSinonimos();
                break;
            case 5:
                // Mostramos las palabras sin sinónimos ni antónimos
                lista_principal->mostrarMasAntonimos();
                break;
            case 6:
                // Mostramos las palabras por tipo
                lista_principal->mostrarPorTipo();
                break;
            case 7:
                // Mostramos el sinónimo que más se repite entre las palabras
                lista_principal->mostrarSinonimosMasFrecuentes();
                break;
            case 8:
                // Mostramos el sinónimo que más se repite entre las palabras
                lista_principal->mostrarAntonimosMasFrecuentes();
                break;
            case 9:
                // Mostrar detalles de una palabra
                lista_principal->mostrarPalabra();
                break;
            case 10:
                // Mostrar todos los sinónimos y antónimos asociados a las palabras
                lista_principal->mostrarSinonimosAntonimos();
                break;
            case 0:
                // Salimos del ciclo
                continuar = false;
                break;
            default:
                // Mostramos error
                cout << "\nError de entrada. Intenta nuevamente\n\n";
        }
        // Siempre que no se haya saido del menú, mostrar mensaje de espera
        if (opcion_menu)
        {
            cout << "\nPresione enter para continuar...";
            cin.get();
        }
        cout << endl;
    }
}
