#include<stdio.h>
#include<string.h>
#include<pedir.h>
#include<struct.h>
#include<functions.h>
#include<consultas.h>

main()
{
	int opcion;

	printf("[1] Acceso a carga y modificacion\t[2] Acceso a consultas.\nIngrese una opcion (1-2): ");
	scanf("%d", &opcion);
	while (opcion < 1 || opcion > 2)
	{
		printf("El valor ingresado esta fuera de rango (1-2).\n");
		printf("Ingrese la opcion nuevamente: ");
		scanf("%d", &opcion);
	}

	switch (opcion)
	{
	case 1:
		printf("\n[ CARGA Y MODIFICACION ]\n\n");

		printf("[1] Carga.\t[2] Modificacion.\nIngrese una opcion (1-2): ");
		scanf("%d", &opcion);
		while (opcion < 1 || opcion > 2)
		{
			printf("El valor ingresado esta fuera de rango (1-2).\n");
			printf("Ingrese la opcion nuevamente: ");
			scanf("%d", &opcion);
		}

		switch (opcion) {
		case 1:
			printf("\n[ MENU DE CARGA ]\n\n");
			printf("[1] Cargar paciente.\n");
			printf("[2] Cargar transfusion.\n");
			scanf("%d", &opcion);
			while (opcion < 1 || opcion >2)
			{
				printf("El valor ingresado esta fuera de rango (1-2).\n");
				printf("Ingrese la opcion nuevamente: ");
				scanf("%d", &opcion);
			}
			switch (opcion)
			{
			case 1:
				printf("\nUsted ha accedido a la carga de paciente.\n");
				cargaPaciente();
				break;

			case 2:
				printf("\nUsted ha accedido a la carga de transfusiones.\n");
				cargaSanatorioTransfusiones();
				break;
			}
			break;

		case 2:
			printf("\n[ MENU DE MODIFICACION ]\n\n");
			printf("[1] Modificar paciente.\n");
			printf("[2] Modificar familiar.\n");
			printf("[3] Modificar unidad de sangre.\n");
			printf("[4] Modificar datos de medico.\n");
			printf("[5] Modificar sanatorio o sectores.\n");
			printf("[6] Modificar datos de transfusiones.\n");
			printf("Ingrese una opcion: ");
			scanf("%d", &opcion);

			while (opcion < 1 || opcion > 6)
			{
				printf("El valor ingresado esta fuera de rango (1-6).\n");
				printf("Ingrese la opcion nuevamente: ");
				scanf("%d", &opcion);
			}

			switch (opcion) {
			case 1:
				printf("\nUsted ha accedido a la modificacion de paciente.\n");
				modificarPaciente();
				break;

			case 2:
				printf("\nUsted ha accedido a la modificacion de familiar.\n");
				modificarFamiliar();
				break;

			case 3:
				printf("\nUsted ha accedido a la modificacion de unidad de sangre.\n");
				break;
			case 4:
				printf("\nUsted ha accedido a la modificacion de medicos.\n");
				modificarMedico();
				break;
			case 5:
				printf("\nUsted ha accedido a la modificación de sanatorio o sectores.\n");
				break;
			case 6:
				printf("\nUsted ha accedido a la modificación de datos de transfusiones.\n");
				break;
			}
			break;
		}
		break;

	case 2:
		printf("\n[MENU DE CONSULTA]\n");
		printf("[1] Consultar transfusiones hechas en un plazo determinado.\n");
		printf("[2] Consultar los 5 medicos que mas transfusiones solicitaron.\n");
		printf("[3] Consultar el mayor porcentaje de transfusiones segun diagnostico.\n");
		printf("[4] Consultar las transfusiones realizadas a un paciente.\n");
		printf("[5] Consultar el sector con mayor transfusiones realizadas.\n");
		printf("Ingrese una opcion: ");
		scanf("%d", &opcion);

		switch (opcion) {
		case 1:
			printf("\nUsted ha accedido a la consulta de transfusiones entre dos fechas\n\n");
			printf("Ingrese dos fechas para realizar la consulta (formato: dd, mm, aaaa):\n\n");
			consultarEntreFechas();
			break;

		case 2:
			printf("Los 5 médicos que mas transfusiones realizaron son: \n");
			break;

		case 3:
			printf("El diagnostico con mayor porcentaje de transfusiones realizadas es: \n");
			break;

		case 4:
			printf("[Consulta de paciente]\n\n");
			break;

		case 5:
			printf("El sector que mayor cantidad de transfusiones realizo es: \n");
			break;
		}
		break;
	}
}