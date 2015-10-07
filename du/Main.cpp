/*
 * Copyright (C) 2015 Alvaro Stagg [alvarostagg@openmailbox.org]
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

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

void show_help();

size_t get_file_size(char* path);

int main(int argc, char* argv[])
{
  int i, args = 1, newline = 0, hr = 0;
  // hr = human readable
  size_t sz;
  // sz = size
  char* fst;
  // fst = File Size Tag

  for(i = 1; i < argc; i++)
  {
    // Los if's no están anidados por obvias razones...
    if(args == 1 && strcmp(argv[i], "--help") == 0)
    {
      show_help();
      return 0;
    }
    if(args == 1 && ((strcmp(argv[i], "-0") == 0) || (strcmp(argv[i], "--null") == 0)))
    {
      newline = 1;
      continue;
    }
    if(args == 1 && ((strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "--human-readable") == 0)))
    {
      hr = 1;
      continue;
    }

    // Obtenemos el tamaño del archivo en Bytes
    sz = get_file_size(argv[i]);

    // Empieza la magia
    if(hr) // Quiere que salgan las medidas (B -> Bytes, KB -> KiloBytes, MG -> MegaBytes, GB -> GigaBytes)
    {
      if(sz < 1024)
	fst = "B";
      if(sz >= (1024))
        fst = "KB";
      if(sz >= (1024 * 1024))
	fst = "MB";
      if(sz >= (1024 * 1024 * 1024))
	fst = "GB";

      printf("%d%s	%s", sz, fst, argv[i]);
    }
    else // No quiere que salgan las medidas...
      printf("%d	%s", sz, argv[i]);
  }

  if(!newline)
    printf("\n");

  return 0;
}

// Muestra una ayuda
void show_help()
{
  printf("Modo de empleo: du [OPCIÓN]... [FICHERO]...\n"
	 "       o bien:  du [OPCIÓN]... --files0-from=F\n\n");
  printf("Los argumentos obligatorios para las opciones largas son también obligatorios\npara las opciones cortas.\n");
  printf("  -0, --null            termina cada línea con NUL, no con nueva línea\n");
  printf("  -h, --human-readable  muestra los tamaños de forma legible\n"
         "                        (p. ej., 1K 234M 2G)\n");
  printf("\n\n[Trabajando en el resto...]\n\n");
}

// Función para obtener el tamaño del archivo
size_t get_file_size(char* path)
{
  struct stat st;

  if(stat(path, &st) < 0)
    return -1;

  return st.st_size;
}
