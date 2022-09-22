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

void initPIT(int channel, int accessMode, int timerMode, int hertz);    // Initialize timer
void timerHandler(void);                                                // Called everytime the timer fires an interrupt

// Functions so the kernel can communicate with the time system
void wait(int Msecs);                                                   // Waits the specified number of milliseconds

