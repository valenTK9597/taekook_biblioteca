#ifndef BUSQUEDAPORTITULO_H
#define BUSQUEDAPORTITULO_H

#include "IBusqueda.h"

class BusquedaPorTitulo : public IBusqueda {
public:
    std::vector<Recurso*> buscar(const std::vector<Recurso*>& recursos, const std::string& criterio) const override;
};

#endif
