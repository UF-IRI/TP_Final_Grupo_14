#define _CRT_SECURE_NO_WARNINGS
#include "Funciones.h"
#include <string>

bool chequearfechas(ultConsulta* Consulta)
{
    time_t auxiliar_fecha = time(0);
    tm* hoy = localtime(&auxiliar_fecha);
    tm fecha_hoy;
    fecha_hoy.tm_mday = hoy->tm_mday;
    fecha_hoy.tm_mon = hoy->tm_mon;
    fecha_hoy.tm_year = hoy->tm_year;
    int dif = 0;//

    time_t aux_fin = mktime(&fecha_hoy);
    time_t aux_inicio = mktime(&(Consulta->consulta.fecha));

    dif = difftime(aux_fin, aux_inicio) / (31536000); //calculo la diferencia de tiempo en segundos y lo transformamos a anios

    if (dif > 10)
        return false;
    else
        return true;

}
void guardararchivo(fstream& archivo, Paciente* pac)
{
    
    string aux;

    if (archivo.is_open())
    {
        getline(archivo, aux);

        if (aux == "\0") //si en la primer linea no hay nada,tengo que poner el encabezad
        {
            archivo << "Dni" << ',' << "Nombre" << ',' << "Apellido" << ',' << "Sexo" << ',' << "Natalicio" << ',' << "Estado" << ',' << "id" << endl;
        }
        else
        {
            archivo << pac->nombre << ',' << pac->apellido << ',' << pac->sexo << ',' << pac->nacimiento.fecha.tm_mday << '/' << pac->nacimiento.fecha.tm_mon << '/' << pac->nacimiento.fecha.tm_year << '/' << pac->estado << ',' << pac->dni << endl; //todo preguntar
        }
    }
    archivo.close();

}


paciente& buscarPaciente(ifstream Archivocompleto, string _id) {
    string coma = ",";
    string barra = "/";
    paciente aux;
    paciente aux1;
    while (Archivocompleto)
    {


        Archivocompleto >> aux.dni >> coma >> aux.nombre >> coma >> aux.apellido >> coma >> aux.estado >> coma >> aux.dni >> coma >> aux.sexo >> coma >> aux.nacimiento.fecha.tm_mday >> barra >> aux.nacimiento.fecha.tm_mon >> barra >> aux.nacimiento.fecha.tm_year;
        if (aux.dni == _id)
        {
            aux1 = aux;
        }
        else
        {
            aux.dni = "404";
            return aux;
        }
    }
    return aux1;

}
void recuperarPaciente(ifstream ArchivoConsultas, ifstream ArchivoCompleto, fstream& Archivados, fstream& ArchivoPacientes) {
    ultimaConsulta aux;
    char coma = ',';
    char barra = '/';
    string encabezado;
    ArchivoConsultas >> encabezado >> coma >> encabezado >> barra >> encabezado >> barra >> encabezado >> barra >> encabezado >> barra >> encabezado >> barra >> encabezado >> barra >> encabezado >> coma >> encabezado;//todo ver
    ArchivoConsultas >> aux.dni_pac >> coma >> aux.consulta.fecha.tm_mday >> barra >> aux.consulta.fecha.tm_mon >> barra >> aux.consulta.fecha.tm_year >> barra >> aux.fecha_turno.fecha.tm_mday >> barra >> aux.fecha_turno.fecha.tm_mon >> barra >> aux.fecha_turno.fecha.tm_year >> barra >> aux.presento >> coma >> aux.matricula_med;
    paciente* Pac = &buscarPaciente(ArchivoCompleto, aux.dni_pac);
    if (Pac->dni == "404") //si el paciente esta vacio quiere decir q no lo encontre, aca hay q ver tema punteros.
    {
        cout << "No se encontro el paciente" << endl;
    }
    else if (chequearfechas(&aux) == true && Pac->asistencia == false) {
        if (Pac->estado == "DIFUNTO") {
            Pac->archivado = "Archivado";
            guardararchivo(Archivados, Pac); //lo mando al archivo q no se recuperan
        }
        else if (Pac->estado == "INTERNADO") {
            cout << "El paciente se encuentra internado " << endl;
            guardararchivo(ArchivoPacientes, Pac);
        }
        else {
            informarsecretaria(*Pac,); //se lo mando a secretaria para preguntarle al paciente si vuelve
            guardararchivo(ArchivoPacientes, Pac); // lo guardo para despues preguntar si vuelve
        }
    }// si pasaron menos de 10 años y no reprogramo puede volver
}

void informarsecretaria(Paciente& pac, fstream& Archivados, fstream Archivocontactos)
{
    int n = 0;
    Contacto* contactoaux = new Contacto[n];
    Contacto contact;
    string aux;
    string encabezado;
    char coma = ',';
    int i = 0;
    while (Archivocontactos) {
        if (i == 0)
        {
            Archivocontactos >> encabezado >> coma >> encabezado >> coma >> encabezado >> coma >> encabezado >> coma >> encabezado;
            i++;
        }
        else
        {
            Archivocontactos >> contactoaux[n].dni_pac >> coma >> contactoaux[n].telefono >> coma >> contactoaux[n].celular >> coma >> contactoaux[n].direccion >> coma >> contactoaux[n].email;
            resizecontacto(contactoaux, &n);
        }
    }
    for (int k = 0;k < n;k++) {
        if (contactoaux[k].dni_pac == pac.dni) {
            contact = contactoaux[k];
        }
    }

    cout << "Llamando al paciente: " << pac.nombre << pac.apellido << "Su numero es: " << contact.celular << endl;
    cout << "Vuelve";
    cin >> aux;
    if (aux == "si" || aux == "Si" || aux == "SI" || aux == "sI")
    {
        cout << "Vuelve el paciente";
        pac.retorno = true;
        cout << "ingrese su nueva obra social";
        if (pac.obra_social != aux)
        {
            pac.obra_social = aux;
        }
    }
    else
    {
        cout << "No vuelve el paciente";
        pac.archivado = "archivado";
        guardararchivo(Archivados, &pac);
    }
}
void guardararchivocontacto(fstream &Archivo, contacto Contacto)
{
    string aux;
    if (Archivo.is_open())
    {
        getline(Archivo, aux);

        if (aux == "\0") //si en la primer linea no hay nada,tengo que poner el encabezad
        {
            Archivo << "Dni" << "telefono" << "celular" << "direccion" << "mail" << endl;
        }
        else
        {
            Archivo << Contacto.dni_pac << Contacto.telefono << Contacto.celular << Contacto.direccion << Contacto.email << endl; //todo preguntar
        }
    }

}
void guardarmedicos(fstream &Archivo, medico medico)
{
    string aux;
    char coma = ',';
    if (Archivo.is_open())
    {
        getline(Archivo, aux);

        if (aux == "\0") //si en la primer linea no hay nada,tengo que poner el encabezad
        {
            Archivo << "matricula" << coma << "nombre" << coma << "apellido" << coma << "telefono" << coma << "especialidad" << coma << "activo" << endl;
        }
        else
        {
            Archivo << medico.matricula << coma << medico.nombre << coma << medico.apellido << coma << medico.telefono << coma << medico.especialidad << coma << medico.activo << endl; //todo preguntar
        }
    }
}
void resizecontacto(Contacto*& vector, int* n)
{
    *n = *(n)+1; //aumento en uno mi contador de tamanio
    Contacto* aux = new Contacto[*(n)]; //me hago un auxiliar con un nuevo tamanio

    for (int i = 0; i < *n - 1; i++) //es hasta n-1 ya que mi vector todavia tiene tamanio n
    {
        aux[i] = vector[i]; //copio las cosas en el auxiliar
    }
    delete[]vector; //libero la memoria de donde estaba vector

    vector = aux; //le asigno la nueva memoria
}