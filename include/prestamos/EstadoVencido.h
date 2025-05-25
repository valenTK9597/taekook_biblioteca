#ifndef ESTADOVENCIDO_H
#define ESTADOVENCIDO_H

#include "EstadoPrestamo.h"

class EstadoVencido : public EstadoPrestamo {
public:
    std::string getNombre() const override;
    double calcularMulta(const Prestamo* prestamo, const std::string& fechaActual) const override;
    void mostrarEstado() const override;
};

#endif
