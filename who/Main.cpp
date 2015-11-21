/*
 * Copyright (C) 2015 Dan Rulos, Alvaro Stagg [alvarostagg@openmailbox.org]
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

#include <unistd.h>
#include <stdlib.h>
#include "who.h"

int main(int argc, char **argv)
{
	
	char host[128];
	/* Obtenemos el usuario actual */
	gethostname(host, sizeof(host));
	/* funcion principal */
	WhoCommand who(host);
	
	return EXIT_SUCCESS;
}
