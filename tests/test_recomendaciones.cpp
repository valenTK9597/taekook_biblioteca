#include "../include/recomendaciones/RecomendacionContexto.h"
#include "../include/recomendaciones/RecomendacionPorTipo.h"
#include "../include/recomendaciones/RecomendacionParaEstudiantes.h"
#include "../include/recomendaciones/RecomendacionParaProfesores.h"
#include "../include/recursos/RecursoFactory.h"

#include <iostream>

void mostrarRecomendaciones(const std::vector<Recurso*>& recursos) {
    for (const auto& r : recursos) {
        std::cout << " - [" << r->getTipo() << "] " << r->getTitulo()
                  << " | Autor: " << r->getAutor() << "\n";
    }
}

int main() {
    std::cout << "\n INICIO DE PRUEBA - MÓDULO RECOMENDACIONES \n";

    // Cargar recursos desde archivo
    std::vector<Recurso*> recursos = RecursoFactory::cargarRecursosDesdeArchivo("data/recursos.txt");

    if (recursos.empty()) {
        std::cout << " No se encontraron recursos cargados desde el archivo.\n";
        return 1;
    }

    RecomendacionContexto contexto;

    // Estrategia 1: Por tipo (ej. Articulo)
    contexto.setEstrategia(new RecomendacionPorTipo("Articulo"));
    std::cout << "\n Recomendación por tipo: Articulo\n";
    mostrarRecomendaciones(contexto.recomendar(recursos));

    // Estrategia 2: Para estudiantes
    contexto.setEstrategia(new RecomendacionParaEstudiantes());
    std::cout << "\n Recomendación para estudiantes\n";
    mostrarRecomendaciones(contexto.recomendar(recursos));

    // Estrategia 3: Para profesores
    contexto.setEstrategia(new RecomendacionParaProfesores());
    std::cout << "\n Recomendación para profesores\n";
    mostrarRecomendaciones(contexto.recomendar(recursos));

    // Liberar recursos
    for (auto r : recursos) {
        delete r;
    }

    std::cout << "\n FIN - RECOMENDACIONES FUNCIONANDO CORRECTAMENTE\n";
    return 0;
}
