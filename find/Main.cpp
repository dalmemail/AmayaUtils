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

#include "find.h"

int main(int argc, char **argv)
{
	int ret = EXIT_SUCCESS, cnt = 0;

	/* default return */
	char cwd[128];
	getcwd(cwd, sizeof(cwd));

	Find find;

	if (argc < 2)
	{
		ret = find.find(cwd);
	}
	else
	{
		for (int i = 0; i < argc; i++)
		{
			if((strcmp(argv[i], "-help")) == 0 || (strcmp(argv[i], "--help")) == 0)
			{
				cnt = 1;
				break;
			}
			if((strcmp(argv[i], "-version")) == 0 || (strcmp(argv[i], "--version")) == 0)
			{
				cnt = 2;
				break;
			}
		}
	}

	if(cnt == 1)
		find.show_help();
	else if(cnt == 2)
		find.show_version();
	else
	{
		for (int i = 0; i < argc; i++)
		{
			if((strcmp(argv[i], "-name")) == 0)
			{
				if(argv[i - 1] == argv[0])
					ret = find.find(cwd, argv[i + 1]);
				else
					ret = find.find(argv[i - 1], argv[i + 1]);
			}
			if((strcmp(argv[i], "-empty")) == 0)
			{
				if(argv[i - 1] == argv[0])
					ret = find.find_empty(cwd);
				else
					ret = find.find_empty(argv[1]);
			}
		}
	}

	return ret;
}
