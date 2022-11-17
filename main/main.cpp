#include "iri.cpp"
#include <iostream>
#include <fstream>
#include "funciones.h"
#include <string>
using namespace std;
int main() {

    //Inicio de programa, declaro los archivos y los abro archivos
    fstream ArchivoConsul;
    fstream ArchivoContact;
    fstream ArchivoMedicos;
    fstream ArchivoPacientes;

    ArchivoConsul.open("Consultas.csv", ios::app);
    ArchivoContact.open("Contactos.csv", ios::app);
    ArchivoMedicos.open("Medicos.csv", ios::app);
    ArchivoPacientes.open("Pacientes.csv", ios::app);

    //creamos variables para agregarles a las funciones
    Contacto contacto;
    //18902837 , +54(801)04193744 , +54(176)68420326 , Nebraska , MelodieMercier1@nowhere.com
    contacto.telefono = "+54(176)68965726";
    contacto.celular = "+54(801)69562142";
    contacto.dni_pac = "89754335";
    contacto.direccion = "Nebraska";
    contacto.email = "so.guerrapazos@nowhere.com";

    ultimaConsulta consulta;
   // 43963883, 14 / 5 / 1987, 30 / 7 / 1987, 0, 11 - 089 - 2367
    consulta.dni_pac = "45321333";
    consulta.consulta.fecha.tm_mday = 13;
    consulta.consulta.fecha.tm_mon = 7;
    consulta.consulta.fecha.tm_year = 1990;
    consulta.fecha_turno.fecha.tm_mday = 11;
    consulta.fecha_turno.fecha.tm_mon = 9;
    consulta.fecha_turno.fecha.tm_year = 1990;
    consulta.presento = true;
    consulta.matricula_med = "11 - 333 - 4567";

    medico medico;
    //matricula, nombre, apellido, telefono, especialidad, activo
    //03-957-5455 , Jacinta , Ralston , +54(929)89112253 , geriatria , 0
    medico.matricula = "05-233-6654";
    medico.nombre = "Jazmin";
    medico.apellido = "Ijurco";
    medico.telefono = "+54(249)4576850";
    medico.especialidad = "pediatria";
    medico.activo = true;

    paciente paciente;
    /*dni, nombre, apellido, sexo, natalicio, estado, obra_social
     10242582, Cersty, Thurston, F, 9 / 6 / 1970, internado, Medicus*/
    paciente.dni = "45493432";
    paciente.nombre = "Juan";
    paciente.apellido = "Almada";
    paciente.sexo = "F";
    paciente.nacimiento.fecha.tm_mday = 29;
    paciente.nacimiento.fecha.tm_mon = 9;
    paciente.nacimiento.fecha.tm_year = 2003;
    paciente.estado = "internado";
    paciente.obra_social = "Galeno";





    guardararchivocontacto(ArchivoContact, contacto);

    return EXIT_SUCCESS;
}

