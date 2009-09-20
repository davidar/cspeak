#!/usr/bin/python
# Copyright (C) 2009  David Roberts <d@vidr.cc>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
# 02110-1301, USA.

import sys

"""
Converts English text to a string of SAMPA phonemes.
$ python reciter.py The quick brown fox jumps over the lazy dog.
D@ kwIk br@Un fQks dZVmps @Uv@R D@ l{zI dQg
"""

# Regular English Pronunciation rules
# <http://www.phon.ucl.ac.uk/home/mark/regeng/>
rules = [
    "#|BE+||bI",
    "#|RE+||rI",
    "|-ABLE|#|@b@l",
    "|-AGE||IdZ",
    "|-AL|#|@l",
    "|-ARY||@rI",
    "|ATION|#|eIS@n",
    "|-ED|#|-d",
    "|-ES|#|-s",
    "|-EST|#|Ist",
    "|-FUL|#|fUl",
    "L#|LY|#|I",
    "#|LY|#|lI",
    "|-TY|#|tI",
    "#|MENT|#|m@nt",
    "|-N'T|#|@nt",
    "|-S|#|-s",
    "|-'S||-s",
    "|-S'|#|-s",
    "|SSION|#|S@n",
    "|SION|#|Z@n",
    "|TION|#|S@n",
    "|-Y|#|I",
    "#|A|#|eI",
    "#|ARE|#|AR",
    "#|AS|#|{z",
    "#|B|#|bi",
    "#|C|#|si",
    "#|COULD|#|kUd",
    "#|D|#|di",
    "#|DO|#|du",
    "#|DOES|#|dVz",
    "#|DON'T|#|d@Unt",
    "#|E|#|i",
    "#|F|#|ef",
    "#|G|#|dZi",
    "#|H|#|eItS",
    "#|HAS|#|h{z",
    "#|HAVE|#|h{v",
    "#|HER|#|h3R",
    "#|HIS|#|hIz",
    "#|HOW|#|haU",
    "#|I|#|aI",
    "#|IS|#|Iz",
    "#|J|#|dZeI",
    "#|K|#|keI",
    "#|L|#|el",
    "#|M|#|em",
    "#|N|#|en",
    "#|O|#|@U",
    "#|OF|#|Qv",
    "#|ONE|#|wVn",
    "#|P|#|pi",
    "#|Q|#|kju",
    "#|R|#|AR",
    "#|S|#|es",
    "#|SHE|#|Si",
    "#|SHOULD|#|SUd",
    "#|SOME|#|sVm",
    "#|T|#|ti",
    "#|THAN|#|D{n",
    "#|THAT|#|D{t",
    "#|THE|#|D@",
    "#|THEIR|#|De@R",
    "#|THEM|#|Dem",
    "#|THEN|#|Den",
    "#|THERE|#|De@R",
    "#|THESE|#|Diz",
    "#|THEY|#|DeI",
    "#|THIS|#|DIs",
    "#|THOSE|#|D@Uz",
    "#|TO|#|tu",
    "#|TWO|#|tu",
    "#|U|#|ju",
    "#|V|#|vi",
    "#|W|#|dVb@lju",
    "#|WANT|#|wQnt",
    "#|WAS|#|wQz",
    "#|WHAT|#|wQt",
    "#|WHERE|#|we@R",
    "#|WHOLE|#|h@Ul",
    "#|WHO||hu",
    "#|WITH|#|wID",
    "#|WOULD|#|wUd",
    "#|X|#|eks",
    "#|Y|#|waI",
    "#|YOU|#|ju",
    "#|Z|#|zed",
    "|TCH||tS",
    "S|CH||k",
    "|CH|^|k",
    "|CH||tS",
    "#|WH||w",
    "#|KN||n",
    "^|I|GH|aI",
    "|TH|ER|D",
    "|TH||T",
    "|SH||S",
    "|DGE|#|dZ",
    "|GE|#|dZ",
    "|NG||N",
    "|NK||Nk",
    "|BB||b",
    "|DD||d",
    "|FF||f",
    "|A|LL|O",
    "|LL||l",
    "|MM||m",
    "|NN||n",
    "|PP||p",
    "|RR||r",
    "|SS||s",
    "|TT||t",
    "|ZZ||z",
    "Q|U||w",
    "|EAR||I@",
    "|OOR||OR",
    "|OUR||OR",
    "|ARE|#|e@R",
    "|EA|D|e",
    "|ER|#|@R",
    "W|OR||3R",
    "|URE|#|@R",
    "|AI||eI",
    "|AU||O",
    "|EA||i",
    "|EE||i",
    "|IA||I@",
    "|IE||i",
    "|IO||I@",
    "|OA||@U",
    "|OE||@U",
    "|OI||OI",
    "|OO||U",
    "|OU||aU",
    "|UA||U@",
    "|UE||u",
    "|UI||I",
    "|A|^E|eI",
    "|A|NGE|eI",
    "#^|E|#|i",
    "^|LE|#|@l",
    "^|E|#|",
    "|I|^E#|aI",
    "|O|^E|@U",
    "^|O|#|@U",
    "|U|^E|ju",
    "|AR||AR",
    "|AW|.|@w",
    "|AW||O",
    "|AY||eI",
    "|ER||3R",
    "|EW||u",
    "|IR||3R",
    "|OR||OR",
    "|OW||@U",
    "|OY||OI",
    "|UR||3R",
    "|UY||aI",
    "|B||b",
    "|C|E|s",
    "|SC|I|s",
    "|C|I|s",
    "|C|Y|s",
    "|CK||k",
    "|C||k",
    "|F||f",
    "|GG||g",
    "|G|Y|dZ",
    "|GH||",
    "|G||g",
    "|PH||f",
    "|H||h",
    "|J||dZ",
    "|K||k",
    "|L||l",
    "|M||m",
    "|N||n",
    "|P||p",
    "|Q||k",
    "|T||t",
    "|V||v",
    "#|WR||R",
    "|W||w",
    "|X||ks",
    "^|Y|^|I",
    "#^^|Y|#|aI",
    "#^|Y|#|aI",
    "|Y|.|j",
    "|Y||I",
    "|Z||z",
    "|R||R",
    "|D||d",
    "|S||s",
    "^|A|#|@",
    "|A||{",
    "|E||e",
    "|I||I",
    "|O||Q",
    "|U||V",
]

def consonant(c):
    return c.upper() in 'BCDFGHJKLMNPQRSTVWXYZ'

def vowel(c):
    return c.upper() in 'AEIOUY'

def match_kind(kind, c):
    if kind == '#':   return c.upper() in '()#-+.'
    elif kind == '^': return consonant(c)
    elif kind == '.': return vowel(c)
    else:             return c.upper() == kind

def match_left(left, word):
    if len(word) < len(left): return False
    for i in xrange(len(left)):
        if not match_kind(left[-i-1], word[-i-1]):
            return False
    return True

def match_right(right, word):
    if len(word) < len(right): return False
    for i in xrange(len(right)):
        if not match_kind(right[i], word[i]):
            return False
    return True

def apply_rule(word, rule, output):
    left, central, right, phonemes = rule.split('|')
    match = -1
    while True:
        match = word.find(central, match+1)
        if match == -1: return word
        word_left = word[:match]
        word_right = word[match+len(central):]
        if not match_left(left, word_left): continue
        if not match_right(right, word_right): continue
        # rule matches
        output[match] = phonemes
        # convert matching characters to lowercase
        word = word_left + word[match:match+len(central)].lower() + word_right

def apply_plural_rule(phonemes):
    return phonemes.replace('s-s','sIz').replace('S-s','SIz') \
                   .replace('z-s','zIz').replace('Z-s','ZIz') \
                   .replace('p-s','ps') .replace('t-s','ts') \
                   .replace('k-s','ks') .replace('f-s','fs') \
                   .replace('T-s','Ts') .replace('-s','z')

def apply_past_tense_rule(phonemes):
    return phonemes.replace('t-d','tId').replace('d-d','dId') \
                   .replace('p-d','pt') .replace('k-d','kt') \
                   .replace('f-d','ft') .replace('T-d','Tt') \
                   .replace('s-d','st') .replace('S-d','St') \
                   .replace('-d','d')

def apply_r_deletion_rule(phonemes):
    return phonemes.replace('Ra','ra').replace('Re','re').replace('Ri','ri') \
                   .replace('Ro','ro').replace('Ru','ru').replace('RA','rA') \
                   .replace('RE','rE').replace('RI','rI').replace('RO','rO') \
                   .replace('RU','rU').replace('R3','r3').replace('R@','r@') \
                   .replace('RQ','rQ').replace('RV','rV').replace('R{','r{')

def main():
    phrase = ' '.join(sys.argv[1:]).upper().split()
    for word in phrase:
        word = '(' + word + ')'
        output = ['']*len(word)
        for rule in rules:
            word = apply_rule(word, rule, output)
        phonemes = ''.join(output)
        phonemes = apply_plural_rule(phonemes)
        phonemes = apply_past_tense_rule(phonemes)
        phonemes = apply_r_deletion_rule(phonemes)
        print phonemes,
    print
if __name__ == '__main__': main()
