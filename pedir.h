#pragma once

void pedirString(char* stringPtr, char string[40])
{
	char specialChar[] = { 160,181,130,144,161,214,162,224,163,233 };

	printf("Ingresar %s: ", string);
	gets(stringPtr);

	while (strlen(stringPtr) < 4)
	{
		printf("El valor ingresado es muy corto (minimo 4 caracteres).\n");
		printf("Ingrese %s nuevamente: ", string);
		gets(stringPtr);
	}

	// REEMPLAZAR TILDES
	for (int i = 0; i < strlen(stringPtr); i++)
	{
		if (stringPtr[i] == specialChar[0] || stringPtr[i] == specialChar[1]) stringPtr[i] = 'a';
		if (stringPtr[i] == specialChar[2] || stringPtr[i] == specialChar[3]) stringPtr[i] = 'e';
		if (stringPtr[i] == specialChar[4] || stringPtr[i] == specialChar[5]) stringPtr[i] = 'i';
		if (stringPtr[i] == specialChar[6] || stringPtr[i] == specialChar[7]) stringPtr[i] = 'o';
		if (stringPtr[i] == specialChar[8] || stringPtr[i] == specialChar[9]) stringPtr[i] = 'u';
	}
	_strupr(stringPtr);
	// PRINT DEL STRING
	printf("%s ingresado: %s\n\n", string, stringPtr);
}

int pedirIntEntre(int min, int max, char string[40])
{
	int num;
	printf("Ingresar %s: ", string);
	scanf("%d", &num);

	while (num < min || num > max) {
		printf("El %s ingresado esta fuera de rango (%d-%d).\n", string, min, max);
		printf("Ingrese %s nuevamente: ", string);
		scanf("%d", &num);
	}

	printf("%s ingresado: %d\n\n", string, num);
	return num;
}

int pedirFecha(char string[20])
{
	int aaaa, mm, dd, fecha;

	printf("Ingresar a%co de %s: ", 164, string);
	scanf("%d", &aaaa);

	while (aaaa < 1000 || aaaa > 9999)
	{
		printf("El año ingresado esta fuera de rango (1-9999).\n");
		printf("Ingrese a%co de %s nuevamente: ", 164, string);
		scanf("%d", &aaaa);
	}

	printf("Ingresar mes de %s: ", string);
	scanf("%d", &mm);
	while (mm < 1 || mm > 12)
	{
		printf("El mes ingresado esta fuera de rango (1-12).\n");
		printf("Ingrese mes de %s nuevamente: ", string);
		scanf("%d", &mm);
	}

	switch (mm)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		printf("Ingrese dia de %s: ", string);
		scanf("%d", &dd);
		while (dd < 1 || dd > 31)
		{
			printf("EL dia ingresado esta fuera de rango (1-31).\n");
			printf("Ingrese dia de %s nuevamente: ", string);
			scanf("%d", &dd);
		}
		break;

	case 4:
	case 6:
	case 9:
	case 11:
		printf("Ingrese dia de %s: ", string);
		scanf("%d", &dd);
		while (dd < 1 || dd > 30)
		{
			printf("EL dia ingresado esta fuera de rango (1-30).\n");
			printf("Ingrese dia de %s nuevamente", string);
			scanf("%d", &dd);
		}
		break;

	case 2:
		printf("Ingrese dia de %s: ", string);
		scanf("%d", &dd);
		while (dd < 1 || dd > 29)
		{
			printf("EL dia ingresado esta fuera de rango (1-29).\n");
			printf("Ingrese dia de %s nuevamente", string);
			scanf("%d", &dd);
		}
		break;
	}

	fecha = ((aaaa * 10000) + (mm * 100) + dd);

	printf("Fecha ingresada = %d\n\n", fecha);
	return fecha;
}

int pedirOpciones(int cantOpciones, char string[40], char opcion1[20], char opcion2[20], char opcion3[20], char opcion4[20])
{
	int opcionElegida;
	char str[20];

	if (cantOpciones == 3)
	{
		printf("[1] %s\t[2] %s\t[3] %s\n", opcion1, opcion2, opcion3);
		printf("Ingresar %s: ", string);
		scanf("%d", &opcionElegida);

		while (opcionElegida < 1 || opcionElegida > 3)
		{
			printf("El valor ingresado esta fuera de rango (1-3).\n");
			printf("[1] %s\t[2] %s\t[3] %s\n", opcion1, opcion2, opcion3);
			printf("Ingresar %s nuevamente: ", string);
			scanf("%d", &opcionElegida);
		}
		if (opcionElegida == 1) strcpy(str, opcion1);
		if (opcionElegida == 2) strcpy(str, opcion2);
		if (opcionElegida == 3) strcpy(str, opcion3);
	}

	if (cantOpciones == 4)
	{
		printf("[1] %s\t[2] %s\t[3] %s\t[4] %s\n", opcion1, opcion2, opcion3, opcion4);
		printf("Ingresar %s: ", string);
		scanf("%d", &opcionElegida);

		while (opcionElegida < 1 || opcionElegida > 4) {
			printf("El valor ingresado esta fuera de rango (1-4).\n");
			printf("[1] %s\t[2] %s\t[3] %s\t[4] %s\n", opcion1, opcion2, opcion3, opcion4);
			printf("Ingresar %s nuevamente: ", string);
			scanf("%d", &opcionElegida);
		}

		if (opcionElegida == 1) strcpy(str, opcion1);
		if (opcionElegida == 2) strcpy(str, opcion2);
		if (opcionElegida == 3) strcpy(str, opcion3);
		if (opcionElegida == 4) strcpy(str, opcion4);
	}

	printf("%s ingresado: %s\n\n", string, str);
	return opcionElegida;
}

double pedirTelefono(char string[8])
{
	double telefono;
	printf("Ingresar telefono (%s): ", string);
	scanf("%lf", &telefono);

	while (telefono < 1000000000 || telefono > 9999999999) {
		printf("El telefono ingresado esta fuera de rango (1000000000-9999999999).\n");
		printf("Ingrese telefono (%s) nuevamente: ", string);
		scanf("%lf", &telefono);
	}

	printf("Telefono (%s) ingresado: %.0lf\n\n", string, telefono);
	return telefono;
}