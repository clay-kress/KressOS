/***********************************************************************/
/* Copyright (c) 2022 Clay Kress                                       */
/*                                                                     */
/* This file is part of KressOS.                                       */
/* KressOS is free software: you can redistribute it and/or modify it  */
/* under the terms of the GNU General Public License as published by   */
/* the Free Software Foundation, either version 3 of the License, or   */
/* (at your option) any later version.                                 */
/*                                                                     */
/* Foobar is distributed in the hope that it will be useful,           */
/* but WITHOUT ANY WARRANTY; without even the implied warranty         */
/* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.             */
/*                                                                     */
/* See the GNU General Public License for more details.                */
/*                                                                     */
/* You should have received a copy of the GNU General Public License   */
/* along with Foobar. If not, see <https://www.gnu.org/licenses/>.     */
/*                                                                     */
/***********************************************************************/

void reboot(void);

// ex: memCopy(0x7c00, 0x7e00, 50);
// This moves 50 bytes from 7c00 to 7e00 (overwriting nessesary bytes in the process)
void memCopy(char* source, char* dest, int NumBytes);
void memSet(char* low, char* high, char byteVal);

unsigned char byteREAD(unsigned short port);
unsigned short wordREAD(unsigned short port);

void byteWRITE(unsigned short port, unsigned char data);
void wordWRITE(unsigned short port, unsigned short data);

