// TmccCommsDef.h
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

#ifndef TMCCCOMMSDEF_H
#define TMCCCOMMSDEF_H



#define TMCCDATAMASK		0x001F
#define TMCCCOMMANDMASK		0x0003
#define TMCCCOMMANDSHIFT	5
#define TMCCFULLADDRMASK	0x007F
#define TMCCFULLADDRSHIFT	7
#define TMCCROUTEADDRMASK	0x001F
#define TMCCTRAINADDRMASK	0x000F
#define TMCCGROUPADDRMASK	0x000F
#define TMCCCMDDATAMASK		0x007F	// Cmd field + Data field

#define TMCCSWITCHCMD		0x0008
#define TMCCROUTECMD		0x001A
#define TMCCENGINECMD		0x0000
#define TMCCTRAINCMD		0x0019
#define TMCCACCESSORYCMD	0x0010
#define TMCCGROUPCMD		0x0018
#define TMCCLONGCMDBITS		0x0018

#define TMCCTYPEMASK		0x001F
#define TMCCTYPESHIFT		11

// Global commands
#define TMCCSYSTEMHALT		0xFFFF
#define TMCCNOP				0xFF80
#define TMCCRESERVED1		0xFEFF
#define TMCCRESERVED2		0xFFFE

// fixed data commands
#define TMCCFIXEDCMDMASK			0x007F

// Switch  commands (fixed data)
#define TMCCSWITCHTHROUGH			0x0000
#define TMCCSWITCHOUT				0x001F
#define TMCCSWITCHSETADDR			0x002B

// Switch route assignment commands ... 
#define TMCCSWITCHASSIGNTHROUGH		0x0040	// + 5 bits route ID
#define TMCCSWITCHASSIGNOUT			0x0060	// + 5 bits route ID


// Route commands (fixed data)
#define TMCCROUTETHROW				0x001F
#define TMCCROUTECLEAR				0x002C

// Engine and Train Action commands (fixed data)
#define TMCCACTIONFORWARD			0x0000
#define TMCCACTIONDIRECTION			0x0001
#define TMCCACTIONREVERSE			0x0003
#define TMCCACTIONBOOST				0x0004
#define TMCCACTIONBRAKE				0x0007
#define TMCCACTIONFRONT				0x0005
#define TMCCACTIONREAR				0x0006
#define TMCCACTIONHORN1				0x001C
#define TMCCACTIONBELL				0x001D
#define TMCCACTIONSOUNDDWN			0x001E
#define TMCCACTIONHORN2				0x001F
#define TMCCACTIONAUX1OFF			0x0008
#define TMCCACTIONCABAUX1			0x0009
#define TMCCACTIONAUX1OPT2			0x000A
#define TMCCACTIONAUX1ON			0x000B
#define TMCCACTIONAUX2OFF			0x000C
#define TMCCACTIONCABAUX2			0x000D
#define TMCCACTIONAUX2OPT2			0x000E
#define TMCCACTIONAUX2ON			0x000F

// Engine Extended commands (fixed data)
#define TMCCENGEXTSINGLEUNITFORWARD	0x0020
#define TMCCENGEXTSINGLEUNITREVERSE	0x0024
#define TMCCENGEXTHEADUNITFORWARD	0x0021
#define TMCCENGEXTHEADUNITREVERSE	0x0025
#define TMCCENGEXTMIDDLEUNITFORWARD	0x0022
#define TMCCENGEXTMIDDLEUNITREVERSE	0x0026
#define TMCCENGEXTREARUNITFORWARD	0x0023
#define TMCCENGEXTREARUNITREVERSE	0x0027
#define TMCCENGEXTMOMENTUMLOW		0x0028	// also is a train ext cmd
#define TMCCENGEXTMOMENTUMMEDIUM	0x0029	// also is a train ext cmd
#define TMCCENGEXTMOMENTUMHIGH		0x002A	// also is a train ext cmd
#define TMCCENGEXTSETADDRESS		0x002B	// also is a train & acc ext cmd

// Train Extended commands
#define TMCCTRAINEXTCLEARLASHUP		0x002C

// Train relative speed commands ... 
#define TMCCENGNUMERIC				0x0010	// + 4 bits of data
#define TMCCENGASSIGN				0x0030	// + 4 bits of data
#define TMCCENGABSOLUTESPEED		0x0060	// + 5 bits of speed
#define TMCCENGRELATIVESPEED		0x0040	// + 5 bits of speed


// Accessory Action Commands (fixed data)
#define TMCCACCAUX1OFF				0x0008
#define TMCCACCAUX1OPTION1			0x0009
#define TMCCACCAUX1OPTION2			0x000A
#define TMCCACCAUX1ON				0x000B
#define TMCCACCAUX2OFF				0x000C
#define TMCCACCAUX2OPTION1			0x000D
#define TMCCACCAUX2OPTION2			0x000E
#define TMCCACCAUX2ON				0x000F

// Accessory Extended Commands (fixed data)
#define TMCCACCEXTALLOFF			0x0020
#define TMCCACCEXTALLON				0x002F
#define TMCCACCEXTSETADDRESS		0x002B	// same as Eng & Train set addr

// Accessory variable commands
#define TMCCACCNUMERIC				0x0010	// + 4 bits of data [0-9]
#define TMCCACCASSIGNAUX1			0x0020	// + 4 bits of data [0-9]
#define TMCCACCRELATIVESPEED		0x0040	// + 4 bits of speed

// Group Commands
#define TMCCGROUPOFF				0x0008
#define TMCCGROUPOPTION1			0x0009
#define TMCCGROUPOPTION2			0x000A
#define TMCCGROUPON					0x000B
#define TMCCGROUPCLEAR				0x002C

typedef struct _tmccString
{
	WORD _wCmd;
	char * _pStrg;
}	TMCC_STRING;

TMCC_STRING SwitchStrgs[] =
{
	{ TMCCSWITCHTHROUGH,	TEXT("Through")},
	{ TMCCSWITCHOUT,		TEXT("Out")},
	{ TMCCSWITCHSETADDR,	TEXT("Set Address")},
	{ TMCCNOP, NULL}
};

TMCC_STRING RouteStrgs[] =
{
	{ TMCCROUTETHROW,		TEXT("Throw")},
	{ TMCCROUTECLEAR,		TEXT("Clear")},
	{ TMCCNOP, NULL}
};

TMCC_STRING EngTrainStrgs[] =
{
	{ TMCCACTIONFORWARD,	TEXT("Forward")},
	{ TMCCACTIONDIRECTION,	TEXT("Toggle Direction")},
	{ TMCCACTIONREVERSE,	TEXT("Reverse")},
	{ TMCCACTIONBOOST,		TEXT("Boost")},
	{ TMCCACTIONBRAKE,		TEXT("Brake")},
	{ TMCCACTIONFRONT,		TEXT("Front Coupler")},
	{ TMCCACTIONREAR,		TEXT("Rear Coupler")},
	{ TMCCACTIONHORN1,		TEXT("Horn1")},
	{ TMCCACTIONBELL,		TEXT("Bell")},
	{ TMCCACTIONSOUNDDWN,	TEXT("Sound Letdown")},
	{ TMCCACTIONHORN2,		TEXT("Horn2")},
	{ TMCCACTIONAUX1OFF,	TEXT("Aux 1 Off")},
	{ TMCCACTIONCABAUX1,	TEXT("CAB Aux 1")},
	{ TMCCACTIONAUX1OPT2,	TEXT("Aux 1 Option 2")},
	{ TMCCACTIONAUX1ON,		TEXT("Aux 1 On")},
	{ TMCCACTIONAUX2OFF,	TEXT("Aux 2 Off")},
	{ TMCCACTIONCABAUX2,	TEXT("CAB Aux 2")},
	{ TMCCACTIONAUX2OPT2,	TEXT("Aux 2 Option 2")},
	{ TMCCACTIONAUX2ON,		TEXT("Aux 2 On")},
	// Engine Extended commands 
	{ TMCCENGEXTSINGLEUNITFORWARD,	TEXT("Assign as Single Unit Forward")},
	{ TMCCENGEXTSINGLEUNITREVERSE,	TEXT("Assign as Single Unit Reverse")},
	{ TMCCENGEXTHEADUNITFORWARD,	TEXT("Assign as Head Unit Forward")},
	{ TMCCENGEXTHEADUNITREVERSE,	TEXT("Assign as Head Unit Reverse")},
	{ TMCCENGEXTMIDDLEUNITFORWARD,	TEXT("Assign as Middle Unit Forward")},
	{ TMCCENGEXTMIDDLEUNITREVERSE,	TEXT("Assign as Middle Unit Reverse")},
	{ TMCCENGEXTREARUNITFORWARD,	TEXT("Assign as Rear Unit Forward")},
	{ TMCCENGEXTREARUNITREVERSE,	TEXT("Assign as Rear Unit Reverse")},
	{ TMCCENGEXTMOMENTUMLOW,		TEXT("Set Momentum Low")},
	{ TMCCENGEXTMOMENTUMMEDIUM,		TEXT("Set Momentum Medium")},
	{ TMCCENGEXTMOMENTUMHIGH,		TEXT("Set Momentum High")},
	{ TMCCENGEXTSETADDRESS,			TEXT("Set Address")},
	// Train Extended commands
	{ TMCCTRAINEXTCLEARLASHUP,		TEXT("Clear Lashup")},

	{ TMCCNOP, NULL}
};

TMCC_STRING AccessoryStrgs[] =
{
	{ TMCCACCAUX1OFF,			TEXT("AUX1 Off")},
	{ TMCCACCAUX1OPTION1,		TEXT("AUX1 Option 1")},
	{ TMCCACCAUX1OPTION2,		TEXT("AUX1 Option 2")},
	{ TMCCACCAUX1ON,			TEXT("AUX1 On")},
	{ TMCCACCAUX2OFF,			TEXT("AUX2 Off")},
	{ TMCCACCAUX2OPTION1,		TEXT("AUX2 Option 1")},
	{ TMCCACCAUX2OPTION2,		TEXT("AUX2 Option 2")},
	{ TMCCACCAUX2ON,			TEXT("AUX2 On")},
	// Accessory Extended Commands (fixed data)
	{ TMCCACCEXTALLOFF,			TEXT("All Off")},
	{ TMCCACCEXTALLON,			TEXT("All On")},
	{ TMCCACCEXTSETADDRESS,		TEXT("Set Address")},
	{ TMCCNOP, NULL}
};

TMCC_STRING GroupStrgs[] =
{
	{ TMCCGROUPOFF,			TEXT("Off")},
	{ TMCCGROUPOPTION1,		TEXT("Option 1")},
	{ TMCCGROUPOPTION2,		TEXT("Option 2")},
	{ TMCCGROUPON,			TEXT("On")},
	{ TMCCGROUPCLEAR,		TEXT("Clear")},
	{ TMCCNOP, NULL}
};



#endif  TMCCCOMMSDEF_H