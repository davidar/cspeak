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

const int FRAMES_CONSONANT = 6;
const int FRAMES_VOWEL = 8;
const int PITCH = 50;

#define CONSONANT if(phase==-1 || phase%2==1) phase++;
#define VOWEL if(phase==-1) phase = 1; \
              else if(phase%2==0) phase++; \
              if(phase>2) pitch = PITCH-2;

int peekchar(void) {
    int c = getchar();
    if(c != EOF) ungetc(c, stdin);
    return c;
}

int main() {
    char c;
    int phase = -1;
    int pitch = PITCH;
    
    while((c = getchar()) != EOF)
        switch(c) {
        case ' ': case '\n':
            synth(_NUL,FRAMES_VOWEL,pitch);
            phase = -1;
            pitch = PITCH;
            break;
        
        case 't': CONSONANT
                  if(peekchar() == 'S') {
                      synth(_CHa,FRAMES_CONSONANT,pitch);
                      synth(_CHb,FRAMES_CONSONANT,pitch);
                      getchar();
                  } else {
                      synth(_Ta,FRAMES_CONSONANT/3,pitch);
                      synth(_Tb,FRAMES_CONSONANT/3,pitch);
                      synth(_Tc,FRAMES_CONSONANT/3,pitch);
                  }
                  break;
        case 'd': CONSONANT
                  if(peekchar() == 'Z') {
                      synth(_Ja,FRAMES_CONSONANT/4,pitch);
                      synth(_Jb,FRAMES_CONSONANT/4,pitch);
                      synth(_Jc,FRAMES_CONSONANT/4,pitch);
                      synth(_Jd,FRAMES_CONSONANT/4,pitch);
                      getchar();
                  } else {
                      synth(_Da,FRAMES_CONSONANT/3,pitch);
                      synth(_Db,FRAMES_CONSONANT/3,pitch);
                      synth(_Dc,FRAMES_CONSONANT/3,pitch);
                  }
                  break;
        case 'p': CONSONANT
                  synth(_Pa,FRAMES_CONSONANT/3,pitch);
                  synth(_Pb,FRAMES_CONSONANT/3,pitch);
                  synth(_Pc,FRAMES_CONSONANT/3,pitch);
                  break;
        case 'b': CONSONANT
                  synth(_Ba,FRAMES_CONSONANT/3,pitch);
                  synth(_Bb,FRAMES_CONSONANT/3,pitch);
                  synth(_Bc,FRAMES_CONSONANT/3,pitch);
                  break;
        case 'k': CONSONANT
                  synth(_Ka,FRAMES_CONSONANT/3,pitch);
                  synth(_Kb,FRAMES_CONSONANT/3,pitch);
                  synth(_Kc,FRAMES_CONSONANT/3,pitch);
                  break;
        case 'g': CONSONANT
                  synth(_Ga,FRAMES_CONSONANT/3,pitch);
                  synth(_Gb,FRAMES_CONSONANT/3,pitch);
                  synth(_Gc,FRAMES_CONSONANT/3,pitch);
                  break;
        case 'f': CONSONANT synth(_F, FRAMES_CONSONANT,pitch); break;
        case 'v': CONSONANT synth(_V, FRAMES_CONSONANT,pitch); break;
        case 'T': CONSONANT synth(_TH,FRAMES_CONSONANT,pitch); break;
        case 'D': CONSONANT synth(_DH,FRAMES_CONSONANT,pitch); break;
        case 's': CONSONANT synth(_S, FRAMES_CONSONANT,pitch); break;
        case 'z': CONSONANT synth(_Z, FRAMES_CONSONANT,pitch); break;
        case 'S': CONSONANT synth(_SH,FRAMES_CONSONANT,pitch); break;
        case 'Z': CONSONANT synth(_ZH,FRAMES_CONSONANT,pitch); break;
        case 'h': CONSONANT synth(__H,FRAMES_CONSONANT,pitch); break;
        case 'm': CONSONANT synth(_M, FRAMES_CONSONANT,pitch); break;
        case 'n': CONSONANT synth(_N, FRAMES_CONSONANT,pitch); break;
        case 'N': CONSONANT synth(_NX,FRAMES_CONSONANT,pitch); break;
        case 'R': CONSONANT synth(_RX,FRAMES_CONSONANT,pitch); break;
        case 'r': CONSONANT synth(_R, FRAMES_CONSONANT,pitch); break;
        case 'l': CONSONANT synth(_L, FRAMES_CONSONANT,pitch); break;
        case 'w': CONSONANT synth(_W, FRAMES_CONSONANT,pitch); break;
        case 'j': CONSONANT synth(_Y, FRAMES_CONSONANT,pitch); break;
        
        case 'a': VOWEL
                  if(peekchar() == 'I') {
                      synth(_AY,FRAMES_VOWEL,pitch);
                      synth(_YX,FRAMES_CONSONANT,pitch);
                      getchar();
                  } else if(peekchar() == 'U') {
                      synth(_AW,FRAMES_VOWEL,pitch);
                      synth(_WX,FRAMES_CONSONANT,pitch);
                      getchar();
                  }
                  break;
        case 'e': VOWEL
                  if(peekchar() == 'I') {
                      synth(_EY,FRAMES_VOWEL,pitch);
                      synth(_YX,FRAMES_CONSONANT,pitch);
                      getchar();
                  } else {
                      synth(_EH,FRAMES_VOWEL,pitch);
                  }
                  break;
        case '@': VOWEL
                  if(peekchar() == 'U') {
                      synth(_OW,FRAMES_VOWEL,pitch);
                      synth(_WX,FRAMES_CONSONANT,pitch);
                      getchar();
                  } else {
                      synth(_ER,FRAMES_VOWEL,pitch);
                  }
                  break;
        case 'O': VOWEL
                  if(peekchar() == 'I') {
                      synth(_OY,FRAMES_VOWEL,pitch);
                      synth(_YX,FRAMES_CONSONANT,pitch);
                      getchar();
                  } else {
                      synth(_AO,FRAMES_VOWEL,pitch); break;
                  }
                  break;
        case 'I': VOWEL synth(_IH,FRAMES_VOWEL,pitch); break;
        case '{': VOWEL synth(_AE,FRAMES_VOWEL,pitch); break;
        case 'Q': VOWEL synth(_AA,FRAMES_VOWEL,pitch); break;
        case 'V': VOWEL synth(_AH,FRAMES_VOWEL,pitch); break;
        case 'U': VOWEL synth(_UH,FRAMES_VOWEL,pitch); break;
        case 'i': VOWEL synth(_IY,FRAMES_VOWEL,pitch); break;
        case 'u': VOWEL synth(_UX,FRAMES_VOWEL,pitch); break;
        case '3': VOWEL synth(_ER,FRAMES_VOWEL,pitch); break;
        case 'A': VOWEL synth(_AH,FRAMES_VOWEL,pitch); break;
        
        default: fprintf(stderr, "Unrecognised character: '%c'\n", c); break;
        }
    return 0;
}
