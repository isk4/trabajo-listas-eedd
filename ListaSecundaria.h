#pragma once
#include <iostream>
#define MAX_PALABRA 20
using namespace std;

// Struct de los nodos de la lista
struct nodo_secundario
{
    char palabra[MAX_PALABRA];
    int frecuencia_conocimiento;
    nodo_secundario* sig;
};

class ListaSecundaria
{
private:
    nodo_secundario* p;
public:
    ListaSecundaria();
    ~ListaSecundaria();
    // Funcion ingreso modificada para los datos requeridos
    void ingresar(char palabra[], int frecuencia_conocimiento);
    void eliminar(char palabra[]);
    void mostrar();
};
