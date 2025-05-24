#include "../../include/recursos/Revista.h"

Revista::Revista(std::string id, std::string titulo, std::string autor, int anio, bool disponible)
    : Recurso(id, titulo, autor, anio, disponible) {}

void Revista::registrar() const {
    std::cout << "📰 Revista registrada: " << titulo << std::endl;
}

double Revista::calcularMulta(int diasRetraso) const {
    return diasRetraso * 0.75; // $0.75 por día de retraso
}

std::string Revista::getTipo() const {
    return "Revista";
}

void Revista::mostrarInformacion() const {
    std::cout << "📰 Revista:" << std::endl;
    std::cout << " - ID: " << id << std::endl;
    std::cout << " - Título: " << titulo << std::endl;
    std::cout << " - Autor: " << autor << std::endl;
    std::cout << " - Año: " << anioPublicacion << std::endl;
    std::cout << " - Disponible: " << (disponible ? "Sí" : "No") << std::endl;
}
