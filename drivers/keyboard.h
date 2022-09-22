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

void keyboardHandler(void);                                             // Called everytime the keyboard interrupt fires
void sendKeyboardCommand(int command);                                  // Sends a command to the keyboard (port 0x60)
void sendControllerCommand(int command);                                // Sends a command to the keyboard controller (port 0x64)

// I/O Ports that the keyboard uses (There is a Controller on the motherboard and a Encoder on the keyboard)
#define EncoderCommandPort 0x60                                         // This is the port where we send commands to the keyboard
#define EncoderDataPort 0x60                                            // This is the port we read to get out scancodes

#define ControllerCommandPort 0x64                                      // This is the port where we send commands to the onboard keyboard controller
#define ControllerStatusPort 0x64                                       // This is the port we read to get the status of the keyboard

/*
 * Constants to keep track of special keys and events
 *
 */

#define ACK 0xFA                                                        // The Success response of the keyboard
#define RESND 0xFE                                                      // The command failed response of the keyboard

// The scanCode of the down press
#define ESC 0x01
#define DEL 0x0E
#define TAB 0x0F
#define RET 0x1C

#define LSHIFT 0x2A
#define RSHIFT 0x36

#define CAPLK 0x3a
#define NUMLK 0x45
#define SCRLK 0x46

#define CTL 0x1d
#define ALT 0x38
/**********************************************************************/

// The scanCode of the up press
#define ESC_UP 0x81
#define DEL_UP 0x8E
#define TAB_UP 0x8F
#define RET_UP 0x9C

#define LSHIFT_UP 0xAA
#define RSHIFT_UP 0xB6

#define CAPLK_UP 0xBA
#define NUMLK_UP 0xC5
#define SCRLK_UP 0xC6

#define CTL_UP 0x9d
#define ALT_UP 0xb8
/**********************************************************************/

