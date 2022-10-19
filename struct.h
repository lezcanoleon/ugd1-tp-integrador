#pragma once

struct paciente
{
	int dni;
	char nombreCompleto[50];
	int fechaNacimiento, genero;
	char direccion[50];
	double telefono;
	int grupoSanguineo, factorRh;
	char obraSocial[20], diagnostico[30];
};

struct familiar
{
	int dni;
	char nombreCompleto[50];
	double telefono;
	char parentesco[20];
};

struct medico
{
	int dni;
	char nombreCompleto[50];
	int matricula;
	char especialidad[30];
};

struct unidadSangre
{
	int numeroGuia, fechaVencimiento, fechaExtraccion, grupoSanguineo, factorRh;
};