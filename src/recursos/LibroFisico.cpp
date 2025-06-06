#include "../../include/recursos/LibroFisico.h"

LibroFisico::LibroFisico(std::string id, std::string titulo, std::string autor, int anio, bool disponible)
    : Recurso(id, titulo, autor, anio, disponible) {}

void LibroFisico::registrar() const {
    std::cout << "Libro fisico registrado: " << titulo << std::endl;
}

double LibroFisico::calcularMulta(int diasRetraso) const {
    return diasRetraso * 1.0; // $1 por día de retraso
}

std::string LibroFisico::getTipo() const {
    return "LibroFisico";
}

void LibroFisico::mostrarInformacion() const {
    std::cout << " - Libro Fisico:" << std::endl;
    std::cout << " - ID: " << id << std::endl;
    std::cout << " - Titulo: " << titulo << std::endl;
    std::cout << " - Autor: " << autor << std::endl;
    std::cout << " - Anio: " << anioPublicacion << std::endl;
    std::cout << " - Disponible: " << (disponible ? "Sí" : "No") << std::endl;
}
