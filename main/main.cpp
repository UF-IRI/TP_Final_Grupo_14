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

    fstream Archivados;

    ArchivoConsul.open("Consultas.csv", ios::app);
    ArchivoContact.open("Contactos.csv", ios::app);
    ArchivoMedicos.open("Medicos.csv", ios::app);
    ArchivoPacientes.open("Pacientes.csv", ios::app);
    Archivados.open("Archivados.csv", ios::app);
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

    Paciente pac1;
    pac1.dni = "45493432";
    pac1.nombre = "Juan";
    pac1.apellido = "Almada";
    pac1.sexo = "F";
    pac1.nacimiento.fecha.tm_mday = 29;
    pac1.nacimiento.fecha.tm_mon = 9;
    pac1.nacimiento.fecha.tm_year = 2003;
    pac1.estado = "internado";
    pac1.obra_social = "Galeno";

    Paciente pac2;
    pac2.dni = "45445367";
    pac2.nombre = "Jazmin";
    pac2.apellido = "Izjurjo";
    pac2.sexo = "F";
    pac2.nacimiento.fecha.tm_mday = 3;
    pac2.nacimiento.fecha.tm_mon = 5;
    pac2.nacimiento.fecha.tm_year = 2002;
    pac2.estado = "internado";
    pac2.obra_social = "Medicus";

    Paciente pac3;
    pac3.dni = "46754675";
    pac3.nombre = "Isabella";
    pac3.apellido = "Dionesalvi";
    pac3.sexo = "F";
    pac3.nacimiento.fecha.tm_mday = 5;
    pac3.nacimiento.fecha.tm_mon = 10;
    pac3.nacimiento.fecha.tm_year = 2003;
    pac3.estado = "difunto";
    pac3.obra_social = "Italiano";

    Paciente pac4;
    pac3.dni = "43527465";
    pac3.nombre = "Sofia";
    pac3.apellido = "Guerra";
    pac3.sexo = "F";
    pac3.nacimiento.fecha.tm_mday = 3;
    pac3.nacimiento.fecha.tm_mon = 9;
    pac3.nacimiento.fecha.tm_year = 2002;
    pac3.estado = "n/c";
    pac3.obra_social = "Italiano";

    guardararchivo(Archivados, pac1);
    guardararchivo(Archivados, pac2);
    guardararchivo(Archivados, pac3);
    guardararchivo(Archivados, pac4);

    //guardararchivo(ArchivoPacientes, &paciente);
    guardararchivocontacto(ArchivoContact, contacto);
    guardarmedicos(ArchivoMedicos, medico);

    ultimaConsulta consulaux;
    Paciente pacaux;

    recuperarPaciente(ArchivoConsul, Archivados, ArchivoPacientes, ArchivoContact,ArchivoContact);
    bool resul1 = false;
    bool resul2 = false;
    bool resul3 = false;
    resul1 = vincularcontacto(pac1, Archivados);
    resul2 = archivarmedico(ArchivoMedicos, pac2, Archivados, ArchivoConsul);
    resul3 = informarsecretaria(pac3, Archivados, ArchivoContact,ArchivoPacientes);

    ArchivoConsul.close();
    ArchivoContact.close();
    ArchivoMedicos.close();
    ArchivoPacientes.close();
    Archivados.close();
    return EXIT_SUCCESS;
}
