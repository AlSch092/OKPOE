# OKPOE: Automation &amp; scripting tool for Path of Exile

Includes: Monster attacking, movement, looting, inventory management, flasking/healing, element reading, network emulation, and more!

![Alt text](gopoe.PNG?raw=true "Sample")  

# Updated: March 2024  
- Full and final upload of all files, no further development will be done on this project
- Still requires a server (can be localhost) to feed memory addresses to the client -> This can be found in the `OffsetServer` directory, and is written as a C# project

# How to use:  
- Inject into running process. For auto-injection, you'll need to 'proxy' an existing DLL which the game uses. Make sure hardware ID/Offset server is running at the IP and port specified in NetLogger.hpp (static byte serverIP[]).  
- Memory addresses/Offsets are fed by a server, which also handles Hardware ID authentication & Heartbeats which are sent when certain features are activated/deactivated.