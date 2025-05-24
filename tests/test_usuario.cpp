#include <iostream>
#include "../include/usuarios/UsuarioFactory.h"
#include "../include/usuarios/Estudiante.h"
#include "../include/usuarios/Profesor.h"
#include "../include/usuarios/Administrador.h"

int main() {
    Usuario* u1 = UsuarioFactory::crearUsuario("Estudiante", "E01", "Valentina", "valen@uni.edu", "1234");
    Usuario* u2 = UsuarioFactory::crearUsuario("Profesor", "P01", "Kim Taehyung", "tae@uni.edu", "abcd");
    Usuario* u3 = UsuarioFactory::crearUsuario("Administrador", "A01", "Jungkook", "jk@uni.edu", "admin");

    if (u1) u1->mostrarInformacion();
    if (u2) u2->mostrarInformacion();
    if (u3) u3->mostrarInformacion();

    delete u1;
    delete u2;
    delete u3;

    return 0;
}

