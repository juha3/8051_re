# Tool for analyzing 8051 firmware

## Introduction

A tool tries to analyze code by following calls and jumps and 
disassembles only parts of the binary, it detects as accessible parts of code.
User inteface implemented by using ncurses library,

## Usage

key   |   action
------|---------------
right | follow call / jump
left  | return to previous address
h     | help
q     | exit



```
0000    02 7f d5         ljmp 0x7fd5
0003    02 4a 2b         ljmp 0x4a2b
0006    02               byte 0x02
0007    02               byte 0x02
0008    02               byte 0x02
0009    02               byte 0x02
000a    02               byte 0x02
000b    02 4a 41         ljmp 0x4a41
000e    02               byte 0x02
000f    02               byte 0x02
0010    02               byte 0x02
0011    02               byte 0x02
0012    02               byte 0x02
0013    02 4a 83         ljmp 0x4a83
0016    02               byte 0x02
0017    02               byte 0x02
0018    02               byte 0x02
0019    02               byte 0x02
001a    02               byte 0x02
001b    02 4a 86         ljmp 0x4a86
001e    02          ========================================
001f    02           <left>    return to jump address
0020    02
0021    02
0022    02
0023    02 4e b2
0026    02
0027    02
0028    02
0029    02          ========================================
002a    02               byte 0x02
002b    02 4e ad         ljmp 0x4ead
002e    02               byte 0x02
002f    02               byte 0x02
0030    02               byte 0x02
0031    02               byte 0x02
0032    02               byte 0x02
0033    02 02 02         ljmp 0x0202
0036    02               byte 0x02
0037    02               byte 0x02
0038    02               byte 0x02
0039    02               byte 0x02
003a    02               byte 0x02
003b    02 02 02         ljmp 0x0202
003e    02               byte 0x02
003f    02               byte 0x02
```






