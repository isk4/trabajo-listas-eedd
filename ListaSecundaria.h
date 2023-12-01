#pragma once
#include <iostream>
#include <map>
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
    // Función ingreso modificada para los datos requeridos
    void ingresar(char palabra[], int frecuencia_conocimiento);
    void eliminar(char palabra[]);
    void mostrar();
    // Función que cuenta la cantidad de elementos en la lista
    int largo();
    // Función que añade las palabras con su numero de repeticiones a un mapa
    void anadirMapaRepeticiones(map<string, int> &mapa);
    // Función que añade las palabras con su frecuencia de conocimiento a un mapa
    void anadirMapa(map<string, int> &mapa);
    // Función que elimina los elementos duplicados de la lista
    void eliminarDuplicados();
};
