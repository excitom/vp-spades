#ifndef _LOG
#define _LOG

class LogRecord
{
private:
	LogRecord*	next;
	LogRecord*  prev;
	BOOL		lastTrick;
	BOOL		trickRec;
	CString		rec;

public:
	LogRecord(BOOL trick);
	~LogRecord();
	void		addStr( CString& rec );
	void		addStr( const char* rec );
	CString&	getStr() { return this->rec; }
	LogRecord*	getNext() { return this->next; }
	LogRecord*	getPrev() { return this->prev; }
	BOOL		isTrickRec() { return this->trickRec; }
	BOOL		isInLastTrick() { return this->lastTrick; }
	void		clearLastTrick() { this->lastTrick = FALSE; }
};

class Log {

public:
	static	void	writeLog( CString& line );
	static	void	writeLog(const char* line);
	static	void	writeLog( CString& line, BOOL trick );
	static	void	writeLog(const char* line, BOOL trick );
	static  void	trickEnded();
	static	void	update();
	static	unsigned char* saveState( unsigned char* p );
	static	unsigned char* loadState( unsigned char* p );
	static  LogRecord* getNext( LogRecord* curr );
	static  LogRecord* getPrev( LogRecord* curr );
	static  void	removeAll();
	static  void	setPref( BOOL newestFirst );
	static  BOOL	getPref();
//	static	void	scroll();
};
#endif
