/*
Copyright (C) 1996-2001 Id Software, Inc.
Copyright (C) 2010-2014 QuakeSpasm developers

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#ifndef _QUAKE_SYS_H
#define _QUAKE_SYS_H

// sys.h -- non-portable functions

void Sys_Init (void);

// retrieves the directory where *Steam* is installed (not Steam Quake!)
qboolean Sys_GetSteamDir (char *path, size_t pathsize);

// fills in the user-specific path where add-ons are downloaded
// (%userprofile%\Saved Games\Nightdive Studios\Quake)
qboolean Sys_GetSteamQuakeUserDir (char *path, size_t pathsize, const char *library);

//
// file IO
//

// returns the file size or -1 if file is not present.
// the file should be in BINARY mode for stupid OSs that care
int Sys_FileOpenRead (const char *path, int *hndl);

int Sys_FileOpenWrite (const char *path);
void Sys_FileClose (int handle);
void Sys_FileSeek (int handle, int position);
int Sys_FileRead (int handle, void *dest, int count);
int Sys_FileWrite (int handle,const void *data, int count);
qboolean Sys_FileExists (const char *path);
void Sys_mkdir (const char *path);
FILE *Sys_fopen (const char *path, const char *mode);
int Sys_remove (const char *path);

typedef enum {
	FA_DIRECTORY	= 1 << 0,
} fileattribs_t;

typedef struct findfile_s {
	fileattribs_t	attribs;
	char			name[MAX_OSPATH];
} findfile_t;

findfile_t *Sys_FindFirst (const char *dir, const char *ext);
findfile_t *Sys_FindNext (findfile_t *find);

// Only needs to be called manually when breaking out of the loop,
// otherwise the last Sys_FindNext will also close the handle
void Sys_FindClose (findfile_t *find);

//
// system IO
//
FUNC_NORETURN void Sys_Quit (void);
FUNC_NORETURN void Sys_Error (const char *error, ...) FUNC_PRINTF(1,2);
// an error will cause the entire program to exit
#ifdef __WATCOMC__
#pragma aux Sys_Error aborts;
#pragma aux Sys_Quit aborts;
#endif

void Sys_Printf (const char *fmt, ...) FUNC_PRINTF(1,2);
// send text to the console

double Sys_DoubleTime (void);

const char *Sys_ConsoleInput (void);

void Sys_Sleep (unsigned long msecs);
// yield for about 'msecs' milliseconds.

void Sys_SendKeyEvents (void);
// Perform Key_Event () callbacks until the input que is empty

void Sys_RemoveKeyFilter (void);

#endif	/* _QUAKE_SYS_H */

