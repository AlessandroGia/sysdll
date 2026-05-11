# sysdll

sysdll is a 64-bit Windows system DLL that provides a small subset of the Windows API by directly invoking system calls. It is designed to operate without relying on the C runtime library (CRT) or the Windows API.

## Design

### Retrieving System Call Numbers
Every process has `ntdll.dll` loaded in its address space, so sysdll retrieves system call numbers by parsing the export table of `ntdll.dll` at runtime. By using pattern matching, sysdll identifies the system call stubs in `ntdll.dll` and extracts the corresponding system call numbers.

### System Call Invocation
The system call stubs in `ntdll.dll` follow a specific structure, where the system call number is moved into the `eax` register, and the `syscall` instruction is used to transition to kernel mode. sysdll replicates this behavior by implementing its own assembly code that mimics the structure of the stubs in `ntdll.dll`, allowing it to invoke system calls directly.

## Build Instructions
To build sysdll, you can use the provided Makefile. The Makefile defines targets for building both the `exe` debug version (CRT) and the `dll` release version (no-CRT) of sysdll.

- To build the debug version (CRT), run:
  ```
  make debug
  ```
- To build the release dll version (no-CRT), run:
  ```
  make build
  ```

After building, you can find the output DLL in the `out\release` directory. The debug version will be located in `out\debug`.

## License
sysdll is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information.
