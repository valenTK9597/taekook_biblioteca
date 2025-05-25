#ifndef IBUSQUEDA_H
#define IBUSQUEDA_H

#include <vector>
#include <string>
#include "../recursos/Recurso.h"

class IBusqueda {
public:
    virtual ~IBusqueda() = default;

    // Método abstracto que busca recursos en base a un criterio
    virtual std::vector<Recurso*> buscar(const std::vector<Recurso*>& recursos, const std::string& criterio) const = 0;
};

#endif
