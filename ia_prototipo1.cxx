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
#include <unistd.h>

using namespace std;

int main()
{

    string Laberinto[12][12] = {
        { "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X" },
        { "X", "P", "O", "O", "Y", "X", "X", "X", "X", "X", "X", "X" },
        { "X", "X", "X", "O", "X", "X", "X", "X", "X", "X", "X", "X" },
        { "X", "O", "O", "O", "O", "O", "O", "O", "X", "X", "X", "X" },
        { "X", "Y", "X", "X", "X", "X", "X", "O", "X", "X", "X", "X" },
        { "X", "X", "X", "Y", "X", "Y", "X", "O", "X", "X", "X", "X" },
        { "X", "O", "O", "O", "X", "O", "O", "O", "X", "X", "X", "X" },
        { "X", "O", "X", "O", "X", "X", "X", "O", "O", "X", "X", "X" },
        { "X", "O", "X", "O", "X", "X", "X", "X", "O", "X", "X", "X" },
        { "X", "O", "X", "O", "O", "O", "O", "O", "O", "O", "O", "X" },
        { "X", "Y", "X", "X", "X", "X", "X", "X", "X", "X", "Y", "X" },
        { "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X" }
    };
    
    int objetivosAlcanzados = 0;
    int totalObjetivos = 0;
    
    for(int x = 1; x <= 11; x++)
    {
      for(int y = 1; y <= 11; y++)
      {
        if(Laberinto[x][y] == "Y");
        {
          totalObjetivos++;
        }
      }
    }

    int posY = 1;
    int posX = 1;

    int prevV = -1;
    int prevH = -1;

    int priorizarH = 1;
    int priorizarV = 0;
    
    int posOriginX = 1;
    int posOriginY = 1;
    
    bool objetivoAlcanzado = false;

    for (int baz = 0; baz < 144; baz++) {
        system("CLS");
        for (int x = 0; x <= 12; x++) {
            for (int y = 0; y <= 12; y++) {
                //LOGICA DE LA IA
                /////////////////////
                
                //MOVIMIENTOS HORIZONTALES
                if (priorizarH == 1) {
                    if (prevH == -1) {
                        if (Laberinto[posY][posX + 1] == "O") {
                            Laberinto[posY][posX] = "O";

                            posX += 1;

                            Laberinto[posY][posX] = "P";
                            prevH = -1;
                            
                            if(posY == posOriginX && posX == posOriginY) {
                              prevH = 1;
                            }
                            
                            //SI ENCUENTRA UNA POSICION ABAJO
                            if((Laberinto[posY + 1][posX] == "O" || Laberinto[posY - 1][posX] == "O") && objetivoAlcanzado == true)
                            {
                              priorizarH = 0;
                              priorizarV = 1;
                              objetivoAlcanzado = false;
                            } else if(Laberinto[posY + 1][posX] == "X" && objetivoAlcanzado == false) {
                              priorizarH = 1;
                              priorizarV = 0;
                              cout << "LLEGO A PRIORIZAR HORIZONTALL\n";
                            }
                        }
                        else if (Laberinto[posY][posX + 1] == "Y") {
                            Laberinto[posY][posX] = "O";

                            posX += 1;

                            Laberinto[posY][posX] = "P";

                            objetivosAlcanzados++;
                            cout << objetivosAlcanzados << "/" << totalObjetivos << " objetivos fueron logrados en la posicion X:" << posY << " Y:" << posX << "\n";
                            prevH = 1;
                            objetivoAlcanzado = true;
                        }
                    }
                    else {
                        if (Laberinto[posY][posX - 1] == "O") {
                            Laberinto[posY][posX] = "O";

                            posX -= 1;

                            Laberinto[posY][posX] = "P";
                            prevH = 1;
                            
                            if(posY == posOriginX && posX == posOriginY) {
                              prevH = -1;
                            }
                            
                            //SI ENCUENTRA UNA POSICION ABAJO
                            if((Laberinto[posY + 1][posX] == "O" || Laberinto[posY - 1][posX] == "O") && objetivoAlcanzado == true)
                            {
                              priorizarH = 0;
                              priorizarV = 1;
                              objetivoAlcanzado = false;
                            } else if(Laberinto[posY + 1][posX] == "X" && objetivoAlcanzado == false) {
                              priorizarH = 1;
                              priorizarV = 0;
                              cout << "LLEGO A PRIORIZAR HORIZONTAL\n";
                            }
                        }
                        else if (Laberinto[posY][posX - 1] == "Y") {
                            Laberinto[posY][posX] = "O";

                            posX -= 1;

                            Laberinto[posY][posX] = "P";
                            
                            objetivosAlcanzados++;
                            cout << objetivosAlcanzados << "/" << totalObjetivos << " objetivos fueron logrados en la posicion X:" << posY << " Y:" << posX << "\n";
                            prevH = -1;
                            objetivoAlcanzado = true;
                        }
                    }
                }
                //MOVIMIENTOS VERTICALES
                else if (priorizarV == 1) {
                    if (prevV == -1) {
                        if (Laberinto[posY + 1][posX] == "O") {
                            Laberinto[posY][posX] = "O";

                            posY += 1;

                            Laberinto[posY][posX] = "P";
                            prevV = -1;
                            
                            //SI ENCUENTRA UNA POSICION AL LADO
                            if((Laberinto[posY][posX + 1] == "O" || Laberinto[posY][posX - 1] == "O") && objetivoAlcanzado == false)
                            {
                              priorizarH = 1;
                              priorizarV = 0;
                              objetivoAlcanzado = false;
                            } else if((Laberinto[posY][posX - 1] == "X" || Laberinto[posY][posX + 1] == "X") && objetivoAlcanzado == false) {
                              priorizarH = 0;
                              priorizarV = 1;
                              cout << "LLEGO A PRIORIZAR VERTICAL\n";
                            }
                        }
                        else if (Laberinto[posY][posX + 1] == "Y") {
                            Laberinto[posY][posX] = "O";

                            posX += 1;

                            Laberinto[posY][posX] = "P";
                            
                            objetivosAlcanzados++;
                            cout << objetivosAlcanzados << "/" << totalObjetivos << " objetivos fueron logrados en la posicion X:" << posY << " Y:" << posX << "\n";
                            objetivoAlcanzado = true;
                        }
                    }
                    else {
                        if (Laberinto[posY - 1][posX] == "O") {
                            Laberinto[posY][posX] = "O";

                            posY -= 1;

                            Laberinto[posY][posX] = "P";
                            prevV = 1;
                            
                            //SI ENCUENTRA UNA POSICION AL LADO
                            if((Laberinto[posY][posX + 1] == "O" || Laberinto[posY][posX - 1] == "O") && objetivoAlcanzado == false)
                            {
                              priorizarH = 1;
                              priorizarV = 0;
                              objetivoAlcanzado = false;
                            } else if((Laberinto[posY][posX - 1] == "X" || Laberinto[posY][posX + 1] == "X") && objetivoAlcanzado == true) {
                              priorizarH = 0;
                              priorizarV = 1;
                              cout << "LLEGO A PRIORIZAR VERTICAL\n";
                            }
                        }
                        else if (Laberinto[posY - 1][posX] == "Y") {
                            Laberinto[posY][posX] = "O";

                            posY -= 1;

                            Laberinto[posY][posX] = "P";

                            objetivosAlcanzados++;
                            cout << objetivosAlcanzados << "/" << totalObjetivos << " objetivos fueron logrados en la posicion X:" << posY << " Y:" << posX << "\n";
                            objetivoAlcanzado = true;
                        }
                    }
                }

                if (prevH == -1 && Laberinto[posY + 1][posX] == "X" && prevV != -1) {
                    prevH = 1;
                }

                if (prevV == -1 && Laberinto[posY][posX + 1] == "X" && prevH != -1) {
                    prevV == 1;
                }

                for (int foo = 1; foo <= 11; foo++) {
                    for (int bar = 1; bar <= 11; bar++) {
                        cout << Laberinto[foo][bar];
                    }
                    cout << "\n";
                }
                cout << "\n";
                sleep(1);
            }
        }
    }

    return 0;
}
