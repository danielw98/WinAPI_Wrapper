ERRORS:
    * it runs in gdb but not without it (why?) - ASLR disabled? (fixed)
    * crashes when you click outside a widget (address zero called apparently) (fixed)
    * crashes when you try to exit from file menu - address feefee... probably buffer overflow (fixed)

TODO:
- make the void functions return an int code for error, along with the getError function.
- make sure the program doesn't crash if given wrong input and the libary catches the errors (partially done)
- create a texture struct with source rect and dest rect
- do something about that ww.c global variable, should be able to pass it as a param (optional, for fun)
- WM_COMMAND should know if it's button window or whatever command from WPARAM or LPARAM so
i could use the whole range instead of 0 1000 2000 ... 
- buttons need a way to set the text color, background color, and images
- texboxes need a way to check for which event happened
- create the renderer and texture structs properly, in their own files.
- make sure the renderer has the correct pixels every frame (buttons, etc) - probably CPU-heavy
- either make a smarter main loop and let the user define a Render() and an Update() function,
or make the user define the main loop himself. [SOLVED]
- make sure all the datatypes match (change int to wwBool where necessary)
- make the structs opaque, unless they have obvious fields (Rect, Point, etc.)
- make drawing somehow work with the existing controls [SOLVED I THINK - MORE TESTS]
- make standard library for drawing (circles, rectangles, lines, etc)
- make a setFPS function instead of the whole timer thing
- make sure the headers included are only the ones needed and nothing more
- don't include the windows header for the user (unsolvable, at least the macros for mouse and keys 
are needed, although they won't change with future versions of windows, hardcoding is bad practice,
consider the risks and rewards if that is possible)
- ideally make main() look standard instead of WINMAIN(...)
- printf to console (too much to ask??)
- make sure all the strings are malloced instead of ptr->text = text
- make a batch file similar to a makefile that compiles only the changed files
- make a shared library so test files can be compiled without recompiling the library
- split headers and c files in different folders - they are too many already
- rearrange the ww.c file or split it in multiple files
- rename root to node, it's really annoying
- mouse input [SOLVED, needs more work]
- keyboard input [SOLVED, needs more work]
- add magic numbers to the pointers to make sure they aren't corrupted
- make error functions and a printError function similar to perror or getError function similar to SDL_GetError
- split the window and renderer struct and think what belongs where, meanwhile renderer is a member of window
- make it work windowless, to draw straight on the screen
- incorporate the BMP library into the project (optional, would be nice as it does nothing by itself)
- a lot of stuff to do
*****************************************8
- the idea is that WINAPI is inaccessible for beginners, and this library should make things easier. The main loop
is user written, but the event loop is taken care of by the library, with the user supplying callbacks if necessary
