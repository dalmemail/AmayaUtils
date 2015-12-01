/*
 * Copyright (C) 2015 Dan Rulos [amaya@amayaos.com], Alvaro Stagg [alvarostagg@openmailbox.org]
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include "find.h"

int find(char *path, char *file)
{
	DIR *d;
	struct dirent *dent;
	char path_[128];
	/* copy path to path_ */
	strcpy(path_, path);
	/* open path */
	if (!(d = opendir(path))) {
		printf("find: error al abrir '%s': %s\r\n",
		path, strerror(errno));
		return EXIT_FAILURE;
	}
	while ((dent = readdir(d))) {
		switch (dent->d_type) {
			case DT_DIR:
				if (dent->d_name[0] != '.') {
					if ((strcmp("/", path) != 0)) {
						strcat(path_, "/");
					}
					strcat(path_, dent->d_name);
					find(path_, file);
				}
				break;
			default:
				if ((strcmp(dent->d_name, file)) == 0) {
					if ((strcmp("/", path)) == 0) {
						printf("/%s\n", file);
					}
					else {
						printf("%s/%s\n", path, file);
					}
				}
		}
		for (int i = 0; i < 128; i++) {
			path_[i] = '\0';
		}
		strcpy(path_, path);
	}
	/* close path */
	closedir(d);
	return EXIT_SUCCESS;
}

size_t file_size(char *path)
{
	struct stat st;

	if(stat(path, &st) != 0)
		return -1;
	else
		return st.st_size;
}

int find_empty(char *path)
{
	DIR *dir;
	struct dirent *dnt;

	if ((dir = opendir(path)) != NULL)
	{
		while ((dnt = readdir(dir)) != NULL)
		{
			if(file_size(dnt->d_name) == 0)
				printf("./%s\n", dnt->d_name);
		}

		closedir(dir);
	}
	else
	{
		printf("find: <<%s>>: No existe el fichero o el directorio\n", path);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int find(char* path)
{
	DIR *dir;
	struct dirent *dnt;

	if ((dir = opendir(path)) != NULL)
	{
		while ((dnt = readdir(dir)) != NULL)
		{
			if (dnt->d_name[1] != '.')
			{
				if(dnt->d_name[0] == '.')
					printf("%s\n", dnt->d_name);
				else
					printf("./%s\n", dnt->d_name);
			}
		}

		closedir(dir);
	}
	else
	{
		printf("find: <<%s>>: No existe el fichero o el directorio\n", path);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void show_help()
{
	printf("Uso: find [path...] [expressions]\n\n"
		   "El path por default es el directorio actual.\n\n"
		   "Nota: este programa sigue en desarrollo.\n\n");
	printf("opciones normales (simpre verdaderas, especificar antes de otras expresiones):\n"
		   "      --help --version [aún en desarrollo...]\n\n");
	printf("pruebas:\n"
		   "      -empty -name PATTERN [aún en desarrollo...]\n\n");
	printf("Informe sobre bugs (y siga el progreso de su corrección) a través de la\n"
           "página de comunicación de bugs en http://bugs.amayaos.com/ o bien, si no\n"
           "tiene acceso a web, enviando un mensaje a <amaya@amayaos.com>.\n");
}

void show_version()
{
	printf("find (AmayaOS findutils) 1.0\n");
	printf("Copyright (C) 2015 Free Software Foundation, Inc.\n"
		   "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.\n"
		   "This is free software: you are free to change and redistribute it.\n"
		   "There is NO WARRANTY, to the extent permitted by law.\n\n");
	printf("Written by Dan Rulos and Alvaro Stagg.\n");
}
