#pragma once
#include <iostream>
#include "ListaSecundaria.h"
#include "Binario.h"
#define MAX_PALABRA 20
#define MAX_TIPO 10
#define MAX_DESCRIPCION 200
#define MAX_EJEMPLO 50
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

class ListaPrincipal
{
private:
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
    void llenarConBinario(info_binario info);
    void eliminar(char palabra[]);
    void mostrar();
};
