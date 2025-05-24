#include <iostream>
#include "../include/recursos/RecursoFactory.h"

int main() {
    std::string archivo = "data/recursos.txt";

    // Crear y registrar distintos tipos de recursos
    struct Registro {
        std::string tipo;
        std::string id;
        std::string titulo;
        std::string autor;
        int anio;
    };

    std::vector<Registro> registros = {
        {"LibroFisico", "L01", "Cien años de soledad", "Gabriel García Márquez", 1967},
        {"Ebook",       "E01", "Curso de C++",         "Bjarne Stroustrup",      2019},
        {"Revista",     "R01", "National Geographic",  "NG Society",             2022},
        {"Articulo",    "A01", "IA y Ética",           "OpenAI",                 2024}
    };

    for (const auto& r : registros) {
        if (!RecursoFactory::idExistente(r.id, archivo)) {
            Recurso* recurso = RecursoFactory::crearRecurso(r.tipo, r.id, r.titulo, r.autor, r.anio, true);
            if (recurso) {
                recurso->registrar();
                RecursoFactory::guardarRecursoEnArchivo(recurso, archivo);
                delete recurso;
                std::cout << " Guardado: " << r.titulo << "\n";
            } else {
                std::cerr << " Error al crear recurso de tipo: " << r.tipo << "\n";
            }
        } else {
            std::cout << " Recurso con ID " << r.id << " ya existe. No se duplicará.\n";
        }
    }

    // Intentar eliminar un recurso específico
    std::string idAEliminar = "A01";
    if (RecursoFactory::eliminarRecursoPorId(idAEliminar, archivo)) {
        std::cout << " Recurso con ID " << idAEliminar << " eliminado exitosamente.\n";
    } else {
        std::cout << " No se encontró ningún recurso con ID " << idAEliminar << "\n";
    }

    // Cargar y mostrar todos los recursos restantes
    std::cout << "\n Recursos disponibles en archivo:\n";
    std::vector<Recurso*> lista = RecursoFactory::cargarRecursosDesdeArchivo(archivo);

    for (Recurso* r : lista) {
        r->mostrarInformacion();
        std::cout << " - Multa por 3 días de retraso: $" << r->calcularMulta(3) << "\n\n";
        delete r;
    }

    return 0;
}


