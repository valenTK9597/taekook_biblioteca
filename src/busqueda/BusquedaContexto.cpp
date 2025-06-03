#include "../../include/busqueda/BusquedaContexto.h"

// Constructor por defecto
BusquedaContexto::BusquedaContexto() : estrategia(nullptr) {}

// Destructor que libera la estrategia actual
BusquedaContexto::~BusquedaContexto() {
    delete estrategia;
}

// Asignar nueva estrategia, liberando la anterior
void BusquedaContexto::setEstrategia(IBusqueda* nueva) {
    if (estrategia) {
        delete estrategia;
    }
    estrategia = nueva;
}

// Ejecutar la búsqueda utilizando la estrategia actual
std::vector<Recurso*> BusquedaContexto::buscar(const std::vector<Recurso*>& recursos, const std::string& criterio) const {
    if (!estrategia) {
        std::cerr << " No se ha definido una estrategia de busqueda.\n";
        return {};
    }

    return estrategia->buscar(recursos, criterio);
}
