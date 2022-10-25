#pragma once

void consultarEntreFechas()
{
	FILE* BINtransfusiones;
	struct transfusion transfusion;
	int fechaMin, fechaMax, transfusionEncontrada = 0;

	if ((BINtransfusiones = fopen("transfusiones.bin", "rb")) != NULL)
	{
		printf("PRIMER FECHA\n");
		fechaMin = pedirFecha("primer fecha");

		printf("SEGUNDA FECHA\n");
		fechaMax = pedirFecha("segunda fecha");

		while (fechaMax < fechaMin)
		{
			printf("La fecha maxima no puede ser inferior a la fecha minima. Por favor, ingrese la segunda fecha nuevamente.\n\n");
			printf("SEGUNDA FECHA\n");
			fechaMax = pedirFecha("segunda fecha");
		}

		while (fread(&transfusion, sizeof(struct transfusion), 1, BINtransfusiones) != NULL)
		{
			if (transfusion.fechaTransfusion > fechaMin && transfusion.fechaTransfusion < fechaMax)
			{
				transfusionEncontrada = 1;
				printf("____________TRANSFUSION AL PACIENTE %s____________\n\n", transfusion.nombrePaciente);

				printf("Sanatorio donde se realizo la transfusion: %s\n", transfusion.nombreSanatorio);
				printf("Fecha de la transfusion: %d\n", transfusion.fechaTransfusion);
				printf("Numero guia de la unidad de sangre utilizada: %d\n", transfusion.numeroGuia);
				if (transfusion.hemocomponente == 1) printf("Hemocomponente utilizado: Globulos rojos.\n");
				if (transfusion.hemocomponente == 2) printf("Hemocomponente utilizado: Plaquetas.\n");
				if (transfusion.hemocomponente == 3) printf("Hemocomponente utilizado: Plasma.\n");
				if (transfusion.hemocomponente == 4) printf("Hemocomponente utilizado: Crioprecipitado.\n");

				printf("\nDATOS DE LOS TECNICOS A CARGO DE LA TRANSFUSION\n");
				if (transfusion.sector == 1) printf("Sector donde se realizo la transfusion: Habitaciones generales (de internacion)\n");
				if (transfusion.sector == 2) printf("Sector donde se realizo la transfusion: UTI (unidad de cuidados criticos)\n");
				if (transfusion.sector == 3) printf("Sector donde se realizo la transfusion: Guardia de emergencia\n");
				if (transfusion.sector == 4) printf("Sector donde se realizo la transfusion: Sector oncologia\n");
				if (transfusion.sector == 5) printf("Sector donde se realizo la transfusion: Quirofanos\n");
				if (transfusion.sector == 6) printf("Sector donde se realizo la transfusion: Pediatria\n");
				if (transfusion.sector == 7) printf("Sector donde se realizo la transfusion: Neonatologia\n");
				printf("Matricula del medico solicitante: %d\n", transfusion.mtrMedSolicitante);
				printf("Especialidad del medico: %s\n", transfusion.especialidadMedico);
				printf("Nombre del tecnico a cargo de la transfusion: %s\n", transfusion.tecnico.nombre);
				printf("DNI del tecnico: %d\n", transfusion.tecnico.dni);
				printf("______________________________________________________\n\n");
			}
		}

		if (transfusionEncontrada == 0) printf("No se han encontrado transfusiones entre las 2 fechas ingresadas.");
		fclose(BINtransfusiones);
	}
	else printf("Error al abrir el archivo <transfusiones.bin>");

	return;
}

void top5medicos()
{
	FILE* BINsolicitudes, * BINtransfusiones;
	struct transfusion transfusion;
	struct solicitudesMedico solicitudesMedico;
	int matrizMedico[5][2], f, c, medicoEncontrado = 0;

	for (f = 0; f < 5; f++)
	{
		for (c = 0; c < 2; c++)
		{
			matrizMedico[f][c] = 0;
		}
	}

	if ((BINsolicitudes = fopen("solicitudes.bin", "wb")) != NULL)
	{
		if ((BINtransfusiones = fopen("transfusiones.bin", "rb")) != NULL)
		{
			while ((fread(&transfusion, sizeof(struct transfusion), 1, BINtransfusiones)) != NULL)
			{
				while ((fread(&solicitudesMedico, sizeof(struct solicitudesMedico), 1, BINsolicitudes)) != NULL)
				{
					if (transfusion.mtrMedSolicitante == solicitudesMedico.matricula)
					{
						medicoEncontrado = 1;
						solicitudesMedico.cantTransfusiones++;
						fseek(BINsolicitudes, (-1) * sizeof(struct solicitudesMedico), 1, SEEK_CUR);
						fwrite(&solicitudesMedico, sizeof(struct solicitudesMedico), 1, BINsolicitudes);
					}
				}

				if (medicoEncontrado == 0)
				{
					fseek(BINsolicitudes, 0, SEEK_END);
					solicitudesMedico.matricula = transfusion.mtrMedSolicitante;
					solicitudesMedico.cantTransfusiones = 1;
					fwrite(&solicitudesMedico, sizeof(struct solicitudesMedico), 1, BINsolicitudes);
				}

				rewind(BINsolicitudes);
			}
			fclose(BINtransfusiones);
		}
		else printf("Error al abrir el archivo <transfusiones.bin>");
		fclose(BINsolicitudes);
	}
	else printf("Error al abrir el archivo <solicitudes.bin>");

	if ((BINsolicitudes = fopen("solicitudes.bin", "rb")) != NULL)
	{
		while ((fread(&solicitudesMedico, sizeof(struct solicitudesMedico), 1, BINsolicitudes)) != NULL)
		{
			for (f = 0; f < 5; f++)
			{
				if (solicitudesMedico.cantTransfusiones > matrizMedico[f][2])
				{
					matrizMedico[f][0] = solicitudesMedico.matricula;
					matrizMedico[f][1] = solicitudesMedico.cantTransfusiones;
					break;
				}
			}
		}
		fclose(BINsolicitudes);
	}
	else printf("Error al abrir el archivos <solicitudes.bin>");

	printf("Los 5 medicos con mas transfusiones solicitadas son:\n");
	printf("MATRICULA\tSOLICITUDES\n");
	for (f = 0; f < 5; f++)
	{
		if (matrizMedico[f][0] != 0)
		{
			printf("%d\t\t%d transfusion(es)\n", matrizMedico[f][0], matrizMedico[f][1]);
		}
		else printf("[No hay datos]\t[No hay datos]\n");
	}
	return;
}