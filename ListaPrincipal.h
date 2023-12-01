#pragma once
#include <iostream>
#include "ListaSecundaria.h"
#include "Binario.h"

// Definicion de largos maximos para strings
#define MAX_PALABRA 20
#define MAX_TIPO 20
#define MAX_DESCRIPCION 200
#define MAX_EJEMPLO 100

using namespace std;

// Struct de los nodos de la lista
struct nodo_principal
{
    char palabra[MAX_PALABRA];
    char tipo[MAX_TIPO];
    char descripcion[MAX_DESCRIPCION];
    int frecuencia_conocimiento;
    char ejemplo[MAX_EJEMPLO];
    ListaSecundaria* sinonimos;
    ListaSecundaria* antonimos;
    nodo_principal* sig;
};

// Clase para la lista principal
class ListaPrincipal
{
private:
    // Cabeza de la lista
    nodo_principal* p;
public:
    ListaPrincipal();
    ~ListaPrincipal();
    // Funcion ingreso modificada para los datos requeridos
    void ingresar
    (
        char palabra[],
        char tipo[],
        char descripcion[],
        int frecuencia_conocimiento,
        char ejemplo[],
        ListaSecundaria* sinonimos,
        ListaSecundaria* antonimos
    );
    // Función que acepta información extraida de un binario y llena la lista
    void llenarConBinario(info_binario info);
    // Función que elimina una palabra de la lista
    void eliminar(char palabra[]);
    // Función que muestra la lista (con cada sublista asociada a cada palabra)
    void mostrar();
    // Función que muestra las palabras con mayor y menor frecuencia
    void mostrarMayorMenorFreq();
    // Función que muestra palabras sin sinónimos o antónimos
    void mostrarSinSecundarias();
    // Función que muestra las palabras con más sinónimos
    void mostrarMasSinonimos();
    // Función que muestra las palabras con más antónimos
    void mostrarMasAntonimos();
    // Función que muestra las palabras de cierto tipo
    void mostrarPorTipo(int &opcion_menu);
    // Función que muestra los sinónimos más frecuente entre las palabras
    void mostrarSinonimosMasFrecuentes();
    // Función que muestra los antónimos más frecuente entre las palabras
    void mostrarAntonimosMasFrecuentes();
    // Función que elimina los elementos duplicados de la lista
    void eliminarDuplicados();
    // Función que muestra los detalles de una palabra en particular
    void mostrarPalabra();
    // Función que muestra todos los sinónimos y antónimos asociados a las palabras
    void mostrarSinonimosAntonimos();
};
