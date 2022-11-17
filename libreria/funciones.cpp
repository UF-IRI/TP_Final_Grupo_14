#include "Funciones.h"
#include <string>
#
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
void guardararchivo(string nombrearchivo, Paciente* pac)
{
    fstream archivo;
    string aux;
    archivo.open(nombrearchivo, ios::app);
    if (archivo.is_open())
    {
        getline(archivo, aux);

        if (aux == "\0") //si en la primer linea no hay nada,tengo que poner el encabezad
        {
            archivo << "Dni" << ',' << "Nombre" << ',' << "Apellido" << ',' << "Sexo" << ',' << "Natalicio" << ',' << "Estado" << ',' << "id" << endl;
        }
        else
        {
            archivo << pac->nombre << ',' << pac->apellido << ',' << pac->sexo << ',' << pac->nacimiento << ',' << pac->estado << ',' << pac->id << endl; //todo preguntar
        }
    }
    archivo.close();

}


paciente& buscarPaciente(string ArchivoCompleto, string _id) {
    string coma;
    paciente aux;
    paciente aux1;
    fstream miArchivo;
    miArchivo.open(ArchivoCompleto, ios::in);
    while (miArchivo)
    {
        dni, , , sexo, natalicio,

            miArchivo >> aux.id >> coma >> aux.nombre >> coma >> aux.apellido >> coma >> aux.estado >> coma >> aux.dni >> coma >> aux.sexo >> coma >> aux.natalicio;
        if (aux.id == _id)
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
void recuperarPaciente(ultimaConsulta consultaPaciente, ifstream ArchivoCompleto) {
    paciente* Pac = &buscarPaciente("ArchivoCompleto.csv", consultaPaciente.id);
    if (Pac->dni == "404") //si el paciente esta vacio quiere decir q no lo encontre, aca hay q ver tema punteros.
    {
        cout << "No se encontro el paciente" << endl;
    }
    else if (chequearfechas(&consultaPaciente) == true && Pac->asistencia == false) {
        if (Pac->estado == DIFUNTO) {
            Pac->archivado = "Archivado";
            guardararchivo("ArchivosArchivados.csv", Pac); //lo mando al archivo q no se recuperan
        }
        else if (Pac->estado == INTERNADO) {
            cout << "El paciente se encuentra internado " << endl;
            guardararchivo("ArchivoPac", Pac);
        }
        else {
            informarsecretaria(*Pac); //se lo mando a secretaria para preguntarle al paciente si vuelve
            guardararchivo("ArchivoPac.csv", Pac); // lo guardo para despues preguntar si vuelve
        }
    }// si pasaron menos de 10 años y no reprogramo puede volver
}
void informarsecretaria(Paciente& pac)
{
    string aux;
    cout << "Llamando al paciente: " << pac.nombre << pac.apellido << "Su numero es: " << pac.cont.telefono;
    cout << "Vuelve";
    cin >> aux;
    if (aux == "si" || aux == "Si" || aux == "SI" || aux == "sI")
    {
        cout << "VUelve el paciente";
        pac.retorno = true;
        cout << "ingrese su nueva obra social";
        if (pac.obrasocial != aux)
        {
            pac.obrasocial = aux;
        }
    }
    else
    {
        cout << "No vuelve el paciente";
        pac.archivado = "archivado";
        guardararchivo("ArchivosArchivados.csv", &pac);
    }
}
void guardararchivocontacto(string nombrearchivo, contacto cont)
{
    fstream archivo;
    string aux;
    archivo.open(nombrearchivo, ios::app);
    if (archivo.is_open())
    {
        getline(archivo, aux);

        if (aux == "\0") //si en la primer linea no hay nada,tengo que poner el encabezad
        {
            archivo << "Dni" << "telefono" << "celular" << "direccion" << "mail" << endl;
        }
        else
        {
            archivo << cont.dni_pac << cont.telefono << cont.celular << cont.direccion << cont.email << endl; //todo preguntar
        }
    }
    archivo.close();

}
void guardarmedicos(string nombrearchivo, medico medico)
{
    fstream archivo;
    string aux;
    char coma = ',';
    archivo.open(nombrearchivo, ios::app);
    if (archivo.is_open())
    {
        getline(archivo, aux);

        if (aux == "\0") //si en la primer linea no hay nada,tengo que poner el encabezad
        {
            archivo << "matricula" << coma << "nombre" << coma << "apellido" << coma << "telefono" << coma << "especialidad" << coma << "activo" << endl;
        }
        else
        {
            archivo << medico.matricula << coma << medico.nombre << coma << medico.apellido << coma << medico.telefono << coma << medico.especialidad << coma << medico.activo << endl; //todo preguntar
        }
    }
    archivo.close();

}