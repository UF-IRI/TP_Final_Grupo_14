#pragma once
#include <string>
#include <iostream>
using namespace std;

//enum Estado {
//	SANO, INTERNADO, DIFUNTO
//}eEstado;


struct fecha
{
	tm fecha;
};
typedef struct fecha Fecha;

struct contacto
{

	string  telefono;
	string email;
	string direccion;
	string dni_pac;
	string celular;
};
typedef struct contacto Contacto;
struct medico
{
	string nombre;
	string apellido;
	string telefono;
	string especialidad;
	bool activo;
	string matricula;

};
typedef struct medico Medico;

struct ultimaConsulta
{
	//dni_pac, fecha_solicitado, fecha_turno, presento, matricula_med
	Fecha consulta;  //fecha_solicitado
	Fecha fecha_turno;
	bool presento;
	string matricula_med;
	string dni_pac;


	Medico medicoAsignado;
	string medico;
};
typedef struct ultimaConsulta ultConsulta;


struct paciente
{
	//dni, nombre, apellido, sexo, natalicio, estado, obra_social

	string dni;
	string nombre;
	string apellido;
	string sexo;
	Fecha nacimiento;
	string estado;
	string obra_social;

	Contacto cont;
	ultConsulta consulta;
	bool asistencia;
	bool retorno;
	string archivado;
	//string id;


};
typedef struct paciente Paciente;
