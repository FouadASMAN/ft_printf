# `ft_printf` Master Checklist & Evaluation Guide

*This document serves as the complete technical roadmap, theoretical breakdown, and peer-evaluation prep for the `ft_printf` project in the 42 Common Core curriculum.*

---

## 1. Project Overview & Mandatory Specifiers

The objective of `ft_printf` is to recreate the standard C library `printf` function without buffer management (unless taking on bonus flags), handling dynamic formatting via variadic functions (`<stdarg.h>`).

### Mandatory Conversion Specifiers
| Specifier | Argument Type | Expected Output Format | Critical Edge Cases / Traps |
| :--- | :--- | :--- | :--- |
| `%c` | `int` (promoted) | Single character | Printing `\0` (must count as 1 char printed). |
| `%s` | `char *` | Null-terminated string | `NULL` pointer input $\rightarrow$ Output `(null)` (or `(null)` prefix depending on OS/libc standard). |
| `%p` | `void *` | Hexadecimal address with `0x` prefix | `NULL` address input $\rightarrow$ Output `(nil)` or `0x0`. |
| `%d` | `int` | Signed decimal integer | `INT_MIN` (`-2147483648`). |
| `%i` | `int` | Signed integer (base 10) | `INT_MIN` (`-2147483648`). |
| `%u` | `unsigned int` | Unsigned decimal integer | `UINT_MAX` (`4294967295`). |
| `%x` | `unsigned int` | Lowercase Hexadecimal (base 16) | Passing `0` $\rightarrow$ output `0` (not empty). |
| `%X` | `unsigned int` | Uppercase Hexadecimal (base 16) | Passing `0` $\rightarrow$ output `0`. |
| `%%` | N/A | Literal `%` character | No `va_arg` call required. |

---

## 2. Variadic Functions Breakdown (`<stdarg.h>`)

### Core Mechanics & Memory Architecture
Variadic functions pass arguments beyond the last fixed parameter on the **Stack**. 
`va_list` acts as a stateful memory pointer tracking where the next parameter sits.

```
High Memory
  +-----------------------+
  | Argument n            |  <-- Traversed by calling va_arg(args, type)
  +-----------------------+
  | Argument 1            |  <-- va_start(args, format) sets cursor here
  +-----------------------+
  | Format string pointer |  <-- Last fixed parameter
  +-----------------------+
Low Memory (Stack Pointer)
```

### Macro Reference
* **`va_list args;`**  
  * *Type:* Pointer/Cursor structure allocated on the Stack.
  * *Role:* Holds state required to step through variable arguments.
* **`va_start(args, format);`**  
  * *Role:* Takes the address of the last fixed parameter (`format`), calculates its stack offset, and initializes `args` to point to the first variadic argument.
* **`va_arg(args, Type);`**  
  * *Role:* Reads the value sitting at the current stack cursor cast to `Type`, and advances the `args` pointer to the start of the next argument.
* **`va_end(args);`**  
  * *Role:* Cleans up `va_list` state. Mandatory to avoid dangling pointers or undefined behavior across system ABIs.

### Default Argument Promotions (Evaluator Favorite)
When passing arguments through `...`, C automatically promotes smaller data types:
* `char`, `short`, `signed char` $\rightarrow$ Promoted to **`int`** (or `unsigned int`).
* `float` $\rightarrow$ Promoted to **`double`**.

> **Evaluation Defense Tip:** If an evaluator asks why `va_arg(args, char)` is wrong for `%c`, answer: *"Because under default argument promotions, any `char` passed through variadic arguments is automatically promoted to an `int` on the stack."*

---

## 3. Recommended Project Architecture

Keep your code modular and 42 Norm-compliant by separating the dispatcher from specific type formatters:

```
ft_printf/
├── Makefile
├── includes/
│   └── ft_printf.h
└── srcs/
    ├── ft_printf.c         # Main function & format string scanner loop
    ├── ft_dispatch.c       # Conversion specifier router (%c, %s, %d, etc.)
    ├── ft_print_chars.c    # Character & String handlers (%c, %s, %%)
    ├── ft_print_numbers.c  # Signed & Unsigned decimal handlers (%d, %i, %u)
    └── ft_print_hex.c      # Hexadecimal & Pointer handlers (%x, %X, %p)
```

---

## 4. Execution Flow Checklist

- [ ] **Step 1: Header Guard & Prototype Setup**
  - Prototype matches `int ft_printf(const char *format, ...);`.
  - Header includes `<stdarg.h>` and `<unistd.h>`.
- [ ] **Step 2: Initialization**
  - Declare `va_list args;` and running count accumulator `int count = 0;`.
  - Validate `format` string input.
  - Call `va_start(args, format);`.
- [ ] **Step 3: Linear Parsing Loop**
  - Loop through `format[i]`:
    - If `format[i] != '%'`: Print character directly via `write`, increment `count`.
    - If `format[i] == '%'`: Advance index `i++`, route `format[i]` to dispatcher.
- [ ] **Step 4: Subroutine Execution & Return Value Accumulation**
  - Dispatcher calls specific printer function based on specifier.
  - Each sub-function writes output and returns bytes printed (or `-1` on error).
  - Add printed bytes to `count`.
- [ ] **Step 5: Teardown & Return**
  - Call `va_end(args);`.
  - Return total `count`.

---

## 5. Peer Evaluation Checklist (Defense Prep)

### Question 1: Memory & Variadic Architecture
* **Q:** *Where do variadic arguments sit in memory, and how does `va_start` find them?*
* **A:** They sit contiguously on the Stack above the function stack frame. `va_start` takes the memory address of the last named parameter, computes its memory boundary, and initializes the pointer to the address immediately following it.

### Question 2: Return Value & Write Error Propagation
* **Q:** *What happens if a `write` system call fails halfway through execution?*
* **A:** All print routines must monitor the return value of `write`. If `write` returns `-1`, error status should propagate up, `va_end` must be called to prevent resource leaks, and `ft_printf` must return `-1`.

### Question 3: Extreme Numeric Boundaries
* **Q:** *How does your `%d` or `%i` handler manage `INT_MIN` (`-2147483648`)?*
* **A:** `INT_MIN` cannot be made positive by multiplying by `-1` within a standard signed 32-bit `int` because `INT_MAX` is `2147483647` (causing signed integer overflow). It must be handled using unsigned data types, explicit long casting, or direct string branch checks.

### Question 4: Pointers on Different Systems
* **Q:** *Why does pointer formatting (`%p`) require an `unsigned long long` or `uintptr_t` cast?*
* **A:** Memory address width depends on system architecture (32-bit vs 64-bit). Casting the pointer to `unsigned long long` ensures the address value fits into an integer large enough to hold any valid address without truncation before base-16 conversion.

---

## 6. Testing Strategy

Verify your implementation against standard `printf` behavior:

1. **Basic strings & characters:**  
   `ft_printf("Char: %c, String: %s\n", 'A', "42 Common Core");`
2. **Null string pointer handling:**  
   `ft_printf("Null string: %s\n", (char *)NULL);`
3. **Pointer addressing:**  
   `int x = 42; ft_printf("Pointer: %p, Null Pointer: %p\n", &x, NULL);`
4. **Boundary Integers:**  
   `ft_printf("INT_MIN: %d, INT_MAX: %i, UINT_MAX: %u\n", -2147483648, 2147483647, 4294967295U);`
5. **Hexadecimal zero and limits:**  
   `ft_printf("Zero Hex: %x, Max Hex: %X\n", 0, 4294967295U);`
6. **Return value verification:**  
   Compare `int ret1 = printf(...)` vs `int ret2 = ft_printf(...)`.