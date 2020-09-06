Derived from [Marlin Coding Standards](http://marlinfw.org/docs/development/coding_standards.html)  

# Coding Style

To use the Code Formatter in Eclipse press `Ctrl + Shift + F`.  
To configure the Code Formatter in Eclipse navigate to `Windows -> Preferences -> C/C++ -> Code Style > Formatter` and choose the `BSD/Allman` profile. 
You can modify the profile by changing the `Tab policy` to `Spaces Only`.

## Indentation
Indentation is important for readability and maintainability of code, and provides guidance for naïve code editors (e.g., TextMate, Sublime, et. al.) to properly fold code blocks by level.  
*  Entab lines with `4` spaces and don’t use tabs. Set your editor to use 4 Spaces! Tabs will bite you in the end.
*  All block elements should increase the indentation level:

```
void myFunction() 
{
    if (myCondition == 0) {
#ifdef PETER_PARKER
      slingWeb(100);
#else
      findPhoneBooth();
#endif
    }
}
```

## Spacing
*  One space after control keywords:
`if (…)`, `while (…)`, `do {…} while(…)`, `switch (…)` etc.
*  No space is needed for `sizeof()` and other “function-like” language features.
*  No space between a function and its arguments: `val = myFunction(…);`
*  No spaces around `.` or `->` operators: `the_place = state->parks[echo];`
*  No space between a cast and its target: `old_state = (int)state;`
*  Use one space around (on each side of) most binary and ternary operators:  
`myVar = aVar + bVar * cVar; `  
`myVal = (a * b + b * c);`  

## Trailing Whitespace
Don’t leave trailing whitespace at the ends of lines. Some editors will auto-indent new lines, leaving extra whitespace behind on blank lines. As a result, you end up with lines containing trailing whitespace.

Git can warn you about patches that introduce trailing whitespace, and optionally strip the trailing whitespace for you; however, if applying a series of patches, this may make later patches in the series fail by changing their context lines.

## Commenting
Comments are good, but avoid over-commenting. Never try to explain how your code works in a comment: it’s much better to write the code so that the working is obvious, and it’s a waste of time to explain badly written code.

Generally, you want your comments to explain what your code does, not how. Keep comments inside a function body short. If a function is so complex that you need to separately comment parts of it, consider splitting it up into simpler units. Make small comments to note or warn about something particularly clever (or ugly), but avoid excess. Reserve detailed comments for the head of the function, explaining what it does, and possibly why it does it.

Use Doxygen-style comments for functions, classes, and other defined entities, and concentrate documentation in the .h files.
```
/**
 * This is the preferred style for multi-line comments 
 *
 * This mimics Doxygen/HeaderDoc style, and once keywords are added
 * we'll be able to auto-generate code documentation and provide more
 * complete development guidance.
 */
```
To comment a single line of code use this line:
```
rtems_signal_catch( signal_handler, RTEMS_DEFAULT_MODES );  /* register signal catcher (handler) */
```
# Names and Symbols
## Filenames
Filenames for Marlin code should favor lowercase_with_underscores.ext format. Contributed code will follow its own standard.

*  use `.cpp` for C++ sources
*  use `.c` for C only sources
*  use `.h` for headers of all types

## Directories
*  Lowercase names.
*  A hierarchical layout:

```
+ include/
|-- all .h files 
+ lib/
|-- all thirdparty library files (.a files)
+ obj/
|-- all .o files 
+ src/
|-- all .c files 
+ bin/
|-- all the executable files
+ Makefile
```
Or a directory structure managed by used IDE.

## Capitalization
For variables, data members, functions, and methods use lowercase_with_underscores. Use camelCase names only when class names and methods already uses that format. Marlin classes may use MyClassName format or my_class_name. Core classes tend to use camel-case, with general-purpose classes using underscore format.

*  `my_function_name(int in_integer, float in_float=0.0)`
*  `MyClass`, `classMethod`, `classData`
*  `local_variable`, `global_variable`, `const_value`
*  `MACRO_NAME` – anything created with `#define`
*  `EnumeratedType`

## Libraries
Whenever possible, use the functions supplied by avr-libc or Arduino bundled libraries. Any libraries required to compile Marlin should be included in the package so that they are guaranteed to be compatible versions.

# Language Features
Marlin is written in C/C++ and needs be able to compile with the supplied `Makefile` or an up-to-date version of Arduino. With Marlin 1.1 we now support building with Arduino IDE, Teensyduino, PlatformIO, `make`, and `cmake`.

*  Do not use extended C++ features like:
  *  Exceptions (throw / catch)
  *  Virtual functions / classes
  *  Standard Template Library (STL)
*  Do use modern C++11 features like:
  *  `constexpr` values and functions.
  *  `static_assert(test,"error")` to sanity-check `float` and `constexpr` values.

## Primitive Types
*  Favor bit-size types like `uint8_t` and `int32_t` over `short`, `int`, and `long`. This helps to keep behavior consistent across architectures.
*  AVR recasts `double` as `float`, so both are 32 bits long. Favor `float` and avoid `double` unless the extra precision is needed on a 32-bit architecture.

## Memory Usage
*  Dynamic allocation (`malloc()`, `free()`, `new`, `delete`) is **verboten**!
*  Avoid unconstrained recursion so the stack won’t explode.
*  Avoid using globals and `static` locals because SRAM is a precious resource.
*  Use `PSTR` and `PROGMEM` macros to keep strings in Program Memory.

## Minimize Repetition
When possible, use macros, small functions, and other clever techniques to avoid redundancy. For example, instead of this…
```
#if ENABLED(FEATURE_ONE)
  const char blue = '1';
#else
  const char blue = '0';
#endif
```
…do this…
```
const char blue =
  #if ENABLED(FEATURE_ONE)
    '1'
  #else
    '0'
  #endif
;
```
## Avoid Expensive Code
*  Pre-calculate instead of calculating on the fly, when possible.
*  Use multiplication (of the reciprocal) instead of division, when possible.
*  Most code doesn’t need to be optimized for speed, so favor smaller code.

## Best-Practices for #include
Follow best practices for `#include`.
*  Only include the headers needed to provide the definitions required by the current source file. This helps provide an accurate view of dependencies.
*  Include `Marlin.h` only when you need its externs. Don’t include `Marlin.h` when just `MarlinConfig.h` (or `MarlinConfigPre.h`) will do.
*  Included headers should be arranged in the following order:
  *  `MarlinConfig.h` (or `MarlinConfigPre.h`), if configuration values are needed for `#if` or other uses.
  *  After the main `#if` condition, include the file’s own corresponding header.
  *  Next, arrange project headers to prevent hiding broken dependencies. For example, if `grape.h` depends on `orange.h`, try to include `grape.h` before `orange.h` so that if `grape.h` fails to include `orange.h` an error will be thrown.
  *  Last come system and library headers, such as `<Arduino.h>`, `<inttypes.h>`, and `<u8glib.h>`.

# Marlin-specific Conventions
## Preprocessor directives
*  Use `#define` instead of `const` for configurable values
*  Don’t use `#if` / `#endif` for commenting-out unused, old or broken code. We have a git repository! If it’s obsolete, delete it.
*  Use `#if ENABLED(FEATURE_NAME)` / `#endif` to compile enabled features. (Using these macros allows features to be set externally.)
*  Use `#if DISABLED(FEATURE_NAME)` / `#endif` to compile disabled features. (Using these macros allows features to be set externally.)
*  Use `#define` macros to avoid repeating boilerplate code.  
Consider both readability and maintainability.
*  Label `#endif` with the opening `#if` condition(s) if the block is over ~15 lines. Make the label compact. For example, `#endif // SDSUPPORT || ULTRALCD`.