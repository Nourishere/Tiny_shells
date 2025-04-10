# README
This is a progressive implementation of a basic Linux shell.
## Pico-level shell
------------------------------------------------------------------
### Features
* Simple.
* Light.
* Supports four built-in commands (pwd, cd, echo, and exit).
### Withdraws
* Does not support i/o redirection.
* Does not support variable declarations and environment variables, yet!
* Does not have an autocomplete.
* Does not offer command suggestions.
* Does not support arguments, (i.e `bash script.sh`)
* Does not support jobs.
* Everything else!
------------------------------------------------------------------
### Building
* Navigate to the base directory.
* Run `gcc pico_shell/pico_shell.c builtins.c -o output` and run `output`. Do not use arguments to the command.
### Example
* Running the shell with `./output` opens up a new shell prompt `$: `.
* Use it as your normal shell and compare! It is probably not the best!
## Nano-level shell
------------------------------------------------------------------
* Based on the Pico-level shell, but enables for the definition of local shell variables and environment variables.
* Updates are based on this shell until a new tiny version is out!
### Building
* Navigate to the base directory.
* Run `gcc nano_shell/nano_shell.c builtins.c -o output` and run `output`. Do not use arguments to the command.
### Example
* Running the shell with `./output` opens up a new shell prompt `$: `.
* Try defining variables and using them in text substitution. Also try the new builtin `export` function to export variables to the environment.
