#include "gmock/gmock.h"
#include "Funciones.h"
#include "fstream"
namespace foobar::tests {
	TEST(Fechas, funcionchequeo) {
		ultimaConsulta consulta;
		fstream Consul;
		string encabezado;
		char coma = ',';
		char barra = '/';
		Consul.open("Consultas.csv", ios::app);
		int i = 0;
		while (Consul) {
			
			if (i == 0) {
			Consul >> encabezado >> coma >> encabezado >> coma >> encabezado >> coma >> encabezado >> coma >> encabezado;
			}
			else			
			Consul >> consulta.dni_pac >> coma >> consulta.consulta.fecha.tm_mday >> barra >> consulta.consulta.fecha.tm_mon >> barra >> consulta.consulta.fecha.tm_year >> barra>> consulta.fecha_turno.fecha.tm_mday >> barra >> consulta.fecha_turno.fecha.tm_mon >> barra >> consulta.fecha_turno.fecha.tm_year >> barra >> consulta.presento >> coma >> consulta.matricula_med;
		}
		EXPECT_TRUE(chequearfechas(consulta)==true);
		Consul.close();
	}
	TEST(informarpaciente, funcioninformar)
	{
		//dni de paciente igual a dni de contacto
		Paciente pac1;
		fstream arch;
		arch.open("Contactos.csv",ios::app);
		pac1.dni="10242585";
		pac1.nombre="Hulda";
		pac1.apellido="Oliveira";
		pac1.sexo= 'M';
		pac1.nacimiento.fecha.tm_mday= 10;
		pac1.nacimiento.fecha.tm_mon=10;
		pac1.nacimiento.fecha.tm_year=1970;
		pac1.estado="n/c";
		pac1.obra_social= "Italiano";
		//10242585 , Hulda , Oliveira , M , 10/10/1970 , n/c , Italiano
		//10242585 , +54(282)86303641 , +54(054)87147146 , Wisconsin , Silverman@example.com
		//(eso son datos sacados de nuestros archivos, el primero del de pacientes y la segunda linea del de contactos, ambos coinciden en dni, se refieren a la misma persona)
		EXPECT_TRUE(vincularcontacto(pac1,arch)==false);
	}
	//TEST(buscarUnPaciente, funcionbusqueda) 
	//{
	//	Paciente pac1;
	//	fstream miArch;
	//	miArch.open("Pacientes.csv", ios::app);
	//	string _id = "10242589";//me copio un id exacto del archivo de paciente para fijarme si realmente encuentra ese paciente 
	//	//10242589 , Nelda , Maness , M , 1/1/1970 , n/c , OSDE (paciente a buscar, info completa)		
	//	pac1.dni = "10242589";
	//	pac1.nombre = "Nelda";
	//	pac1.apellido = "Maness";
	//	pac1.sexo = "M";                        //no funciona 
	//	pac1.nacimiento.fecha.tm_mday = 1;
	//	pac1.nacimiento.fecha.tm_mon = 1;
	//	pac1.nacimiento.fecha.tm_year = 1970;
	//	pac1.estado = "n/c";
	//	pac1.obra_social = "OSDE";
	//	char coma = ',';
	//ASSERT_THAT(buscarPaciente(miArch,_id), pac1.dni);
	//	miArch.close();
	//}
	//TEST()
	TEST(compararmatriculas, funcionchequearpacymed)
	{
		ultConsulta con;
		Medico med;
		med.nombre = "jose";
		med.activo = 1;
		med.apellido = "espert";
		med.telefono = "2334555"; //funciona
		med.matricula = "41";
		med.especialidad = "cardiologo";
		con.matricula_med = "41";
		con.presento = "no";
		
		EXPECT_TRUE(chequearconymed(med,con)==true);
	}
}