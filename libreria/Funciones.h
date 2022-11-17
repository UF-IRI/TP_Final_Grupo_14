#pragma once
#include <time.h>
#include <glob.h>
#include <fstream>
bool chequearfechas(ultConsulta* Consulta);
void guardararchivo(string nombrearchivo, Paciente* pac);
void informarsecretaria(Paciente& pac);
paciente& buscarPaciente(string ArchivoCompleto, string _id);
void guardararchivocontacto(string nombrearchivo, contacto cont);
void guardarmedicos(string nombrearchivo, medico medico);

