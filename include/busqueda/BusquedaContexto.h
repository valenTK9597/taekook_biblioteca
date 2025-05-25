#ifndef BUSQUEDACONTEXTO_H
#define BUSQUEDACONTEXTO_H

#include "IBusqueda.h"

class BusquedaContexto {
private:
    IBusqueda* estrategia;

public:
    BusquedaContexto();                         // Constructor sin estrategia
    ~BusquedaContexto();                        // Destructor
    void setEstrategia(IBusqueda* nueva);       // Asignar estrategia dinámica
    std::vector<Recurso*> buscar(const std::vector<Recurso*>& recursos, const std::string& criterio) const;
};

#endif
