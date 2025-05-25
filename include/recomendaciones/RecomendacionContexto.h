#ifndef RECOMENDACIONCONTEXTO_H
#define RECOMENDACIONCONTEXTO_H

#include "IRecomendacion.h"

class RecomendacionContexto {
private:
    IRecomendacion* estrategia;

public:
    RecomendacionContexto();
    ~RecomendacionContexto();

    void setEstrategia(IRecomendacion* nueva);
    std::vector<Recurso*> recomendar(const std::vector<Recurso*>& recursos) const;
};

#endif
