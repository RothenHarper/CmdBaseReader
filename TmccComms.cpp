// TmccComms.cpp
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




#include "StdAfx.h"

#include "TmccComms.h"
#include "TmccCommsDef.h"



CTmccComms::CTmccComms(void)	
{	
	m_tReadState = WaitingForFE; 
	m_pHandle = (void *) this; 
	return; 
}


CTmccComms::~CTmccComms(void)
{ 
	return; 
}



char * CTmccComms::LookupCommandString( const TMCC_STRING * pTable, const WORD wCmdData )
{
	for ( int i = 0; (pTable + i)->_wCmd != TMCCNOP; i++ )
	{
		if ( wCmdData == (pTable + i)->_wCmd )
			return (pTable + i)->_pStrg;
	}
	//
	// if we get here, then the lookup failed
	//
	return NULL;	// no matching command found
}


char * CTmccComms::LookupSwitchCmdString( const WORD wCmdData )
{
	char * pszText = LookupCommandString( SwitchStrgs, wCmdData );

	if ( pszText != NULL )
		return pszText;

	//
	// look for variable data commands
	//
	if ( (wCmdData & TMCCSWITCHASSIGNTHROUGH) == TMCCSWITCHASSIGNTHROUGH )
	{
		sprintf(m_szCmdBuff, TEXT("Assign to Route %d THROUGH"), (wCmdData & 0x001F) );
		return m_szCmdBuff;
	}
	if ( (wCmdData & TMCCENGRELATIVESPEED) == TMCCENGRELATIVESPEED )
	{
		sprintf(m_szCmdBuff, TEXT("Assign to Route %d OUT"), (wCmdData & 0x001F) );
		return m_szCmdBuff;
	}

	return NULL;
}


char * CTmccComms::LookupRouteCmdString( const WORD wCmdData )
{
	return LookupCommandString( RouteStrgs, wCmdData );
	// no variable data Route commands
}


char * CTmccComms::LookupTrainEngineCmdString( const WORD wCmdData )
{
	char * pszText = LookupCommandString( EngTrainStrgs, wCmdData );

	if ( pszText != NULL )
		return pszText;

	//
	// look for variable data commands
	//
	if ( (wCmdData & TMCCENGRELATIVESPEED) == TMCCENGRELATIVESPEED )
	{
		sprintf(m_szCmdBuff, TEXT("Set Relative Speed %d"), 
			(wCmdData & 0x001F) - 0x0005 );
		return m_szCmdBuff;
	}
	if ( (wCmdData & TMCCENGABSOLUTESPEED) == TMCCENGABSOLUTESPEED )
	{
		sprintf(m_szCmdBuff, TEXT("Set Absolute Speed %d"), (wCmdData & 0x001F) );
		return m_szCmdBuff;
	}
	if ( (wCmdData & TMCCENGASSIGN) == TMCCENGASSIGN )
	{
		sprintf(m_szCmdBuff, TEXT("Assign to Train %d"), (wCmdData & 0x000F) );
		return m_szCmdBuff;
	}
	if ( (wCmdData & TMCCENGNUMERIC) == TMCCENGNUMERIC )
	{
		sprintf(m_szCmdBuff, TEXT("Numeric %d"), (wCmdData & 0x000F) );
		return m_szCmdBuff;
	}

	return NULL;
}


char * CTmccComms::LookupAccessoryCmdString( const WORD wCmdData )
{
	char * pszText = LookupCommandString( AccessoryStrgs, wCmdData );

	if ( pszText != NULL )
		return pszText;

	//
	// look for variable data commands
	//
	if ( (wCmdData & TMCCACCNUMERIC) == TMCCACCNUMERIC )
	{
		sprintf(m_szCmdBuff, TEXT("Numeric %d"), (wCmdData & 0x000F) );
		return m_szCmdBuff;
	}
	if ( (wCmdData & TMCCACCASSIGNAUX1) == TMCCACCASSIGNAUX1 )
	{
		sprintf(m_szCmdBuff, TEXT("Assign AUX1 to Group %d"), (wCmdData & 0x000F) );
		return m_szCmdBuff;
	}
	if ( (wCmdData & TMCCACCRELATIVESPEED) == TMCCACCRELATIVESPEED )
	{
		sprintf(m_szCmdBuff, TEXT("Set Relative Speed %d"), 
			(wCmdData & 0x001F) - 0x0005 );
		return m_szCmdBuff;
	}

	return NULL;
}


char * CTmccComms::LookupGroupCmdString( const WORD wCmdData )
{
	return LookupCommandString( GroupStrgs, wCmdData );
	// no variable data for Group commands
}


char * CTmccComms::LookupCommandString( const WORD wType, const WORD wCmdData )
{
	switch ( wType )
	{
	case TMCCSWITCHCMD:		// 0x0008
		return LookupSwitchCmdString( wCmdData );
	case TMCCROUTECMD:		// 0x001A
		return LookupRouteCmdString( wCmdData );
	case TMCCENGINECMD:		// 0x0000
	case TMCCTRAINCMD:		// 0x0019
		return LookupTrainEngineCmdString( wCmdData );
	case TMCCACCESSORYCMD:	// 0x0010
		return LookupAccessoryCmdString( wCmdData );
	case TMCCGROUPCMD:		// 0x0018
		return LookupGroupCmdString( wCmdData );
	default:
		return NULL;
	}
}






char * CTmccComms::LookupTypeString( const WORD wType )
{
	switch ( wType )
	{
	case TMCCSWITCHCMD:		// 0x0008
		return TEXT("Switch");
	case TMCCROUTECMD:		// 0x001A
		return TEXT("Route");
	case TMCCENGINECMD:		// 0x0000
		return TEXT("Engine");
	case TMCCTRAINCMD:		// 0x0019
		return TEXT("Train");
	case TMCCACCESSORYCMD:	// 0x0010
		return TEXT("Accessory");
	case TMCCGROUPCMD:		// 0x0018
		return TEXT("Group");
	}
	return NULL;
}


bool CTmccComms::ParseTmccCmd(void)
{
	m_pszCmdText = "";

	// look for global commands
	WORD wCmd		= (m_cmdBuff[1] << 8) + m_cmdBuff[2];

	switch ( wCmd )
	{
	case TMCCSYSTEMHALT:
		m_pszCmdText = "SYSTEM HALT!";
		return true;
	case TMCCNOP:
		m_pszCmdText = "SYSTEM NOP";
		return true;
	case TMCCRESERVED1:
		m_pszCmdText = "Reserved 1";
		return true;
	case TMCCRESERVED2:
		m_pszCmdText = "Reserved 2";
		return true;
	}

	// Get the fixed-size fields
	m_wTmccData		= wCmd & TMCCDATAMASK;
	m_wTmccCommand	= (wCmd >> TMCCCOMMANDSHIFT) & TMCCCOMMANDMASK;

	// Get the address including extra bits (to be masked off later)
	m_wTmccCmdAddr	= (wCmd >> TMCCFULLADDRSHIFT) & TMCCFULLADDRMASK;

	// parse the variable-length command type field 
	m_wTmccCmdType	= (wCmd >> TMCCTYPESHIFT) & TMCCTYPEMASK;

	if ( (m_wTmccCmdType & TMCCLONGCMDBITS) != TMCCLONGCMDBITS )
	{
		m_wTmccCmdType &= TMCCLONGCMDBITS;	// 2-bit command type
	}
	else
	{
		if ( (m_wTmccCmdType & TMCCROUTECMD) == TMCCROUTECMD )
		{
			m_wTmccCmdType &= TMCCROUTECMD;		// 4-bit command type
			m_wTmccCmdAddr &= TMCCROUTEADDRMASK;	// 5 address bits
		}
		else
		{
			// else leave the type as a 5-bit command type
			m_wTmccCmdAddr &= TMCCTRAINADDRMASK;	// 4 address bits
		}
	}

	// build a command string
	m_pszTypeStrg = LookupTypeString( m_wTmccCmdType );
	if ( m_pszTypeStrg == NULL )
		return false;

	m_pszCmdStrg = LookupCommandString( m_wTmccCmdType, (wCmd & TMCCCMDDATAMASK) );

	static char buffer[ 256 ];
	sprintf( buffer, "%s %d %s", m_pszTypeStrg, m_wTmccCmdAddr, m_pszCmdStrg ); 
	m_pszCmdText = buffer;
	return true;
}


void CTmccComms::ProcessChar( BYTE byData )
{
	switch( m_tReadState )
	{
		case WaitingForFE:
		{
			if ( byData == 0xFE )
			{
				m_tReadState = GotFE;
				m_cmdBuff[ 0 ] = byData;
			}
			break;
		}

		case GotFE:
		{
			m_tReadState = GotByte1;
			m_cmdBuff[ 1 ] = byData;
			break;
		}

		case GotByte1:
		{
			m_tReadState = GotCmd;
			m_cmdBuff[ 2 ] = byData;
		}
		// fall through
		case GotCmd:
		{
			ParseTmccCmd();
			m_tReadState = WaitingForFE;
		}
		default:
			break;
	}
}


void CTmccComms::ProcessCharCallback( void * pHandle, BYTE byData )
{
	CTmccComms *v = (CTmccComms *)pHandle;
	if ( v->m_pHandle == pHandle )			// sanity check
		v->ProcessChar( byData );
}

