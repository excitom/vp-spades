#include "stdafx.h"
#include <winsock.h>
#include <string.h>
#include "ubique.h"
#include "LightNdr.h"
//#include <UbqOs.h>

#ifdef _WIN16
#include "windowsx.h"
# define MEMCPY hmemcpy
#else
# define MEMCPY memcpy
#endif

///////////////////////////////////////////////////////
// Defines, routines, and vars for handling the pool //
///////////////////////////////////////////////////////
#define POOL_SIZE 5
#define BUFF_SIZE 1024

void ubqMemAllocError() {}


class NdrPool {
 private:
  static char** pool; // must be static, due to construction order...

 public:
  ~NdrPool();
  char* allocateBuffer(UbqUlong size);
  void      freeBuffer(UbqUlong size, char* buffer);
};

char** NdrPool::pool = 0;
static NdrPool thePool;

NdrPool::~NdrPool()
{
  if (pool) {
    for (int i = 0; i < POOL_SIZE; i++)
      if (pool[i])
  delete [] pool[i];
  }
  delete [] pool;
  pool = 0;
}

char* NdrPool::allocateBuffer(UbqUlong size)
{
  ubqAssert((size == BUFF_SIZE) || ((size & 0x0ffff) == 0));
  char* rc = 0;

  if (size == BUFF_SIZE) {
    int i;
    if (!pool) {
      if (!(pool = new (char* [POOL_SIZE])))
  ubqMemAllocError();
      for (i = 0; i < POOL_SIZE; i++)
  pool[i] = 0;
    }
    for (i = 0; (i < POOL_SIZE) && !pool[i]; i++)
      ;
    if (i < POOL_SIZE) {
      rc      = pool[i];
      pool[i] = 0;
    }
    else
      rc = new char[BUFF_SIZE];
  }
  else
#ifdef _WIN16
    rc = (char*)GlobalAllocPtr(0, size);
#else
    rc = new char[size];
#endif /* _WIN16 */
  if (!rc)
    ubqMemAllocError();
  return rc;
}

void NdrPool::freeBuffer(UbqUlong size, char* buffer)
{
  ubqAssert(buffer && ((size == BUFF_SIZE) || ((size & 0x0ffff) == 0)));
  if (size == BUFF_SIZE) {
    if (pool) {
      for (int i = 0; i < POOL_SIZE; i++)
  if (!pool[i]) {
    pool[i] = buffer;
    return;
  }
    }
  }
#ifdef _WIN16
  else {
    GlobalFreePtr(buffer);
    return;
  }
#endif /* _WIN16 */
  delete [] buffer;
}


//////////////////
// Constructors //
//////////////////
UbqNdr::UbqNdr() :
  incoming(UBQ_FALSE),
  buf(thePool.allocateBuffer(BUFF_SIZE)),
  size(BUFF_SIZE),
  position(buf)
{
}

UbqNdr::UbqNdr(UbqUlong len, const char UBQ_HUGE* data) :
  incoming(UBQ_TRUE),
  buf((char UBQ_HUGE*)data),
  size(len),
  position(buf)
{
}


////////////////
// Destructor //
////////////////
UbqNdr::~UbqNdr()
{
  if (!incoming)
    thePool.freeBuffer(size, buf);
}

/////////////
// Methods //
/////////////
void UbqNdr::ensureSpace(UbqUlong l)
{
  ubqAssert(!incoming && buf && position);
  if (!hasSpace(l)) {
    UbqUlong       used    = getLength();
    UbqUlong       newSize = (((used+l)*2)+0xffff) & 0xffff0000;
    char UBQ_HUGE* newBuf  = thePool.allocateBuffer(newSize);
    MEMCPY(newBuf, buf, used);
    thePool.freeBuffer(size, buf);
    size     = newSize;
    buf      = newBuf;
    position = &(newBuf[used]);
    ubqAssert(hasSpace(l));
  }
}

UbqBool UbqNdr::hasSpace(UbqUlong len)
{
  return(((getLength() + len) <= size) ? UBQ_TRUE : UBQ_FALSE);
}

UbqBool UbqNdr::isOk() const
{
  return((UbqBool)(getLength() <= size));
}

UbqBool UbqNdr::isIncoming() const
{
  return incoming;
}

UbqUlong UbqNdr::getLength() const
{
  ubqAssert((buf && position) || (!buf && !position));
  return((UbqUlong)(position-buf));
}

UbqUlong UbqNdr::getSize() const
{
  return size;
}

const char UBQ_HUGE* UbqNdr::getData() const
{
  return buf;
}

/*
const char UBQ_HUGE* UbqNdr::atOffset(UbqUlong offset) const
{
  ubqAssert((offset <= size) && buf);
  return(&(buf[offset]));
}

void UbqNdr::rewind(UbqUlong offset)
{
  ubqAssert((offset <= size) && buf);
  position = &(buf[offset]);
}
*/

void UbqNdr::dump(char v)
{
  ensureSpace(1);
  *position++ = v;
}

void UbqNdr::dump(UbqUchar v)
{
  dump((char)v);
}

void UbqNdr::dump(UbqUshort v, UbqBool doTranslate)
{
  ensureSpace(sizeof(v));
  if (doTranslate)
    v = htons(v);
  MEMCPY(position, (char*)&v, sizeof(v));
  position += sizeof(v);
}

void UbqNdr::dump(UbqUlong v, UbqBool doTranslate)
{
  ensureSpace(sizeof(v));
  if (doTranslate)
    v = htonl(v);
  MEMCPY(position, (char*)&v, sizeof(v));
  position += sizeof(v);
}

void UbqNdr::dump(UbqBool v)
{
  char c = (v ? 1 : 0);
  dump(c);
}

/*
void UbqNdr::dump(const CString& v)
{
  UbqUlong l = v.GetLength();
  if (l > UBQ_MAX_SIGNED_INT)
    ubqExit();
  ubqAssert((l & 0xffff0000) == 0);   //todo: use VP_IS_SHORT
  dump((UbqUshort)l);
  dump(l, v);
}
*/

void UbqNdr::dump(UbqUlong len, const char UBQ_HUGE* v)
{
  if (len) {
    ensureSpace(len);
    MEMCPY(position, v, len);
    position += len;
  }
}

UbqBool UbqNdr::load(char& v)
{
  ubqAssert(incoming);
  if (!hasSpace(1))
    return UBQ_FALSE;
  v = *position++;
  return UBQ_TRUE;
}

UbqBool UbqNdr::load(UbqUchar& v)
{
  return load((char&)v);
}

UbqBool UbqNdr::load(UbqUshort& v, UbqBool doTranslate)
{
  ubqAssert(incoming);
  if (!hasSpace(sizeof(v)))
    return UBQ_FALSE;
  MEMCPY((char*)&v, position, sizeof(v));
  position += sizeof(v);
  if (doTranslate)
    v = ntohs(v);
  return UBQ_TRUE;
}

UbqBool UbqNdr::load(UbqUlong& v, UbqBool doTranslate)
{
  ubqAssert(incoming);
  if (!hasSpace(sizeof(v)))
    return UBQ_FALSE;
  MEMCPY((char*)&v, position, sizeof(v));
  position += sizeof(v);
  if (doTranslate)
    v = ntohl(v);
  return UBQ_TRUE;
}

UbqBool UbqNdr::load(UbqBool& v)
{
  char c;
  if (!load(c))
    return UBQ_FALSE;
  v = ((c & 0x01) ? UBQ_TRUE : UBQ_FALSE);
  return UBQ_TRUE;
}

//*
UbqBool UbqNdr::load(CString& v)
{
  UbqUshort len;
  if (!load(len) || (len > UBQ_MAX_SIGNED_INT) || !hasSpace(len))
    return UBQ_FALSE;
  v.Empty();
  char* p = v.GetBufferSetLength(len);
  ubqAssert(p);
  MEMCPY(p, position, len);
  position += len;
  ubqAssert(isOk());
  return UBQ_TRUE;
}
//*/

UbqBool UbqNdr::load(UbqUlong len, char UBQ_HUGE* v)
{
  ubqAssert(incoming);
  if (len) {
    if (!v || !hasSpace(len))
      return UBQ_FALSE;
    MEMCPY(v, position, len);
    position += len;
  }
  return UBQ_TRUE;
}

/*
UbqNdr::operator const char*() const
{
  return buf;
}

const UbqNdr& UbqNdr::operator=(const UbqNdr& other)
{
  ubqAssert(isOk() && other.isOk());

  if (this != &other) {
    if (!incoming) {
      ubqAssert(buf && size && position);
      thePool.freeBuffer(size, buf);
    }

    incoming = other.incoming;
    size     = other.size;

    if (other.incoming) {
      buf      = other.buf;
      position = other.position;
    }
    else {
      ubqAssert(other.buf && other.size && other.position);
      UbqUlong used = other.getLength();
      buf           = thePool.allocateBuffer(other.size);
      position      = buf + used;
      MEMCPY(buf, other.buf, used);
    }
  }

  return *this;
}
*/
