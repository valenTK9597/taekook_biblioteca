#include "../../include/prestamos/EstadoDisponible.h"
#include "../../include/prestamos/Prestamo.h"
#include <iostream>

std::string EstadoDisponible::getNombre() const {
    return "Disponible";
}

double EstadoDisponible::calcularMulta(const Prestamo* /*prestamo*/, const std::string& /*fechaActual*/) const {
    return 0.0;  // Aún no ha sido prestado, no aplica multa
}

void EstadoDisponible::mostrarEstado() const {
    std::cout << " Estado actual: Disponible (esperando ser prestado)\n";
}
