#!/bin/bash

function cmusPlayPause
{
    STATUS=$(cmus-remote -Q | grep -a '^status' | awk '{gsub("status ", "");print}')

    if [ "$STATUS" = "playing" ]; then
        $(cmus-remote --pause)
    else
        $(cmus-remote --play)
    fi
}

case $1 in
    play) cmusPlayPause;;
    next) $(cmus-remote --next);;
    prev) $(cmus-remote --prev);;
esac
