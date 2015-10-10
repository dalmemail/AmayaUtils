/*
 * Copyright (C) 2009 Alexander Schrijver, 2015 Alvaro Stagg [alvarostagg@openmailbox.org]
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
#include <fcntl.h>

int main(int argc, char* argv[])
{
  int i, j, args = 1;
  // fp = file
  int fp;

  // "Bools"
  int n_line = 1;

  for(i = 1; i < argc; i++)
  {
    if(args == 1 && (strcmp(argv[i], "-n") == 0))
    {
      n_line = 0;
      continue;
    }
    if(args == 1 && (strcmp(argv[i], ">") == 0))
    {
      for(j = 0; j < i; j++)
      {
        // If file exists
        if((fp = open(argv[i + 1], O_WRONLY)) == 0)
        {
          write(fp, argv[j - 1], strlen(argv[j - 1]));
          write(fp, "\r\n", 2);
          close(fp);
          return 0;
        }
        else
        {
          // If file doesn't exists
          if((fp = open(argv[i + 1], O_RDWR | O_CREAT| S_IWUSR | S_IRUSR, 0666)) == 0)
          {
            write(fp, argv[j - 1], strlen(argv[j - 1]));
            write(fp, "\r\n", 2);
            close(fp);
            return 0;
          }
          // There was an error...
          else
          {
            return -1;
          }
        }
      }
    }
    if(args == 1 && (strcmp(argv[i], ">>") == 0))
    {
      for(j = 0; j < i; j++)
      {
        // If file exists
        if((fp = open(argv[i + 1], O_WRONLY | O_APPEND)) == 0)
        {
          write(fp, argv[j - 1], strlen(argv[j - 1]));
          write(fp, "\r\n", 2);
          close(fp);
          return 0;
        }
        else
        {
          // If file doesn't exists
          if((fp = open(argv[i + 1], O_RDWR | O_CREAT| S_IWUSR | S_IRUSR, 0666)) == 0)
          {
            write(fp, argv[j - 1], strlen(argv[j - 1]));
            write(fp, "\r\n", 2);
            close(fp);
            return 0;
          }
          // There was an error...
          else
          {
            return -1;
          }
        }
      }
    }

    args = 0;
    printf("%s ", argv[i]);
  }

  if(n_line)
    printf("\n");

  return 0;
}
