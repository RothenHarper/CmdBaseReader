// TmccTtyCallbacks.cpp
/***************************************************************************
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
*****************************************************************************/

#include "StdAfx.h"
#include "TtyInfo.h"

#include "TmccComms.h"


void * g_pReadHandle = NULL;
void (* pfnTtyReadHandler)(void * pHandle, BYTE byData) = NULL;


//
// default functions
//
void UpdateStatus( char * szStatus )
{
	TRACE(_T("%s\n"), szStatus );
}


static BYTE byteOutputBuffer[ 2048 ];
static int iPosition = 0;

void FlushBuffer(void )
{
	byteOutputBuffer[iPosition] = '\0';
	TRACE(_T("%s\n"), byteOutputBuffer );
printf(_T("%s\n"), byteOutputBuffer );

	//
	// call upper level handler
	//
	if ( pfnTtyHandler )
		pfnTtyHandler( byteOutputBuffer );
//	GisParseNmeaSentence( (char *)byteOutputBuffer );

	memset(byteOutputBuffer, 0, sizeof(byteOutputBuffer));
	iPosition = 0;
}


void OutputABuffer( char * szBuff, DWORD dwCount )
{
	while ( dwCount )
	{
		if ( iPosition == sizeof(byteOutputBuffer) - 2 )
		{
			FlushBuffer();
		}
		else 
		{
			switch ( *szBuff )
			{
			case 0x0D:
				FlushBuffer();
				break;
			case 0x0A:
				break;
			default:
				byteOutputBuffer[iPosition++] = *szBuff;
				break;
			}
//			if ( *szBuff == 0x0D )
//			{
//				FlushBuffer();
//			}
//			else
//			{
//				byteOutputBuffer[iPosition++] = *szBuff;
//			}
			szBuff++;
			dwCount--;
		}
	}
	//
	// final flush if needed ...
	//
	if ( iPosition == sizeof(byteOutputBuffer) - 2 )
	{
		FlushBuffer();
	}
}