#include "../../include/prestamos/EstadoDevuelto.h"
#include "../../include/prestamos/Prestamo.h"
#include <iostream>

std::string EstadoDevuelto::getNombre() const {
    return "Devuelto";
}

double EstadoDevuelto::calcularMulta(const Prestamo* /*prestamo*/, const std::string& /*fechaActual*/) const {
    return 0.0; // No aplica multa si ya fue devuelto
}

void EstadoDevuelto::mostrarEstado() const {
    std::cout << " Estado actual: Devuelto (finalizado)\n";
}
