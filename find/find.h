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

#ifndef FIND_H
#define FIND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* find() seeks files on path */
int find(char* path);
/* find() seeks file on path */
int find(char *path, char *file);
/* find_empty() seeks empty files on path */
int find_empty(char *path);
/* show_help() show a little help */
void show_help();
/* show_version() show version */
void show_version();

#endif
