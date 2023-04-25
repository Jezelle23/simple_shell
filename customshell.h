#ifndef _CUSTOMSHELL_H_
#define _CUSTOMSHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>


#define INPUT_BUFF 1024
#define OUTPUT_BUFF 1024
#define BUFF_SHELL -1


#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3


#define CONVERT_LOWER	1
#define CONVERT_FUNCTION	2
#define CALL_LINE 0
#define USE_STRTOK 0
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct listOfString - linkedlist of strings
 * @num: number
 * @str: string
 * @next: next node ptr
 */
typedef struct listOfString
{
	int num;
	char *str;
	struct listOfString *next;
} list_t;

/**
 *struct giveInfo - has related info for passing to functions
 *@arg: string made for arguments
 *@argv: array of string arguments
 *@path: path for a command
 *@argc: count of args
 *@line_count: error count
 *@errorInt: error code
 *@countl: line count
 *@fileword: file name of code
 *@env: list of copy of env
 *@environ: modified copy of list env
 *@history: node of history
 *@alias: node of alias
 *@changedenviro: env changed or not
 *@result: ret output of last command
 *@commandbuff: pointer location of command buff
 *@membuff: type of command & | ;
 *@readfd: file where we read line in
 *@historycount: line number count of prev
 */
typedef struct giveInfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int errorInt;
	int countl;
	char *fileword;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int changedenviro;
	int result;

	char **membuff;
	int commandbuff;
	int readfd;
	int historycount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - built in strings for function
 *@type: cmd flag
 *@func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

int shellLoop(info_t *, char **);
int getBIcmd(info_t *);
void getCommand(info_t *);
void forkCommand(info_t *);
int cmdcheck(info_t *, char *);
void errorout(char *);
int displaye(char);
int dispfd(char c, int fd);
int displayin(char *str, int fd);
char *cloneChars(char *, int, int);
char *pathSearch(info_t *, char *, char *);
int _strlen(char *);
int stringcomp(char *, char *);
char *copyString(char *, char *);
char *duplicateString(const char *);
char *copytext(char *, char *, int);
char *cat2str(char *, char *, int);
char *charaloc(char *, char);
void printString(char *);
int _putchar(char);
char *str_Prefix(const char *, const char *);
char *_strcat(char *, char *);
char **splitDelStr(char *, char *);
char **splitDelStr2(char *, char);
char *setMemory(char *, char, unsigned int);
void freestr(char **);
void *reallocMemory(void *, unsigned int, unsigned int);
int pointfree(void **);
int shelli(info_t *);
int shell_delim(char, char *);
int alphaCheck(int);
int str2int(char *);
int convString2int(char *);
void display_errmsg(info_t *, char *);
int decint(int, int);
char *convertfunction(long int, int, int);
void replacetext(char *);
int shellEscape(info_t *);
int displayHist(info_t *);
int copyAlias(info_t *);
ssize_t lineneg(info_t *);
int callstr(info_t *, char **, size_t *);
void blocksig(int);
void info_init(info_t *);
void set_stone(info_t *, char **);
void releasew(info_t *, int);
int directChange(info_t *);
int change_currP(info_t *);
char *callenv(info_t *, const char *);
int currenviro(info_t *);
int initialen(info_t *);
int remenviroV(info_t *);
int poplinkedenv(info_t *);
int enviroInit(info_t *, char *, char *);
list_t *node_append(list_t **, const char *, int);
int deletenodeI(list_t **, unsigned int);
void freenodes(list_t **);
list_t *node_appendLast(list_t **, const char *, int);
size_t strList_print(const list_t *);
char *getFileHist(info_t *info);
int histListBuild(info_t *info, char *buf, int linecount);
int histWrite(info_t *info);
int histRead(info_t *info);
int histNumbAssign(info_t *info);
char **stringcopyenv(info_t *);
int delenviro(info_t *, char *);
int isMultiDelim(info_t *, char *, size_t *);
void shouldChain(info_t *, char *, size_t *, size_t, size_t);
int repalias(info_t *);
int switchvar(info_t *);
int switchString(char **, char *);
size_t getListlen(const list_t *);
char **textlist(list_t *);
size_t displaydet(const list_t *);
list_t *retnode(list_t *, char *, char);
ssize_t getnodeI(list_t *, list_t *);

#endif
