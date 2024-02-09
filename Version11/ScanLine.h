#ifndef __SCANLINE_H__
#define __SCANLINE_H__


typedef struct{
	int x;
} ScanLine;

int RC_SCAN[2] = {SS_ALTO,-1};

ScanLine *SLA = NULL;
ScanLine *SLB = NULL;


void InitScan( int x ){
	SLA = (ScanLine*)malloc( x * sizeof(ScanLine) );
	SLB = (ScanLine*)malloc( x * sizeof(ScanLine) );
	for (unsigned int I = 0; I < x; ++I){
		SLA[I].x=SS_ANCHO,
		SLB[I].x=-1;
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
	int x0,y0, x1,y1, NC = 0;

	x0 = src[0],
	y0 = src[1],
	x1 = src[2],
	y1 = src[3];

	if ( y0 > y1 ){
		SWAP_(&x0,&x1);
		SWAP_(&y0,&y1);
		Scaner = SLA;
		NC = 1;
	}

	if ( y0 == y1 ) return;

	RC_SCAN[0] = ( y0 < RC_SCAN[0]? y0 : RC_SCAN[0] ),
	RC_SCAN[1] = ( y1 > RC_SCAN[1]? y1 : RC_SCAN[1] ),

	Scaner += y0;

	Len = abs( y1 - y0 );
	Len += 1>>Len;

	#define FIXED 15

	x1 = (( x1 - x0 )<<FIXED) / Len;
	x0 <<= FIXED;

	while( Len-- ){

		if( NC == 0 ){
			if ( (x0>>FIXED) >= Scaner->x ){
				Scaner->x = x0>>FIXED;
			}
		}

		if( NC == 1 ){
			if( (x0>>FIXED) <= Scaner->x ){
				Scaner->x = x0>>FIXED;
			}
		}

		// En normal solo estaria esto aca.
		// Scaner->x = x0>>FIXED;

		x0 += x1;
		Scaner++;
	}

	#undef FIXED

}


void ScanLineFill( int color ){

	printf("MIN Y: %i\n", RC_SCAN[0] );
	printf("MAX Y: %i\n", RC_SCAN[1] );

	// Linea( 0, RC_SCAN[0], SS_ANCHO, RC_SCAN[0] ,0xffff0000 );
	// Linea( 0, RC_SCAN[1], SS_ANCHO, RC_SCAN[1] ,0xffff0000 );

	for (int I = RC_SCAN[0]; I < RC_SCAN[1]; ++I)
	{
		for (int O = SLA[I].x; O < SLB[I].x; ++O)
		{
			Punto( O, I, color);
		}
		SLA[I].x = SS_ANCHO;
		SLB[I].x = -1;
	}
	RC_SCAN[0] = SS_ALTO, RC_SCAN[1] = -1;
}


#endif