#include "../include/recursos/RecursoFactory.h"
#include "../include/busqueda/BusquedaContexto.h"
#include "../include/busqueda/BusquedaPorTitulo.h"
#include "../include/busqueda/BusquedaPorAutor.h"
#include "../include/busqueda/BusquedaPorTipo.h"

#include <iostream>

void mostrarResultados(const std::vector<Recurso*>& resultados) {
    std::cout << "\n Resultados encontrados: " << resultados.size() << "\n";
    for (Recurso* r : resultados) {
        std::cout << " - [" << r->getTipo() << "] " << r->getTitulo()
                  << " | Autor: " << r->getAutor() << "\n";
    }
}

int main() {
    std::string ruta = "data/recursos.txt";

    // Cargar recursos desde archivo
    std::vector<Recurso*> recursos = RecursoFactory::cargarRecursosDesdeArchivo(ruta);

    if (recursos.empty()) {
        std::cout << " No se encontraron recursos cargados desde el archivo.\n";
        return 1;
    }

    BusquedaContexto contexto;

    // 🔍 Búsqueda por título
    contexto.setEstrategia(new BusquedaPorTitulo());
    std::cout << "\n Buscando por título: 'Cien años'\n";
    auto porTitulo = contexto.buscar(recursos, "Cien años");
    mostrarResultados(porTitulo);

    // ✍️ Búsqueda por autor
    contexto.setEstrategia(new BusquedaPorAutor());
    std::cout << "\n Buscando por autor: 'García Márquez'\n";
    auto porAutor = contexto.buscar(recursos, "García Márquez");
    mostrarResultados(porAutor);

    // 📦 Búsqueda por tipo
    contexto.setEstrategia(new BusquedaPorTipo());
    std::cout << "\n Buscando por tipo: 'Revista'\n";
    auto porTipo = contexto.buscar(recursos, "Revista");
    mostrarResultados(porTipo);

    // Liberar memoria
    for (Recurso* r : recursos) {
        delete r;
    }

    return 0;
}
