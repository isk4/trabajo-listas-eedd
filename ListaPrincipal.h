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
};
