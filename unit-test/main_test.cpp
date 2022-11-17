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
		EXPECT_TRUE(chequearfechas(&consulta)==true);
	}
	//TEST(ExampleTests, Example) {
	//	ASSERT_THAT(1, 1);
	//}
	//TEST(ExampleTests, Example) {
	//	ASSERT_THAT(1, 1);
	//}
}