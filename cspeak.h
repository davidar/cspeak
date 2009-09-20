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

#ifndef CSPEAK_H
#define CSPEAK_H

typedef enum { _NUL,
    _IY, _IH, _EH, _AE, _AA, _AH, _AO, _UH, _AX, _IX, _ER, _UX, _OH, _RX, _LX,
    _WX, _YX, _WH, _R, _L, _W, _Y, _M, _N, _NX, _DX, _Q, _S, _SH, _F, _TH, __H,
    __X, _Z, _ZH, _V, _DH, _CHa, _CHb, _Ja, _Jb, _Jc, _Jd, _EY, _AY, _OY, _AW,
    _OW, _UW, _Ba, _Bb, _Bc, _Da, _Db, _Dc, _Ga, _Gb, _Gc, _GXa, _GXb, _GXc,
    _Pa, _Pb, _Pc, _Ta, _Tb, _Tc, _Ka, _Kb, _Kc, _KXa, _KXb, _KXc
} symbol_t;

void synth(const symbol_t symbol, const unsigned int num_frames,
           const unsigned char midi_note);

#endif
