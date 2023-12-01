#include "ListaPrincipal.h"
#include "ListaSecundaria.h"
#include <map>
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
    nodo_principal* q;
    nodo_principal* r;
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
                    delete q->sinonimos;
                    delete q->antonimos;
                    delete q;
                }
            }
        }
    }
}

void ListaPrincipal::mostrar()
{
    nodo_principal* q = p;
    cout << "Palabras disponibles y sus detalles\n"
        << "------------------------------------------------\n\n";
    while (q)
    {
        // Se muestra la información de la palabra
        cout << " Palabra: " << q->palabra << endl
            << " Tipo: " << q->tipo << endl
            << " Descripción: " << q->descripcion << endl
            << " Frecuencia de conocimiento: " << q->frecuencia_conocimiento << endl
             << " Ejemplo de uso: " << q->ejemplo << endl;
        cout << " Sinonimos:" << endl;
        // Se muestran las listas de sinónimos y antónimos de la palabra
        q->sinonimos->mostrar();
        cout << " Antonimos:" << endl;
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
        // Eliminamos los sinónimos duplicados
        lista_sinonimos->eliminarDuplicados();
        for (int j = 0; j < info.datos[i].cant_antonimos; j++)
            lista_antonimos->ingresar(info.datos[i].antonimos[j].palabra, info.datos[i].antonimos[j].frecuencia_conocimiento);
        // Eliminamos los antónimos duplicados
        lista_antonimos->eliminarDuplicados();
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
    eliminarDuplicados();
}

void ListaPrincipal::mostrarMayorMenorFreq()
{
    int max;
    int min;
    if (p)
    {
        nodo_principal* q = p;
        // Inicializamos el máximo
        max = min = q->frecuencia_conocimiento;
        while (q)
        {   
            if (q->frecuencia_conocimiento > max) max = q->frecuencia_conocimiento;
            if (q->frecuencia_conocimiento < min) min = q->frecuencia_conocimiento;

            q = q->sig;
        }
        // Devolvemos "q" a la cabeza de la lista
        q = p;

        cout << "Palabras más usadas (frecuencia máxima: " << max << ")\n"
            << "------------------------------------------------\n";
        // Mostramos las palabras de mayor frecuencia
        while (q)
        {
            if (q->frecuencia_conocimiento == max) cout << " " << q->palabra << endl;
            q = q->sig;
        }

        // Devolvemos "q" a la cabeza de la lista
        q = p;
        cout << "\nPalabras menos usadas (frecuencia mínima: " << min << ")\n"
            << "------------------------------------------------\n";
        // Mostramos las palabras de menor frecuencia
        while (q)
        {
            if (q->frecuencia_conocimiento == min) cout << " " << q->palabra << endl;
            q = q->sig;
        }
    }
    else
    {
        cout << "\n\nLa lista está vacía\n";
    }
}

void ListaPrincipal::mostrarSinSecundarias()
{
    nodo_principal* q = p;
    int cant_sinonimos, cant_antonimos;
    cout << "Palabras sin sinónimos o antónimos\n"
        << "------------------------------------------------\n";
    while (q)
    {
        // Verificamos si tiene alguna lista secundaria vacía y mostramos
        cant_sinonimos = q->sinonimos->largo();
        cant_antonimos = q->antonimos->largo();
        if (!cant_sinonimos || !cant_antonimos)
        {
            cout << " " << q->palabra << " (";
            if (!cant_sinonimos && !cant_antonimos) cout << "sin sinonimos ni antónimos";
            else if (!cant_sinonimos) cout << "sin sinónimos";
            else cout << "sin antónimos";
            cout << ")\n";
        }
        q = q->sig;
    }
}

void ListaPrincipal::mostrarMasSinonimos()
{
    nodo_principal* q = p;
    int max = 0;
    int aux;

    if (q)
    {
        // Calculamos la palabra con mayor cantidad de sinonimos
        while (q)
        {
            aux = q->sinonimos->largo();
            if (aux > max) max = aux;
            q = q->sig;
        }
        // Nos devolvemos a la cabeza de la lista para mostrar las palabras
        // que tengan la mayor cantidad sinónimos
        q = p;
        cout << "Palabras con más sinónimos (máximo: " << max << ")\n"
            << "------------------------------------------------\n";
        while (q)
        {
            aux = q->sinonimos->largo();
            if (aux == max) cout << " " << q->palabra << endl;
            q = q->sig;
        }
    }
}

void ListaPrincipal::mostrarMasAntonimos()
{
    nodo_principal* q = p;
    int max = 0;
    int aux;

    if (q)
    {
        // Calculamos la palabra con mayor cantidad de antónimos
        while (q)
        {
            aux = q->antonimos->largo();
            if (aux > max) max = aux;
            q = q->sig;
        }
        // Nos devolvemos a la cabeza de la lista para mostrar las palabras
        // que tengan la mayor cantidad antónimos
        cout << "Palabras con más antónimos (máximo: " << max << ")\n"
            << "------------------------------------------------\n";
        q = p;
        while (q)
        {
            aux = q->antonimos->largo();
            if (aux == max) cout << " " << q->palabra << endl;
            q = q->sig;
        }
    }
}

void ListaPrincipal::mostrarPorTipo()
{
    nodo_principal* q = p;

    // Relaciones entre números y tipos
    string opciones_tipos[] = 
    {
        "salir",      // 0 
        "sustantivo", // 1
        "adjetivo",   // 2
        "verbo"       // 3
    };
    // Booleano que controla si el submenú continuará mostrándose o no
    bool continuar = true;
    // String que recibe input del usuario y tipo de palabra a consultar
    string input_usuario, tipo;
    // Opción del menu elegida
    int opcion_menu;
    while (continuar)
    {
        cout << "\nElija un tipo de palabra "
            << "\n------------------------------------------------\n"
            << "\n1. Sustantivo\n"
            << "2. Adjetivo\n"
            << "3. Verbo\n"
            << "0. Volver al menú principal\n\nIngrese una opción: ";
        getline(cin, input_usuario);

        // Verificamos si el input es correcto
        try
        {
            opcion_menu = stoi(input_usuario);
            if (opcion_menu < 0 || opcion_menu > 3) throw 0;
        }
        // Atajamos cualquier error y asignamos valor aleatorio en caso de haberlo
        catch (...) { opcion_menu = -1; }
        
        // Si no existe la opción, continuar preguntando por una
        if (opcion_menu == -1) cout << "\nError de entrada. Intenta nuevamente\n\n";
        else continuar = false;
    }
    cout << endl << endl;
    // Si la opción es distinta de 0 (salir), mostramos
    if (opcion_menu)
    {
        // Asignamos el tipo a consultar según la opción elegida
        tipo = opciones_tipos[opcion_menu];
        cout << "Palabras del tipo \"" << tipo << "\"\n"
            << "------------------------------------------------\n";
        while (q)
        {
            if (!strcasecmp(q->tipo, tipo.c_str())) cout << " " << q->palabra << endl;
            q = q->sig;
        }
    }
}

void ListaPrincipal::mostrarSinonimosMasFrecuentes()
{
    nodo_principal* q = p;
    int max = 0;
    map<string, int> mapa_sinonimos;
    map<string, int>::iterator elemento;

    while (q)
    {
        q->sinonimos->anadirMapaRepeticiones(mapa_sinonimos);
        q = q->sig;
    }

    for (elemento = mapa_sinonimos.begin(); elemento != mapa_sinonimos.end(); elemento++)
    {
        if (elemento->second > max && elemento->second >= 2) max = elemento->second;
    }
    cout << "Sinónimos que más se repiten (repeticiones: " << max << ")\n"
        << "------------------------------------------------\n";

    for (elemento = mapa_sinonimos.begin(); elemento != mapa_sinonimos.end(); elemento++)
    {
        if (elemento->second == max) cout << " " << elemento->first << endl;
    }
}

void ListaPrincipal::mostrarAntonimosMasFrecuentes()
{
    nodo_principal* q = p;
    int max = 0;
    map<string, int> mapa_antonimos;
    map<string, int>::iterator elemento;

    while (q)
    {
        q->antonimos->anadirMapaRepeticiones(mapa_antonimos);
        q = q->sig;
    }

    for (elemento = mapa_antonimos.begin(); elemento != mapa_antonimos.end(); elemento++)
    {
        if (elemento->second > max && elemento->second >= 2) max = elemento->second;
    }
    cout << "Sinónimos que más se repiten (repeticiones: " << max << ")\n"
        << "------------------------------------------------\n";

    for (elemento = mapa_antonimos.begin(); elemento != mapa_antonimos.end(); elemento++)
    {
        if (elemento->second == max) cout << " " << elemento->first << endl;
    }
}

void ListaPrincipal::eliminarDuplicados()
{
    nodo_principal* q = p;
    nodo_principal* aux;
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

void ListaPrincipal::mostrarPalabra()
{
    nodo_principal* q = p;
    // Palabra a buscar
    string input_usuario;
    cout << "Ingrese palabra a buscar: ";
    getline(cin, input_usuario);

    // Buscamos la palabra
    while (q && strcasecmp(q->palabra, input_usuario.c_str())) q = q->sig;
    // Si se encontró la palabra, mostrar
    if (q)
    {
        cout << "\n------------------------------------------------\n" 
            << " Palabra: " << q->palabra << endl
            << " Tipo: " << q->tipo << endl
            << " Descripción: " << q->descripcion << endl
            << " Frecuencia de conocimiento: " << q->frecuencia_conocimiento << endl
            << " Ejemplo de uso: " << q->ejemplo << endl;
        cout << " Sinonimos:" << endl;
        // Se muestran las listas de sinónimos y antónimos de la palabra
        q->sinonimos->mostrar();
        cout << " Antonimos:" << endl;
        q->antonimos->mostrar();
        cout << "------------------------------------------------" << endl;
    }
    else
    {
        cout << "\nNo se encontró la palabra\n";
    }
}

void ListaPrincipal::mostrarSinonimosAntonimos()
{
    nodo_principal* q = p;
    map<string, int> mapa_sinonimos;
    map<string, int> mapa_antonimos;
    map<string, int>::iterator elemento;

    cout << "Mostrando todos los sinónimos y antónimos disponibles\n\n";

    while (q)
    {
        q->sinonimos->anadirMapa(mapa_sinonimos);
        q->antonimos->anadirMapa(mapa_antonimos);
        q = q->sig;
    }

    cout << "Sinónimos\n"
        << "------------------------------------------------\n";

    for (elemento = mapa_sinonimos.begin(); elemento != mapa_sinonimos.end(); elemento++)
    {
        cout << " " << elemento->first << " (frecuencia:" << elemento->second << ")" << endl;
    }
    cout << "\n\nAntónimos\n"
        << "------------------------------------------------\n";

    for (elemento = mapa_antonimos.begin(); elemento != mapa_antonimos.end(); elemento++)
    {
        cout << " " << elemento->first << " (frecuencia: " << elemento->second << ")" << endl;
    }
}