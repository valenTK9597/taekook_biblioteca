#include "../../include/recomendaciones/ModuloRecomendaciones.h"
#include "../../include/busqueda/ModuloBusqueda.h"
#include "../../include/recomendaciones/RecomendacionParaEstudiantes.h"
#include "../../include/recomendaciones/RecomendacionParaProfesores.h"
#include "../../include/recomendaciones/RecomendacionPorTipo.h"
#include "../../include/recursos/RecursoFactory.h"
#include "../../include/prestamos/ModuloPrestamos.h"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iomanip> 




namespace fs = std::filesystem;

ModuloRecomendaciones::ModuloRecomendaciones(const std::string& recursos, const std::string& prestamos, const std::string& usuarios)
    : rutaRecursos(recursos), rutaPrestamos(prestamos), rutaUsuarios(usuarios), buscador(recursos) {}


// 🧾 Leer solo IDs del historial
std::vector<std::string> ModuloRecomendaciones::leerIdsHistorial(const std::string& usuarioId) {
    std::vector<std::string> ids;
    std::string ruta = "data/historiales/historial_" + usuarioId + ".txt";  // CORREGIDO
    std::ifstream archivo(ruta);

    if (!archivo.is_open()) {
        std::cerr << " ⚠️ No se encontró historial para el usuario: " << usuarioId << "\n";
        return ids;  // Retorna lista vacía pero NO crea ningún archivo
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        // Extraer solo el ID entre corchetes, si existe
        size_t inicio = linea.find("[");
        size_t fin = linea.find("]");
        if (inicio != std::string::npos && fin != std::string::npos && fin > inicio) {
            std::string id = linea.substr(inicio + 1, fin - inicio - 1);
            ids.push_back(id);
        }
    }

    return ids;
}

std::map<std::string, int> ModuloRecomendaciones::contarTiposDesdeHistorial(const std::string& usuarioId) {
    std::map<std::string, int> conteo;
    std::string ruta = "data/historiales/historial_" + usuarioId + ".txt";
    std::ifstream archivo(ruta);

    if (!archivo.is_open()) {
        std::cerr << "⚠️ No se pudo abrir el historial del usuario: " << usuarioId << "\n";
        return conteo;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        size_t posTipo = linea.find("Tipo:");
        if (posTipo != std::string::npos) {
            std::string tipo = linea.substr(posTipo + 5); // 5 = strlen("Tipo:")
            tipo.erase(0, tipo.find_first_not_of(" "));   // Eliminar espacio inicial si existe
            conteo[tipo]++;
        }
    }

    return conteo;
}

// Función para convertir una cadena a minúsculas
std::string toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

std::string ModuloRecomendaciones::obtenerIdDesdeNombre(const std::string& nombreUsuario) {
    std::ifstream archivo("data/usuarios.txt");
    std::string linea;

    if (!archivo.is_open()) {
        std::cerr << "❌ No se pudo abrir el archivo de usuarios.\n";
        return "";
    }

    std::string nombreUsuarioLower = toLower(nombreUsuario);  // Convertir a minúsculas

    while (std::getline(archivo, linea)) {
        std::istringstream ss(linea);
        std::string id, nombre, correo, clave, tipo;

        std::getline(ss, id, '|');
        std::getline(ss, nombre, '|');
        std::getline(ss, correo, '|');
        std::getline(ss, clave, '|');
        std::getline(ss, tipo, '|');

        // Eliminar espacios sobrantes
        nombre.erase(0, nombre.find_first_not_of(" "));
        nombre.erase(nombre.find_last_not_of(" ") + 1);

        // Eliminar espacios intermedios
        nombre.erase(std::remove_if(nombre.begin(), nombre.end(), ::isspace), nombre.end());

        // Comparación sin tener en cuenta mayúsculas/minúsculas
        if (toLower(nombre) == nombreUsuarioLower) {
            return id;
        }
    }

    return ""; // No se encontró
}


// 👤 Recomendación por tipo de usuario (usa historial o recursos totales)
void ModuloRecomendaciones::recomendarPorTipoUsuario(const std::string& nombreUsuario, const std::string& tipoUsuario) {
    std::vector<std::string> idsHistorial = leerIdsHistorial(nombreUsuario);
    std::vector<Recurso*> recursos;

    if (!idsHistorial.empty()) {
        for (const std::string& id : idsHistorial) {
            Recurso* r = RecursoFactory::buscarRecursoPorId(id);
            if (r) recursos.push_back(r);
        }
    } else {
        std::cout << "No hay historial. Se usarán todos los recursos del sistema.\n";
        recursos = RecursoFactory::leerRecursosDesdeArchivo("data/recursos.txt");
    }

    RecomendacionContexto contexto;
    if (tipoUsuario == "Estudiante") {
        contexto.setEstrategia(new RecomendacionParaEstudiantes());
    } else if (tipoUsuario == "Profesor") {
        contexto.setEstrategia(new RecomendacionParaProfesores());
    } else {
        std::cout << "Tipo de usuario no reconocido.\n";
        return;
    }

    std::vector<Recurso*> recomendados = contexto.recomendar(recursos);
    std::cout << "\n📚 Recursos recomendados para " << tipoUsuario << ":\n";
    for (Recurso* r : recomendados) {
        std::cout << "- [" << r->getId() << "] " << r->getTitulo() << " (" << r->getTipo() << ")\n";
    }

    for (Recurso* r : recursos) delete r;
}

// 📂 Recomendación por tipo específico
void ModuloRecomendaciones::recomendarPorTipoRecurso(const std::string& tipo) {
    std::vector<Recurso*> recursos = RecursoFactory::leerRecursosDesdeArchivo("data/recursos.txt");

    RecomendacionContexto contexto;
    contexto.setEstrategia(new RecomendacionPorTipo(tipo));

    std::vector<Recurso*> recomendados = contexto.recomendar(recursos);
    std::cout << "\n📂 Recursos del tipo '" << tipo << "':\n";
    for (Recurso* r : recomendados) {
        std::cout << "- [" << r->getId() << "] " << r->getTitulo() << " (" << r->getTipo() << ")\n";
    }

    for (Recurso* r : recursos) delete r;
}

void ModuloRecomendaciones::recomendarPorPreferenciaDetectada(const std::string& nombreUsuario) {
    std::string idUsuario = obtenerIdDesdeNombre(nombreUsuario);

    if (idUsuario.empty()) {
        std::cerr << "❌ No se encontró el ID para el usuario: " << nombreUsuario << "\n";
        return;
    }

    std::string ruta = "data/historiales/historial_" + idUsuario + ".txt";

    std::cerr << "[DEBUG] ID obtenido: '" << idUsuario << "'\n";
    std::cerr << "[DEBUG] Ruta generada: '" << ruta << "'\n";

    if (!std::filesystem::exists(ruta)) {
        std::cerr << "❌ Archivo NO existe según std::filesystem::exists().\n";
        return;
    }

    std::map<std::string, int> conteo = contarTiposDesdeHistorial(idUsuario);

    if (conteo.empty()) {
        std::cout << "⚠️ No hay historial para detectar preferencias.\n";
        return;
    }

    // Detectar tipo más frecuente
    std::string preferido = "";
    int max = 0;
    for (const auto& par : conteo) {
        if (par.second > max) {
            preferido = par.first;
            max = par.second;
        }
    }

    if (!preferido.empty()) {
        std::cout << "📌 Tipo de recurso preferido detectado: " << preferido << "\n";
        recomendarPorTipoRecurso(preferido);
    } else {
        std::cout << "❌ No se detectaron preferencias claras.\n";
    }
}


void ModuloRecomendaciones::mostrarSubmenuRecomendaciones(const std::string& nombreUsuario, const std::string& tipoUsuario) {
    int opcion;

    do {
        std::cout << "\n📌 SUBMENÚ DE RECOMENDACIONES 📌\n";
        std::cout << "1. Recomendaciones según tu tipo de usuario (" << tipoUsuario << ")\n";
        std::cout << "2. Recomendaciones por tipo específico (libro, revista, etc.)\n";
        std::cout << "3. Recomendaciones según tus preferencias detectadas\n";
        std::cout << "4. Volver al menú anterior\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
            case 1:
                recomendarPorTipoUsuario(nombreUsuario, tipoUsuario);
                break;

            case 2: {
                std::string tipo;
                std::cout << "Ingrese el tipo de recurso (LibroFisico, Revista, Articulo, Ebook): ";
                std::getline(std::cin, tipo);
                recomendarPorTipoRecurso(tipo);
                break;
            }
            case 3:
                recomendarPorPreferenciaDetectada(nombreUsuario);
                break;
            case 4:
                std::cout << "Regresando a menú principal.\n";
                opcion = false; // Para salir del bucle
                break;
            default:
                std::cout << " Opción inválida. Intente nuevamente.\n";
                break;
        }
    } while (opcion != 0);
}


