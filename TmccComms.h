// TmccComms
//
/****************************************************************************
MIT License

Copyright (c) 2001, 2018 John Harper

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
****************************************************************************/

#ifndef TMCCCOMMS_H
#define TMCCCOMMS_H

struct _tmccString;

class CTmccComms
{
public:
	CTmccComms(void); 
	~CTmccComms(void);

	//
	// Command parsing
	//
	WORD GetCmdType(void)		{ return m_wTmccCmdType; };
	WORD GetCmdAddr(void)		{ return m_wTmccCmdAddr; };
	WORD GetCommand(void)		{ return m_wTmccCommand; };
	WORD GetCmdData(void)		{ return m_wTmccData; };
	char * GetTypeStrg(void)	{ return m_pszTypeStrg; };
	char * GetCmdStrg(void)		{ return m_pszCmdStrg; };
	char * GetCmdText(void)		{ return m_pszCmdText; };
	//
	// tty read linkages
	//
	static void ProcessCharCallback( void * pHandle, BYTE byData );
	void * GetHandle(void)		{ return m_pHandle; };

private:

	char * LookupCommandString( const struct _tmccString * pTable, const WORD wCmdData );
	char * LookupSwitchCmdString( const WORD wCmdData );
	char * LookupRouteCmdString( const WORD wCmdData );
	char * LookupTrainEngineCmdString( const WORD wCmdData );
	char * LookupAccessoryCmdString( const WORD wCmdData );
	char * LookupGroupCmdString( const WORD wCmdData );
	char * LookupCommandString( const WORD wType, const WORD wCmdData );
	char * LookupTypeString( const WORD wType );
	bool ParseTmccCmd(void);
	void ProcessChar( BYTE byData );


private:
	WORD m_wTmccCmdType;	// bits 14-15 unless '11', then bits 11-15
	WORD m_wTmccCmdAddr;	// bits 7-13 (reduced for route, train & grp)
	WORD m_wTmccCommand;	// bits 5-6
	WORD m_wTmccData;		// bits 0-4
	char m_szCmdBuff[ 256 ];
	char * m_pszTypeStrg;
	char * m_pszCmdStrg;
	char * m_pszCmdText;

private:
	void * m_pHandle;
	enum TmccReadState
	{
		WaitingForFE = 0,
		GotFE,
		GotByte1,
		GotCmd
	};
	TmccReadState m_tReadState;
	BYTE m_cmdBuff[ 3 ];

};



#endif  TMCCCOMMS_H
