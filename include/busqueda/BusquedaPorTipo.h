#ifndef BUSQUEDAPORTIPO_H
#define BUSQUEDAPORTIPO_H

#include "IBusqueda.h"

class BusquedaPorTipo : public IBusqueda {
public:
    std::vector<Recurso*> buscar(const std::vector<Recurso*>& recursos, const std::string& criterio) const override;
};

#endif
