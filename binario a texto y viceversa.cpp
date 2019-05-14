#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#include<conio.h> 
#include<math.h>
#include<windows.h>
#define DIM 300

long binario_decimal(char *binario, int longitud);
void decimal_texto(char *binario, int longtitudbinario, char *texto, int simbcont);
void formatobinario(char *input, int longitud, char *output);
int validartex(char *texto);
int validarbin(char *binario);
void encriptar(char texto[]);
void guardar(int *cerosyunos);

int main()
{
	FILE *archivo;
	char binario[559], fichero[50], opt, sn;
	char *texto, *binarioformateado = 0, *text;
	int cerosyunos[20];
	int contador = 0, entrada, i = 0, c = 0, longitudbinaria = 0, simbcont = 0;

	text = (char*)malloc((simbcont + 1) * sizeof(char));
	binarioformateado = (char*)malloc((longitudbinaria + 1) * sizeof(char));
	texto = (char*)malloc(DIM * sizeof(char));

	if (texto[i] == 0)
	{
		printf("No hay memoria suficiente\n");
		exit(0);
	}
	else
	{
		printf("Memoria correctamente asignada\n");
	}
	while (1)
	{
		printf("Seleccione una opci%cn: \nE: Encriptar \nD: Desencriptar \nS: Salir \nL: Limpiar Pantalla \n", 162);
		scanf("%c", &opt);
		while (getchar() != '\n');
		switch (opt)
		{
		case 'L':
		case 'l':
		{
			system("cls");
			break;
		}

		case 'S':
		case's':
		{
			exit(1);
			break;
		}

		case'E':
		case'e':
		{
			printf("Seleccione modo de entrada\n1:Teclado\n2:Archivo\n");
			scanf("%d", &entrada);
			if (entrada == 1)
			{
				i = 0;
				encriptar(&texto[i]);
				printf("\n");
				printf("%cQuiere guardar el texto?\n", 168);
				scanf("%c", &sn);
				while (getchar() != '\n');
				if (sn == 's' || sn == 'S')
				{
					guardar(cerosyunos);
				}
			}
			else if (entrada == 2)
			{
				printf("Introduzca el nombre del texto\n");
				getchar();
				gets_s(fichero, 50);
				archivo = fopen(fichero, "r");
				while (feof(archivo) == 0)
				{
					fgets(texto, DIM, archivo);
					encriptar(&texto[i]);
					printf("%cQuiere guardar el texto?\n", 168);
					scanf("%c", &sn);
					while (getchar() != '\n');
					if (sn == 's' || sn == 'S')
					{
						guardar(cerosyunos);
					}
				}
				fclose(archivo);
			}
			break;
		}

		case 'D':
		case 'd':
		{
			printf("Introduce c%codigo binario:\n", 162);
			scanf("%558[^\n]s", binario);
			printf("\n");

			longitudbinaria = (int)strlen(binario);
			if (validarbin(binario))
			{
				simbcont = longitudbinaria / 8 + 1;

				if (text == NULL || binarioformateado == NULL)
				{
					exit(1);
				}
				if (longitudbinaria % 8 == 0)
				{
					--simbcont;
				}
				formatobinario(binario, longitudbinaria, binarioformateado);
				decimal_texto(binarioformateado, (int)strlen(binarioformateado), texto, simbcont);
				printf("El texto es el siguiente :\n%s\n", texto);
			}
			else
			{
				printf("El input deberia ser un numero en binario, conteniendo solo ceros(0) y unos(1).\n");
			}
			break;
		}
		}
	}
	free(texto);
	system("pause");
}

void encriptar(char texto[])
{
	int cerosyunos[20];
	int num, contador = 0, i = 0, resul, valido;
	printf("Introduzca un texto para convertirlo a codigo binario:\n");
	getchar();
	do
	{
		gets_s(texto, DIM);
		valido = validartex(&texto[i]);
		if (valido == 0)
		{
			printf("Texto introducido incorrecto, introduzca un texto de nuevo:\n");
		}
	} 
	while (valido == 0);
	while (contador < strlen(texto))
	{
		i = 0;
		num = texto[contador];
		if (num < 64 && num >= 32)
		{
			while (num > 0)
			{
				resul = num % 2;
				if (resul == 0)
				{
					cerosyunos[i] = 0;
					i = i + 1;
				}
				else
				{
					cerosyunos[i] = 1;
					i = i + 1;
					num = num - 1;
				}
				num = num / 2;
			}
			cerosyunos[i] = 0;
			i = i + 1;
		}

		if (num < 128)
		{
			while (num > 0)
			{
				resul = num % 2;
				if (resul == 0)
				{
					cerosyunos[i] = 0;
					i = i + 1;
				}
				else
				{
					cerosyunos[i] = 1;
					i = i + 1;
					num = num - 1;
				}
				num = num / 2;
			}
			cerosyunos[i] = 0;
			i = i + 1;
		}
		i = i - 1;
		while (i >= 0)
		{
			printf("%i", cerosyunos[i]);
			i = i - 1;
		}
		printf("\t");
		contador = contador + 1;
	}
}

void decimal_texto(char *binario, int longitudbinaria, char *texto, int simbcont)
{
	int i;
	for (i = 0; i < longitudbinaria; i += 8, binario += 8)
	{
		char *byte = binario;
		byte[8] = '\0';
		*texto++ = (char)binario_decimal(byte, 8);
	}
	texto -= simbcont;
}

long binario_decimal(char *binario, int longitud)
{
	int i;
	long decimal = 0;
	long peso = 1;
	binario += longitud - 1;
	for (i = 0; i < longitud; ++i, --binario)
	{
		if (*binario == '1')
			decimal += peso;
		peso *= 2;
	}
	return decimal;
}

void formatobinario(char *input, int longitud, char *output)
{
	while (*input)
	{
		if (*input == '0' || *input == '1')
		{
			*output++ = *input++;
		}
		else
		{
			++input;
			--longitud;
		}
	}
	output -= longitud;
}

int validarbin(char *binario)
{
	while (*binario)
	{
		if ((*binario != '0') && (*binario != '1') && (*binario != ' '))
			return 0;
		++binario;
	}
	return 1;
}

void guardar(int *cerosyunos)
{
	FILE*archivo;
	char nombre[50];
	printf("Pulse espacio e introduzca el nombre del texto \n");
	getchar();
	gets_s(nombre, 50);
	archivo = fopen(nombre, "a");
	fprintf(archivo, "%i", *cerosyunos);
	fclose(archivo);
}

int validartex(char *texto)
{
	if (*texto < 32 || *texto > 128)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
