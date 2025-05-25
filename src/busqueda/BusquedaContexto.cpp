#include "../../include/busqueda/BusquedaContexto.h"

BusquedaContexto::BusquedaContexto() : estrategia(nullptr) {}

BusquedaContexto::~BusquedaContexto() {
    delete estrategia;
}

void BusquedaContexto::setEstrategia(IBusqueda* nueva) {
    if (estrategia) delete estrategia;
    estrategia = nueva;
}

std::vector<Recurso*> BusquedaContexto::buscar(const std::vector<Recurso*>& recursos, const std::string& criterio) const {
    if (!estrategia) return {};
    return estrategia->buscar(recursos, criterio);
}
