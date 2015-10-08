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
void show_version();

size_t get_file_size(char* path);

int main(int argc, char* argv[])
{
  int i, args = 1, newline = 0, hr = 0, _si = 0;
  /* hr  = human readable
   * _si = lo mismo que hr pero en potencias de 1000
   */
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
    if(args == 1 && strcmp(argv[i], "--version") == 0)
    {
      show_version();
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
    if(args == 1 && (strcmp(argv[i], "--si") == 0))
    {
      _si = 1;
      continue;
    }

    // Obtenemos el tamaño del archivo en Bytes
    sz = get_file_size(argv[i]);

    // Empieza la magia
    if(hr) // Quiere que salgan las medidas (B -> Bytes, K -> KiloBytes, M -> MegaBytes, G -> GigaBytes) [Potencias de 1024]
    {
      // Potencias de 1024
      if(sz < 1024)
      {
        fst = "B";
      }
      else if(sz >= (1024))
      {
        fst = "K";
        sz = sz / (1024);
      }
      else if(sz >= (1024 * 1024))
      {
        fst = "M";
        sz = sz / (1024 * 1024);
      }
      else if(sz >= (1024 * 1024 * 1024))
      {
        fst = "G";
        sz = sz / (1024 * 1024 * 1024);
      }

      printf("%d%s	%s", sz, fst, argv[i]);
    }
    else if(_si) // Quiere que salgan las medidas (B -> Bytes, KB -> KiloBytes, MB -> MegaBytes, GB -> GigaBytes) [Potencias de 1000]
    {
      // Potencias de 1000
      if(sz < 1000)
      {
        fst = "B";
      }
      else if(sz >= (1000))
      {
        fst = "k";
        sz = sz / (1000);
      }
      else if(sz >= (1000 * 1000))
      {
        fst = "M";
        sz = sz / (1000 * 1000);
      }
      else if(sz >= (1000 * 1000 * 1000))
      {
        fst = "G";
        sz = sz / (1000 * 1000 * 1000);
      }

      printf("%d%s	%s", sz, fst, argv[i]);
    }
    else // No quiere que salgan las medidas...
      printf("%d	%s", sz, argv[i]);
  }

  // En caso de que quiera terminar con una línea NUL
  if(!newline)
    printf("\n");

  // Limpiamos
  fst = NULL;
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
  printf("      --si              como -h, pero utiliza potencias de 1000, no de 1024\n");
  printf("      --help     muestra esta ayuda y finaliza\n");
  printf("      --version  informa de la versión y finaliza\n");
  printf("\n\n[Trabajando en el resto...]\n\n");
}

// Muestra la versión y algunos detalles de la licencia
void show_version()
{
  printf("du (AmayaOS coreutils) 0.5.4\n");
  printf("Copyright © 2015 AmayaOS Team, Inc.\n"
         "Licencia GPLv3+: GPL de GNU versión 3 o posterior\n"
         "<http://gnu.org/licenses/gpl.html>.\n");
  printf("Esto es software libre: usted es libre de cambiarlo y redistribuirlo.\n");
  printf("No hay NINGUNA GARANTÍA, hasta donde lo permite la ley.\n\n");
  printf("Escrito por Alvaro Stagg.\n");
}

// Función para obtener el tamaño del archivo
size_t get_file_size(char* path)
{
  struct stat st;

  if(stat(path, &st) < 0)
    return -1;

  return (double)st.st_size;
}
