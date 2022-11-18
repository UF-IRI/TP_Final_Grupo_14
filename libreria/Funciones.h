#pragma once
#include <time.h>
#include "glob.h"
#include <fstream>

bool chequearfechas(ultConsulta Consulta);
void guardararchivo(fstream& archivo, Paciente* pac);
bool informarsecretaria(Paciente& pac, fstream& Archivados, fstream &Archivocontactos);
paciente buscarPaciente(ifstream& Archivocompleto, string _id);
void guardararchivocontacto(fstream &Archivo, contacto Contacto);
void guardarmedicos(fstream& Archivo, medico medico);
void recuperarPaciente(ifstream& ArchivoConsultas, ifstream& ArchivoCompleto, fstream& Archivados, fstream& ArchivoPacientes, fstream& Archivocontactos);
void resizecontacto(Contacto*& vector, int* n);
bool vincularcontacto(Paciente pac, fstream& Archivocontactos);
bool archivarmedico(fstream& archivomedicoslistados, Paciente pac, fstream& archivo,fstream& consultas);
void resizeConsultas(ultimaConsulta*& vector, int* n);
void resizeMedico(Medico*& vector, int* n);
ultConsulta chequearUltFechaConsulta(Paciente pac, ifstream& ArchConsultas);

