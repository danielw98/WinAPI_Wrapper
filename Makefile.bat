@echo off
gcc -c button.c checkbox.c draw.c keyboard.c textbox.c label.c listbox.c list.c utils.c menu.c mouse.c renderer.c timer.c widget.c window.c ww.c 

gcc -shared -o ww.dll button.o checkbox.o draw.o keyboard.o textbox.o label.o listbox.o list.o utils.o menu.o mouse.o renderer.o timer.o widget.o window.o ww.o -mwindows -lcomctl32 -lgdi32

del button.o checkbox.o draw.o keyboard.o textbox.o label.o listbox.o list.o utils.o menu.o mouse.o renderer.o timer.o widget.o window.o ww.o

@echo on
gcc -o main  main.c  -L. -lww
gcc -o main2 main2.c -L. -lww
gcc -o main3 main3.c -L. -lww