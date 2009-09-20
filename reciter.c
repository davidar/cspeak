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

#include <stdio.h>

#include "cspeak.h"

/* Recite SAMPA phonemes read from stdin. */

const int FRAMES_CONSONANT = 3;
const int FRAMES_VOWEL = 10;
const int PITCH = 40;

int peekchar(void) {
    int c = getchar();
    if(c != EOF) ungetc(c, stdin);
    return c;
}

int main() {
    char c;
    while((c = getchar()) != EOF)
        switch(c) {
        case ' ': case '\n': synth(_NUL,FRAMES_CONSONANT,PITCH); break;
        case 'p': synth(_Pa,FRAMES_CONSONANT/3,PITCH);
                  synth(_Pb,FRAMES_CONSONANT/3,PITCH);
                  synth(_Pc,FRAMES_CONSONANT/3,PITCH);
                  break;
        case 'b': synth(_Ba,FRAMES_CONSONANT/3,PITCH);
                  synth(_Bb,FRAMES_CONSONANT/3,PITCH);
                  synth(_Bc,FRAMES_CONSONANT/3,PITCH);
                  break;
        case 't': if(peekchar() == 'S') {
                      synth(_CHa,FRAMES_CONSONANT/2,PITCH);
                      synth(_CHb,FRAMES_CONSONANT/2,PITCH);
                      getchar();
                  } else {
                      synth(_Ta,FRAMES_CONSONANT/3,PITCH);
                      synth(_Tb,FRAMES_CONSONANT/3,PITCH);
                      synth(_Tc,FRAMES_CONSONANT/3,PITCH);
                  }
                  break;
        case 'd': if(peekchar() == 'Z') {
                      synth(_Ja,FRAMES_CONSONANT/4,PITCH);
                      synth(_Jb,FRAMES_CONSONANT/4,PITCH);
                      synth(_Jc,FRAMES_CONSONANT/4,PITCH);
                      synth(_Jd,FRAMES_CONSONANT/4,PITCH);
                      getchar();
                  } else {
                      synth(_Da,FRAMES_CONSONANT/3,PITCH);
                      synth(_Db,FRAMES_CONSONANT/3,PITCH);
                      synth(_Dc,FRAMES_CONSONANT/3,PITCH);
                  }
                  break;
        case 'k': synth(_Ka,FRAMES_CONSONANT/3,PITCH);
                  synth(_Kb,FRAMES_CONSONANT/3,PITCH);
                  synth(_Kc,FRAMES_CONSONANT/3,PITCH);
                  break;
        case 'g': synth(_Ga,FRAMES_CONSONANT/3,PITCH);
                  synth(_Gb,FRAMES_CONSONANT/3,PITCH);
                  synth(_Gc,FRAMES_CONSONANT/3,PITCH);
                  break;
        case 'f': synth(_F,FRAMES_CONSONANT,PITCH); break;
        case 'v': synth(_V,FRAMES_CONSONANT,PITCH); break;
        case 'T': synth(_TH,FRAMES_CONSONANT,PITCH); break;
        case 'D': synth(_DH,FRAMES_CONSONANT,PITCH); break;
        case 's': synth(_S,FRAMES_CONSONANT,PITCH); break;
        case 'z': synth(_Z,FRAMES_CONSONANT,PITCH); break;
        case 'S': synth(_SH,FRAMES_CONSONANT,PITCH); break;
        case 'Z': synth(_ZH,FRAMES_CONSONANT,PITCH); break;
        case 'h': synth(__H,FRAMES_CONSONANT,PITCH); break;
        case 'm': synth(_M,FRAMES_CONSONANT,PITCH); break;
        case 'n': synth(_N,FRAMES_CONSONANT,PITCH); break;
        case 'N': synth(_NX,FRAMES_CONSONANT,PITCH); break;
        case 'R': synth(_RX,FRAMES_CONSONANT,PITCH); break;
        case 'r': synth(_R,FRAMES_CONSONANT,PITCH); break;
        case 'l': synth(_L,FRAMES_CONSONANT,PITCH); break;
        case 'w': synth(_W,FRAMES_CONSONANT,PITCH); break;
        case 'j': synth(_Y,FRAMES_CONSONANT,PITCH); break;
        case 'I': synth(_IH,FRAMES_VOWEL,PITCH); break;
        case 'e': if(peekchar() == 'I') {
                      synth(_EY,FRAMES_VOWEL,PITCH);
                      getchar();
                  } else {
                      synth(_EH,FRAMES_VOWEL,PITCH);
                  }
                  break;
        case '{': synth(_AE,FRAMES_VOWEL,PITCH); break;
        case 'Q': synth(_AA,FRAMES_VOWEL,PITCH); break;
        case 'V': synth(_AH,FRAMES_VOWEL,PITCH); break;
        case 'U': synth(_UH,FRAMES_VOWEL,PITCH); break;
        case '@': if(peekchar() == 'U') {
                      synth(_OW,FRAMES_VOWEL,PITCH);
                      getchar();
                  } else {
                      synth(_ER,FRAMES_VOWEL,PITCH);
                  }
                  break;
        case 'i': synth(_IY,FRAMES_VOWEL,PITCH); break;
        case 'a': if(peekchar() == 'I') {
                      synth(_AY,FRAMES_VOWEL,PITCH);
                      getchar();
                  } else if(peekchar() == 'U') {
                      synth(_AW,FRAMES_VOWEL,PITCH);
                      getchar();
                  }
                  break;
        case 'O': if(peekchar() == 'I') {
                      synth(_OY,FRAMES_VOWEL,PITCH);
                      getchar();
                  } else {
                      synth(_AO,FRAMES_VOWEL,PITCH); break;
                  }
                  break;
        case 'u': synth(_UX,FRAMES_VOWEL,PITCH); break;
        case '3': synth(_ER,FRAMES_VOWEL,PITCH); break;
        case 'A': synth(_AH,FRAMES_VOWEL,PITCH); break;
        default: fprintf(stderr, "Unrecognised character: '%c'\n", c); break;
        }
    return 0;
}
