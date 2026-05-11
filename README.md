# sysdll

sysdll is a 64-bit Windows system DLL that provides a small subset of the Windows API by directly invoking system calls. It is designed to operate without relying on the C runtime library (CRT) or the Windows API.

## Design

### Retrieving System Call Numbers
Every process has `ntdll.dll` loaded in its address space, so sysdll retrieves system call numbers by parsing the export table of `ntdll.dll` at runtime. By using pattern matching, sysdll identifies the system call stubs in `ntdll.dll` and extracts the corresponding system call numbers.

### System Call Invocation
The system call stubs in `ntdll.dll` follow a specific structure, where the system call number is moved into the `eax` register, and the `syscall` instruction is used to transition to kernel mode. sysdll replicates this behavior by implementing its own assembly code that mimics the structure of the stubs in `ntdll.dll`, allowing it to invoke system calls directly.

## Build Instructions
To build sysdll, you can use the provided Makefile. The Makefile defines targets for building both the debug version (CRT) and the release dll version (no-CRT) of sysdll.

- To build the debug version (CRT), run:
  ```
  make crt
  ```
- To build the release dll version (no-CRT), run:
  ```
  make nocrt
  ```

After building, you can find the output DLLs in the `out` directory. The debug version will be located in `out/crt`, while the release dll version will be located in `out/nocrt`.

## License
sysdll is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information.
