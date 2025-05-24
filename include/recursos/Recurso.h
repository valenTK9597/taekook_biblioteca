#ifndef RECURSO_H
#define RECURSO_H

#include <string>
#include <iostream>

class Recurso {
protected:
    std::string id;
    std::string titulo;
    std::string autor;
    int anioPublicacion;
    bool disponible;

public:
    Recurso(std::string id, std::string titulo, std::string autor, int anio, bool disponible = true);
    virtual ~Recurso() = default;

    std::string getId() const;
    std::string getTitulo() const;
    std::string getAutor() const;
    int getAnioPublicacion() const;
    bool estaDisponible() const;

    void setTitulo(const std::string& t);
    void setAutor(const std::string& a);
    void setAnioPublicacion(int anio);
    void setDisponible(bool d);

    virtual void registrar() const = 0;
    virtual double calcularMulta(int diasRetraso) const = 0;
    virtual std::string getTipo() const = 0;
    virtual void mostrarInformacion() const = 0;
};

#endif
