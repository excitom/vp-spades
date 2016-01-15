#ifndef __UBIQUE_H
#define __UBIQUE_H

/************************************************************************/
/* History Log:								*/
/*									*/
/*  	When 		Who		What                      	*/
/*     									*/
/*	08-Mar-94	Alon		Create				*/
/*									*/
/************************************************************************/

// Until MAC people find out how to do this externally.
//#define __ISMAC__
//#define UBQ_DEBUG

#include <stdio.h>
#include <sys/types.h>
#ifndef __ISMAC__
# include <malloc.h>
#endif

/**************************************/
/* Architecture specific definitions. */
/**************************************/
#if defined(_WINDOWS) || defined(__ISMAC__)
# define __ISPC__
#endif

#ifdef _WINDOWS 
# ifdef _WIN32
//#  pragma message("Compiling for 32 bit Windows")
# else
#  define _WIN16
//#  pragma message("Compiling for 16 bit Windows")
# endif
# ifdef UBQ_DEBUG
//#  pragma message("Debug is on")
# endif
#endif /* _WINDOWS */

/***********************/
/* types & enumerators */
/***********************/
enum UbqBool {
  UBQ_FALSE = 0,
  UBQ_TRUE  = 1
};

typedef unsigned long	UbqUlong;
typedef unsigned short	UbqUshort;
typedef unsigned char	UbqUchar;

typedef void		(*UBQ_PFV)();

/*********************/
/* Public prototypes */
/*********************/
#ifdef _WINDOWS
  extern void         ubqSetErrorFile(FILE*       fp);
#endif /* _WINDOWS */
extern void           ubqDisplayError(const char* title, const char* format, ...);
extern void            ubqSetExitFunc(UBQ_PFV     callback);
extern void        ubqExitOnAssertion(int         line,  const char* file);
extern void            ubqExitProcess(int         line,  const char* file);
extern void                 ubqDoExit(int         code);
extern void ubqMemSetExceptionRoutine(UBQ_PFV     callback);
extern void	     ubqMemAllocError();
extern UbqUlong        ubqGetCurrTime();	// in seconds
extern const char*  ubqGetCurrTimeStr();
extern const char*        ubqGetIpStr(UbqUlong    netIp);
extern const char*     ubqGetSysError(int         errNum);

/***********************************/
/* Runtime check (assertion) stuff */
/***********************************/
#define ubqExit()  ubqExitProcess(__LINE__,__FILE__)
#ifdef UBQ_DEBUG
#  define ubqAssert(ex)  ((ex) ? 1 : (ubqExitOnAssertion(__LINE__,__FILE__),0))
#else
#  define ubqAssert(ex)  1
#endif	/* UBQ_DEBUG */

////////////////////
// Win 16 porting //
////////////////////
#define UBQ_MAX_SIGNED_INT	0x7fff

#ifdef _WIN16
# define UBQ_HUGE		__huge
#else
# define UBQ_HUGE
#endif /* _WIN16 */

#endif	/* __UBIQUE_H */
