#ifndef __SCANLINE_H__
#define __SCANLINE_H__

#include <stdlib.h>

typedef struct{
	int x;
	int z;
} ScanLine;

static ScanLine *SLA = NULL;
static ScanLine *SLB = NULL;
static int RC_SCAN[2] = {SS_ALTO,-1};
static unsigned char mul8[256][256];


void InitScan( int x ){
	int i, j;
	SLA = (ScanLine*)malloc( x * sizeof(ScanLine) );
	SLB = (ScanLine*)malloc( x * sizeof(ScanLine) );
	for (i = 0; i < x; ++i){
		SLA[i].x=SS_ANCHO,
		SLB[i].x=-1;
	}
	/* 8-bit * 8-bit number multiplication table */
    for (i = 0; i < 256; i++) {
        for (j = 0; j < 256; j++) {
            mul8[i][j] = (unsigned char)((i * j) >> 8);
        }
    }
}

void FreeScan(void){
	free(SLA), SLA=NULL;
	free(SLB), SLB=NULL;
}


void SWAP_( int* A, int* B ){
	int T = *A;
	*A = *B;
	*B = T;
}

void SetScanLine( int *src ){

	ScanLine *Scaner = SLB;
	register int Len;
	int x0,y0,z0, x1,y1,z1, NC = 0;

	x0 = src[0],
	y0 = src[1],
	z0 = src[2],
	x1 = src[3],
	y1 = src[4];
	z1 = src[5];

	if ( y0 == y1 ) return;

	if ( y0 > y1 ){
		SWAP_(&x0,&x1);
		SWAP_(&y0,&y1);
		SWAP_(&z0,&z1);
		Scaner = SLA;
		NC = 1;
	}


	RC_SCAN[0] = ( y0 < RC_SCAN[0]? y0 : RC_SCAN[0] ),
	RC_SCAN[1] = ( y1 > RC_SCAN[1]? y1 : RC_SCAN[1] ),

	Scaner += y0;

	Len = abs( y1 - y0 );
	Len += 1>>Len;

	#define FIXED 16

	x1 = (( x1 - x0 )<<FIXED) / Len;
	x0 <<= FIXED;

	z1 = (( z1 - z0 )<<FIXED) / Len;
	z0 <<= FIXED;


	while( Len-- ){

		if( NC == 0 ){
			if ( (x0>>FIXED) >= Scaner->x ){
				Scaner->x = x0>>FIXED;
				Scaner->z = z0;
			}
		}

		if( NC == 1 ){
			if( (x0>>FIXED) <= Scaner->x ){
				Scaner->x = x0>>FIXED;
				Scaner->z = z0;
			}
		}

		// En normal solo estaria esto aca.
		// Scaner->x = x0>>FIXED;
		// Scaner->z = z0>>FIXED;

		x0 += x1;
		z0 += z1;
		Scaner++;
	}

	#undef FIXED

}


void ScanLineFill( int color ){

    int r8 = color >> 16 & 0xff;
    int g8 = color >> 8 & 0xff;
    int b8 = color >> 0 & 0xff;
    int Len,d;

	for (int I = RC_SCAN[0]; I < RC_SCAN[1]; ++I)
	{

		Len = (SLB[I].x - SLA[I].x);
		Len += 1>>Len;
		SLB[I].z = (SLB[I].z - SLA[I].z) / Len;

		for (int O = SLA[I].x; O < SLB[I].x; ++O){

			if ( GetDepth( O, I ) <= SLA[I].z){
				Depth( O, I, SLA[I].z );
				d = (SLA[I].z >> 16) * 3 / 2;
				if (d >= 256){
					Punto( O, I, color );
				} else {
					Punto( O, I, mul8[d][r8] << 16 | mul8[d][g8] << 8 | mul8[d][b8] );
				}
			}

			SLA[I].z += SLB[I].z;
		}
		SLA[I].x = SS_ANCHO;
		SLB[I].x = -1;
	}
	RC_SCAN[0] = SS_ALTO, RC_SCAN[1] = -1;
}


#endif