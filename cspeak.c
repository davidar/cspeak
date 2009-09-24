/* Copyright (C) 2009  David Roberts <d@vidr.cc>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include "cspeak.h"
#include "formants.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

const int FRAME_LENGTH = 15; /* 15ms */
const int SAMPLE_RATE = 44100; /* 44.1kHz */
const int FORMANT_SCALE = 50;

int sine(unsigned int phase, unsigned int amplitude) {
    /* sinusoidal wave */
    return amplitude * sin(2*M_PI * (double)phase/0x10000);
}

int rect(unsigned int phase, unsigned int amplitude) {
    /* sqaure wave */
    if(phase < 0x8000) return  amplitude;
    else               return -amplitude;
}

int saw(unsigned int phase, unsigned int amplitude) {
    /* (reverse) sawtooth wave */
    return amplitude - phase*amplitude/0x10000;
}

void putint(int x) {
    fwrite(&x, sizeof(int), 1, stdout);
}

double midi_freq(unsigned char m) {
    /* converts a MIDI note number to a frequency
       <http://en.wikipedia.org/wiki/MIDI_Tuning_Standard> */
    return 440 * pow(2, (double)(m-69)/12);
}

void synth(const symbol_t symbol, const unsigned int num_frames,
           const unsigned char midi_note) {
    /* Synthesize the given phoneme and output it to stdout as raw 32-bit
       signed PCM */
    const formant_t formant = formants[symbol];
    const unsigned int pitch = midi_freq(midi_note);
    
    int i, t;
    int pitch_period = SAMPLE_RATE/pitch;
    
    int *chunk = malloc(sizeof(int)*pitch_period);
    for(t = 0; t < pitch_period; t++)
        chunk[t] = saw(t*pitch, 0x1000) * (
                   sine(t*formant.f1*FORMANT_SCALE, formant.A1<<14)
                 + sine(t*formant.f2*FORMANT_SCALE, formant.A2<<14)
                 + rect(t*formant.f3*FORMANT_SCALE, formant.A3<<14) );
    
    for(i = 0; i < SAMPLE_RATE*num_frames*FRAME_LENGTH/1000/pitch_period; i++)
        for(t = 0; t < pitch_period; t++)
            putint(chunk[t] + (rand()>>6)*formant.noise);
}
