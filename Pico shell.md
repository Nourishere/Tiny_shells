This is a simple implementation of a Pico-level shell that supports basic operations.
## Features
* Simple.
* Light.
## Withdraws
* Does not support i/o redirection.
* Does not support variable declarations and environment variables, yet!
* Does not have an autocomplete.
* Does not offer command suggestions.
* Does not support arguments, (i.e `bash script.sh`)
* Everything else!
------------------------------------------------------------------
## Building
* Use `gcc pico_shell.c` and run`a.out` for output or use `gcc pico_shell -o output`. Do not use arguments to the command.
## Example
* Running the shell with `./output` opens up a new shell prompt `$: `.
* Use it as your normal shell and compare! It is probably not the best!