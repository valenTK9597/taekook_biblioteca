#include "../../include/recursos/ModuloRecursos.h"
#include "../../include/recursos/RecursoFactory.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>

ModuloRecursos::ModuloRecursos(const std::string& ruta) : rutaArchivoRecursos(ruta) {}

Recurso* ModuloRecursos::obtenerRecursoPorId(const std::string& idBuscado) {
    return RecursoFactory::obtenerRecursoPorId(idBuscado, rutaArchivoRecursos);
}


void ModuloRecursos::agregarRecurso() {
    std::string tipo, id, titulo, autor;
    int anio;

    std::cout << "\n Registro de nuevo recurso\n";
    std::cout << "Tipo (LibroFisico / Ebook / Revista / Articulo): ";
    std::cin >> tipo;
    std::cout << "ID: "; std::cin >> id;

    if (RecursoFactory::idExistente(id, rutaArchivoRecursos)) {
        std::cout << " Ya existe un recurso con ese ID.\n";
        return;
    }

    std::cout << "Título: "; std::cin.ignore(); std::getline(std::cin, titulo);
    std::cout << "Autor: "; std::getline(std::cin, autor);
    std::cout << "Año de publicación: "; std::cin >> anio;

    Recurso* nuevo = RecursoFactory::crearRecurso(tipo, id, titulo, autor, anio, true);
    if (!nuevo) {
        std::cout << " Tipo de recurso invalido.\n";
        return;
    }

    nuevo->registrar();
    RecursoFactory::guardarRecursoEnArchivo(nuevo, rutaArchivoRecursos);
    delete nuevo;

    std::cout << " Recurso agregado exitosamente.\n";
}

void ModuloRecursos::verRecursosDisponibles() {
    std::vector<Recurso*> recursos = RecursoFactory::cargarRecursosDesdeArchivo(rutaArchivoRecursos);
    bool encontrados = false;

    std::cout << "\n Recursos disponibles:\n";

    for (auto r : recursos) {
        if (r->estaDisponible()) {
            std::cout << "\n---------------------------\n";
            r->mostrarInformacion();
            encontrados = true;
        }
    }

    if (!encontrados) std::cout << " No hay recursos disponibles.\n";

    for (auto r : recursos) delete r;
}

void ModuloRecursos::verTodosLosRecursos() {
    std::vector<Recurso*> recursos = RecursoFactory::cargarRecursosDesdeArchivo(rutaArchivoRecursos);

    std::cout << "\n Lista completa de recursos:\n";
    if (recursos.empty()) {
        std::cout << " No hay recursos registrados.\n";
    } else {
        for (auto r : recursos) {
            std::cout << "\n---------------------------\n";
            r->mostrarInformacion();
        }
    }

    for (auto r : recursos) delete r;
}

void ModuloRecursos::eliminarRecursoPorId() {
    std::string id;
    std::cout << "\n Eliminar recurso\nIngrese el ID del recurso: ";
    std::cin >> id;

    if (RecursoFactory::eliminarRecursoPorId(id, rutaArchivoRecursos)) {
        std::cout << " Recurso eliminado correctamente.\n";
    } else {
        std::cout << " No se encuentra el recurso con ese ID.\n";
    }
}

void ModuloRecursos::editarRecursoPorId() {
    std::string id;
    std::cout << "\n Editar recurso\nIngrese el ID del recurso a editar: ";
    std::cin >> id;

    Recurso* recurso = RecursoFactory::obtenerRecursoPorId(id, rutaArchivoRecursos);
    if (!recurso) {
        std::cout << " Recurso no encontrado.\n";
        return;
    }

    std::string nuevoTitulo, nuevoAutor;
    int nuevoAnio;

    std::cout << "Nuevo titulo: "; std::cin.ignore(); std::getline(std::cin, nuevoTitulo);
    std::cout << "Nuevo autor: "; std::getline(std::cin, nuevoAutor);
    std::cout << "Nuevo anio de publicacion: "; std::cin >> nuevoAnio;

    recurso->setTitulo(nuevoTitulo);
    recurso->setAutor(nuevoAutor);
    recurso->setAnioPublicacion(nuevoAnio);

    std::vector<Recurso*> recursos = RecursoFactory::cargarRecursosDesdeArchivo(rutaArchivoRecursos);
    std::ofstream archivo("data/temp_recursos.txt");

    for (auto r : recursos) {
        if (r->getId() == id) {
            archivo << recurso->getId() << "|"
                    << recurso->getTitulo() << "|"
                    << recurso->getAutor() << "|"
                    << recurso->getAnioPublicacion() << "|"
                    << recurso->estaDisponible() << "|"
                    << recurso->getTipo() << "\n";
        } else {
            archivo << r->getId() << "|"
                    << r->getTitulo() << "|"
                    << r->getAutor() << "|"
                    << r->getAnioPublicacion() << "|"
                    << r->estaDisponible() << "|"
                    << r->getTipo() << "\n";
        }
        delete r;
    }

    archivo.close();
    std::remove(rutaArchivoRecursos.c_str());
    std::rename("data/temp_recursos.txt", rutaArchivoRecursos.c_str());

    std::cout << " Recurso actualizado correctamente.\n";
    delete recurso;
}

void ModuloRecursos::buscarPorTitulo() {
    std::string tituloBuscado;
    std::cout << "\n Buscar recurso por titulo: ";
    std::cin.ignore(); std::getline(std::cin, tituloBuscado);

    std::vector<Recurso*> recursos = RecursoFactory::cargarRecursosDesdeArchivo(rutaArchivoRecursos);
    bool encontrado = false;

    for (auto r : recursos) {
        if (r->getTitulo() == tituloBuscado) {
            r->mostrarInformacion();
            encontrado = true;
        }
    }

    if (!encontrado) std::cout << " No se encontraron recursos con ese titulo.\n";
    for (auto r : recursos) delete r;
}

void ModuloRecursos::buscarPorAutor() {
    std::string autorBuscado;
    std::cout << "\n Buscar recurso por autor: ";
    std::cin.ignore(); std::getline(std::cin, autorBuscado);

    std::vector<Recurso*> recursos = RecursoFactory::cargarRecursosDesdeArchivo(rutaArchivoRecursos);
    bool encontrado = false;

    for (auto r : recursos) {
        if (r->getAutor() == autorBuscado) {
            r->mostrarInformacion();
            encontrado = true;
        }
    }

    if (!encontrado) std::cout << " No se encontraron recursos con ese autor.\n";
    for (auto r : recursos) delete r;
}

void ModuloRecursos::gestionarRecursosAdministrador() {
    bool continuar = true;
    while (continuar) {
        std::cout << "\n Gestion de Recursos:\n";
        std::cout << "1. Ver todos los recursos\n";
        std::cout << "2. Ver recursos disponibles\n";
        std::cout << "3. Agregar recurso\n";
        std::cout << "4. Editar recurso\n";
        std::cout << "5. Eliminar recurso\n";
        std::cout << "6. Buscar por titulo\n";
        std::cout << "7. Buscar por autor\n";
        std::cout << "8. Volver al menu anterior\n";

        int opcion;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1: verTodosLosRecursos(); break;
            case 2: verRecursosDisponibles(); break;
            case 3: agregarRecurso(); break;
            case 4: editarRecursoPorId(); break;
            case 5: eliminarRecursoPorId(); break;
            case 6: buscarPorTitulo(); break;
            case 7: buscarPorAutor(); break;
            case 8: continuar = false; break;
            default: std::cout << " Opcion invalida.\n";
        }
    }
}
