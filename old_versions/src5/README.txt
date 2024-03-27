- do something about that ww.c global variable, should be able to pass it as a param (optional, for fun)
- WM_COMMAND should know if it's button window or whatever command - i could use the whole range instead of 0 1000 2000 ... 
- buttons need a way to set the text color, background color, and images
- texboxes need a way to check for which event happened
- create the renderer and texture structs properly, in their own files.
- make sure the renderer has the correct pixels every frame (buttons, etc) - probably CPU-heavy
- either make a smarter main loop and let the user define a Render() and an Update() function,
or make the user define the main loop himself.
- make sure all the datatypes match 
- make the structs opaque, unless they have obvious fields (Rect, Point, etc.)
- make drawing somehow work with the existing controls
- make standard library for drawing (circles, rectangles, lines, etc)
- make a setFPS function
- make sure the headers included are only the ones needed and nothing more
- don't include the windows header for the user
- ideally make main() look standard instead of WINMAIN(...)
- printf to console (too much to ask??)
- make sure all the strings are malloced instead of ptr->text = text
- make a batch file similar to a makefile that compiles only the changed files
- make a shared library so test files can be compiled without recompiling the library
- split headers and c files in different folders - they are too many already
- rearrange the ww.c file or split it in multiple files
- rename root to node, it's really annoying
- mouse input
- keyboard input

- make it work windowless, to draw straight on the screen

- a lot of stuff to do