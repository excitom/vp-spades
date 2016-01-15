#ifndef __UBQNDR_H
#define __UBQNDR_H


class UbqNdr
{
 private:
  void ensureSpace(UbqUlong len);

 protected:
  UbqBool        incoming;
  char UBQ_HUGE* buf;
  UbqUlong       size;
  char UBQ_HUGE* position;

 public:
  UbqNdr();
  UbqNdr(UbqUlong      len, const char UBQ_HUGE* data);
  virtual ~UbqNdr();

  // state query methods
  UbqBool        hasSpace(UbqUlong len);
  UbqBool              isOk()       const;
  UbqBool              isIncoming() const;
  UbqUlong             getLength()  const;
  UbqUlong             getSize()    const;
  const char UBQ_HUGE* getData()    const;
  const char UBQ_HUGE* atOffset(UbqUlong offset) const;

  void    dump(char           v);
  void    dump(UbqUchar       v);
  void    dump(UbqUshort      v, UbqBool doTranslate = UBQ_TRUE);
  void    dump(UbqUlong       v, UbqBool doTranslate = UBQ_TRUE);
  void    dump(UbqBool        v);
//  void    dump(const CString& v);
  void    dump(UbqUlong       len, const char UBQ_HUGE* v);

  UbqBool load(char&          v);
  UbqBool load(UbqUchar&      v);
  UbqBool load(UbqUshort&     v, UbqBool doTranslate = UBQ_TRUE);
  UbqBool load(UbqUlong&      v, UbqBool doTranslate = UBQ_TRUE);
  UbqBool load(UbqBool&       v);
  UbqBool load(CString&       v);
  UbqBool load(UbqUlong       len, char UBQ_HUGE* v);

};


#endif  /* __UBQNDR_H */
