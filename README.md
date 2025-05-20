# NewPopBIOS

Fork popBIOS for custom bios per game

# Usage

1. Copy `newpopbios.prx` to `ms0:/seplugins/` and add `ms0:/seplugins/newpopbios.prx 1` to `ms0:/seplugins/pops.txt`
   > change `ms0` to `ef0` if you are using a PSP Go.
2. Rename your bios to `bios.bin` and place it in the game directory.
   > example for SLPS03040 (game of Tenchu 2) `ms0:/PSP/GAME/SLPS03040/bios.bin`

# References

- [get execute module path](https://github.com/qwikrazor87/ps1doc/blob/master/src/main.c#L120)
- [psp plugin list](https://www.gamebrew.org/wiki/List_of_PSP_plugins)
- [file systems](https://www.psdevwiki.com/psp/Filesystem)
- [CFW API LIB NOTE](https://github.com/xan1242/PSPModBase?tab=readme-ov-file#pspdev-side-note)
