#pragma once
#include <time.h>
#include "glob.h"
#include <fstream>

bool chequearfechas(ultConsulta* Consulta);
void guardararchivo(fstream& archivo, Paciente* pac);
void informarsecretaria(Paciente& pac, fstream& Archivados, fstream Archivocontactos);
paciente& buscarPaciente(ifstream Archivocompleto, string _id);
void guardararchivocontacto(fstream &Archivo, contacto Contacto);
void guardarmedicos(fstream& Archivo, medico medico);
void recuperarPaciente(ifstream ArchivoConsultas, ifstream ArchivoCompleto, fstream& Archivados, fstream& ArchivoPacientes);
void resizecontacto(Contacto*& vector, int* n);
