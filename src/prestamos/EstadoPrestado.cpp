#include "../../include/prestamos/EstadoPrestado.h"
#include "../../include/prestamos/Prestamo.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>

std::string EstadoPrestado::getNombre() const {
    return "Prestado";
}

double EstadoPrestado::calcularMulta(const Prestamo* prestamo, const std::string& fechaActual) const {
    std::tm fechaDev = {};
    std::tm fechaAct = {};

    std::istringstream ssDev(prestamo->getFechaDevolucion());
    std::istringstream ssAct(fechaActual);

    ssDev >> std::get_time(&fechaDev, "%Y-%m-%d");
    ssAct >> std::get_time(&fechaAct, "%Y-%m-%d");

    std::time_t tDev = std::mktime(&fechaDev);
    std::time_t tAct = std::mktime(&fechaAct);

    double diasRetraso = std::difftime(tAct, tDev) / (60 * 60 * 24);

    return (diasRetraso > 0) ? diasRetraso * 1.0 : 0.0; // 1 unidad por día
}

void EstadoPrestado::mostrarEstado() const {
    std::cout << " Estado actual: Prestado (en curso)\n";
}
