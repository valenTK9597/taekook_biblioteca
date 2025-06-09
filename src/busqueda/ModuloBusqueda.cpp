#include "../../include/busqueda/ModuloBusqueda.h"
#include "../../include/busqueda/BusquedaPorTitulo.h"
#include "../../include/busqueda/BusquedaPorAutor.h"
#include "../../include/busqueda/BusquedaPorTipo.h"
#include "../../include/recursos/RecursoFactory.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <string>

// Constructor
ModuloBusqueda::ModuloBusqueda(const std::string& rutaRecursos)
    : rutaArchivoRecursos(rutaRecursos) {}

//  Cargar recursos (todos o solo disponibles según parámetro)
std::vector<Recurso*> ModuloBusqueda::cargarRecursos(bool incluirNoDisponibles) const {
    std::vector<Recurso*> todos = RecursoFactory::cargarRecursosDesdeArchivo(rutaArchivoRecursos);
    if (incluirNoDisponibles) return todos;

    std::vector<Recurso*> disponibles;
    for (Recurso* r : todos) {
        if (r->estaDisponible()) {
            disponibles.push_back(r);
        } else {
            delete r;
        }
    }
    return disponibles;
}

//  Método genérico de impresión
void imprimirResultados(const std::vector<Recurso*>& resultados, bool mostrarEstado) {
    if (resultados.empty()) {
        std::cout << " No se encontraron recursos.\n";
    } else {
        std::cout << "\n Resultados:\n";
        for (Recurso* r : resultados) {
            r->mostrarInformacion();
            if (mostrarEstado) {
                std::cout << "  Estado: " << (r->estaDisponible() ? "Disponible\n" : "No disponible\n");
            }
        }
    }

    for (Recurso* r : resultados) delete r;
}

// Buscar por título
void ModuloBusqueda::buscarPorTitulo(bool incluirNoDisponibles) const {
    std::string criterio;
    std::cout << "\n Ingrese parte o todo el titulo: ";
    std::cin.ignore();
    std::getline(std::cin, criterio);

    BusquedaContexto contexto;
    contexto.setEstrategia(new BusquedaPorTitulo());
    std::vector<Recurso*> resultados = contexto.buscar(cargarRecursos(incluirNoDisponibles), criterio);

    imprimirResultados(resultados, incluirNoDisponibles);
}

// Buscar por autor
void ModuloBusqueda::buscarPorAutor(bool incluirNoDisponibles) const {
    std::string criterio;
    std::cout << "\n Ingrese parte o todo el nombre del autor: ";
    std::cin.ignore();
    std::getline(std::cin, criterio);

    BusquedaContexto contexto;
    contexto.setEstrategia(new BusquedaPorAutor());
    std::vector<Recurso*> resultados = contexto.buscar(cargarRecursos(incluirNoDisponibles), criterio);

    imprimirResultados(resultados, incluirNoDisponibles);
}

void ModuloBusqueda::buscarPorTipo(bool incluirNoDisponibles) const {
    std::string criterio;
    std::cout << "\n Ingrese el tipo de recurso a buscar (LibroFisico, Ebook, Revista, Articulo): ";
    std::cin >> criterio;

    BusquedaContexto contexto;
    contexto.setEstrategia(new BusquedaPorTipo());
    std::vector<Recurso*> resultados = contexto.buscar(cargarRecursos(incluirNoDisponibles), criterio);

    imprimirResultados(resultados, incluirNoDisponibles);
}

std::map<std::string, int> ModuloBusqueda::contarRecursosPorTipoDesdeIds(const std::vector<std::string>& ids) const {
    std::map<std::string, int> conteo;
    std::ifstream archivo("data/recursos.txt");  // Se usa la ruta directa
    std::string linea;

    std::set<std::string> idsBuscados(ids.begin(), ids.end());

    while (std::getline(archivo, linea)) {
        std::istringstream iss(linea);
        std::string id, tipo, titulo, autor;
        std::getline(iss, id, '|');
        std::getline(iss, tipo, '|');
        std::getline(iss, titulo, '|');
        std::getline(iss, autor, '|');

        if (idsBuscados.count(id)) {
            conteo[tipo]++;
        }
    }

    return conteo;
}



