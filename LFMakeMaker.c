/*
 *  LFMakeMaker
 *
 *  � LFSoft 1997-2018
 *
 *   I wrote this little code for automaticaly creating MakeFile for
 *  GCC (but may be used with others compilers).
 *   It was developped on the Amiga in a portable way. No Amiga
 *  specific function is used... see ports notes.
 *
 *  French words:
 *  -------------
 *   Ouais, je sais, �a la fout mal qu'un programme fait par un fran�ais ne
 *  soit pas en fran�ais! Cependant, pensez � votre r�action face � un
 *  programme m�ga g�nial dont vous ne comprenez pas un mot... (je ne veux pas
 *  dire non plus que ce programme est m�ga-g�nial, � vous de juger).
 *
 *   C'est pourquoi, hormis ces quelques mots, le reste du source
 *  est majoritairement en anglais (d'ailleurs pas terrible).
 *
 *   Je suis toujours � la recherche de bonnes �mes pour traduire mes
 *  productions & pour r�diger des documentations qui tiennent le coup...
 *
 *   Actuellement, je n'ai pas le temps de localiser ce programme! Peut-�tre
 *  pour une prochaine version...
 *
 *  How to use it:
 *  ~~~~~~~~~~~~~~
 *      LFMakeMaker [option] source_files
 *
 *   Invoque 'LFMakeMaker' without any argument to get the list of available
 *  options. Never forget that a source is affected only by options before it.
 *  E.g.:
 *      LFMakeMaker file1.c +c=truc.h file2.c -c=truc.h file3.c
 *  'truc.h' is only checked in file2.c.
 *
 *   Before reading arguments, LFMakeMaker looks for "LFMakeMaker"
 *  environnemental variable that may contains always used options. Its best
 *  use is to define path to your include directories tree (-I option).
 *  Look at your compiler's documentation about where includes are
 *  located. Some compilers like Gcc may display all include directories at
 *  run time but adding '-v' argument (or --verbose) to the command line.
 *
 *  This is an example of LFMakeMaker variable content i use with GCC 2.7.0
 *  on my Amigas:
 *
  setenv LFMakeMaker "-I/gnu/lib/gcc-lib/m68k-cbm-amigados/2.7.0/g++-include/
    -I/gnu/lib/g++-include/ -I/gnu/local/include/
    -I/gnu/m68k-cbm-amigados/include/
    -I/gnu/lib/gcc-lib/m68k-cbm-amigados/2.7.0/include/ -I/gnu/os-include/
    -I/gnu/include/"
 *
 *  Notes:
 *  ~~~~~~
 *  -If an #include "" can't be found in the current directory, it'll be
 *  searched AS A GLOBAL #include (so --global, ... apply to it).
 *
 *  -LFMakeMaker understand C and C++ source code. In all cases, C++ comments
 *  '//' are allowed. Remember, it looks only for '#include' statement, custom
 *  commands like GNU's '#includenext' are IGNORED...
 *
 *  -This tool tries to interpret C's syntax in source files, so commented out
 *  includes are ignored (as your compiler does). On the other hand, it does
 *  nothing with preprocessor's #if.
 *
 *  -Because it's not a real compiler, it is somewhat easy to trouble syntax
 *  parsing of LFMakeMaker. In other words: Intended use of this tool is for
 *  "civilized" source code; if your source have syntax error, then LFMakeMaker
 *  may generate wrong makefile.
 *
 *  -Because of preprocessor's #if are ignored, be carefull about '{}' paires.
 *  For example:
 *      ...
 *  #ifdef DEBUG
 *      if(ok && test){ // }
 *  #else
 *      if(ok){
 *  #endif
 *  Notez-bien : One of the opening '{' is paired by a commented-out '}'.
 *  The second is paired (as usual) at the block-ending.
 *
 *  -again because of #if, be carefull with the "--fatal" option as include
 *  file may be searched even if it's not applied to your system.
 *
 *  -Remember to indicate include directories (-I) if you want global includes.
 *
 *  -#include macro (where 'macro' is the name of a previous #define) can't
 *  be treated.
 *
 *  -On the Amiga, it is safer to use always Unix-like directories notations (as
 *  ':' have an special meaning in Makefiles).
 *
 *
 *  Ports notes:
 *  ~~~~~~~~~~~~
 *  -This source code is in a pure C language. No GNUisme or system specifics
 *  are used. It may be compiled by any decent C compiler on much system.
 *
 *  -On the other hand, include files aren't all standardised . Especially,
 *  'unistd.h' and 'sys/syslimits.h' may not exit on your system. access()'s
 *  prototype may reside in another file (i.e. 'fcntl.h' for some compilers
 *  like DICE on the Amiga). PATH_MAX may have another name or is defined in
 *  another file ('dir.h' on ms-dog system).
 *
 *  -Multiple assignations aren't used on bits fields as this may trouble
 *  some compilers...
 *
 *  -LFMakeMaker doesn't try to interpret syntax of pathname. So, it may run
 *  on other systems with different path syntax like VMS (sorry but,
 *  unfortunatly, I don't have the licence to run the VMS-C compiler on my VAX).
 *
 *  -CAUTION : As readsource() may be recursively called, have a look on your
 *  stack's size (for fixed stack system only). On my Amiga, a 4K stack looks
 *  like to be suffisant (but 8K or more is safer).
 *
 *  -Compiling:
 *  Gcc 2.7.0 produces no warnings when compiling with -Wall (all warning
 *  enabled). On all systems, following options may be added:
 *      -O (optimise object code, see your compiler documentation),
 *      -DDEBUG (Add some run-time messages),
 *      -DDEBUGALL (Add full run-time messages -- For debugging only --),
 *
 *  On the Amiga, you may add following options to GCC
 *      -s (discard symbol and debug hunks, smaller executable),
 *      -resident (if you want a pure command).
 *      -noixemul (don't use ixemul.librairy so no external library is needed
 *  -- Unrecommended because you loose UNIX syntax for pathname, or you may use
 *  external commodities to patch system's syntax parsing-- ).
 *
 *  CopyRight:
 *  ~~~~~~~~~~
 *  Even this tool is FREEWARE, gifts are welcome ( 68060 board, Multi-Sync
 *  monitor (ha ha), chocolates, ... or only a post card ).
 *  Write to:
 *  	l_faillie(at)yahoo.com
 *
 *  LFMakeMaker was developped and tested on
 *      - Amiga 1000 (68010, 8Mb, HD 52Mb, WB 2.1),
 *      - Amiga 4000 (68040, 14 Mb, HD 120 Mb, CD-ROMx4 IDE, WB 3.0),
 *      - MicroVAX II (16Mb, 2x RD54, Ultrix 4.2).
 *
 *  All under GCC 2.7.0 from Amiga's CD-ROM Fresh Fish 10.
 *
 *  Some part of this source code was inspired by my very own LFLocalize 0.5�.
 *
 *  MungWall & Enforcer are CopyRighted Commodore - Amiga.
 *
 *  Examples:
 *  ~~~~~~~~~
 *      LFMakeMaker >makefile +gr +c=myinc.h +c=sys/cdefs.h truc.c
 *  with 'truc.c'
 *      ...
 *      #include <myinc.h>
 *      #include <stdio.h>
 *      ...
 *  and 'myinc.h'
 *      ...
 *      #include <sys/machine.h>
 *      #include <sys/cdefs.h>
 *      ...
 *  find 2 dependancies for truc.c:
 *      'myinc.h' (because in check list and in truc.c even if global are
 *  disabled),
 *      'sys/cdefs.h' (because in check list and in 'myinc.h').
 *  'stdio.h' and 'sys/machine.h' aren't found because global include are
 *  disabled).
 *
 *************
 *      LFMakeMaker -e=exec1 file1.c file2.c -e=exec2 file3.c -o file4.c file5.c -t=exec3.c
 *  Generate target for:
 *      exec1 depending on file1.c and file2.c
 *      exec2 depending on file3.c
 *      exec3 depending on file4.c and file5.c (file4.o and file5.o will be created).
 *
 *  TO DO
 *  ~~~~~
 *  - To speed LFMakeMaker, a cache may be added for dependancies of include
 *  files (as most sources files of a project use same includes).
 *
 *  Know bugs:
 *  ~~~~~~~~~~
 *  - Since version 1.1, LFMakeMaker was tested by MungWall 37.21 (memories
 *  allocated/freed tests) and Enforcer 37.55 (illegal memory access). This
 *  prevent from memory corruption caused by LFMakeMaker (but not by the code
 *  generated by your C compiler).
 *
 *  - if '--global' isn't set, no warning is displayed if a local include
 *  didn't exist, because, it will be treated like a global one. As search
 *  for global include are disabled, LFMakeMaker doesn't test if the file
 *  exits or not. This is a side effect, not a bug. Maybe fixed in a future
 *  version.
 *
 *  Until now, following bugs had been found in the Amiga version of LFMakeMaker,
 *  may not appli to others architectures...
 *
 *  - On 16 bits powered Amigas (with 68000 or 68010 CPU), LFMakeMaker will
 *  crash if you break (by CTRL-C or by using Break command) while it runs.
 *  thoses craches are caused by ixemul.library (version 41.2). I can't
 *  fix anything but I hope that future versions of this library will run correctly
 *  on 16 bits systems. Such crashes aren't found on 32 bits systems (tested
 *  on an Amiga 1200/68020 and on my Amiga 4000/68040).
 *
 *  - Startup code generated by GCC 2.7.0 (and, I think, with many others
 *  versions) doesn't like international characters (i.e. ASCII > 128).
 *  example :
 *      LFMakeMaker -I/progs/D�veloppement/Dice/include/ ...
 *  is interpreted as
 *  1) add '/progs/D' in includes directories list,
 *  2) try to read a file named 'veloppement/Dice/include/'
 *
 *  History: BF: Bug fix, A: Added
 *  ~~~~~~~~
 *      Version 1.0
 *      -----------
 *  22-01-1997 : Start of development.
 *  09-02-1997 SB: Its seems that white-spaces may be inserted after '#' for
 *      a preprocessor command. fixed now...
 *             A: new option : "--compiler"
 *
 *      Version 1.1
 *      -----------
 *  12-02-1997 A: 'ltarget' store all generated targets. so
 *      -> an object file (and as all other targets) is checked to be
 *      generated only one time (if many executables use a same file),
 *      -> the 'all :' target may be generated.
 *             SB : Many enforcer hits removed (reading at NULL).
 *
 *      Version 1.2
 *      -----------
 *  30-05-2015	SB : EOF is casted to a char
 *  			SB : incorrect free() in freelsta()
 *
 * 		Version 1.3
 * 		-----------
 * 	13-04-2016	A: Add --shared target
 *
 * 		Version 1.4
 * 		-----------
 * 	03-04-2018	A: Add --opts to be compatible with GCC 5.4+
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <unistd.h> /* For access()'s prototype */

    /*  This file is only used for PATH_MAX (the maximum byte allowed in a
     * pathname). If this include fail, another value may be defined elsewhere
     * in your compiler's includes tree.
     * For the Amiga, a filename is known to be at last 30 bytes long (may be
     * up to 107 in futur), but it seems to be no limit (except your free
     * memory) for path name. For Amiga's GCC 2.7.0, PATH_MAX is set to 1024!
#include <sys/syslimits.h>
     */
#include <sys/param.h>

    /* The line length by default (in fact DEFLINE + 2)*/
#define DEFLINE 70

#define DEFTAB  8   /* The length of a TAB character */

#ifdef DEBUG
    #define DMSG(x) {fputs(x,stderr);}
    #ifdef DEBUGALL
        #define DAMSG(x) {fputs(x,stderr);}
    #else
        #define DAMSG(x)
    #endif
#else
    #define DMSG(x)
    #define DAMSG(x)
#endif

#define VERSION "1.4 ("__DATE__ " " __TIME__ ")"

struct ldata {
    struct ldata *succ; /* Notez-bien : This must be the first field */
    char *x;
};

struct _opt {
    unsigned local: 1;
    unsigned r_local: 1;
    unsigned global: 1;
    unsigned r_global: 1;
    unsigned csens : 1;
    unsigned verbose : 1;
    unsigned nc : 1;
    unsigned fatal : 1;

    unsigned fgen : 1;  /* TRUE if a target had already been generated */

    unsigned int line;
    unsigned int tab;

    const char *exec;   /* NULL if objects will be generated */
    const char *oprefix; /* NULL if no prefix will be added */
    const char *cc;     /* The compiler command */
	const char *opts;	/* The compiler options */

    struct ldata *ginc; /* List of all global include read for the current source file (malloc())*/
    struct ldata *linc; /* List of all local include read for the current source file (malloc())*/
    struct ldata *obj;  /* List of all objects files (malloc())*/
    struct ldata *ltarget;  /* List of all targets (malloc()) */
    struct ldata *chk;  /* List of file to be checked */
    struct ldata *force;/* List of file to be forced */
    struct ldata *ign;  /* List of file to be ignored */
    struct ldata *inc;  /* List of directory where include reside in */
};

#ifdef __GNUC__
inline
#endif
struct ldata *ldfind( struct _opt *ctx, struct ldata **lst, const char *x, struct ldata **prec ){
/* Find 'x' in 'lst'.
 * return the pointer to 'x' if it exist or NULL else.
 * if 'prec' is non-null, the pointer of the 'succ' field of its predecessor is
 * stored.
 */
    register struct ldata *c, *p;

    if(!x) return NULL;

    DAMSG("*DAD ldfind()\n");

    for(c=*lst, p= (struct ldata *)lst; c; p=c, c=c->succ){
        if(ctx->csens){
            if(!strcmp(x,c->x)) break;
        } else
            if(!strcasecmp(x,c->x)) break;
    }

    if(prec) *prec=p;

    DAMSG("*DAF ldfind()\n");

    return c;
}

#ifdef __GNUC__
inline
#endif
struct ldata *ldadd( struct _opt *ctx, struct ldata **lst, char *x, int end ){
/* Add a new data 'x' to the list 'lst'.
 * end == 1 if you want the data to be added at THE END of 'lst'.
 * If 'x' is already in the list, the old one is returned.
 * May exit if a new node can't be allocated.
 */
    struct ldata *der, *nn=ldfind(ctx, lst, x, &der);

    if(!x) return NULL;

    DAMSG("*DAD ldadd()\n");

    if(nn){ /* This entry already exits */
        DAMSG("*DAF ldadd() -- node found\n");
        return nn;
    }

    nn = malloc( sizeof( struct ldata ) );
    if(!nn){
        fputs("Not enough memory\n",stderr);
        exit(EXIT_FAILURE);
    }

        /*  A warning may be added if der == NULL but, on the other hand,
         * this is a bug and may never be.
         */
    if(end && der) {
        nn->succ = NULL;
        der->succ = nn;
    } else {
        nn->succ = *lst;
        *lst = nn;
    }
    nn->x = x;

    DAMSG("*DAF ldadd() -- node allocated\n");
    return nn;
}

#ifdef __GNUC__
inline
#endif
struct ldata *ldadda( struct _opt *ctx, struct ldata **lst, char *x, int end ){
/* Like ldadd() but 'x' will be strdup()ed.
 */
    struct ldata *der, *nn=ldfind(ctx, lst, x, &der);

    if(!x) return NULL;

#ifdef DEBUGALL
    fprintf(stderr,"*DAD ldadda(%s)\n",x);
#endif

    if(nn){ /* This entry already exits */
        DAMSG("*DAF ldadda() -- node found\n");
        return nn;
    }

    nn = malloc( sizeof( struct ldata ) );
    if(!nn){
        fputs("Not enough memory\n",stderr);
        exit(EXIT_FAILURE);
    }

        /*  A warning may be added if der == NULL but, in the other hand,
         * this is a bug and may never be.
         */
    if(end && der) {
        nn->succ = NULL;
        der->succ = nn;
    } else {
        nn->succ = *lst;
        *lst = nn;
    }

    if(!(nn->x = strdup(x))){
        fputs("Not enough memory\n",stderr);
        exit(EXIT_FAILURE);
    }

    DAMSG("*DAF ldadda() -- node allocated\n");
    return nn;
}

#ifdef __GNUC__
inline
#endif
void freelst(struct ldata **lst){
/* Free a list of non-allocated objects */
    register struct ldata *nd,*succ;

    for(nd=*lst; nd; nd=succ){
        succ = nd->succ;
        free(nd);
    }

    *lst=NULL;
}

#ifdef __GNUC__
inline
#endif
void freelsta(struct ldata **lst){
/* Free a list of allocated objects */
    register struct ldata *nd=*lst,*succ;

    for(; nd; nd=succ){
        if(nd->x) free(nd->x);
        succ = nd->succ;
        free(nd);
    }
    *lst = NULL;
}

void genline(struct _opt *ctx, const char *fch){
/* Add 'fch' to the current generated line
 * Note only first character is checked for TAB.
 */
    static int cll = 0;
    int i;

    if(!fch){ /* Generating a new line */
        puts("");
        cll = 0;
        return;
    }

    if(cll + (i=strlen(fch)) > ctx->line){
        cll = 2;
        printf("\\\n  ");
    }

    if(*fch == '\t')
        cll += ctx->tab-1;

    if(fch[i-1] == '\n'){   /* The last char is a new line */
        printf("%s",fch);
        cll = 0;
    } else {
        printf("%s ",fch);
        cll += i + 1;
    }
}

void generate(struct _opt *ctx, const char *dst, int gen_obj, int ign_lt, int so){
/* Generate makefile for 'dst'.
 * if 'dst'==NULL, an executable will be generated (if ctx->exec is valide).
 * 'gen_obj' == 1 if we generate an object file so ctx->obj will be ignored.
 * ign_lt == 1 if the check in 'ltarget' must be ignored.
 * so == 1 if a shared object will be created (dst had to be NULL).
 */
    register struct ldata *nd;

    if(!ctx->fgen){
        if(ctx->verbose)
            fputs("Generating CC command.\n",stderr);
        puts("\n#The compiler (may be customized for compiler's options).");
        printf("cc=%s\nopts=%s\n\n",ctx->cc, ctx->opts ? ctx->opts : "");
        ctx->fgen = 1;
    }

    if(!dst && !ctx->exec){ /* Called at end of main() or when objects must be forgotten */
        fputs("WARNING: Pending objects without a target.\n",stderr);
        return;
    }

    if(dst){
        if(!ign_lt){
            if(ldfind(ctx, &ctx->ltarget, dst, NULL)){
                fprintf(stderr,"WARNING: '%s' will be generated twice!!",dst);
                if(ctx->fatal) exit(EXIT_FAILURE);
            } else
                ldadda(ctx, &ctx->ltarget, (char *)dst, 0);
        } else
            ldadda(ctx, &ctx->ltarget, (char *)dst, 0);
    }

    if(gen_obj){ /* Object will be generated */
        genline(ctx,dst);
        genline(ctx,":");
        for(nd=ctx->linc; nd; nd = nd->succ) genline(ctx,nd->x);
        for(nd=ctx->ginc; nd; nd = nd->succ) genline(ctx,nd->x);
        for(nd=ctx->force; nd; nd = nd->succ) genline(ctx,nd->x);
        genline(ctx,NULL);

        genline(ctx,"\t$(cc) -c -o");
        genline(ctx,dst);

        if(ctx->verbose)
            fprintf(stderr,"Generating '%s'.\n",dst);

        if(!ctx->linc){
            fputs("Internal error : Can't generate object without source!\n",stderr);
            exit(EXIT_FAILURE);
        } else
            genline(ctx,ctx->linc->x);
        genline(ctx,"$(opts)");
        genline(ctx,NULL); genline(ctx,NULL);
    } else { /* Generate an executable */
        if(ctx->exec){
            dst = ctx->exec;
            ldadda(ctx, &ctx->ltarget, (char *)dst, 0);
        }

        if(ctx->verbose)
            fprintf(stderr,"Generating '%s'.\n",dst);

        genline(ctx,dst);
        genline(ctx,":");
        for(nd=ctx->obj; nd; nd = nd->succ) genline(ctx,nd->x); /* Add sources */
        for(nd=ctx->linc; nd; nd = nd->succ) genline(ctx,nd->x); /* And includes */
        for(nd=ctx->ginc; nd; nd = nd->succ) genline(ctx,nd->x);
        for(nd=ctx->force; nd; nd = nd->succ) genline(ctx,nd->x); /* Finaly forced files */
        genline(ctx,NULL);
		if(so)
        	genline(ctx,"\t $(cc) -shared -o");
		else
        	genline(ctx,"\t $(cc) -o");
        genline(ctx,dst);
        for(nd=ctx->obj; nd; nd = nd->succ) genline(ctx,nd->x);
        genline(ctx,"$(opts)");
        genline(ctx,"\n\n");

        freelsta(&ctx->obj); /* Destroy source file for this target */
    }

        /* As treated, all dependancies may be destroyed */
    freelsta(&ctx->ginc);
    freelsta(&ctx->linc);
}

struct _status {
    unsigned long nl;   /* Line number */
    unsigned short com; /* Level of nested C comments */
    unsigned short bloc;        /* Level of nested '{ }' blocks */
    unsigned char isinclude;    /* Include (9 if '#include' was readed) */
    unsigned lcom : 1;  /* C++ comment */
    unsigned slt  : 1;  /* Last char is a '/' */
    unsigned star : 1;  /* Last char is a '*' */
    unsigned ignore : 1;/* Last char is a '\' */
    unsigned instr : 1; /* We are reading a "" string */
    unsigned incot : 1; /* We are reading a '' string */
};

char cfn[PATH_MAX],     /* Static buffer holding currently readen filename */
     cpn[PATH_MAX];     /* cfn + one of a path stored in the -I list */

int cfnidx;

/* Some old compilers dislike such prototype. Try
 *      void readsource();
 */
void readsource(struct _opt *, const char *);

#ifdef __GNUC__
inline
#endif
int valide(struct _opt *ctx, int local){
/*  Look in context if the file in cfn may be treated.
 *  <- ctx : Current context,
 *     local : It's a local (1) or global (0) file.
 *  -> 1 : Accepte this file,
 *     0 : Ignore this file.
 */
    if(ldfind(ctx, &ctx->chk, cfn, NULL)) /* This file must be checked ? */
        return 1;

    if(ldfind(ctx, &ctx->ign, cfn, NULL)) /* This file must be ignored ? */
        return 0;

    if(ctx->local && local) return 1;

    if(ctx->global && !local) return 1;

    return 0;
}

int lookfor(struct _opt *ctx, int nr){
/* Look for an include file (cfn) in all path in ctx->inc list
 *  -> 1 : If the file can be found (the result is in cpn).
 *  -> 0 : If the file can't be found (cpn is invalid).
 */
    register struct ldata *nd;
    int fl = strlen(cfn);

    for(nd=ctx->inc; nd; nd = nd->succ){
        if(fl + strlen(nd->x) >= PATH_MAX)
            fprintf(stderr,"Warning : Following path is too long (and ignored).\n'%s%s'\n",nd->x,cfn);
        else {
            strcpy(cpn,nd->x);
            strcat(cpn,cfn);

            if(ctx->verbose){
                int i;
                for(i=nr; i>1; i--)
                    fputs("-",stderr);
                fprintf(stderr, "-> Looking for '%s' ...",cpn);
            }

            if(!access(cpn,0)){
                if(ctx->verbose) fputs(" found.\n",stderr);
                return 1;
            } else
                if(ctx->verbose) fputs(" not found.\n",stderr);
        }
    }

    return 0;
}

void addglobal(struct _opt *ctx, struct _status *status, int nr){
#ifdef DEBUG
    fprintf(stderr,"*DAD addglobal(%s)\n",cfn);
#endif
    if(valide(ctx,0)){
        if(lookfor(ctx, nr)) {
            if(ctx->r_global){
                if(!ldfind(ctx, &ctx->ginc, cpn, NULL)){ /* Already treated ? */
                    struct ldata *nd = ldadda(ctx, &ctx->ginc, cpn, 0);
                    if(nd)
                        readsource(ctx,nd->x);
                    else {
                        fputs("Internal error: Unexpected NULL from ldadda().\n",stderr);
                        exit(EXIT_FAILURE);
                    }
                }
            } else
                ldadda(ctx, &ctx->ginc, cpn, 0);
        } else {
            fprintf(stderr, "'%s' %ld : Can't locate '%s'.\n", cfn, status->nl,cfn);
            if(ctx->fatal)
                exit(EXIT_FAILURE);
            else
                printf("# Warning : '%s' can't be located for this node.\n", cfn);
        }
    }
    DAMSG("*DAF addglobal()\n");
}

void addlocal(struct _opt *ctx, struct _status *status, int nr){
#ifdef DEBUG
    fprintf(stderr,"*DAD addlocal(%s)\n",cfn);
#endif

    if(valide(ctx,1)){
        if(access(cfn,0))  /* This file can't be found in the current directory */
            addglobal(ctx, status, nr);
        else {
            if(ctx->r_local){ /* Recursively yours */
                if(!ldfind(ctx, &ctx->linc, cfn, NULL)){ /* Already treated ? */
                    struct ldata *nd = ldadda(ctx, &ctx->linc, cfn, 1);
                    strcpy(cpn,cfn); /* readsource() regarde dans cpn */
                    if(nd)
                        readsource(ctx,nd->x);
                    else {
                        fputs("Internal error: Unexpected NULL from ldadda().\n",stderr);
                        exit(EXIT_FAILURE);
                    }
                }
            } else
                ldadda(ctx,&ctx->linc,cfn,1);
        }
    }

    DAMSG("*DAF addlocal()\n");
}

void readsource(struct _opt *ctx, const char *x){
/* Read a source file */
    static unsigned int nbre_rec = 0; /* Nbre of recursion */
    int i;
    struct _status status;
    FILE *fp;
    char c;

    if(!(fp=fopen(x,"r"))){
        fprintf(stderr,"can't open '%s':%s\n",x,strerror(errno));
        exit(EXIT_FAILURE);
    }

    for(i=++nbre_rec; i>1 && ctx->verbose; i--)
        fputs("=",stderr);

    if(ctx->verbose)
        fprintf(stderr,"reading '%s'\n",x);

    status.nl = 1;
    status.com = status.bloc = 0;
    status.lcom = 0; status.slt = 0; status.star = 0; status.ignore = 0;
    status.isinclude = 0; status.instr = 0; status.incot = 0;

    while((c=fgetc(fp))!=(char)EOF){
        if(status.isinclude){ /* Reading an include */
            if(status.isinclude == 9){
#if 1 /* Only for security */
if(cfnidx > PATH_MAX){
    fputs("** FATAL ERROR : invalide cfnidx...\n",stderr);
    exit(EXIT_FAILURE);
}
#endif
                switch(c){ /* No interpretation of the name is done as it's system dependant...*/
                case '\n':
                    fprintf(stderr,"'%s' %ld : Unterminated #include filename.\n", x, status.nl);
                    exit(EXIT_FAILURE);
                case '"':
                    if(status.instr){   /* It's a local include */
                        cfn[cfnidx]=0;
                        addlocal(ctx, &status, nbre_rec);
                        status.instr = 0;
                        status.isinclude = 0;
                    } else goto inc_autre;
                    break;
                case '>':
                    if(!status.instr){  /* It's a global include */
                        cfn[cfnidx]=0;
                        addglobal(ctx, &status, nbre_rec);
                        status.isinclude = 0;
                    } else goto inc_autre;
                    break;
                default :
                inc_autre:
                    cfn[cfnidx++]=c;
                }
                if(cfnidx >= PATH_MAX){
                    fprintf(stderr,"'%s' %ld : #include filename too long.\n", x, status.nl);
                    exit(EXIT_FAILURE);
                }
            } else switch(c){
            case 'i':
                if(status.isinclude != 1) goto autre;
                status.isinclude++;
                break;
            case 'n':
                if(status.isinclude != 2) goto autre;
                status.isinclude++;
                break;
            case 'c':
                if(status.isinclude != 3) goto autre;
                status.isinclude++;
                break;
            case 'l':
                if(status.isinclude != 4) goto autre;
                status.isinclude++;
                break;
            case 'u':
                if(status.isinclude != 5) goto autre;
                status.isinclude++;
                break;
            case 'd':
                if(status.isinclude != 6) goto autre;
                status.isinclude++;
                break;
            case 'e':
                if(status.isinclude != 7) goto autre;
                status.isinclude++;
                break;
            case '\t':
            case ' ':
                if(status.isinclude != 8 && status.isinclude != 1) goto autre;
                break;
            case '<':
                if(status.isinclude != 8) goto autre;
                status.isinclude++; cfnidx = 0;
                break;
            case '"':
                if(status.isinclude != 8) goto autre;
                status.isinclude++; cfnidx = 0;
                status.instr = 1;
                break;
            default :
                goto autre;
            }
        } else if(status.instr || status.incot) switch(c){ /* In a string ... */
        case '\n':
            fprintf(stderr,"'%s' %ld: Unterminated string.\n",x,status.nl);
            exit(EXIT_FAILURE);
        case '\\':
            if(status.ignore)
                status.ignore = 0;
            else
                status.ignore = 1;
            break;
        case '"':
            if(status.instr && !status.ignore)
                status.instr = 0;
            else
                status.ignore = 0;
            break;
        case '\'':
            if(status.incot && !status.ignore)
                status.incot = 0;
            else
                status.ignore = 0;
            break;
        default:
            status.ignore = 0;
        } else if(status.lcom){ /* Reading a C++ comment */
            if(c == '\n'){
                status.lcom = 0;
                status.nl++;
            }
        } else if(status.com){ /* Reading a C comment */
            if(c == '\n'){
                status.nl++; status.star = 0;
            } else if(c=='*'){
                if(status.slt){ /* Nesting ? */
                    status.slt = 0;
                    if(!ctx->nc){
                        fprintf(stderr,"'%s' %ld : Nested comments are not allowed.\n", x, status.nl);
                        exit(EXIT_FAILURE);
                    } else
                        status.com++;
                    status.star = 0;
                } else
                    status.star = 1;
            } else if(c=='/'){
                if(status.star){ /* Closing ? */
                    status.star = 0; status.slt = 0;
                    status.com--;
                } else
                    status.slt = 1;
            } else {
                status.star = 0; status.slt = 0;
            }
        } else { /* In plain source code */
            if(status.ignore){
                if(c == '\n') status.nl++;
                status.ignore = 0;
                continue;
            }

autre:
            status.isinclude = 0; /* Because of the goto when reading '#include' */

            switch(c){
            case '/':
                if(status.slt){ /* A C++ comment ? */
                    status.slt = 0; status.lcom = 1;
                } else if(status.star){
                    fprintf(stderr,"'%s' %ld: Unmatching */.\n",x,status.nl);
                    exit(EXIT_FAILURE);
                } else
                    status.slt = 1;
                break;
            case '*':
                if(status.slt){ /* Openning a new comment ? */
                    status.slt = 0;
                    if(++status.com > 1 && !ctx->nc){
                        fprintf(stderr,"'%s' %ld: Nested comments not allowed.\n",x,status.nl);
                        exit(EXIT_FAILURE);
                    }
                } else
                    status.star = 1;
                break;
            case '\n':
                status.nl++; status.star=0; status.slt=0;
                break;
            case '\\':
                status.ignore = 1; status.star=0; status.slt=0;
                break;
            case '\'':
                status.incot = 1; status.star=0; status.slt=0;
                break;
            case '"':
                status.instr = 1; status.star=0; status.slt=0;
                break;
            case '{':
                status.bloc++; status.star=0 ;status.slt=0;
                break;
            case '}':
                if(!status.bloc){
                    fprintf(stderr,/*{*/"'%s' %ld: Unmatching '}'\n", x, status.nl);
                    exit(EXIT_FAILURE);
                } else
                    status.bloc--;
                status.star=0 ;status.slt=0;
                break;
            case '#':
                status.star=0 ;status.slt=0; status.isinclude = 1;
                break;
            default:
                status.star=0 ;status.slt=0; status.isinclude = 0;
            }
        }
    }
    fclose(fp);

    if(status.bloc){
        fprintf(stderr,"'%s' : %d pending block%c\n",x, status.bloc, (status.bloc>1) ? 's':' ');
        exit(EXIT_FAILURE);
    }
    if(status.com){
        fprintf(stderr,"'%s' : %d pending C comment%c\n", x, status.com, (status.com>1) ? 's':' ');
        exit(EXIT_FAILURE);
    }
    if(status.instr || status.incot){
        fprintf(stderr,"'%s' : Unterminated string\n", x);
        exit(EXIT_FAILURE);
    }
    if(status.isinclude == 9){
        fprintf(stderr,"'%s' : Unexpected end of file when reading '#include' directive!\n",x);
        exit(EXIT_FAILURE);
    }

    nbre_rec--;
}

#ifdef __GNUC__
inline
#endif
int strcmpopt(const char *y, const char *x, const char **end){
/* Like strcmp() but looks only on x's len.
 * 'end' contains the pointer on 'y' of the first character not in 'x'.
 * Note: '*end' is only modified if this function succeeds.
 */
    for(;*x;x++,y++)
        if(*x != *y) return *x - *y;

    if(end) *end = y;
    return 0;
}

#ifdef __GNUC__
inline
#endif
void tstarg(const char *x){
/* Some systems (like AmigaDOS) use ':' as special separator in filename (i.e.
 * after drivename). This may confuse 'make' so we display a warning.
 */
    if(strchr(x,':'))
        fprintf(stderr,"'%s' may confuse 'make'. Please avoid use of ':'\n",x);
}

void option(struct _opt *ctx, const char *x){
/* Interpret (and modify 'ctx') according to the option pointed by 'x'.
 * Caution : Be carfull about options' ordering. As example, "-cc" must be
 * checked befor "-c" this function thinks that a "-cc" is a "-c" option
 * with a wrong "c=..." parameter!
 */
    const char *o;

    DAMSG("*DAD option()");

    if(!strcmp(x,"+l") || !strcmp(x,"--local")){
        DAMSG(" -> --local");
        ctx->local = 1;

    } else if(!strcmp(x,"-l") || !strcmp(x,"--no-local")){
        DAMSG(" -> --no-local");
        ctx->local = 0;

    } else if(!strcmp(x,"+lr") || !strcmp(x,"--recurse-local")){
        DAMSG(" -> --recurse-local");
        ctx->r_local = 1;

    } else if(!strcmp(x,"-lr") || !strcmp(x,"--no-recurse-local")){
        DAMSG(" -> --no-recurse-local");
        ctx->r_local = 0;

    } else if(!strcmp(x,"+g") || !strcmp(x,"--global")){
        DAMSG(" -> --global");
        ctx->global = 1;

    } else if(!strcmp(x,"-g") || !strcmp(x,"--no-global")){
        DAMSG(" -> --no-global");
        ctx->global = 0;

    } else if(!strcmp(x,"+gr") || !strcmp(x,"--recurse-global")){
        DAMSG(" -> --recurse-global");
        ctx->r_global = 1;

    } else if(!strcmp(x,"-gr") || !strcmp(x,"--no-recurse-global")){
        DAMSG(" -> --no-recurse-global");
        ctx->r_global = 0;

    } else if(!strcmpopt(x,"-e",&o) || !strcmpopt(x,"--exec",&o)){
        #ifdef DEBUGALL
            fprintf(stderr,"--exec (%s)",o);
        #endif

        if(ctx->obj){    /* Pending sources */
            generate(ctx,NULL,0,0,0);
            freelsta(&ctx->obj); /* Clear it */
        }

        if(*o != '='){
            fputs("--exec needs an argument\n",stderr);
            exit(EXIT_FAILURE);
        }

        tstarg(ctx->exec = ++o);

    } else if(!strcmp(x,"-o") || !strcmp(x,"--object")){
        DAMSG(" -> --object");

        if(ctx->obj){    /* Pending sources */
            generate(ctx,NULL,0,0,0);
            freelsta(&ctx->obj); /* Clear it */
        }

        ctx->exec = NULL;

    } else if(!strcmpopt(x,"-t",&o) || !strcmpopt(x,"--target",&o)){
        #ifdef DEBUGALL
            fprintf(stderr,"--target (%s)",o);
        #endif

        if(ctx->exec){
            generate(ctx,NULL,0,0,0); /* Pending --exec */
            freelsta(&ctx->obj);
        }

        if(*o == '='){
            tstarg(++o);
            if(!ctx->obj){
                fprintf(stderr,"For target '%s': No objects files.\n",o);
                printf("\nFor target '%s': No objects files.\n",o);
            } else
                generate(ctx,o,0,0,0);
        }

        freelsta(&ctx->obj);

    } else if(!strcmpopt(x,"-so",&o) || !strcmpopt(x,"--shared",&o)){
        #ifdef DEBUGALL
            fprintf(stderr,"--shared (%s)",o);
        #endif

        if(ctx->exec){
            generate(ctx,NULL,0,0,0); /* Pending --exec */
            freelsta(&ctx->obj);
        }

        if(*o == '='){
            tstarg(++o);
            if(!ctx->obj){
                fprintf(stderr,"For target '%s': No objects files.\n",o);
                printf("\nFor target '%s': No objects files.\n",o);
            } else
                generate(ctx,o,0,0,1);
        }

        freelsta(&ctx->obj);

    } else if(!strcmpopt(x,"-po",&o) || !strcmpopt(x,"--prefix",&o)){
        #ifdef DEBUGALL
            fprintf(stderr,"--prefix (%s)",o);
        #endif

        if(*o == '='){
            tstarg(++o);
            ctx->oprefix = o;
        } else
            ctx->oprefix = NULL;

    } else if(!strcmpopt(x,"-cc",&o) || !strcmpopt(x,"--compiler",&o)){
        #ifdef DEBUGALL
            fprintf(stderr,"--compiler (%s)",o);
        #endif
        if(*o != '='){
            fputs("--compiler needs an argument\n",stderr);
            exit(EXIT_FAILURE);
        }

		if(ctx->fgen){
            fputs("misplaced --compiler option : already used.\n",stderr);
            exit(EXIT_FAILURE);
        }
        ctx->cc = ++o;

    } else if(!strcmpopt(x,"--opts",&o)){
        #ifdef DEBUGALL
            fprintf(stderr,"--opts (%s)",o);
        #endif
        if(*o != '='){
            fputs("--opts needs an argument\n",stderr);
            exit(EXIT_FAILURE);
        }

		if(ctx->fgen){
            fputs("misplaced --opts option : already used.\n",stderr);
            exit(EXIT_FAILURE);
        }
        ctx->opts = ++o;


    } else if(!strcmpopt(x,"+c",&o) || !strcmpopt(x,"--check",&o)){
        #ifdef DEBUGALL
            fprintf(stderr,"--check (%s)",o);
        #endif
        if(*o != '='){
            fputs("--check needs an argument\n",stderr);
            exit(EXIT_FAILURE);
        }
        ldadd(ctx,&(ctx->chk),(char *)++o, 0);

    } else if(!strcmpopt(x,"-c",&o) || !strcmpopt(x,"--no-check",&o)){
        struct ldata *nd,*p;
        #ifdef DEBUGALL
            fprintf(stderr,"--no-check (%s)",o);
        #endif
        if(*o != '='){
            fputs("--no-check needs an argument\n",stderr);
            exit(EXIT_FAILURE);
        }
        if((nd = ldfind(ctx, &ctx->chk, ++o, &p))){
            p->succ = nd->succ;
            free(nd);
        } else if(ctx->verbose)
            fprintf(stderr,"'%s' not found in list of files to check.\n",o);

    } else if(!strcmpopt(x,"+f",&o) || !strcmpopt(x,"--force",&o)){
        #ifdef DEBUGALL
            fprintf(stderr,"--force (%s)",o);
        #endif
        if(*o != '='){
            fputs("--force needs an argument\n",stderr);
            exit(EXIT_FAILURE);
        }
        ldadd(ctx,&(ctx->force), (char *)++o, 0);

    } else if(!strcmpopt(x,"-f",&o) || !strcmpopt(x,"--no-force",&o)){
        struct ldata *nd,*p;
        #ifdef DEBUGALL
            fprintf(stderr,"--no-force (%s)",o);
        #endif
        if(*o != '='){
            fputs("--no-force needs an argument\n",stderr);
            exit(EXIT_FAILURE);
        }
        if((nd = ldfind(ctx, &ctx->force, ++o, &p))){
            p->succ = nd->succ;
            free(nd);
        } else if(ctx->verbose)
            fprintf(stderr,"'%s' not found in list of files to force.\n",o);

    } else if(!strcmpopt(x,"+i",&o) || !strcmpopt(x,"--ignore",&o)){
        #ifdef DEBUGALL
            fprintf(stderr,"--ignore (%s)",o);
        #endif
        if(*o != '='){
            fputs("--ignore needs an argument\n",stderr);
            exit(EXIT_FAILURE);
        }
        ldadd(ctx,&(ctx->ign),(char *)++o,0);

    } else if(!strcmpopt(x,"-i",&o) || !strcmpopt(x,"--no-ignore",&o)){
        struct ldata *nd,*p;
        #ifdef DEBUGALL
            fprintf(stderr,"--no-ignore (%s)",o);
        #endif
        if(*o != '='){
            fputs("--no-ignore needs an argument\n",stderr);
            exit(EXIT_FAILURE);
        }
        if((nd = ldfind(ctx, &ctx->ign, ++o, &p))){
            p->succ = nd->succ;
            free(nd);
        } else if(ctx->verbose)
            fprintf(stderr,"'%s' not found in list of files to ignore.\n",o);

    } else if(!strcmpopt(x,"-I",&o)){
        #ifdef DEBUGALL
            fprintf(stderr,"-I (%s)",o);
        #endif
        if(!*o){
            fputs("-I needs an argument\n",stderr);
            exit(EXIT_FAILURE);
        }
        ldadd(ctx,&(ctx->inc),(char *)o,1);

    } else if(!strcmpopt(x,"--line",&o)){
        unsigned int i;
        #ifdef DEBUGALL
            fprintf(stderr,"--line (%s)",o);
        #endif
        if(!*o){
            fputs("--line needs an argument\n",stderr);
            exit(EXIT_FAILURE);
        }
        if((i=(unsigned int)atoi(++o))<2)
            fputs("Invalide --line value.\n",stderr);
        else
            ctx->line = i-2;
        if(ctx->verbose)
            fprintf(stderr,"Line length set to (%u)\n",ctx->line);

    } else if(!strcmpopt(x,"--tab",&o)){
        unsigned int i;
        #ifdef DEBUGALL
            fprintf(stderr,"--tab (%s)",o);
        #endif
        if(!*o){
            fputs("--tab needs an argument\n",stderr);
            exit(EXIT_FAILURE);
        }
        if((i=(unsigned int)atoi(++o))<2)
            fputs("Invalide --tab value.\n",stderr);
        else
            ctx->tab = i-2;
        if(ctx->verbose)
            fprintf(stderr,"TAB length set to (%u)\n",ctx->tab);

    } else if(!strcmp(x,"+cs") || !strcmp(x,"--case-sensitive")){
        DAMSG(" -> --case-sensitive");
        ctx->csens = 1;

    } else if(!strcmp(x,"-cs") || !strcmp(x,"--no-case-sensitive")){
        DAMSG(" -> --no-case-sensitive");
        ctx->csens = 0;

    } else if(!strcmp(x,"+nc") || !strcmp(x,"--nested")){
        DAMSG(" -> --nested");
        ctx->nc = 1;

    } else if(!strcmp(x,"-nc") || !strcmp(x,"--no-nested")){
        DAMSG(" -> --no-nested");
        ctx->nc = 0;

    } else if(!strcmp(x,"--fatal")){
        DAMSG(" -> --fatal");
        ctx->fatal = 1;

    } else if(!strcmp(x,"--nofatal")){
        DAMSG(" -> --no-fatal");
        ctx->fatal = 0;

    } else if(!strcmp(x,"-v") || !strcmp(x,"--verbose")){
        DAMSG(" -> --verbose");
        ctx->verbose = 1;
        fputs("LFMakeMaker "VERSION"\n(c) LFSoft 1997 - 2016.\n",stderr);

    } else if(!strcmp(x,"--debug")){
        struct ldata *nd;

        fprintf(stderr,"Currents options :\n"
            "local %d (rec %d)\nglobal %d (rec %d)\n"
            "case sensitif %d\nverbose %d\n"
            "line length %u\nTAB length %u\n",
            ctx->local, ctx->r_local, ctx->global, ctx->r_global,
            ctx->csens, ctx->verbose,ctx->line+2, ctx->tab
        );

        if(ctx->exec)
            fprintf(stderr,"Executable : '%s'\n",ctx->exec);
        else
            fputs("Generate objects\n",stderr);

        if(ctx->oprefix)
            fprintf(stderr,"Objects' prefix :'%s'\n",ctx->oprefix);

        fprintf(stderr,"Compiler :'%s'\n",ctx->cc);

        fputs("Objects :",stderr);
        for(nd=ctx->obj; nd; nd = nd->succ) fprintf(stderr,"'%s' ",nd->x);

        fputs("\nFiles to check :",stderr);
        for(nd=ctx->chk; nd; nd = nd->succ) fprintf(stderr,"'%s' ",nd->x);

        fputs("\nFiles to force :",stderr);
        for(nd=ctx->force; nd; nd = nd->succ) fprintf(stderr,"'%s' ",nd->x);

        fputs("\nFiles to ignore :",stderr);
        for(nd=ctx->ign; nd; nd = nd->succ) fprintf(stderr,"'%s' ",nd->x);

        fputs("\nInclude directories :",stderr);
        for(nd=ctx->inc; nd; nd = nd->succ) fprintf(stderr,"'%s' ",nd->x);

        fputs("\nLocal includes for previous source :",stderr);
        for(nd=ctx->linc; nd; nd = nd->succ) fprintf(stderr,"'%s' ",nd->x);

        fputs("\nGlobal includes for previous source :",stderr);
        for(nd=ctx->ginc; nd; nd = nd->succ) fprintf(stderr,"'%s' ",nd->x);

        fputs("\nList of targets :",stderr);
        for(nd=ctx->ltarget; nd; nd = nd->succ) fprintf(stderr,"'%s' ",nd->x);

        fputs("\n",stderr);

    } else {
        fprintf(stderr,"Unknown option :'%s'.\n",x);
        exit(EXIT_FAILURE);
    }

    DAMSG("\n");
}

void readargument(struct _opt *ctx, char *av){
    if(*av == '-' || *av == '+') /* This is an option */
        option(ctx,av);
    else { /* Reading a source file */
        if(!ctx->exec){ /* a new object target will be generated */
            char *x;

            if(strlen(av) >= PATH_MAX){
                fprintf(stderr,"Following name is too long.\n'%s'\n",av);
                exit(EXIT_FAILURE);
            }

            ldadda(ctx,&ctx->linc,av,0); /* Add source as first dependancy */
            strcpy(cfn,av);
            if((x=strrchr(cfn,'.'))) *x=0; /* cut extention */

            if(strlen(cfn)+2 >= PATH_MAX){
                fprintf(stderr,"Following name is too long for adding '.o'.\n'%s'\n",av);
                exit(EXIT_FAILURE);
            }
            strcat(cfn,".o");

            if(ctx->oprefix){
                if(strlen(cfn)+strlen(ctx->oprefix) >= PATH_MAX){
                    fprintf(stderr,"Following name is too long for adding objects prefix.\n'%s'\n",av);
                    exit(EXIT_FAILURE);
                }
                strcpy(cpn,ctx->oprefix);
                strcat(cpn,cfn);
            } else
                strcpy(cpn,cfn);

            if(!ldfind(ctx, &ctx->ltarget, cpn, NULL)){ /* May be already generated */
                struct ldata *nd=ldadda(ctx, &ctx->ltarget, cpn, 0);;
                readsource(ctx,av); /* CAUTION: this function modify cpn */
                if(nd){
                    generate(ctx,nd->x,1,1,0);
                    ldadda(ctx,&ctx->obj,nd->x,0); /* Add this new object file */
                } else {
                    fputs("Internal error: Unexpected NULL from ldadda().\n",stderr);
                    exit(EXIT_FAILURE);
                }
            } else {
                if(ctx->verbose)
                    fprintf(stderr,"'%s' skiped.\n",cpn);
                ldadda(ctx,&ctx->obj,cpn,0); /* Add this new object file */
            }
        } else {
            readsource(ctx,av);
            ldadda(ctx,&ctx->obj,av,0); /* Add this source file */
        }
    }
}

int main(int ac, char **av){
    int na;
    struct _opt opt;
    char *var = getenv("LFMakeMaker");

    opt.local = 1;
    opt.r_local = 1;
    opt.global = opt.r_global = 0;
    opt.verbose = 0;
    opt.nc = 1; opt.fatal = 0;
    opt.fgen = 0;
    opt.cc = "cc";  /* The default compiler command */
	opt.opts = NULL;
    opt.line = DEFLINE; opt.tab=DEFTAB;
    opt.exec = opt.oprefix = NULL;
    opt.ginc = opt.linc = opt.ltarget = NULL;
    opt.obj = opt.chk = opt.force = opt.ign = opt.inc = NULL;

#if defined(AMIGA)
    opt.csens = 0;
#else
#if defined(unix)
    opt.csens = 1;
#else
#error "Unknown system; you must define if it's a case-sensitive system."
#endif
#endif

    if(ac<2){
        fputs("LFMakeMaker " VERSION "\n"
            "\t(c) LFSoft 1997 - 2016.\n\n"
            "LFMakeMaker [options] sources_file\n"
            "options are:\n"
"options for local headers (#include \"xxx\")\n"
"+l or --local : Looks for local headers (default)\n"
"-l or --no-local : Doesn't look for local headers\n"
"+lr or --recurse-local : Looks recursively into local headers (default)\n"
"-lr or --no-recurse-local : Doesn't look recursively into local headers\n"
"\noptions for global headers (#include <xxx>)\n"
"+g or --global : Looks for global headers\n"
"-g or --no-global : Doesn't look for global headers (default)\n"
"+gr or --recurse-global : Looks recursively into global headers\n"
"-gr or --no-recurse-global : Doesn't look recursively into global headers (default)\n"
"\nTarget's options:\n"
"-o or --object : Generate objects file (default)\n"
"-e=\"filename\" or --exec=\"filename\" : Generate executable file\n"
"-t{=\"filename\"} or --target{=\"filename\"} : Links all objects files to the given\n"
"\texecutable. If no \"filename\" is given, all precedent objects are\n\tonly forgotten.\n"
"-so=\"filename\" or --shared=\"filename\" : Links all objects files to the given shared object.\n"
"-po{=\"xxxx\"} or --prefix{=\"xxxx\"} : Specify a prefix for object files.\n"
"\nmisceanlous options:\n"
"+c=\"filename\" or --check=\"filename\" : Add \"filename\" to dependancies lists\n"
"\tif present in source file (overwrite '--no-local' and '--no-global')\n"
"-c=\"filename\" or --no-check=\"filename\" : Remove \"filename\" from the list of\n\tfiles to checks.\n"
"+f=\"filename\" or --force=\"filename\" : Unconditionnaly add \"filename\" to\n\t dependancies lists.\n"
"-f=\"filename\" or --no-force=\"filename\" : Remove \"filename\" form the list of\n\tfiles to forces.\n"
"+i=\"filename\" or --ignore=\"filename\" : Always ignore \"filename\".\n"
"-i=\"filename\" or --no-ignore=\"filename\" : Remove \"filename\" from the list\n\tof files to ignore.\n"
"-I\"directory\" : Add \"directory\" to the list of include directories.\n" /* Note "/gnu/include" is by default added on the amiga if no variable is defined */
"\tNotes: Don't forget trailing separator ('/' on UNIX and AmigaDOS).\n"
"\tSearches are made in reverse order (last -I searched first).\n"
"+cs or --case-sensitif : Be case sensitive.\n"
"-cs or --no-case-sensitif : Be case insensitive.\n"
"+nc or --nested : Allow nested comments (default).\n"
"-nc or --no-nested : Forbid nested comments.\n"
"\tThe default is accorded with your architecture file-system\n\t(-cs on the Amiga or +cs on Unix).\n"
"-cc=\"cmd\" or --compiler=\"cmd\" : Use 'cmd' as compiler command,\n\tdefault is 'cc'.\n"
"--opts=\"compiler's options\" : options to be put after sources and targets.\n"
"--line=\"number\" : Set the limite of a line length in generated makefile.\n"
"--tab=\"number\": Set the number of space for a TAB.\n"
"--fatal : Abort if an include file can't be opened\n\tor when a target is generated twice.\n"
"--no-fatal : Warn if an include file can't be opened (default).\n"
"-v or --verbose : Display all processed file.\n"
"--debug : Display currently active options.\n"
            "\n", stderr);
        exit(EXIT_SUCCESS);
    }

    puts("# makefile created automaticaly by LFMakeMaker\n# LFMakeMaker "VERSION" (c)LFSoft 1997");

    if(var){
        char *arg;
        for(arg = strtok(var, " \t"); arg; arg = strtok(NULL, " \t"))
            readargument(&opt,arg);
    }
#if defined(AMIGA)
    else {
        DMSG("'/gnu/include/' is automaticaly added...\n");
        ldadd(&opt, &(opt.inc), "/gnu/include/",1);
    }
#endif

    puts("\ngotoall: all\n");

    for(na=1;na<ac;na++)
        readargument(&opt,av[na]);

    if(opt.obj)    /* Pending sources */
        generate(&opt,NULL,0,0,0);

    if(opt.ltarget){
        struct ldata *nd;

        if(opt.verbose)
            fputs("Generating 'all'.\n",stderr);

        genline(&opt,"all:");
        for(nd=opt.ltarget; nd; nd = nd->succ){
            size_t i=strlen(nd->x);
            if( nd->x[i-2] != '.' || nd->x[i-1] != 'o' )    /* Skip object files */
                genline(&opt,nd->x);
        }
        genline(&opt,NULL);
    }

    exit(EXIT_SUCCESS);
}
