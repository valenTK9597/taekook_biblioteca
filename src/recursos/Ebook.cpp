#include "../../include/recursos/Ebook.h"

Ebook::Ebook(std::string id, std::string titulo, std::string autor, int anio, bool disponible)
    : Recurso(id, titulo, autor, anio, disponible) {}

void Ebook::registrar() const {
    std::cout << " Ebook registrado: " << titulo << std::endl;
}

double Ebook::calcularMulta(int diasRetraso) const {
    return diasRetraso * 0.5; // $0.5 por día de retraso (menor al libro físico)
}

std::string Ebook::getTipo() const {
    return "Ebook";
}

void Ebook::mostrarInformacion() const {
    std::cout << " - Ebook:" << std::endl;
    std::cout << " - ID: " << id << std::endl;
    std::cout << " - Título: " << titulo << std::endl;
    std::cout << " - Autor: " << autor << std::endl;
    std::cout << " - Año: " << anioPublicacion << std::endl;
    std::cout << " - Disponible: " << (disponible ? "Sí" : "No") << std::endl;
}
