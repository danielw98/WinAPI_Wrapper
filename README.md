# WinAPI Wrapper

A user-friendly WinAPI Wrapper designed to simplify the development of Windows desktop applications. This library aims to make the complex WinAPI more accessible to beginners, providing a more intuitive way to create GUI applications in Windows, while also being as close to the kernel as possible.

## Features

- Simplified creation and management of windows and widgets.
- Error handling for robust application development.
- Structured organization for rendering and texture management.
- Enhanced event handling, allowing custom callbacks for user interactions.


## Demo Features

- `main.c`:
![Lexer Output](https://github.com/danielw98/Lexer/blob/main/Lexer.png?raw=true)

- `main2.c`:
![Lexer Output](https://github.com/danielw98/Lexer/blob/main/Lexer.png?raw=true)

- `main3.c`:
![Lexer Output](https://github.com/danielw98/Lexer/blob/main/Lexer.png?raw=true)

## Getting Started

Clone the repository to start using the WinAPI Wrapper in your project:

```bash
git clone https://github.com/DanielW98/WinAPI_Wrapper.git
cd WinAPI_Wrapper
Makefile.bat
```

Now that the DLL has been created, you can build your own applications using WinAPI_Wrapper:

```bash
gcc [-o <executable_name>]  <your_file.c>  -L. -lww
```

## Dive Into the Code

Explore the `widget.c`, `label.c`, `list.c`, and `menu.c` files for insights into widget management and event handling. The `renderer.c` and `listbox.c` files demonstrate the rendering and list box functionalities, respectively. The `ww.c` file is the core of the application.

There are a few example `main.c` files that showcase the capabilities of the library at the moment and serve at the same time as unit tests.

## Errors and TODOs

Various errors have been addressed, including crash fixes and function enhancements.
Ongoing improvements include error code integration, input validation, and structural refinements like opaque structs and better memory management.

## Contributing

Contributions are encouraged! If you'd like to improve the WinAPI Wrapper or suggest new features, please fork the repository and submit a pull request.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.
