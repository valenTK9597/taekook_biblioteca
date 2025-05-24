#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <iostream>

class Usuario {
protected:
    std::string id;
    std::string nombre;
    std::string correo;
    std::string contrasena;

public:
    Usuario(std::string id, std::string nombre, std::string correo, std::string contrasena);
    virtual ~Usuario() = default;

    std::string getId() const;
    std::string getNombre() const;
    std::string getCorreo() const;
    std::string getContrasena() const;

    void setNombre(const std::string& n);
    void setCorreo(const std::string& c);
    void setContrasena(const std::string& c);

    virtual std::string getTipo() const = 0;
    virtual void mostrarInformacion() const = 0;
};

#endif
