/*
 * ia_prototipo1.cxx
 *
 * Copyright 2019 NikitaRus <NikitaRus@DESKTOP-3JU6D2V>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */


#include <iostream>

using namespace std;

int main()
{
	
	string Laberinto[12][12] = {
		{"X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X"},
		{"X", "P", "O", "O", "Y", "X", "X", "X", "X", "X", "X", "X"},
		{"X", "X", "X", "O", "X", "X", "X", "X", "X", "X", "X", "X"},
		{"X", "O", "O", "O", "O", "X", "X", "X", "X", "X", "X", "X"},
		{"X", "Y", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X"},
		{"X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X"},
		{"X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X"},
		{"X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X"},
		{"X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X"},
		{"X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X"},
		{"X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X"},
		{"X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X"}
	}
	
	int posX = 1;
	int posY = 1;
	for(int baz = 0; baz < 144; baz++)
	{
		for(int x = 0; x <= 12; x++)
		{
		  for(int y = 0; y <= 12; y++)
		  {

		    //LOGICA DE LA IA
		    /////////////////////
		    if(Laberinto[posX + 1][posY] == "O" && (Laberinto[posX - 1][posY] != "X" && Laberinto[posX][posY + 1] != "X" && Laberinto[posX][posY - 1] != "X"))
		    {
		      Laberinto[posX][posY] = "O";

		      posX += 1;

		      Laberinto[posX][posY] = "P";
		    }
		    else if(Laberinto[posX - 1][posY] == "O" && (Laberinto[posX + 1][posY] != "X" && Laberinto[posX][posY + 1] != "X" && Laberinto[posX][posY - 1] != "X"))
		    {
		      Laberinto[posX][posY] = "O";

		      posX -= 1;

		      Laberinto[posX][posY] = "P";
		    }
		    else if(Laberinto[posX][posY + 1] == "O" && (Laberinto[posX - 1][posY] != "X" && Laberinto[posX + 1][posY] != "X" && Laberinto[posX][posY - 1] != "X"))
		    {
		     Laberinto[posX][posY] = "O";

		      posY += 1;

		      Laberinto[posX][posY] = "P";
		    }
		    else if(Laberinto[posX][posY - 1] == "O" && (Laberinto[posX - 1][posY] != "X" && Laberinto[posX + 1][posY] != "X" && Laberinto[posX][posY + 1] != "X"))
		    {
		      Laberinto[posX][posY] = "O";

		      posY -= 1;

		      Laberinto[posX][posY] = "P";
		    }

		    for(int foo = 1; foo <= 11; foo++)
		    {
		      for(int bar = 1; bar <= 11; bar++)
		      {
			cout << Laberinto[bar][foo];
		      }
			    cout << "\n";
		    }
		  }
		}
	}
	
	
	
	
	return 0;
}

