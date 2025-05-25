#ifndef BUSQUEDAPORAUTOR_H
#define BUSQUEDAPORAUTOR_H

#include "IBusqueda.h"

class BusquedaPorAutor : public IBusqueda {
public:
    std::vector<Recurso*> buscar(const std::vector<Recurso*>& recursos, const std::string& criterio) const override;
};

#endif
