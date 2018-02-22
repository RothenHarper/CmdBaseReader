// TmccTtyInfo.h - Contains global definitions for the TTYINFO structure
// Derived from the Microsoft Source Code Sample Multi-threaded TTY (MTTTY). 


#ifndef TTYINFO_H
#define TTYINFO_H
//
// constant definitions
//

//
// hard coded maximum number of ports
//
#define MAXPORTS        4

//
// terminal size
//
#define MAXROWS         50
#define MAXCOLS         80

//
// cursor states
//
#define CS_HIDE         0x00
#define CS_SHOW         0x01

//
// ascii definitions
//
#define ASCII_BEL       0x07
#define ASCII_BS        0x08
#define ASCII_LF        0x0A
#define ASCII_CR        0x0D
#define ASCII_XON       0x11
#define ASCII_XOFF      0x13

//
// data structures
//
typedef struct TTYInfoStruct
{
    HANDLE  hCommPort, hReaderStatus, hWriter ;
    DWORD   dwEventFlags;
    CHAR    Screen[MAXCOLS * MAXROWS];
    CHAR    chFlag, chXON, chXOFF;
    WORD    wXONLimit, wXOFFLimit;
    DWORD   fRtsControl;
    DWORD   fDtrControl;
    BOOL    fConnected, fTransferring, fRepeating,
            fLocalEcho, fNewLine,
            fDisplayErrors, fAutowrap,
            fCTSOutFlow, fDSROutFlow, fDSRInFlow, 
            fXonXoffOutFlow, fXonXoffInFlow,
            fTXafterXoffSent,
            fNoReading, fNoWriting, fNoEvents, fNoStatus,
            fDisplayTimeouts;
    BYTE    bPort, bByteSize, bParity, bStopBits ;
    DWORD   dwBaudRate ;
//    WORD    wCursorState ;
//    HFONT   hTTYFont ;
//    LOGFONT lfTTYFont ;
//    DWORD   rgbFGColor ;
    COMMTIMEOUTS timeoutsorig;
    COMMTIMEOUTS timeoutsnew;
//    int     xSize, ySize, xScroll, yScroll, xOffset, yOffset,
//            nColumn, nRow, xChar, yChar , nCharPos;

} TTYINFO;

extern TTYINFO TTYInfo;

//
// macros ( for easier readability )
//
#define COMDEV( x )         (x.hCommPort)
#define CURSORSTATE( x )    (x.wCursorState)
#define PORT( x )           (x.bPort)
#define SCREEN( x )         (x.Screen)
#define CONNECTED( x )      (x.fConnected)
#define TRANSFERRING( x )   (x.fTransferring)
#define REPEATING( x )      (x.fRepeating)
#define LOCALECHO( x )      (x.fLocalEcho)
#define NEWLINE( x )        (x.fNewLine)
#define AUTOWRAP( x )       (x.fAutowrap)
#define BYTESIZE( x )       (x.bByteSize)
#define PARITY( x )         (x.bParity)
#define STOPBITS( x )       (x.bStopBits)
#define BAUDRATE( x )       (x.dwBaudRate)
#define HTTYFONT( x )       (x.hTTYFont)
#define LFTTYFONT( x )      (x.lfTTYFont)
#define FGCOLOR( x )        (x.rgbFGColor)
#define XSIZE( x )          (x.xSize)
#define YSIZE( x )          (x.ySize)
#define XSCROLL( x )        (x.xScroll)
#define YSCROLL( x )        (x.yScroll)
#define XOFFSET( x )        (x.xOffset)
#define YOFFSET( x )        (x.yOffset)
#define COLUMN( x )         (x.nColumn)
#define ROW( x )            (x.nRow)
#define XCHAR( x )          (x.xChar)
#define YCHAR( x )          (x.yChar)
#define DISPLAYERRORS( x )  (x.fDisplayErrors)
#define TIMEOUTSORIG( x )   (x.timeoutsorig)
#define TIMEOUTSNEW( x )    (x.timeoutsnew)
#define WRITERTHREAD( x )   (x.hWriter)
#define READSTATTHREAD( x ) (x.hReaderStatus)
#define EVENTFLAGS( x )     (x.dwEventFlags)
#define FLAGCHAR( x )       (x.chFlag)
//#define SCREENCHAR( x, col, row )   (x.Screen[row * MAXCOLS + col])

#define DTRCONTROL( x )     (x.fDtrControl)
#define RTSCONTROL( x )     (x.fRtsControl)
#define XONCHAR( x )        (x.chXON)
#define XOFFCHAR( x )       (x.chXOFF)
#define XONLIMIT( x )       (x.wXONLimit)
#define XOFFLIMIT( x )      (x.wXOFFLimit)
#define CTSOUTFLOW( x )     (x.fCTSOutFlow)
#define DSROUTFLOW( x )     (x.fDSROutFlow)
#define DSRINFLOW( x )      (x.fDSRInFlow)
#define XONXOFFOUTFLOW( x ) (x.fXonXoffOutFlow)
#define XONXOFFINFLOW( x )  (x.fXonXoffInFlow)
#define TXAFTERXOFFSENT(x)  (x.fTXafterXoffSent)

#define NOREADING( x )      (x.fNoReading)
#define NOWRITING( x )      (x.fNoWriting)
#define NOEVENTS( x )       (x.fNoEvents)
#define NOSTATUS( x )       (x.fNoStatus)
#define SHOWTIMEOUTS( x )   (x.fDisplayTimeouts)


//
// this section from mttty.h ... needs heavy pruning
//

//
// GLOBAL DEFINES
//
//#define TTY_BUFFER_SIZE         MAXROWS * MAXCOLS
#define MAX_STATUS_BUFFER       20000
#define MAX_WRITE_BUFFER        1024
#define MAX_READ_BUFFER         2048
#define READ_TIMEOUT            500
#define STATUS_CHECK_TIMEOUT    500
#define WRITE_CHECK_TIMEOUT     500
#define PURGE_FLAGS             PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR 
#define EVENTFLAGS_DEFAULT      EV_BREAK | EV_CTS | EV_DSR | EV_ERR | EV_RING | EV_RLSD
#define FLAGCHAR_DEFAULT        '\n'

//
// Write request types
//
#define WRITE_CHAR          0x01
#define WRITE_FILE          0x02
#define WRITE_FILESTART     0x03
#define WRITE_FILEEND       0x04
#define WRITE_ABORT         0x05
#define WRITE_BLOCK         0x06

//
// Read states
//
#define RECEIVE_TTY         0x01
#define RECEIVE_CAPTURED    0x02

//
// window coords
//
//#define MAXXWINDOW          750
//#define MAXYWINDOW          530
//#define STARTXWINDOW        80
//#define STARTYWINDOW        70
//
//#define SETTINGSFACTOR      5
//#define STATUSFACTOR        5

//
// window timer ids
// 
//#define TIMERID             1

//
// GLOBAL VARIABLES
//
extern OSVERSIONINFO g_OSV;
//extern HINSTANCE     g_hInst;
//extern HACCEL        g_hAccel;
//extern HWND          g_hwndMain;
//extern HWND          g_hWndToolbarDlg;
//extern HWND          g_hWndStatusDlg;
//extern HWND          g_hWndTTY;
//extern HWND          g_hWndHidden;

//
// COMMTIMEOUTS is init'd in Init.c
//
extern COMMTIMEOUTS gTimeoutsDefault;

//
//  Window placement variables
//
//WORD gwBaseY;
//LONG gcyMinimumWindowHeight;

//
//  Flags controlling thread actions
//
extern HANDLE	g_hThreadExitEvent;
extern BOOL		g_fAbortTransfer;

//
//  File transfer variables
//
extern DWORD  g_dwFileTransferLeft;
extern DWORD  g_dwReceiveState;
extern HANDLE g_hFileCapture;

//
//  Status updating
//
extern CRITICAL_SECTION		g_critsectStatus;
extern HANDLE				g_hStatusMessageEvent;
extern HANDLE				g_hStatusMessageHeap;
extern HFONT				g_hFontStatus;
extern int					g_nStatusIndex;

//typedef struct STATUS_MESSAGE;

typedef struct STATUS_MESSAGE
{
    struct STATUS_MESSAGE * lpNext;     // pointer to next node
    char chMessageStart;                // variable length string start here
} STATUS_MESSAGE;

extern struct STATUS_MESSAGE * g_lpStatusMessageHead;
extern struct STATUS_MESSAGE * g_lpStatusMessageTail;


//
//  Port name and configurable parameters
//
extern char g_szPort[10];
extern DWORD g_dwBaud;

//
//  Writer heap variables
//
extern CRITICAL_SECTION g_critsectWriterHeap;
extern CRITICAL_SECTION g_critsectDataHeap;
extern HANDLE g_hWriterHeap;
extern HANDLE g_hWriterEvent;
extern HANDLE g_hTransferCompleteEvent;

//
//  Write request data structure; look in Writer.c for more info
//
//typedef struct WRITEREQUEST;

typedef struct WRITEREQUEST
{
  DWORD      dwWriteType;        // char, file start, file abort, file packet
  DWORD      dwSize;             // size of buffer
  char       ch;                 // ch to send
  char *     lpBuf;              // address of buffer to send
  HANDLE     hHeap;              // heap containing buffer
  HWND       hWndProgress;       // status bar window handle
  struct WRITEREQUEST *pNext;    // next node in the list
  struct WRITEREQUEST *pPrev;    // prev node in the list
} WRITEREQUEST, *PWRITEREQUEST;

extern struct WRITEREQUEST *g_pWriterHead;
extern struct WRITEREQUEST *g_pWriterTail;


//
// Prototypes of functions called between source files
//

//
//  Error functions
//
void ErrorReporter( char * szMessage );
void ErrorHandler( char * szMessage );
void ErrorInComm( char * szMessage );

//
//  Initialization/deinitialization/settings functions
//
HANDLE SetupCommPort( void );
void ChangeConnection( HWND, BOOL );
BOOL BreakDownCommPort( void );
BOOL UpdateConnection( void );
void GlobalInitialize( void );
void DestroyTtyInfo( void );
void GlobalCleanup( void );
void UpdateTtyInfo( void );
BOOL DisconnectOK( void );
BOOL InitTtyInfo( void );
//void InitNewFont( LOGFONT, COLORREF );

//
//  TTY functions
//
void OpenSettingsToolbar( HWND );
void OpenStatusToolbar( HWND );
BOOL CmdAbout( HWND );

//
//  TTY functions
//
//BOOL MoveTTYCursor( HWND );
//BOOL KillTTYFocus( HWND );
//BOOL SetTTYFocus( HWND );
//BOOL SizeTTY( HWND, WORD, WORD );

//
//  Thread procedures
//
DWORD WINAPI TtyReaderAndStatusThread( LPVOID );
DWORD WINAPI TtyWriterThread( LPVOID );

//
//  File transfer functions
//
void CALLBACK TransferRepeatDo( UINT, UINT, DWORD, DWORD, DWORD );  
void TransferRepeatCreate( LPCSTR, DWORD );
void TransferRepeatDestroy( void );
void TransferFileTextStart( LPCSTR );
void TransferFileTextEnd( void );
// void TransferFileText( LPCTSTR );
void ReceiveFileText( LPCTSTR );
DWORD GetAFrequency( void );

//
//  Buffer manipulation functions
//
//void OutputABufferToWindow( HWND, char *, DWORD );
//void OutputABuffer( HWND, char *, DWORD );
void OutputABuffer( char *, DWORD );
BOOL ClearTTYContents( void );

//
//  Status functions
//
HFONT CreateStatusEditFont( void );
void ReportStatusEvent( DWORD ); 
void CheckModemStatus( BOOL );
void ReportCommError( void );
void ReportComStat( COMSTAT );
void StatusMessage( void );
void UpdateStatus( char * );
void CheckComStat( BOOL );

//
//  Writer heap functions
//
BOOL WriterAddNewNode( DWORD, DWORD, char, char *, HANDLE, HWND );
BOOL WriterAddExistingNode( PWRITEREQUEST, DWORD, DWORD, char, char *, HANDLE, HWND );
BOOL WriterAddNewNodeTimeout( DWORD, DWORD, char, char *, HANDLE, HWND, DWORD );
BOOL WriterAddFirstNodeTimeout( DWORD, DWORD, char, char *, HANDLE, HWND, DWORD );


//
// callback hook
//
extern void (* pfnTtyHandler)(BYTE * pBuffer);



#endif TTYINFO_H
