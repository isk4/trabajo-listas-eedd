#include "Binario.h"
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
using namespace std;

const char NOMBRE_CSV[] = "palabras.csv";
const char NOMBRE_BIN[] = "palabras.dat";
void mostrar_info_principal(struct_principal info)
{
    cout << info.palabra << endl;
    cout << info.tipo << endl;
    cout << info.descripcion << endl;
    cout << info.frecuencia_conocimiento << endl;
    cout << info.ejemplo << endl;
}

void Binario::construir()
{
    // Se incializan en cero las cantidades de elementos
    info_binario struct_binario = {};
    // Nodo para trabajar con las palabras principales
    struct_principal info_principal;
    // Nodo para trabajar con las palabras secundarias
    struct_secundario info_secundaria;
    // Archivo binario donde se escribiran los archivos
    FILE* binario = fopen(NOMBRE_BIN, "wb");
    // Linea a leer del archivo
    string linea;
    // Numero de columna a leer, id de palabra principal
    int columna, aux_datos;
    // Archivo csv de donde se extraen los datos para generar el binario
    ifstream archivo_entrada(NOMBRE_CSV);
    // Contenido del archivo CSV correspondiente columnas y sus datos
    istringstream columnas_archivo, datos_col, sub_datos_col;

    if (archivo_entrada.is_open() && binario)
    {
        // Sacando el encabezado del archivo
        getline(archivo_entrada, linea);
        // Leyendo contenido
        while(getline(archivo_entrada, linea))
        {
            info_principal = {};
            columna = 1;
            columnas_archivo.str(linea);
            while (getline(columnas_archivo, linea, ';'))
            {
                // Si la columna tiene contenido
                if (linea.length() != 0 && linea[0] != '\n' && linea[0] != '\r')
                {
                    switch (columna)
                    {
                        case 1:
                            strcpy(info_principal.palabra, linea.c_str());
                            break;
                        case 2:
                            strcpy(info_principal.tipo, linea.c_str());
                            break;
                        case 3:
                            strcpy(info_principal.descripcion, linea.c_str());
                            break;
                        case 4:
                            info_principal.frecuencia_conocimiento = stoi(linea);
                            break;
                        case 5:
                            strcpy(info_principal.ejemplo, linea.c_str());
                            break;
                        case 6:
                            datos_col.str(linea);
                            while (getline(datos_col, linea, '-'))
                            {
                                sub_datos_col.str(linea);
                                // Obteniendo palabra
                                getline(sub_datos_col, linea, ':');
                                // Asignando palabra a nuevo dato
                                strcpy(info_secundaria.palabra, linea.c_str());
                                // Obteniendo frecuencia
                                getline(sub_datos_col, linea);
                                info_secundaria.frecuencia_conocimiento = stoi(linea);
                                // Añadiendo a sinonimos
                                info_principal.sinonimos[info_principal.cant_sinonimos] = info_secundaria;
                                info_principal.cant_sinonimos++;
                                // Limpiando variables
                                info_secundaria = {};
                                sub_datos_col.clear();
                            }
                            break;
                        case 7:
                            datos_col.str(linea);
                            while (getline(datos_col, linea, '-'))
                            {
                                sub_datos_col.str(linea);
                                // Obteniendo palabra
                                getline(sub_datos_col, linea, ':');
                                // Asignando palabra a nuevo dato
                                strcpy(info_secundaria.palabra, linea.c_str());
                                // Obteniendo frecuencia
                                getline(sub_datos_col, linea);
                                info_secundaria.frecuencia_conocimiento = stoi(linea);
                                // Añadiendo a antonimos
                                info_principal.antonimos[info_principal.cant_antonimos] = info_secundaria;
                                info_principal.cant_antonimos++;
                                // Limpiando variables
                                info_secundaria = {};
                                sub_datos_col.clear();
                            }
                            break;
                    }
                }
                datos_col.clear();
                columna == 7 ? columna = 1 : columna++;
            }
            columnas_archivo.clear();
            struct_binario.datos[struct_binario.cant_datos] = info_principal;
            struct_binario.cant_datos++;
        }
    }
    fwrite(&struct_binario, sizeof(info_binario), 1, binario);
    fclose(binario);
}

// Lectura de binario
info_binario Binario::extraerDatos()
{
    FILE* binario = fopen("palabras.dat", "rb");
    info_binario info = {};
    if (binario) fread(&info, sizeof(info_binario), 1, binario);
    fclose(binario);
    return info;
}

// void leer_binario()
// {
//     FILE* binario = fopen("palabras.dat", "rb");
//     info_binario info;
//     if (binario)
//     {
//         fread(&info, sizeof(info_binario), 1, binario);

//         cout << "Informacion binario:\n\n";
//         for (int i = 0; i < info.cant_datos; i++)
//         {
//             cout << "Palabra: " << info.datos[i].palabra << endl;
//             cout << "Sinonimos: \n";
//             for (int j = 0; j < info.datos[i].cant_sinonimos; j++)
//             {
//                 cout << "  " << info.datos[i].sinonimos[j].palabra << " - frecuencia: "
//                     << info.datos[i].sinonimos[j].frecuencia_conocimiento << endl;
//             }
//             cout << "Cantidad de sinonimos: " << info.datos[i].cant_sinonimos << endl;
//             cout << "Antonimos: \n";
//             for (int j = 0; j < info.datos[i].cant_antonimos; j++)
//             {
//                 cout << "  " << info.datos[i].antonimos[j].palabra << " - frecuencia: "
//                     << info.datos[i].sinonimos[j].frecuencia_conocimiento << endl;
//             }
//             cout << "Cantidad de antonimos: " << info.datos[i].cant_antonimos << endl << endl;

//         }
//         cout << endl << "Cantidad de palabras en el archivo: " << info.cant_datos << endl;
//     }
//     fclose(binario);
// }