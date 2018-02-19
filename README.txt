ICP - Game 2017
‾‾‾‾‾‾‾‾‾‾‾‾‾‾
Author: Svätopluk Hanzel (2017), 2BIT
Academic year: 2016/2017

Task: Create a Solitaire-like game in C++ and Qt with both graphical and command-line interface.

Notes:
    * Using Makefile
        * running `make` will generate binaries for both the GUI (hra2017), and the CLI (hra2017-cli) and
          generate documentation using Doxygen
        * running `make docs` will run doxygen generating documentation for the project
        * running `make run` will run `hra2017` and `hra2017-cli` simultaneously
        * compilation on Merlin school server should be done by running `make merlin`.
          this command will compile both the GUI and the CLI binaries using locations on Merlin

    * CLI version
        * example game: https://asciinema.org/a/3imwh855bz38s8tgbsmbfaxgb
        * available commands in the CLI can be shown issuing the `help` comand

    * GUI version
