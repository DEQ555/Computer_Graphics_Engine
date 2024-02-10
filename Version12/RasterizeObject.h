#ifndef __RasterizeObject_H__
#define __RasterizeObject_H__

#define __AREA(A,B,C) (((C[0]) - (A[0])) * ((B[1]) - (A[1])) - ((C[1]) - (A[1])) * ((B[0]) - (A[0])))

// typedef struct{}ObjectModel;

static unsigned int DrawTriangleCount = 0;
static int _Camera_[4] = {0,0,0,1};
static int *VWorld = NULL;



void SetCameraPos( int x, int y, int z ){
	0[_Camera_] = x;
	1[_Camera_] = y;
	2[_Camera_] = z;
}


void VertexProyective( int *src, int *dst, int fov, int len ){
	int shift = 0;
	int ffac = (1 << (fov + 12));

	shift = fov - 8;

	while(len--){
		fov = ffac / *(src+2);
		*dst++ = ( ( *src++ * fov + (1 << 11)) >> 12 ) + SM_ANCHO;
		*dst++ = SM_ALTO - ( (*src++ * fov + (1 << 11)) >> 12 );
		*dst++ = fov >> shift;
		src++;
	}

}



void RasterModel( int *src, int *dst, int fov, int color ){
	DrawTriangleCount = 0;
	int* V = NULL;
	unsigned int Len;

	Len = CubeVerticesLen;
	V = src;

	while(Len--){

		*V++ += 0[_Camera_],
		*V++ += 1[_Camera_],
		*V++ += 2[_Camera_];

	}

	VertexProyective(src,dst,fov,CubeVerticesLen);

	V = CubeFaces;

	Len = CubeFacesLen;

	while( Len-- ){

		const int A = *V++ * 3;
		const int B = *V++ * 3;
		const int C = *V++ * 3;
		V++;

		int LA[6] = { (A+0)[dst], (A+1)[dst], (A+2)[dst], (B+0)[dst], (B+1)[dst], (B+2)[dst] };
		int LB[6] = { (B+0)[dst], (B+1)[dst], (B+2)[dst], (C+0)[dst], (C+1)[dst], (C+2)[dst] };
		int LC[6] = { (C+0)[dst], (C+1)[dst], (C+2)[dst], (A+0)[dst], (A+1)[dst], (A+2)[dst] };

		if( __AREA(LA,LB,LC) >=0 ) continue;

		SetScanLine( LA );
		SetScanLine( LB );
		SetScanLine( LC );

		#if FILLING_PARTS
		ScanLineFill( color ); // Filled for each triangle.
		#endif

		DrawTriangleCount++;

	}

	#if DIRECT_FILL
	ScanLineFill( color ); // Filling in a single pass.
	#endif

}




#endif