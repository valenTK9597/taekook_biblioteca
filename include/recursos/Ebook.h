#ifndef EBOOK_H
#define EBOOK_H

#include "Recurso.h"

class Ebook : public Recurso {
public:
    Ebook(std::string id, std::string titulo, std::string autor, int anio, bool disponible = true);

    void registrar() const override;
    double calcularMulta(int diasRetraso) const override;
    std::string getTipo() const override;
    void mostrarInformacion() const override;
};

#endif
