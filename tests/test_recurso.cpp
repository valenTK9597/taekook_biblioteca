#include <iostream>
#include "../include/recursos/RecursoFactory.h"

int main() {
    std::string archivo = "data/recursos.txt";

    // Crear y registrar un recurso
    Recurso* recurso = RecursoFactory::crearRecurso("LibroFisico", "L01", "Cien años de soledad", "Gabriel García Márquez", 1967, true);
    recurso->registrar();
    RecursoFactory::guardarRecursoEnArchivo(recurso, archivo);
    delete recurso;

    recurso = RecursoFactory::crearRecurso("Ebook", "E01", "Curso de C++", "Bjarne Stroustrup", 2019, true);
    recurso->registrar();
    RecursoFactory::guardarRecursoEnArchivo(recurso, archivo);
    delete recurso;

    // Leer recursos del archivo
    std::cout << "\n Recursos registrados:\n";
    std::vector<Recurso*> lista = RecursoFactory::cargarRecursosDesdeArchivo(archivo);

    for (Recurso* r : lista) {
        r->mostrarInformacion();
        std::cout << " - Multa por 3 días de retraso: $" << r->calcularMulta(3) << "\n\n";
        delete r;
    }

    return 0;
}
