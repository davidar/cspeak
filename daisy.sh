#!/bin/sh

SOX_ARGS="-t raw -b 32 -e signed-integer -r 44100"

# play raw PCM output
make && ./daisy | play $SOX_ARGS -

# convert to Ogg Vorbis before playing
#make && ./daisy | sox $SOX_ARGS - daisy.ogg && play daisy.ogg
