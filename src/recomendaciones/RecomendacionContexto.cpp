#include "../../include/recomendaciones/RecomendacionContexto.h"

RecomendacionContexto::RecomendacionContexto() : estrategia(nullptr) {}

RecomendacionContexto::~RecomendacionContexto() {
    delete estrategia;
}

void RecomendacionContexto::setEstrategia(IRecomendacion* nueva) {
    if (estrategia) delete estrategia;
    estrategia = nueva;
}

std::vector<Recurso*> RecomendacionContexto::recomendar(const std::vector<Recurso*>& recursos) const {
    if (!estrategia) return {};
    return estrategia->recomendar(recursos);
}
