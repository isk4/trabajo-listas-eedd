#include "ListaSecundaria.h"
#include <iostream>
#include <cstring>
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
        cout << "\t" << q->palabra << endl;
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