#include "../../include/recursos/RecursoFactory.h"
#include "../../include/recursos/LibroFisico.h"
#include "../../include/recursos/Ebook.h"
#include "../../include/recursos/Revista.h"
#include "../../include/recursos/Articulo.h"
#include <fstream>
#include <sstream>

Recurso* RecursoFactory::crearRecurso(const std::string& tipo, const std::string& id,
                                      const std::string& titulo, const std::string& autor,
                                      int anio, bool disponible) {
    if (tipo == "LibroFisico") {
        return new LibroFisico(id, titulo, autor, anio, disponible);
    } else if (tipo == "Ebook") {
        return new Ebook(id, titulo, autor, anio, disponible);
    } else if (tipo == "Revista") {
        return new Revista(id, titulo, autor, anio, disponible);
    } else if (tipo == "Articulo") {
        return new Articulo(id, titulo, autor, anio, disponible);
    } else {
        return nullptr;
    }
}

void RecursoFactory::guardarRecursoEnArchivo(Recurso* recurso, const std::string& rutaArchivo) {
    std::ofstream archivo(rutaArchivo, std::ios::app);
    if (archivo.is_open()) {
        archivo << recurso->getId() << "|"
                << recurso->getTitulo() << "|"
                << recurso->getAutor() << "|"
                << recurso->getAnioPublicacion() << "|"
                << recurso->estaDisponible() << "|"
                << recurso->getTipo() << "\n";
        archivo.close();
    } else {
        std::cerr << "⚠️ No se pudo abrir el archivo para guardar el recurso.\n";
    }
}

std::vector<Recurso*> RecursoFactory::cargarRecursosDesdeArchivo(const std::string& rutaArchivo) {
    std::vector<Recurso*> recursos;
    std::ifstream archivo(rutaArchivo);
    std::string linea;

    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string id, titulo, autor, anioStr, disponibleStr, tipo;
        int anio;
        bool disponible;

        std::getline(ss, id, '|');
        std::getline(ss, titulo, '|');
        std::getline(ss, autor, '|');
        std::getline(ss, anioStr, '|');
        std::getline(ss, disponibleStr, '|');
        std::getline(ss, tipo, '|');

        anio = std::stoi(anioStr);
        disponible = (disponibleStr == "1");

        Recurso* recurso = crearRecurso(tipo, id, titulo, autor, anio, disponible);
        if (recurso) recursos.push_back(recurso);
    }

    archivo.close();
    return recursos;
}
