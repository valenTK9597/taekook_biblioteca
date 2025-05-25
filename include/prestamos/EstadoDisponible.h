#ifndef ESTADODISPONIBLE_H
#define ESTADODISPONIBLE_H

#include "EstadoPrestamo.h"

class EstadoDisponible : public EstadoPrestamo {
public:
    std::string getNombre() const override;
    double calcularMulta(const Prestamo* prestamo, const std::string& fechaActual) const override;
    void mostrarEstado() const override;
};

#endif
