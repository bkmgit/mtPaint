/*	inifile.h
	Copyright (C) 2007-2019 Dmitry Groshev

	This file is part of mtPaint.

	mtPaint is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 3 of the License, or
	(at your option) any later version.

	mtPaint is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with mtPaint in the file COPYING.
*/

typedef struct {
	char *key, *value, *defv;
	int sec, chain;
	short type, flags;
} inislot;

typedef struct {
	char *sblocks;
	inislot *slots;
	gint32 *hash;
	int count, slen, maxloop;
	guint32 hmask, seed[2];
} inifile;

/* Access macros */

#define INI_KEY(P,N)  ((P)->slots[(N)].key)
#define INI_VALUE(P,N)  ((P)->slots[(N)].value)
#define INI_PARENT(P,N) ((P)->slots[(N)].sec)

/* Iterator macros */

#define INI_FIRST(P,N) ((int)(P)->slots[(N)].defv)
#define INI_NEXT(P,N) ((P)->slots[(N)].chain)

/* Core functions */

int new_ini(inifile *inip);
void forget_ini(inifile *inip);
int read_ini(inifile *inip, char *fname, int itype);
int write_ini(inifile *inip, char *fname, char *header);

int ini_setstr(inifile *inip, int section, char *key, char *value);
int ini_setint(inifile *inip, int section, char *key, int value);
int ini_setbool(inifile *inip, int section, char *key, int value);
int ini_setref(inifile *inip, int section, char *key, int value);

char *ini_getstr(inifile *inip, int section, char *key, char *defv);
int ini_getint(inifile *inip, int section, char *key, int defv);
int ini_getbool(inifile *inip, int section, char *key, int defv);
int ini_getref(inifile *inip, int section, char *key, int defv);

int ini_setsection(inifile *inip, int section, char *key);
int ini_getsection(inifile *inip, int section, char *key);

int ini_transient(inifile *inip, int section, char *key);

/* File functions */

char *slurp_file_l(char *fname, int before, int *len);
#define slurp_file(A,B) slurp_file_l((A), (B), NULL)
char *get_home_directory(void);
char *extend_path(const char *path);

/* Helper functions */

int str2bool(const char *s);

/* Compatibility functions */

inifile main_ini;

void inifile_init(char *system_ini, char *user_ini);
void inifile_quit();

char *inifile_get(char *setting, char *defaultValue);
int inifile_get_gint32(char *setting, int defaultValue);
int inifile_get_gboolean(char *setting, int defaultValue);

int inifile_set(char *setting, char *value);
int inifile_set_gint32(char *setting, int value);
int inifile_set_gboolean(char *setting, int value);
