#include "../../include/recursos/Articulo.h"

Articulo::Articulo(std::string id, std::string titulo, std::string autor, int anio, bool disponible)
    : Recurso(id, titulo, autor, anio, disponible) {}

void Articulo::registrar() const {
    std::cout << "📄 Artículo registrado: " << titulo << std::endl;
}

double Articulo::calcularMulta(int diasRetraso) const {
    return diasRetraso * 0.25; // $0.25 por día de retraso (muy bajo)
}

std::string Articulo::getTipo() const {
    return "Articulo";
}

void Articulo::mostrarInformacion() const {
    std::cout << " - Artículo:" << std::endl;
    std::cout << " - ID: " << id << std::endl;
    std::cout << " - Título: " << titulo << std::endl;
    std::cout << " - Autor: " << autor << std::endl;
    std::cout << " - Año: " << anioPublicacion << std::endl;
    std::cout << " - Disponible: " << (disponible ? "Sí" : "No") << std::endl;
}
