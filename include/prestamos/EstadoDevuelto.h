#ifndef ESTADODEVUELTO_H
#define ESTADODEVUELTO_H

#include "EstadoPrestamo.h"

class EstadoDevuelto : public EstadoPrestamo {
public:
    std::string getNombre() const override;
    double calcularMulta(const Prestamo* prestamo, const std::string& fechaActual) const override;
    void mostrarEstado() const override;
};

#endif
