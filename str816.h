///////////////////////////////////////////////////////////////////////
//
//                          UBIQUE Ltd.                                 
//                      All Rights Reserved                             
//
///////////////////////////////////////////////////////////////////////
//
//  MODULE:             Str816.h
//  CREATION DATE:      July, 5, 1996
//  DESCRIPTION:        Contains OLE string manipulation shim classes.
//  NOTES:              Adapted from Microsoft Systems Journal, 1995
//  AUTHOR:             Miller Freeman, enhanced by Max Kovalenko  
//
///////////////////////////////////////////////////////////////////////

#ifndef __STR816_H__
#define __STR816_H__

#include <string.h>
#include <stdlib.h>
#ifdef WIN32
  #include <winnls.h>
#endif

///////////////////////////////////////////////////////////////////////
//
//  CLASS:		    String16
//  DESCRIPTION:  Shim class that converts bpth 8-bit (foreign) and
//                16-bit (native) strings to 16-bit wideness.  
//  NOTES:    
//
///////////////////////////////////////////////////////////////////////

#ifdef WIN32  
  #define WCHAR wchar_t
#else
  #define WCHAR char
#endif  
                  
class String16 {
public:
  // native and foreign constructors 
  String16( const char *p8, const int len = -1);
  String16( const WCHAR *p16);
  
  // non-virtual constructor
  ~String16( void);

  // native conversion operator
  operator const WCHAR *() const;

private:
  // native wideness string
  WCHAR *m_sz;
  // is foreign?
  int m_bIsForeign;

  // protect against assignment
  String16( const String16&);
  String16& operator=(const String16&);
};


// native constructor is a pass-through

inline String16::String16( const WCHAR *p16) :
       m_sz( (WCHAR *) p16),
       m_bIsForeign( 0)
{
}         

// give out the native string

inline String16::operator const WCHAR *() const
{
  return m_sz; 
}

// foreigh constructor requires allocation of a native string
// and conversion


inline String16::String16( const char *p8, const int len) :
       m_bIsForeign( 1)
{
#ifdef WIN32
  // determine the size of the required wide-char buffer  
  size_t size = MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, p8, len, NULL, 0); 
  if (m_sz = size ? new wchar_t [size] : NULL)
      MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, p8, len, m_sz, size); 
#else 
  int strLen = len > -1 ? len : (strlen(p8) + 1);
  m_sz = new char[strLen];
  memcpy(m_sz, p8, strLen);
#endif      
}

// delete native string only if was created by 
// foreign constructor
inline String16::~String16( void) 
{
  if (m_bIsForeign)
      delete [] m_sz;
}

///////////////////////////////////////////////////////////////////////
//
//  CLASS:        String8
//  DESCRIPTION:  Shim class that converts both 8-bit (native) and
//                16-bit (foreign) strings to 8-bit wideness.  
//  NOTES:    
//
///////////////////////////////////////////////////////////////////////

class String8 {
public:
  // native and foreign constructors 
  String8( const char *p8);
  String8( const WCHAR *p16, const int len = -1);
  
  // non-virtual constructor
  ~String8( void);

  // native conversion operators
  operator const char * (void) const;
  operator const void * (void) const;
  operator char * (void);
  operator void * (void);

private:
  // native wideness string
  char *m_sz;
  // is foreign?
  int m_bIsForeign;

  // protect against assignment
  String8( const String8&);
  String16& operator=(const String8&);
};

// simply pass through
inline String8::String8( const char *p8) :
       m_sz( (char *) p8),
       m_bIsForeign( 0)
{
}

// need to allocate a string for the foreign string and
// convert
inline String8::String8( const WCHAR *p16, const int len) :
       m_bIsForeign( 1)
{ 
#ifdef WIN32  
 // determine the size of the required multi-byte buffer
  const int size = WideCharToMultiByte( CP_ACP, 0, p16, len, NULL, 0, 
                                        NULL, NULL);   
  if (m_sz = size ? new char [size] : NULL)
      WideCharToMultiByte( CP_ACP, 0, p16, len, m_sz, size, 
                           NULL, NULL);    
#else                                                       
  int strLen = len > -1 ? len : (strlen(p16) + 1);
  m_sz = new char[strLen];
  memcpy(m_sz, p16, strLen);
#endif     
}

// delete native string only if was created by 
// foreign constructor
inline String8::~String8( void) {
  if (m_bIsForeign)
    delete [] m_sz;
}

// simply pass through  
inline String8::operator const char * (void) const
{
  return m_sz;
}

inline String8::operator const void * (void) const
{
  return (const void *) m_sz;
}

inline String8::operator char * (void)
{
  return m_sz;
}

inline String8::operator void * (void)
{
  return (void *) m_sz;
}
            
 
// Conditional typedefs for Win32 and OLE Text Data Types 

// typedef OLESTRCVAR to emulate the OLESTR macro
// (converts any string at run-time instead of simply changing
// layout of string literal at compile-time.

#ifdef OLE2ANSI
typedef String8 OLESTRCVAR;
#else
typedef String16 OLESTRCVAR;
#endif

// typedef __TEXTCVAR to emulate the __TEXT macro
// (converts any string at run-time instead of simply changing
// layout of string literal at compile-time.  MultiByteToWideChar

#ifdef UNICODE
typedef String16 __TEXTCVAR;
#else
typedef String8 __TEXTCVAR;
#endif

#endif // __STR816_H__


