#include "ListaSecundaria.h"
#include <iostream>
#include <cstring>
#include <map>
using namespace std;

ListaSecundaria::ListaSecundaria()
{
    p = NULL;
}

ListaSecundaria::~ListaSecundaria()
{
    nodo_secundario* q;
    while (p)
    {
        q = p;
        p = p->sig;
        delete q;
    }
}

void ListaSecundaria::ingresar
(
    char palabra[],
    int frecuencia_conocimiento
)
{
    nodo_secundario* q;
    nodo_secundario* r;
    q = new nodo_secundario;
    if (!q)
    {
        exit(1);
    }
    else
    {
        strcpy(q->palabra, palabra);
        q->frecuencia_conocimiento = frecuencia_conocimiento;
        q->sig = p;
        
        // Comparamos segun destino alfabeticamente
        if (!p || strcasecmp(q->palabra, p->palabra) <= 0)
            p = q;
        else {
            r = p->sig;
            while (r && strcasecmp(r->palabra, q->palabra) < 0) {
                q->sig = r;
                r = r->sig;
            }
            q->sig->sig = q;
            q->sig = r;
        }
    }
}

void ListaSecundaria::mostrar()
{
    nodo_secundario* q = p;
    while (q)
    {
        cout << "\t" << q->palabra << " (frecuencia: " << q->frecuencia_conocimiento << ")" << endl;
        q = q->sig;
    }
}

void ListaSecundaria::eliminar(char palabra[])
{
    nodo_secundario* q;
    nodo_secundario* r;
    if (p)
    {
        q = p;
        if (!strcasecmp(p->palabra, palabra))
        { 
            p = p->sig;
            delete q;
        }
        else
        {
            // Eliminamos todas las coincidencias
            while (q)
            {
                r = q;
                q = q->sig;

                if (q && !strcasecmp(q->palabra, palabra))
                {
                    r->sig = q->sig;
                    delete q;
                }
            }
        }
    }
}

int ListaSecundaria::largo()
{
    nodo_secundario* q = p;
    int largo = 0;
    while (q)
    {
        largo++;
        q = q->sig;
    }
    return largo;
} 

void ListaSecundaria::anadirMapaRepeticiones(map<string, int> &mapa)
{
    nodo_secundario* q = p;

    while (q)
    {
        // Intentamos ingresar la palabra en el mapa
        if (!mapa.insert(pair<string, int>(q->palabra, 1)).second)
            // Si no se pudo insertar, actualizamos su frecuencia
            mapa[q->palabra]++;
        q = q->sig;
    }
}

void ListaSecundaria::anadirMapa(map<string, int> &mapa)
{
    nodo_secundario* q = p;

    while (q)
    {
        // Intentamos ingresar la palabra con su fercuencia de conocimiento en el mapa
        mapa.insert(pair<string, int>(q->palabra, q->frecuencia_conocimiento));
        q = q->sig;
    }
}

void ListaSecundaria::eliminarDuplicados()
{
    nodo_secundario* q = p;
    nodo_secundario* aux;
    while (q)
    {
        // Si existe palabra siguiente y son iguales, eliminar
        if (q->sig && !strcasecmp(q->palabra, q->sig->palabra))
        {
            aux = q->sig->sig;
            delete q->sig;
            q->sig = aux;
        }
        q = q->sig;
    }
}