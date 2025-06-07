#include "utils/Utilidades.h"
#include <ctime>
#include <iomanip>
#include <sstream>

// Obtener fecha actual en formato YYYY-MM-DD
std::string obtenerFechaActual() {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", now);
    return std::string(buffer);
}

bool esFormatoFechaValido(const std::string& fecha) {
    std::tm tmFecha = {};
    std::istringstream ss(fecha);
    ss >> std::get_time(&tmFecha, "%Y-%m-%d");
    return !ss.fail();
}

// Calcular días de retraso entre dos fechas
int calcularDiasRetraso(const std::string& fechaLimite, const std::string& fechaActual) {
    std::tm tmLimite = {}, tmActual = {};
    std::istringstream ss1(fechaLimite);
    std::istringstream ss2(fechaActual);

    ss1 >> std::get_time(&tmLimite, "%Y-%m-%d");
    ss2 >> std::get_time(&tmActual, "%Y-%m-%d");

    std::time_t timeLimite = std::mktime(&tmLimite);
    std::time_t timeActual = std::mktime(&tmActual);

    double segundos = std::difftime(timeActual, timeLimite);
    return static_cast<int>(segundos / (60 * 60 * 24));
}

// Calcular días entre dos fechas cualquiera
int calcularDiasEntre(const std::string& fecha1, const std::string& fecha2) {
    std::tm tm1 = {}, tm2 = {};
    std::istringstream ss1(fecha1), ss2(fecha2);
    ss1 >> std::get_time(&tm1, "%Y-%m-%d");
    ss2 >> std::get_time(&tm2, "%Y-%m-%d");

    time_t t1 = std::mktime(&tm1);
    time_t t2 = std::mktime(&tm2);
    return static_cast<int>(std::difftime(t2, t1) / (60 * 60 * 24));
}

// Validar canal
bool canalValido(const std::string& canal) {
    return canal == "app" || canal == "email" || canal == "sms";
}
