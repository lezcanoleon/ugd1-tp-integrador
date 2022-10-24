#pragma once

consultarEntreFechas()
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