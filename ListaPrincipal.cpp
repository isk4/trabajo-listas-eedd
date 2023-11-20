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
        // Se borran las listas secundarias al borrar un nodo principal
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
        // Se copian los strings en los casos necesarios
        strcpy(q->palabra, palabra);
        strcpy(q->tipo, tipo);
        strcpy(q->descripcion, descripcion);
        q->frecuencia_conocimiento = frecuencia_conocimiento;
        strcpy(q->ejemplo, ejemplo);
        q->sinonimos = sinonimos;
        q->antonimos = antonimos;
        q->sig = p;
        
        // Comparamos alfabéticamente las palabras para ingresarlas
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
        // Si coincide la palabra, se borran sus sublistas asociadas
        if (!strcasecmp(q->palabra, palabra))
        {
            delete q->sinonimos;
            delete q->antonimos;
            delete q;
        }
    }
}

void ListaPrincipal::mostrar()
{
    nodo_principal* q = p;
    while (q)
    {
        // Se muestra la información de la palabra
        cout << "Palabra: " << q->palabra << endl
            << "Tipo: " << q->tipo << endl
            << "Descripción: " << q->descripcion << endl
            << "Frecuencia de conocimiento: " << q->frecuencia_conocimiento << endl
             << "Ejemplo de uso: " << q->ejemplo << endl;
        cout << "Sinonimos:" << endl;
        // Se muestran las listas de sinónimos y antónimos de la palabra
        q->sinonimos->mostrar();
        cout << "Antonimos:" << endl;
        q->antonimos->mostrar();
        cout << "------------------------------------------------" << endl;
        q = q->sig;
    }
}

void ListaPrincipal::llenarConBinario(info_binario info)
{
    // Se crean las listas secundarias para guardar sinónimos y antónimos
    ListaSecundaria* lista_sinonimos;
    ListaSecundaria* lista_antonimos;
    for (int i = 0; i < info.cant_datos; i++)
    {
        // Se inicializan asigna memoria para dos nuevas sublistas
        lista_sinonimos = new ListaSecundaria;
        lista_antonimos = new ListaSecundaria;

        // Se recorren todos los sinónimos y antónimos existentes en los datos
        // extraídos y se ingresan a sus listas correspondientes
        for (int j = 0; j < info.datos[i].cant_sinonimos; j++)
            lista_sinonimos->ingresar(info.datos[i].sinonimos[j].palabra, info.datos[i].sinonimos[j].frecuencia_conocimiento);

        for (int j = 0; j < info.datos[i].cant_antonimos; j++)
            lista_antonimos->ingresar(info.datos[i].antonimos[j].palabra, info.datos[i].antonimos[j].frecuencia_conocimiento);
        
        // Finalmente se ingresa el nuevo nodo con toda la información
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