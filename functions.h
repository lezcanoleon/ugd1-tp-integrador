#pragma once

void flushstdin() {
	int c;
	while ((c = getchar()) != EOF && c != '\n');
}

void cargaPaciente()
{
	struct paciente paciente;
	struct familiar familiar;
	struct medico medico;
	struct unidadSangre unidadSangre;

	FILE* FILEpaciente, * FILEmedico, * FILEunidadSangre;

	if (
		(FILEpaciente = fopen("paciente.bin", "ab")) != NULL &&
		(FILEmedico = fopen("medico.bin", "ab")) != NULL &&
		(FILEunidadSangre = fopen("unidad_sangre.bin", "ab")) != NULL
		)
	{
		int mainFlag = 1;

		printf("[Datos del paciente]\n\n");
		printf("Desea agregar una entrada?\n[1] Si\n[0] No\n");
		scanf("%d", &mainFlag);

		while (mainFlag != 0)
		{
			printf("\n");

			// CARGA PACIENTE
			paciente.dni = pedirIntEntre(10000000, 99999999, "DNI (paciente)");
			flushstdin();
			pedirString(&paciente.nombreCompleto, "Nombre Completo (paciente)");
			paciente.fechaNacimiento = pedirFecha("nacimiento");
			paciente.genero = pedirOpciones(3, "Genero (paciente)", "Hombre", "Mujer", "Otro", "");
			flushstdin();
			pedirString(&paciente.direccion, "Direccion (paciente)");
			paciente.telefono = pedirTelefono("paciente");
			paciente.grupoSanguineo = pedirOpciones(4, "Grupo sanguineo (paciente)", "A", "B", "O", "AB");
			paciente.factorRh = pedirOpciones(3, "Factor Rh (paciente)", "+", "-", "DEBIL", "");
			flushstdin();
			pedirString(&paciente.obraSocial, "Obra social (paciente)");
			pedirString(&paciente.diagnostico, "Diagnostico (paciente)");

			// CARGA FAMILIAR
			printf("[Datos del familiar a cargo]\n\n");
			familiar.dni = pedirIntEntre(10000000, 99999999, "DNI (familiar)");
			flushstdin();
			pedirString(&familiar.nombreCompleto, "Nombre completo (familiar)");
			familiar.telefono = pedirTelefono("familiar");
			flushstdin();
			pedirString(&familiar.parentesco, "Parentesco con el paciente (familiar)");

			// CARGA MEDICO
			printf("[Datos del medico]\n\n");
			medico.dni = pedirIntEntre(10000000, 99999999, "DNI (medico)");
			flushstdin();
			pedirString(&medico.nombreCompleto, "Nombre Completo (medico)");
			medico.matricula = pedirIntEntre(1, 99999, "Matricula (medico)");
			flushstdin();
			pedirString(&medico.especialidad, "Especialidad (medico)");

			// CARGA UNIDAD DE SANGRE
			printf("[Datos de Unidad de sangre]\n\n");
			int flag;
			printf("El paciente se ha realizado una transfusion de sangre?\n[1] Si\t[0] No\n");
			scanf("%d", &flag);

			while (flag < 0 || flag > 1) {
				printf("El valor ingresado esta fuera de rango (0-1).\n");
				printf("[1] Si\t[0] No\n");
				scanf("%d", &flag);
			}

			printf("\n");

			while (flag != 0)
			{
				unidadSangre.numeroGuia = pedirIntEntre(1, 99999, "Numero guia (unidad de sangre)");
				unidadSangre.fechaExtraccion = pedirFecha("extraccion");
				unidadSangre.fechaVencimiento = pedirFecha("vencimiento");
				unidadSangre.grupoSanguineo = pedirOpciones(4, "Grupo sanguineo (unidad de sangre)", "A", "B", "O", "AB");
				unidadSangre.factorRh = pedirOpciones(3, "Factor Rh (unidad de sangre)", "+", "-", "DEBIL", "");

				printf("[Datos de la extraccion]\n");
				printf("Numero guia = %d\n", unidadSangre.numeroGuia);
				printf("Fecha de extraccion = %d\n", unidadSangre.fechaExtraccion);
				printf("Fecha de vencimiento = %d\n", unidadSangre.fechaVencimiento);
				printf("Grupo sanguineo = %d\n", unidadSangre.grupoSanguineo);
				printf("Factor Rh = %d\n", unidadSangre.factorRh);

				// FWRITE UNIDAD DE SANGRE
				fwrite(&unidadSangre, sizeof(struct unidadSangre), 1, FILEunidadSangre);
				printf("\nSe ha cargado el registro de la extraccion correctamente.\n\n");

				printf("Desea agregar otra extraccion al registro?\n[1] Si\t[2] No\n");
				scanf("%d", &flag);
				while (flag < 0 || flag > 1)
				{
					printf("La opcion ingresada es incorrecta. Ingrese nuevamente: ");
					scanf("%d", &flag);
				}
			}

			// FWRITE PACIENTE
			fwrite(&paciente, sizeof(struct paciente), 1, FILEpaciente);
			fwrite(&familiar, sizeof(struct familiar), 1, FILEpaciente);
			fwrite(&medico, sizeof(struct medico), 1, FILEmedico);

			printf("[Datos del paciente]\n\n");
			printf("Desea agregar una entrada?\n[1] Si\n[0] No\n");
			scanf("%d", &mainFlag);
		}
		fclose(FILEpaciente);
		fclose(FILEmedico);
		fclose(FILEunidadSangre);
	}

	return;
}

void modificarPaciente()
{
	struct paciente paciente;
	FILE* FILEpaciente;
	int dniBusqueda, dniEncontrado = 0, opcion;
	fpos_t position;

	if ((FILEpaciente = fopen("paciente.bin", "rb+")) != NULL)
	{
		fgetpos(FILEpaciente, &position);
		dniBusqueda = pedirIntEntre(10000000, 99999999, "DNI del paciente a modificar");

		while ((fread(&paciente, sizeof(struct paciente), 1, FILEpaciente)) != NULL)
		{
			if (dniBusqueda == paciente.dni)
			{
				printf("DNI Encontrado: %d\n\n", paciente.dni);
				dniEncontrado = 1;
				fseek(FILEpaciente, (-1) * (sizeof(struct paciente)), SEEK_CUR);
				fgetpos(FILEpaciente, &position);

				printf("Que desea modificar? (Ingrese 0 para salir)\n");
				printf("[1] Nombre\t[2] Fecha de nacimiento\t[3] Genero\n");
				printf("[4] Direccion\t[5] Telefono\t\t[6] Grupo Sanguineo\n");
				printf("[7] Factor Rh\t[8] Obra Social\t\t[9] Diagnostico\n");

				scanf("%d", &opcion);
				while (opcion < 0 || opcion > 9)
				{
					printf("El valor ingresado esta fuera de rango.\n");
					printf("Ingresar opcion nuevamente: ");
					scanf("%d", &opcion);
				}

				printf("\n");
				while (opcion != 0)
				{
					switch (opcion)
					{
					case 0:
						break;

					case 1:
						printf("Nombre actual: %s\n", paciente.nombreCompleto);
						flushstdin();
						pedirString(&paciente.nombreCompleto, "Nombre Completo (paciente) nuevo");
						break;

					case 2:
						printf("Fecha de nacimiento actual: %d\n", paciente.fechaNacimiento);
						paciente.fechaNacimiento = pedirFecha("nacimiento nuevo");
						break;

					case 3:
						printf("Genero actual: %d\n", paciente.genero);
						paciente.genero = pedirOpciones(3, "Genero (paciente)", "Hombre", "Mujer", "Otro", "");
						break;

					case 4:
						flushstdin();
						printf("Direccion actual: %s\n", paciente.direccion);
						pedirString(&paciente.direccion, "Direccion (paciente)");
						break;

					case 5:
						printf("Telefono actual: %.0lf\n", paciente.telefono);
						paciente.telefono = pedirTelefono("paciente");
						break;

					case 6:
						printf("Grupo sanguineo actual: %s\n");
						paciente.grupoSanguineo = pedirOpciones(4, "Grupo sanguineo (paciente)", "A", "B", "O", "AB");
						break;

					case 7:
						printf("Factor Rh actual: %d\n", paciente.factorRh);
						paciente.factorRh = pedirOpciones(3, "Factor Rh (paciente)", "+", "-", "DEBIL", "");
						break;

					case 8:
						flushstdin();
						printf("Obra social actual: %s\n", paciente.obraSocial);
						pedirString(&paciente.obraSocial, "Obra social (paciente)");
						break;

					case 9:
						flushstdin();
						printf("Diagnostico actual: %s\n", paciente.diagnostico);
						pedirString(&paciente.diagnostico, "Diagnostico (paciente)");
						printf("Diagnostico modificado correctamente.\n");
						break;
					}
					fsetpos(FILEpaciente, &position);
					fwrite(&paciente, sizeof(struct paciente), 1, FILEpaciente);

					printf("Desea modificar algun otro dato? (Ingrese 0 para salir)\n");
					printf("[1] Nombre\t[2] Fecha de nacimiento\t[3] Genero\n");
					printf("[4] Direccion\t[5] Telefono\t\t[6] Grupo Sanguineo\n");
					printf("[7] Factor Rh\t[8] Obra Social\t\t[9] Diagnostico\n");

					scanf("%d", &opcion);
				}
			}
			else fseek(FILEpaciente, sizeof(struct familiar), SEEK_CUR);
		}

		if (dniEncontrado == 0)
		{
			printf("El DNI no se ha encontrado.");
		}
	}
	else printf("\n[ERROR] No se pudo abrir los archivos.\n");
}

void modificarMedico()
{
	struct medico medico;
	FILE* FILEmedico;
	int dniBusqueda, dniEncontrado = 0, opcion;
	fpos_t position;

	if ((FILEmedico = fopen("medico.bin", "rb+")) != NULL)
	{
		fgetpos(FILEmedico, &position);
		dniBusqueda = pedirIntEntre(10000000, 99999999, "DNI del medico a modificar");

		while ((fread(&medico, sizeof(struct medico), 1, FILEmedico)) != NULL)
		{
			if (dniBusqueda == medico.dni)
			{
				printf("DNI Encontrado: %d\n\n", medico.dni);
				dniEncontrado = 1;
				fseek(FILEmedico, (-1) * (sizeof(struct medico)), SEEK_CUR);
				fgetpos(FILEmedico, &position);

				printf("Que desea modificar? (Ingrese 0 para salir)\n");
				printf("[1] Nombre\t[2] Matricula\t[3] Especialidad\n");

				scanf("%d", &opcion);
				while (opcion < 0 || opcion > 3)
				{
					printf("El valor ingresado esta fuera de rango.\n");
					printf("Ingresar opcion nuevamente: ");
					scanf("%d", &opcion);
				}

				printf("\n");
				while (opcion != 0)
				{
					switch (opcion)
					{
					case 0:
						break;

					case 1:
						printf("Nombre actual: %s\n", medico.nombreCompleto);
						flushstdin();
						pedirString(&medico.nombreCompleto, "Nombre Completo (medico) nuevo");
						break;

					case 2:
						printf("Matricula actual: %d\n", medico.matricula);
						medico.matricula = pedirIntEntre(1, 99999, "Matricula (medico)");
						break;

					case 3:
						printf("Especialidad actual: %s\n", medico.especialidad);
						pedirString(&medico.especialidad, "Especialidad (medico)");
						break;
					}
					fsetpos(FILEmedico, &position);
					fwrite(&medico, sizeof(struct medico), 1, FILEmedico);

					printf("Desea modificar algun otro dato? (Ingrese 0 para salir)\n");
					printf("[1] Nombre\t[2] Matricula\t[3] Especialidad\n");

					scanf("%d", &opcion);
				}
			}
			else fseek(FILEmedico, sizeof(struct medico), SEEK_CUR);
		}

		if (dniEncontrado == 0)
		{
			printf("El DNI no se ha encontrado.");
		}
	}
	else printf("\n[ERROR] No se pudo abrir los archivos.\n");
}

void modificarFamiliar()
{
	struct familiar familiar;
	struct paciente paciente;
	FILE* FILEpaciente;
	int dniBusqueda, dniEncontrado = 0, opcion;
	fpos_t position;

	if ((FILEpaciente = fopen("paciente.bin", "rb+")) != NULL)
	{
		fseek(FILEpaciente, sizeof(struct paciente), 1, SEEK_CUR);
		fgetpos(FILEpaciente, &position);
		dniBusqueda = pedirIntEntre(10000000, 99999999, "DNI del familiar a modificar");
		while ((fread(&familiar, sizeof(struct familiar), 1, FILEpaciente)) != NULL)
		{
			if (dniBusqueda == familiar.dni)
			{
				printf("DNI Encontrado: %d\n\n", familiar.dni);
				printf("%d", familiar.telefono);
				dniEncontrado = 1;
				fseek(FILEpaciente, (-1) * (sizeof(struct familiar)), SEEK_CUR);
				fgetpos(FILEpaciente, &position);

				printf("Que desea modificar? (Ingrese 0 para salir)\n");
				printf("[1] Nombre\t[2] Telefono\t[3] Parentesco\n");

				scanf("%d", &opcion);
				while (opcion < 0 || opcion > 3)
				{
					printf("El valor ingresado esta fuera de rango.\n");
					printf("Ingresar opcion nuevamente: ");
					scanf("%d", &opcion);
				}

				printf("\n");
				while (opcion != 0)
				{
					switch (opcion)
					{
					case 0:
						break;

					case 1:
						printf("Nombre actual: %s\n", familiar.nombreCompleto);
						flushstdin();
						pedirString(&familiar.nombreCompleto, "Nombre Completo (familiar) nuevo");
						break;

					case 2:
						printf("Telefono actual: %.0lf\n", familiar.telefono);
						familiar.telefono = pedirTelefono("familiar");
						break;

					case 3:
						printf("Parentesco que posee: %s\n", familiar.parentesco);
						flushstdin();
						pedirString(&familiar.parentesco, "Parentesco (familiar)");
						break;
					}
					fsetpos(FILEpaciente, &position);
					fwrite(&familiar, sizeof(struct familiar), 1, FILEpaciente);

					printf("Desea modificar algun otro dato? (Ingrese 0 para salir)\n");
					printf("[1] Nombre\t[2] Telefono\t[3] Parentesco\n");

					scanf("%d", &opcion);
				}
			}
			else fseek(FILEpaciente, sizeof(struct paciente), SEEK_CUR);
		}

		if (dniEncontrado == 0)
		{
			printf("El DNI no se ha encontrado.");
		}
	}
	else printf("\n[ERROR] No se pudo abrir los archivos.\n");
}

void cargaSanatorioTransfusiones()
{
	struct transfusion transfusion;
	struct sanatorio sanatorio;
	for (int i = 0; i < 7; i++)
	{
		sanatorio.sectores[i] = 0;
	}

	FILE* FILEsanatorios, * FILEtransfusiones, * FILEtxt;
	char buffer[50], stringTxt[80];
	int sanatorioEncontrado = 0, accion, flag, contador = 0;
	if ((FILEsanatorios = fopen("sanatorios.bin", "rb+")) != NULL)
	{
		if (FILEtransfusiones = fopen("transfusiones.bin", "rb+"))
		{
			fseek(FILEtransfusiones, 0, SEEK_END);
			flushstdin();
			pedirString(&buffer, "Nombre del sanatorio");
			while ((fread(&sanatorio, sizeof(struct sanatorio), 1, FILEsanatorios)) != NULL)
			{
				if (strcmp(sanatorio.nombre, buffer) == 0)
				{
					sanatorioEncontrado = 1;
					fseek(FILEsanatorios, (-1) * sizeof(struct sanatorio), SEEK_CUR);
					printf("Sanatorio encontrado.\n");

					printf("Desea agregar una transfusion al registro?\n[1] Si\n[0] No\n");
					scanf("%d", &flag);
					while (flag < 0 || flag > 1)
					{
						printf("La opcion ingresada es invalida.\nIngrese opcion nuevamente: ");
						scanf("%d", &flag);
					}

					while (flag != 0)
					{
						printf("\nEn que sector del sanatorio se realiza la transfusión?\n");
						printf("[1] Habitaciones generales (de internacion)\n");
						printf("Sectores especializados\n");
						printf("\t[2] UTI (unidad de cuidados criticos)\n");
						printf("\t[3] Guardia de emergencia\n");
						printf("\t[4] Sector oncologia\n");
						printf("\t[5] Quirofanos\n");
						printf("\t[6] Pediatria\n");
						printf("\t[7] Neonatologia\n");
						printf("\nIngresar opcion: ");
						scanf("%d", &accion);
						while (accion < 1 || accion > 7)
						{
							printf("La opcion ingresada es invalida (1-7).\nIngrese opcion nuevamente: ");
							scanf("%d", &accion);
						}
						sanatorio.sectores[accion - 1]++;
						transfusion.sector = (accion - 1);

						transfusion.numeroGuia = pedirIntEntre(1, 99999, "Numero guia de la unidad de sangre");
						transfusion.hemocomponente = pedirOpciones(4, "Hemocomponente", "Globulos rojos", "Plaquetas", "Plasma", "Crioprecipitado");
						flushstdin();
						pedirString(&transfusion.nombrePaciente, "Nombre del paciente que recibe la transfusion");
						transfusion.fechaTransfusion = pedirFecha("transfusion");
						transfusion.mtrMedSolicitante = pedirIntEntre(1, 99999, "Matricula del medico solicitante");
						flushstdin();
						pedirString(&transfusion.especialidadMedico, "Especialidad del medico");

						pedirString(&transfusion.tecnico.nombre, "Nombre completo del tecnico");
						transfusion.tecnico.dni = pedirIntEntre(1, 99999999, "DNI del tecnico");

						fwrite(&sanatorio, sizeof(struct sanatorio), 1, FILEsanatorios);
						fwrite(&transfusion, sizeof(struct transfusion), 1, FILEtransfusiones);

						// CREACION TXT
						sprintf(&stringTxt, "comprobante_transfusion_%s.txt", transfusion.nombrePaciente);
						FILEtxt = fopen(stringTxt, "w");

						fprintf(FILEtxt, "Nombre del paciente: %s\n", transfusion.nombrePaciente);
						fprintf(FILEtxt, "Fecha de transfusion: %d\n", transfusion.fechaTransfusion);
						fprintf(FILEtxt, "Numero guia de la unidad de sangre: %d\n", transfusion.numeroGuia);
						if (transfusion.hemocomponente == 1) fprintf(FILEtxt, "Hemocomponente utilizado: Globulos rojos.\n");
						if (transfusion.hemocomponente == 2) fprintf(FILEtxt, "Hemocomponente utilizado: Plaquetas.\n");
						if (transfusion.hemocomponente == 3) fprintf(FILEtxt, "Hemocomponente utilizado: Plasma.\n");
						if (transfusion.hemocomponente == 4) fprintf(FILEtxt, "Hemocomponente utilizado: Crioprecipitado.\n");
						fprintf(FILEtxt, "Medico solicitante (matricula): %d\n", transfusion.mtrMedSolicitante);
						fprintf(FILEtxt, "Especialidad del medico: %s\n", transfusion.especialidadMedico);
						fprintf(FILEtxt, "Nombre del tecnico que realizo el procedimiento: %s\n", transfusion.tecnico.nombre);
						fprintf(FILEtxt, "DNI del tecnico que realizo el procedimiento: %d\n", transfusion.tecnico.dni);
						fclose(FILEtxt);

						printf("\n\nDesea agregar una transfusion al registro?\n[1] Si\n[0] No\n");
						scanf("%d", &flag);
						while (flag < 0 || flag > 1)
						{
							printf("La opcion ingresada es invalida.\nIngrese opcion nuevamente: ");
							scanf("%d", &flag);
						}
					}

					break;
				}
				else fseek(FILEsanatorios, sizeof(struct sanatorio), SEEK_CUR);
			}
			if (sanatorioEncontrado == 0)
			{
				printf("El sanatorio no se ha encontrado, desea agregarlo al registro?\n[1] Si\n[0] No\n");
				scanf("%d", &accion);
				while (accion < 0 || accion > 1)
				{
					printf("La opcion ingresada es invalida (0-1).\nIngrese opcion nuevamente: ");
					scanf("%d", &accion);
				}
				switch (accion)
				{
				case 1:
					strcpy(sanatorio.nombre, buffer);
					printf("\nNombre del sanatorio: %s\n", sanatorio.nombre);
					flushstdin();
					pedirString(&sanatorio.direccion, "Direccion del sanatorio");
					fseek(FILEsanatorios, 0, SEEK_END);
					fwrite(&sanatorio, sizeof(struct sanatorio), 1, FILEsanatorios);
					break;

				case 0:
					break;
				}

				if (accion != 0)
				{
					printf("Desea agregar una transfusion al registro?\n[1] Si\n[0] No\n");
					scanf("%d", &flag);
					while (flag < 0 || flag > 1)
					{
						printf("La opcion ingresada es invalida.\nIngrese opcion nuevamente: ");
						scanf("%d", &flag);
					}

					while (flag != 0)
					{
						printf("En que sector del sanatorio se realiza la transfusión?\n");
						printf("[1] Habitaciones generales (de internacion)\n");
						printf("Sectores especializados\n");
						printf("\t[2] UTI (unidad de cuidados criticos)\n");
						printf("\t[3] Guardia de emergencia\n");
						printf("\t[4] Sector oncologia\n");
						printf("\t[5] Quirofanos\n");
						printf("\t[6] Pediatria\n");
						printf("\t[7] Neonatologia\n");
						printf("\nIngresar opcion: ");
						scanf("%d", &accion);
						while (accion < 1 || accion > 7)
						{
							printf("La opcion ingresada es invalida (1-7).\nIngrese opcion nuevamente: ");
							scanf("%d", &accion);
						}
						sanatorio.sectores[accion - 1]++;
						transfusion.sector = (accion - 1);

						transfusion.numeroGuia = pedirIntEntre(1, 99999, "Numero guia de la unidad de sangre");
						transfusion.hemocomponente = pedirOpciones(4, "Hemocomponente", "Globulos rojos", "Plaquetas", "Plasma", "Crioprecipitado");
						flushstdin();
						pedirString(&transfusion.nombrePaciente, "Nombre del paciente que recibe la transfusion");
						transfusion.fechaTransfusion = pedirFecha("transfusion");
						transfusion.mtrMedSolicitante = pedirIntEntre(1, 99999, "Matricula del medico solicitante");
						flushstdin();
						pedirString(&transfusion.especialidadMedico, "Especialidad del medico");

						pedirString(&transfusion.tecnico.nombre, "Nombre completo del tecnico");
						transfusion.tecnico.dni = pedirIntEntre(1, 99999999, "DNI del tecnico");

						fwrite(&transfusion, sizeof(struct transfusion), 1, FILEtransfusiones);

						// CREACION TXT
						sprintf(&stringTxt, "comprobante_transfusion_%s.txt", transfusion.nombrePaciente);
						FILEtxt = fopen(stringTxt, "w");

						fprintf(FILEtxt, "Nombre del paciente: %s\n", transfusion.nombrePaciente);
						fprintf(FILEtxt, "Fecha de transfusion: %d\n", transfusion.fechaTransfusion);
						fprintf(FILEtxt, "Numero guia de la unidad de sangre: %d\n", transfusion.numeroGuia);
						if (transfusion.hemocomponente == 1) fprintf(FILEtxt, "Hemocomponente utilizado: Globulos rojos.\n");
						if (transfusion.hemocomponente == 2) fprintf(FILEtxt, "Hemocomponente utilizado: Plaquetas.\n");
						if (transfusion.hemocomponente == 3) fprintf(FILEtxt, "Hemocomponente utilizado: Plasma.\n");
						if (transfusion.hemocomponente == 4) fprintf(FILEtxt, "Hemocomponente utilizado: Crioprecipitado.\n");
						fprintf(FILEtxt, "Medico solicitante (matricula): %d\n", transfusion.mtrMedSolicitante);
						fprintf(FILEtxt, "Especialidad del medico: %s\n", transfusion.especialidadMedico);
						fprintf(FILEtxt, "Nombre del tecnico que realizo el procedimiento: %s\n", transfusion.tecnico.nombre);
						fprintf(FILEtxt, "DNI del tecnico que realizo el procedimiento: %d\n", transfusion.tecnico.dni);
						fclose(FILEtxt);

						printf("\n\nDesea agregar una transfusion al registro?\n[1] Si\n[0] No\n");
						scanf("%d", &flag);
						while (flag < 0 || flag > 1)
						{
							printf("La opcion ingresada es invalida.\nIngrese opcion nuevamente: ");
							scanf("%d", &flag);
						}
					}
				}
			}
		}
		else printf("Error al abrir el archivo <transfusiones.bin>");
	}
	else printf("Error al abrir el archivo <sanatorios.bin>");
}