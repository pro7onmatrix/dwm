# dwm - dynamic window manager
My personal fork of the excellent [dwm](https://dwm.suckless.org) window
manager, including some patches and config changes.

## Requirements
* Tag symbols require [Nerd Fonts](https://github.com/ryanoasis/nerd-fonts) to be
    installed (default is Fira Code NerdFont)
* Volume controls require [pamixer](https://github.com/cdemoulins/pamixer)
* Music playback controls require [playerctl](https://github.com/altdesktop/playerctl)
* The Bitwarden shortcut requires [bitwarden-cli](https://github.com/bitwarden/cli) and
    [bitwarden-dmenu](https://github.com/andykais/bitwarden-dmenu) (and, obviously, a Bitwarden
    account)
* The screen lock shortcut requires [slock](https://tools.suckless.org/slock/)
* The poweroff command requires [dmenu](https://tools.suckless.org/dmenu/) with the
    [border](https://tools.suckless.org/dmenu/patches/border/) and
    [center](https://tools.suckless.org/dmenu/patches/border/) patches applied,
    as well as the `dmenu-poweroff` script from [my dotfiles](https://github.com/pro7onmatrix/dotfiles)

## Applied Patches
Patches applied in this build of dwm:
* [alwayscenter](https://dwm.suckless.org/patches/alwayscenter/) -- Always open floating
    windows in the center of the screen
* [centeredmaster](https://dwm.suckless.org/patches/centeredmaster/) -- Adds the
    `centeredmaster` and `centeredfloatingmaster` layouts
* [focusmaster](https://dwm.suckless.org/patches/focusmaster/) -- Adds a keyboard shortcut
    to focus the master window from anywhere in the stack
* [fullgaps](https://dwm.suckless.org/patches/fullgaps/) -- Gap support for those sweet
    [r/unixporn](https://www.reddit.com/r/unixporn/) pictures
* [fullscreen](https://dwm.suckless.org/patches/fullscreen/) -- Fullscreen mode (hides the bar)
* [movestack](https://dwm.suckless.org/patches/movestack/) -- Move windows up and down the stack
    using `Mod+Shift+j` and `Mod+Shift+k`
* [namedscratchpads](https://dwm.suckless.org/patches/namedscratchpads) -- Add support
    for named scratchpads which can be displayed and hidden with a single key combination,
    extremely useful for taking notes or, e.g., listening to music with
    [spotify-tui](https://github.com/Rigellute/spotify-tui)
* [statuscolors](https://dwm.suckless.org/patches/statuscolors/) -- Use different colors rather
    than empty or filled squares to display the status of tags

