# CmdBaseReader
Example code to read and interpret serial bytes transmitted by Lionel's TMCC Command Base

This program was developed in the late ‘90s when Lionel Corp. issued the 6-18043 C&O Yellowbird steam locomotive controlled by the TMCC Command Base and CAB1 handheld control.  The Command Base has a serial port.  The accompanying manual, “Lionel Trainmaster Command - The Complete Guide to Command Control” (Lionel part #71-2911-250) has a section “Base-Computer communications” that described the output of TMCC commands via the serial port.  The CmdBaseReader program was written as a diagnostic tool that echoes the 3-byte TMCC commands transmitted by the Command Base to the console and interprets the commands to human-readable text.  For example: “Engine 1 Forward”.

The program used Microsoft serial port I/O example code.  This code can now be found at 
https://github.com/shellohunter/pincode/tree/master/c_cpp/mttty.

At startup, the program opens COM1 (hard wired in this example) and parses the input bytes for TMCC 3-byte commands.  The CmdBaseReader receives bytes from the tty lib via ProcessCharCallback().

Lionel has published the Legacy commands which overload the original TMCC commands with Legacy-specific commands.  Download the “Lionel LCS Partner Documentation – Legacy Command Protocol” document from the Lionel/LCS web page if you want to extend the CmdBaseReader logic to handle Legacy commands.
