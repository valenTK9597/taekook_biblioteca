#include "../../include/recursos/Recurso.h"

Recurso::Recurso(std::string id, std::string titulo, std::string autor, int anio, bool disponible)
    : id(id), titulo(titulo), autor(autor), anioPublicacion(anio), disponible(disponible) {}

std::string Recurso::getId() const { return id; }
std::string Recurso::getTitulo() const { return titulo; }
std::string Recurso::getAutor() const { return autor; }
int Recurso::getAnioPublicacion() const { return anioPublicacion; }
bool Recurso::estaDisponible() const { return disponible; }

void Recurso::setTitulo(const std::string& t) { titulo = t; }
void Recurso::setAutor(const std::string& a) { autor = a; }
void Recurso::setAnioPublicacion(int anio) { anioPublicacion = anio; }
void Recurso::setDisponible(bool d) { disponible = d; }
