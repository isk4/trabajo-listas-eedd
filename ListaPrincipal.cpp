#include "ListaPrincipal.h"
#include "ListaSecundaria.h"
#include <iostream>
#include <cstring>
using namespace std;

ListaPrincipal::ListaPrincipal()
{
    p = NULL;
}

ListaPrincipal::~ListaPrincipal()
{
    nodo_principal* q;
    while (p)
    {
        q = p;
        p = p->sig;
        if (q->sinonimos) delete q->sinonimos;
        if (q->antonimos) delete q->antonimos;
        delete q;
    }
}

void ListaPrincipal::ingresar
(
    char palabra[],
    char tipo[],
    char descripcion[],
    int frecuencia_conocimiento,
    char ejemplo[],
    ListaSecundaria* sinonimos,
    ListaSecundaria* antonimos
)
{
    nodo_principal* q;
    nodo_principal* r;
    q = new nodo_principal;
    if (!q)
    {
        exit(1);
    }
    else
    {
        strcpy(q->palabra, palabra);
        strcpy(q->tipo, tipo);
        strcpy(q->descripcion, descripcion);
        q->frecuencia_conocimiento = frecuencia_conocimiento;
        strcpy(q->ejemplo, ejemplo);
        q->sinonimos = sinonimos;
        q->antonimos = antonimos;
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

void ListaPrincipal::eliminar(char palabra[])
{
    nodo_principal* q = p;
    while (q)
    {
        if (q->palabra == palabra)
        {
            delete q->sinonimos;
            delete q->sinonimos;
            delete q;
        }
    }
}

void ListaPrincipal::mostrar()
{
    nodo_principal* q = p;
    while (q)
    {
        cout << "Palabra: " << q->palabra << endl;
        cout << "Sinonimos:" << endl;
        q->sinonimos->mostrar();
        cout << "Antonimos:" << endl;
        q->antonimos->mostrar();
        cout << "------------------------------------------------" << endl;
        q = q->sig;
    }
}

void ListaPrincipal::llenarConBinario(info_binario info)
{
    ListaSecundaria* lista_sinonimos;
    ListaSecundaria* lista_antonimos;
    for (int i = 0; i < info.cant_datos; i++)
    {
        lista_sinonimos = new ListaSecundaria;
        lista_antonimos = new ListaSecundaria;

        for (int j = 0; j < info.datos[i].cant_sinonimos; j++)
            lista_sinonimos->ingresar(info.datos[i].sinonimos[j].palabra, info.datos[i].sinonimos[j].frecuencia_conocimiento);

        for (int j = 0; j < info.datos[i].cant_antonimos; j++)
            lista_antonimos->ingresar(info.datos[i].antonimos[j].palabra, info.datos[i].antonimos[j].frecuencia_conocimiento);

        ingresar
        (
            info.datos[i].palabra,
            info.datos[i].tipo,
            info.datos[i].descripcion,
            info.datos[i].frecuencia_conocimiento,
            info.datos[i].ejemplo,
            lista_sinonimos,
            lista_antonimos
        );
    }
}