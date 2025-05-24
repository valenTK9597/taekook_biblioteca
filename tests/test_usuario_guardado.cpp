#include <iostream>
#include "../include/usuarios/UsuarioFactory.h"

int main() {
    std::string archivo = "data/usuarios.txt";

    // Verificar si ya existe el correo antes de registrar
    if (!UsuarioFactory::correoExistente("jisoo@uni.edu", archivo)) {
        Usuario* nueva = UsuarioFactory::crearUsuario("Estudiante", "E02", "Jisoo", "jisoo@uni.edu", "blackpink");
        UsuarioFactory::guardarUsuarioEnArchivo(nueva, archivo);
        std::cout << "✅ Usuario registrado correctamente.\n";
        delete nueva;
    } else {
        std::cout << "⚠️ El correo ya está registrado.\n";
    }

    // Mostrar todos los usuarios cargados desde el archivo
    std::vector<Usuario*> lista = UsuarioFactory::cargarUsuariosDesdeArchivo(archivo);
    for (Usuario* usr : lista) {
        usr->mostrarInformacion();
        delete usr;
    }

    return 0;
}
