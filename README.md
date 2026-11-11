*This project has been created as part of the 42 curriculum by foasman.*

# ft_printf

## Description

`ft_printf` is a re-implementation of the C library function `printf()`.
The goal of the project is to learn how **variadic functions** work in C
(`stdarg.h`) and to build a small, well-structured and extensible library.

The prototype is:

```c
int ft_printf(const char *format, ...);
```

It writes the formatted output to the standard output with `write()` and
returns the number of characters printed, or `-1` if a `write()` failed.
As required by the subject, the buffer management of the original `printf()`
is **not** implemented: every piece of output is written immediately.

### Supported conversions

| Conversion | Prints |
|------------|--------|
| `%c` | a single character |
| `%s` | a string (`(null)` if the pointer is `NULL`) |
| `%p` | a pointer in hexadecimal, prefixed by `0x` (`(nil)` if `NULL`) |
| `%d` | a signed decimal number |
| `%i` | a signed integer in base 10 |
| `%u` | an unsigned decimal number |
| `%x` | an unsigned number in lowercase hexadecimal |
| `%X` | an unsigned number in uppercase hexadecimal |
| `%%` | a percent sign |

The project produces a static library, `libftprintf.a`, built with `ar`.

## Instructions

### Compilation

```sh
make          # builds libftprintf.a at the root of the repository
make clean    # removes the object files
make fclean   # removes the object files and libftprintf.a
make re       # fclean, then all
```

The Makefile uses `cc -Wall -Wextra -Werror`, does not relink when nothing
changed, and creates the library with `ar rcs`.

### Usage

Include the header and link the library:

```c
#include "ft_printf.h"

int main(void)
{
	int	len;

	len = ft_printf("Hello %s, you are %d years old (%x)\n", "42", 21, 255);
	ft_printf("%d characters printed\n", len);
	return (0);
}
```

```sh
cc -Wall -Wextra -Werror main.c libftprintf.a -o test
./test
```

### Files

| File | Role |
|------|------|
| `ft_printf.h` | prototypes |
| `ft_printf.c` | entry point: `va_start`, `va_end`, returns the total |
| `ft_print_format.c` | walks the format string |
| `ft_print_select.c` | chooses the printer for each conversion letter |
| `ft_print_char.c` | prints one character (`%c`, `%%`) |
| `ft_print_str.c` | prints a string (`%s`) |
| `ft_print_nbr.c` | prints a signed number (`%d`, `%i`) |
| `ft_print_unsigned.c` | prints an unsigned number (`%u`) |
| `ft_print_hex.c` | prints a number in base 16 (`%x`, `%X`, digits of `%p`) |
| `ft_print_ptr.c` | prints a pointer (`%p`) |

## Algorithm and data structures

### Structure in three layers

1. **`ft_printf`** owns the `va_list`. It calls `va_start`, hands the work to
   `ft_print_format`, then calls `va_end` and returns the result. Because the
   early failure return happens inside `ft_print_format`, `va_end` is always
   reached.
2. **`ft_print_format`** walks the format string with an index. A normal
   character is printed directly. After a `%`, it checks that the next
   character exists (a lone `%` at the end returns `-1`, so the loop never
   reads past the `'\0'`), then asks for the conversion to be handled and
   skips both characters (`%` and the letter). `%%` is handled there and
   consumes no argument.
3. **`ft_print_select`** receives the conversion letter, reads the argument
   with the right type, and calls the matching printer.

### One shared cursor

The `va_list` is declared once, in `ft_printf`, and passed down as a
`va_list *`. Every function that reads an argument uses `va_arg(*ap, type)`,
so all of them advance the **same** cursor. Passing a `va_list` by value
would leave the caller's cursor indeterminate according to the C standard.

### Reading the right type

`va_arg` must use the type that was really passed:

- `%c` reads an `int` (a `char` is promoted to `int` through `...`).
- `%d` and `%i` read an `int`.
- `%u`, `%x` and `%X` read an `unsigned int`, so negative values wrap to the
  expected unsigned value (`-1` prints `ffffffff` for `%x`).
- `%s` reads a `char *` and `%p` reads a `void *`.

### Return values and errors

Every printer returns the number of characters it printed, or `-1` if a
`write()` failed. The callers check for `-1` **before** adding to the total,
so a failure is never hidden inside a sum, and the loop stops at the first
failure. A result of `0` is valid (for example `%s` with an empty string) and
is not an error.

### Dispatch

The Norm forbids `switch`, so the dispatcher is an `if / else if` chain. It
is simple to read and to extend: a new conversion is one new branch and one
new printer, and every printer shares the same contract (count or `-1`).

### Printing numbers

For decimal and hexadecimal output, the digits of a number are extracted from
the last one to the first (`n % base`, then `n / base`) and stored in a small
local array, then printed in reverse order. This avoids recursion and does
not need `malloc`. Buffer sizes are chosen from the maximum value each
function can receive:

- `ft_print_nbr` converts the `int` to a `long` **before** negating, so
  `INT_MIN` does not overflow. The minus sign is printed once, then the
  digits.
- `ft_print_unsigned` handles up to `4294967295` (10 digits).
- `ft_print_hex` takes an `unsigned long` and the digit set as a parameter
  (`"0123456789abcdef"` or `"0123456789ABCDEF"`). One function therefore
  serves `%x`, `%X` and `%p`, and a pointer is never truncated. A 64-bit
  value needs at most 16 hex digits.
- The value `0` is a special case in each of them, because the digit loop
  would otherwise print nothing.

### Special cases

- `%s` with `NULL` prints `(null)`; the check lives in `ft_print_str`.
- `%p` with `NULL` prints `(nil)`; the check lives in `ft_print_ptr`.
  These two texts match the behavior of the original `printf` on glibc.
- `ft_print_ptr` prints `0x` and the digits in two separate statements, so
  the order is guaranteed and each result is checked.
- A `NULL` format or an unknown conversion returns `-1`.

## Resources

### References

- `man 3 stdarg` (`va_start`, `va_arg`, `va_copy`, `va_end`)
- `man 2 write`
- `man 3 printf`
- `man 1 ar`
- The 42 Norm and the subject of the project
- GeeksforGeeks and YouTube

### Use of AI

I used AI as an additional learning resource when I encountered difficulties that I could not resolve independently or with the help of my peers.

All the C code of the project was written by me. I compared my implementation
with the original `printf()` on both the output and the return value.
