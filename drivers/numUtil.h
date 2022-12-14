/***********************************************************************/
/* Copyright (c) 2022 Clay Kress                                       */
/*                                                                     */
/* This file is part of KressOS.                                       */
/* KressOS is free software: you can redistribute it and/or modify it  */
/* under the terms of the GNU General Public License as published by   */
/* the Free Software Foundation, either version 3 of the License, or   */
/* (at your option) any later version.                                 */
/*                                                                     */
/* KressOS is distributed in the hope that it will be useful,          */
/* but WITHOUT ANY WARRANTY; without even the implied warranty         */
/* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.             */
/*                                                                     */
/* See the GNU General Public License for more details.                */
/*                                                                     */
/* You should have received a copy of the GNU General Public License   */
/* along with KressOS. If not, see <https://www.gnu.org/licenses/>.    */
/*                                                                     */
/***********************************************************************/

#define pi 3.1415
#define e 2.7182

float pwr(float base, float exponent);                                  // Calculates base to the power of exponent
float log2(float x);                                                    // Calculates log base 2 of X

float absVal(float number);                                             // Calculates the absolute value of number
int sign(float number);                                                 // Returns the sign of number (+ or -)


// Functions to determine the length of a number (in different bases)
int numDigits(int number, int base);

