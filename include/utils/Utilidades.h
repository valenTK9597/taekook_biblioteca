#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <string>

// Fecha
std::string obtenerFechaActual();
bool esFormatoFechaValido(const std::string& fecha);
int calcularDiasRetraso(const std::string& fechaLimite, const std::string& fechaActual);
int calcularDiasEntre(const std::string& fecha1, const std::string& fecha2);

// Validaciones
bool canalValido(const std::string& canal);

#endif
