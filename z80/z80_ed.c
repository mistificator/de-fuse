/* z80_ed.c: Z80 CBxx opcodes
   Copyright (c) 1999-2003 Philip Kendall

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

   Author contact information:

   E-mail: philip-fuse@shadowmagic.org.uk

*/

/* NB: this file is autogenerated by './z80/z80.pl' from 'opcodes_ed.dat',
   and included in 'z80_ops.c' */

    case 0x40:		/* IN B,(C) */
      Z80_IN( B, BC );
      break;
    case 0x41:		/* OUT (C),B */
      writeport( BC, B );
      break;
    case 0x42:		/* SBC HL,BC */
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      SBC16(BC);
      break;
    case 0x43:		/* LD (nnnn),BC */
      LD16_NNRR(C,B);
      break;
    case 0x44:
    case 0x4c:
    case 0x54:
    case 0x5c:
    case 0x64:
    case 0x6c:
    case 0x74:
    case 0x7c:		/* NEG */
      {
	libspectrum_byte bytetemp=A;
	A=0;
	SUB(bytetemp);
      }
      break;
    case 0x45:
    case 0x4d:
    case 0x55:
    case 0x5d:
    case 0x65:
    case 0x6d:
    case 0x75:
    case 0x7d:		/* RETN */
      IFF1=IFF2;
      RET();
      z80_retn();
      break;
    case 0x46:
    case 0x4e:
    case 0x66:
    case 0x6e:		/* IM 0 */
      IM=0;
      break;
    case 0x47:		/* LD I,A */
      contend_read_no_mreq( IR, 1 );
      I=A;
      break;
    case 0x48:		/* IN C,(C) */
      Z80_IN( C, BC );
      break;
    case 0x49:		/* OUT (C),C */
      writeport( BC, C );
      break;
    case 0x4a:		/* ADC HL,BC */
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      ADC16(BC);
      break;
    case 0x4b:		/* LD BC,(nnnn) */
      LD16_RRNN(C,B);
      break;
    case 0x4f:		/* LD R,A */
      contend_read_no_mreq( IR, 1 );
      /* Keep the RZX instruction counter right */
      rzx_instructions_offset += ( R - A );
      R=R7=A;
      break;
    case 0x50:		/* IN D,(C) */
      Z80_IN( D, BC );
      break;
    case 0x51:		/* OUT (C),D */
      writeport( BC, D );
      break;
    case 0x52:		/* SBC HL,DE */
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      SBC16(DE);
      break;
    case 0x53:		/* LD (nnnn),DE */
      LD16_NNRR(E,D);
      break;
    case 0x56:
    case 0x76:		/* IM 1 */
      IM=1;
      break;
    case 0x57:		/* LD A,I */
      contend_read_no_mreq( IR, 1 );
      A=I;
      F = ( F & FLAG_C ) | sz53_table[A] | ( IFF2 ? FLAG_V : 0 );
      z80.iff2_read = 1;
      event_add( tstates, z80_nmos_iff2_event );
      break;
    case 0x58:		/* IN E,(C) */
      Z80_IN( E, BC );
      break;
    case 0x59:		/* OUT (C),E */
      writeport( BC, E );
      break;
    case 0x5a:		/* ADC HL,DE */
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      ADC16(DE);
      break;
    case 0x5b:		/* LD DE,(nnnn) */
      LD16_RRNN(E,D);
      break;
    case 0x5e:
    case 0x7e:		/* IM 2 */
      IM=2;
      break;
    case 0x5f:		/* LD A,R */
      contend_read_no_mreq( IR, 1 );
      A=(R&0x7f) | (R7&0x80);
      F = ( F & FLAG_C ) | sz53_table[A] | ( IFF2 ? FLAG_V : 0 );
      z80.iff2_read = 1;
      event_add( tstates, z80_nmos_iff2_event );
      break;
    case 0x60:		/* IN H,(C) */
      Z80_IN( H, BC );
      break;
    case 0x61:		/* OUT (C),H */
      writeport( BC, H );
      break;
    case 0x62:		/* SBC HL,HL */
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      SBC16(HL);
      break;
    case 0x63:		/* LD (nnnn),HL */
      LD16_NNRR(L,H);
      break;
    case 0x67:		/* RRD */
      {
	libspectrum_byte bytetemp = readbyte( HL );
	contend_read_no_mreq( HL, 1 ); contend_read_no_mreq( HL, 1 );
	contend_read_no_mreq( HL, 1 ); contend_read_no_mreq( HL, 1 );
	writebyte(HL,  ( A << 4 ) | ( bytetemp >> 4 ) );
	A = ( A & 0xf0 ) | ( bytetemp & 0x0f );
	F = ( F & FLAG_C ) | sz53p_table[A];
      }
      break;
    case 0x68:		/* IN L,(C) */
      Z80_IN( L, BC );
      break;
    case 0x69:		/* OUT (C),L */
      writeport( BC, L );
      break;
    case 0x6a:		/* ADC HL,HL */
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      ADC16(HL);
      break;
    case 0x6b:		/* LD HL,(nnnn) */
      LD16_RRNN(L,H);
      break;
    case 0x6f:		/* RLD */
      {
	libspectrum_byte bytetemp = readbyte( HL );
	contend_read_no_mreq( HL, 1 ); contend_read_no_mreq( HL, 1 );
	contend_read_no_mreq( HL, 1 ); contend_read_no_mreq( HL, 1 );
	writebyte(HL, (bytetemp << 4 ) | ( A & 0x0f ) );
	A = ( A & 0xf0 ) | ( bytetemp >> 4 );
	F = ( F & FLAG_C ) | sz53p_table[A];
      }
      break;
    case 0x70:		/* IN F,(C) */
      {
	libspectrum_byte bytetemp;
	Z80_IN( bytetemp, BC );
      }
      break;
    case 0x71:		/* OUT (C),0 */
      writeport( BC, IS_CMOS ? 0xff : 0 );
      break;
    case 0x72:		/* SBC HL,SP */
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      SBC16(SP);
      break;
    case 0x73:		/* LD (nnnn),SP */
      LD16_NNRR(SPL,SPH);
      break;
    case 0x78:		/* IN A,(C) */
      Z80_IN( A, BC );
      break;
    case 0x79:		/* OUT (C),A */
      writeport( BC, A );
      break;
    case 0x7a:		/* ADC HL,SP */
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      contend_read_no_mreq( IR, 1 );
      ADC16(SP);
      break;
    case 0x7b:		/* LD SP,(nnnn) */
      LD16_RRNN(SPL,SPH);
      break;
    case 0xa0:		/* LDI */
      {
	libspectrum_byte bytetemp=readbyte( HL );
	BC--;
	writebyte(DE,bytetemp);
	contend_write_no_mreq( DE, 1 ); contend_write_no_mreq( DE, 1 );
	DE++; HL++;
	bytetemp += A;
	F = ( F & ( FLAG_C | FLAG_Z | FLAG_S ) ) | ( BC ? FLAG_V : 0 ) |
	  ( bytetemp & FLAG_3 ) | ( (bytetemp & 0x02) ? FLAG_5 : 0 );
      }
      break;
    case 0xa1:		/* CPI */
      {
	libspectrum_byte value = readbyte( HL ), bytetemp = A - value,
	  lookup = ( (        A & 0x08 ) >> 3 ) |
	           ( (  (value) & 0x08 ) >> 2 ) |
	           ( ( bytetemp & 0x08 ) >> 1 );
	contend_read_no_mreq( HL, 1 ); contend_read_no_mreq( HL, 1 );
	contend_read_no_mreq( HL, 1 ); contend_read_no_mreq( HL, 1 );
	contend_read_no_mreq( HL, 1 );
	HL++; BC--;
	F = ( F & FLAG_C ) | ( BC ? ( FLAG_V | FLAG_N ) : FLAG_N ) |
	  halfcarry_sub_table[lookup] | ( bytetemp ? 0 : FLAG_Z ) |
	  ( bytetemp & FLAG_S );
	if(F & FLAG_H) bytetemp--;
	F |= ( bytetemp & FLAG_3 ) | ( (bytetemp&0x02) ? FLAG_5 : 0 );
      }
      break;
    case 0xa2:		/* INI */
      {
	libspectrum_byte initemp, initemp2;

	contend_read_no_mreq( IR, 1 );
	initemp = readport( BC );
	writebyte( HL, initemp );

        B--; HL++;
        initemp2 = initemp + C + 1;
	F = ( initemp & 0x80 ? FLAG_N : 0 ) |
            ( ( initemp2 < initemp ) ? FLAG_H | FLAG_C : 0 ) |
            ( parity_table[ ( initemp2 & 0x07 ) ^ B ] ? FLAG_P : 0 ) |
            sz53_table[B];
      }
      break;
    case 0xa3:		/* OUTI */
      {
	libspectrum_byte outitemp, outitemp2;

	contend_read_no_mreq( IR, 1 );
	outitemp = readbyte( HL );
	B--;	/* This does happen first, despite what the specs say */
	writeport(BC,outitemp);

	HL++;
        outitemp2 = outitemp + L;
	F = ( outitemp & 0x80 ? FLAG_N : 0 ) |
            ( ( outitemp2 < outitemp ) ? FLAG_H | FLAG_C : 0 ) |
            ( parity_table[ ( outitemp2 & 0x07 ) ^ B ] ? FLAG_P : 0 ) |
            sz53_table[B];
      }
      break;
    case 0xa8:		/* LDD */
      {
	libspectrum_byte bytetemp=readbyte( HL );
	BC--;
	writebyte(DE,bytetemp);
	contend_write_no_mreq( DE, 1 ); contend_write_no_mreq( DE, 1 );
	DE--; HL--;
	bytetemp += A;
	F = ( F & ( FLAG_C | FLAG_Z | FLAG_S ) ) | ( BC ? FLAG_V : 0 ) |
	  ( bytetemp & FLAG_3 ) | ( (bytetemp & 0x02) ? FLAG_5 : 0 );
      }
      break;
    case 0xa9:		/* CPD */
      {
	libspectrum_byte value = readbyte( HL ), bytetemp = A - value,
	  lookup = ( (        A & 0x08 ) >> 3 ) |
	           ( (  (value) & 0x08 ) >> 2 ) |
	           ( ( bytetemp & 0x08 ) >> 1 );
	contend_read_no_mreq( HL, 1 ); contend_read_no_mreq( HL, 1 );
	contend_read_no_mreq( HL, 1 ); contend_read_no_mreq( HL, 1 );
	contend_read_no_mreq( HL, 1 );
	HL--; BC--;
	F = ( F & FLAG_C ) | ( BC ? ( FLAG_V | FLAG_N ) : FLAG_N ) |
	  halfcarry_sub_table[lookup] | ( bytetemp ? 0 : FLAG_Z ) |
	  ( bytetemp & FLAG_S );
	if(F & FLAG_H) bytetemp--;
	F |= ( bytetemp & FLAG_3 ) | ( (bytetemp&0x02) ? FLAG_5 : 0 );
      }
      break;
    case 0xaa:		/* IND */
      {
	libspectrum_byte initemp, initemp2;

	contend_read_no_mreq( IR, 1 );
	initemp = readport( BC );
	writebyte( HL, initemp );

        B--; HL--;
        initemp2 = initemp + C - 1;
	F = ( initemp & 0x80 ? FLAG_N : 0 ) |
            ( ( initemp2 < initemp ) ? FLAG_H | FLAG_C : 0 ) |
            ( parity_table[ ( initemp2 & 0x07 ) ^ B ] ? FLAG_P : 0 ) |
            sz53_table[B];
      }
      break;
    case 0xab:		/* OUTD */
      {
	libspectrum_byte outitemp, outitemp2;

	contend_read_no_mreq( IR, 1 );
	outitemp = readbyte( HL );
	B--;	/* This does happen first, despite what the specs say */
	writeport(BC,outitemp);

	HL--;
        outitemp2 = outitemp + L;
	F = ( outitemp & 0x80 ? FLAG_N : 0 ) |
            ( ( outitemp2 < outitemp ) ? FLAG_H | FLAG_C : 0 ) |
            ( parity_table[ ( outitemp2 & 0x07 ) ^ B ] ? FLAG_P : 0 ) |
            sz53_table[B];
      }
      break;
    case 0xb0:		/* LDIR */
      {
	libspectrum_byte bytetemp=readbyte( HL );
	writebyte(DE,bytetemp);
	contend_write_no_mreq( DE, 1 ); contend_write_no_mreq( DE, 1 );
	BC--;
	bytetemp += A;
	F = ( F & ( FLAG_C | FLAG_Z | FLAG_S ) ) | ( BC ? FLAG_V : 0 ) |
	  ( bytetemp & FLAG_3 ) | ( (bytetemp & 0x02) ? FLAG_5 : 0 );
	if(BC) {
	  contend_write_no_mreq( DE, 1 ); contend_write_no_mreq( DE, 1 );
	  contend_write_no_mreq( DE, 1 ); contend_write_no_mreq( DE, 1 );
	  contend_write_no_mreq( DE, 1 );
	  PC-=2;
	}
        HL++; DE++;
      }
      break;
    case 0xb1:		/* CPIR */
      {
	libspectrum_byte value = readbyte( HL ), bytetemp = A - value,
	  lookup = ( (        A & 0x08 ) >> 3 ) |
		   ( (  (value) & 0x08 ) >> 2 ) |
		   ( ( bytetemp & 0x08 ) >> 1 );
	contend_read_no_mreq( HL, 1 ); contend_read_no_mreq( HL, 1 );
	contend_read_no_mreq( HL, 1 ); contend_read_no_mreq( HL, 1 );
	contend_read_no_mreq( HL, 1 );
	BC--;
	F = ( F & FLAG_C ) | ( BC ? ( FLAG_V | FLAG_N ) : FLAG_N ) |
	  halfcarry_sub_table[lookup] | ( bytetemp ? 0 : FLAG_Z ) |
	  ( bytetemp & FLAG_S );
	if(F & FLAG_H) bytetemp--;
	F |= ( bytetemp & FLAG_3 ) | ( (bytetemp&0x02) ? FLAG_5 : 0 );
	if( ( F & ( FLAG_V | FLAG_Z ) ) == FLAG_V ) {
	  contend_read_no_mreq( HL, 1 ); contend_read_no_mreq( HL, 1 );
	  contend_read_no_mreq( HL, 1 ); contend_read_no_mreq( HL, 1 );
	  contend_read_no_mreq( HL, 1 );
	  PC-=2;
	}
	HL++;
      }
      break;
    case 0xb2:		/* INIR */
      {
	libspectrum_byte initemp, initemp2;

	contend_read_no_mreq( IR, 1 );
	initemp = readport( BC );
	writebyte( HL, initemp );

	B--;
        initemp2 = initemp + C + 1;
	F = ( initemp & 0x80 ? FLAG_N : 0 ) |
            ( ( initemp2 < initemp ) ? FLAG_H | FLAG_C : 0 ) |
            ( parity_table[ ( initemp2 & 0x07 ) ^ B ] ? FLAG_P : 0 ) |
            sz53_table[B];

	if( B ) {
	  contend_write_no_mreq( HL, 1 ); contend_write_no_mreq( HL, 1 );
	  contend_write_no_mreq( HL, 1 ); contend_write_no_mreq( HL, 1 );
	  contend_write_no_mreq( HL, 1 );
	  PC -= 2;
	}
        HL++;
      }
      break;
    case 0xb3:		/* OTIR */
      {
	libspectrum_byte outitemp, outitemp2;

	contend_read_no_mreq( IR, 1 );
	outitemp = readbyte( HL );
	B--;	/* This does happen first, despite what the specs say */
	writeport(BC,outitemp);

	HL++;
        outitemp2 = outitemp + L;
	F = ( outitemp & 0x80 ? FLAG_N : 0 ) |
            ( ( outitemp2 < outitemp ) ? FLAG_H | FLAG_C : 0 ) |
            ( parity_table[ ( outitemp2 & 0x07 ) ^ B ] ? FLAG_P : 0 ) |
            sz53_table[B];

	if( B ) {
	  contend_read_no_mreq( BC, 1 ); contend_read_no_mreq( BC, 1 );
	  contend_read_no_mreq( BC, 1 ); contend_read_no_mreq( BC, 1 );
	  contend_read_no_mreq( BC, 1 );
	  PC -= 2;
	}
      }
      break;
    case 0xb8:		/* LDDR */
      {
	libspectrum_byte bytetemp=readbyte( HL );
	writebyte(DE,bytetemp);
	contend_write_no_mreq( DE, 1 ); contend_write_no_mreq( DE, 1 );
	BC--;
	bytetemp += A;
	F = ( F & ( FLAG_C | FLAG_Z | FLAG_S ) ) | ( BC ? FLAG_V : 0 ) |
	  ( bytetemp & FLAG_3 ) | ( (bytetemp & 0x02) ? FLAG_5 : 0 );
	if(BC) {
	  contend_write_no_mreq( DE, 1 ); contend_write_no_mreq( DE, 1 );
	  contend_write_no_mreq( DE, 1 ); contend_write_no_mreq( DE, 1 );
	  contend_write_no_mreq( DE, 1 );
	  PC-=2;
	}
        HL--; DE--;
      }
      break;
    case 0xb9:		/* CPDR */
      {
	libspectrum_byte value = readbyte( HL ), bytetemp = A - value,
	  lookup = ( (        A & 0x08 ) >> 3 ) |
		   ( (  (value) & 0x08 ) >> 2 ) |
		   ( ( bytetemp & 0x08 ) >> 1 );
	contend_read_no_mreq( HL, 1 ); contend_read_no_mreq( HL, 1 );
	contend_read_no_mreq( HL, 1 ); contend_read_no_mreq( HL, 1 );
	contend_read_no_mreq( HL, 1 );
	BC--;
	F = ( F & FLAG_C ) | ( BC ? ( FLAG_V | FLAG_N ) : FLAG_N ) |
	  halfcarry_sub_table[lookup] | ( bytetemp ? 0 : FLAG_Z ) |
	  ( bytetemp & FLAG_S );
	if(F & FLAG_H) bytetemp--;
	F |= ( bytetemp & FLAG_3 ) | ( (bytetemp&0x02) ? FLAG_5 : 0 );
	if( ( F & ( FLAG_V | FLAG_Z ) ) == FLAG_V ) {
	  contend_read_no_mreq( HL, 1 ); contend_read_no_mreq( HL, 1 );
	  contend_read_no_mreq( HL, 1 ); contend_read_no_mreq( HL, 1 );
	  contend_read_no_mreq( HL, 1 );
	  PC-=2;
	}
	HL--;
      }
      break;
    case 0xba:		/* INDR */
      {
	libspectrum_byte initemp, initemp2;

	contend_read_no_mreq( IR, 1 );
	initemp = readport( BC );
	writebyte( HL, initemp );

	B--;
        initemp2 = initemp + C - 1;
	F = ( initemp & 0x80 ? FLAG_N : 0 ) |
            ( ( initemp2 < initemp ) ? FLAG_H | FLAG_C : 0 ) |
            ( parity_table[ ( initemp2 & 0x07 ) ^ B ] ? FLAG_P : 0 ) |
            sz53_table[B];

	if( B ) {
	  contend_write_no_mreq( HL, 1 ); contend_write_no_mreq( HL, 1 );
	  contend_write_no_mreq( HL, 1 ); contend_write_no_mreq( HL, 1 );
	  contend_write_no_mreq( HL, 1 );
	  PC -= 2;
	}
        HL--;
      }
      break;
    case 0xbb:		/* OTDR */
      {
	libspectrum_byte outitemp, outitemp2;

	contend_read_no_mreq( IR, 1 );
	outitemp = readbyte( HL );
	B--;	/* This does happen first, despite what the specs say */
	writeport(BC,outitemp);

	HL--;
        outitemp2 = outitemp + L;
	F = ( outitemp & 0x80 ? FLAG_N : 0 ) |
            ( ( outitemp2 < outitemp ) ? FLAG_H | FLAG_C : 0 ) |
            ( parity_table[ ( outitemp2 & 0x07 ) ^ B ] ? FLAG_P : 0 ) |
            sz53_table[B];

	if( B ) {
	  contend_read_no_mreq( BC, 1 ); contend_read_no_mreq( BC, 1 );
	  contend_read_no_mreq( BC, 1 ); contend_read_no_mreq( BC, 1 );
	  contend_read_no_mreq( BC, 1 );
	  PC -= 2;
	}
      }
      break;
    case 0xfb:		/* slttrap */
      slt_trap( HL, A );
      break;
    default:		/* All other opcodes are NOPD */
      break;
