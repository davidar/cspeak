#!/bin/sh

SOX_ARGS="-t raw -b 32 -e signed-integer -r 44100"

# play raw PCM output
make && python reciter.py $@ | ./reciter | play $SOX_ARGS -

# convert to Ogg Vorbis before playing
#make && python reciter.py $@ | ./reciter | sox $SOX_ARGS - daisy.ogg && play daisy.ogg
