#pragma once
#include <string>
#include <iostream>
//#define Archivados "Archivados.csv" //van los que no retornan
//#define HistoriasClinicas ".../data_files/input/IRI_Pacientes.csv" // todos los que alguna vez se atendieron en el sanatorio
//#define Contacto ".../data_files/input/IRI_Contactos.csv" // datos para ccontactar cada paciente
//#define Consultas ".../data_files/input/IRI_Consultas.csv" //toda las ultimas consultas de todos los pacientes
//#define Medicos  ".../data_files/input/IRI_Medicos.csv" // archivo  con todos los medicos
//#define Actuales "Actuales.csv" // donde guardaremos los pacientes que se seguiran atendiendo en el hospital
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
