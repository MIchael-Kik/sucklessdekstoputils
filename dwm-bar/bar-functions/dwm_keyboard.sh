#!/bin/sh

# A dwm_bar function that displays the current keyboard layout
# Joe Standring <git@joestandring.com>
# GNU GPLv3

# Dependencies: xorg-setxkbmap
PREV="us"

dwm_keyboard () {
    
    printf "%s" "$SEP1"
    CURRENT_METHOD=$(fcitx-remote)

    case $CURRENT_METHOD in
        1) 
            printf "  %s" "us"
            $PREV="us" ;;
        2) 
            printf "  %s" "jp"
            $PREV="jp" ;;
        *) printf "  %s" "$PREV" ;;
    esac
    printf "%s\n" "$SEP2"
}

dwm_keyboard
