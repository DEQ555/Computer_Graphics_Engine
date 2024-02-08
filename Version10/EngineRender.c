

#include "EngineRender.h"
#include <stdlib.h>
#include <stdio.h>



// Los datos del buffer iamgen.
int *vbuff = NULL;
int wbuff = 0; // ancho buffer
int hbuff = 0; // alto buffer

// Creamos un buffer de imagen 2D
void CrearBuffer( const int w, const int h ){

	int i;

	vbuff = (int*)malloc( w * h * sizeof(int) ); // creamos un tamaño al buffer

	wbuff = w;
	hbuff = h;

	// ponemos en cero todo el arreglo
	for ( i = 0; i < w * h; ++i)
	{
		vbuff[ i ] = 0;
	}

}

// Este codigo no hablaremos mucho...
static void _Memset( void* _x, char _y, unsigned _z ){
	char *_X_=(char*)_x;
	for (unsigned int i = 0; i < _z; ++i)_X_[i] = _y;
}
// Este codigo no hablaremos mucho...
void SaveBMP( const char* filename, unsigned char *data, const unsigned int ancho, const unsigned int alto, unsigned char bpp ){
	int Y;
	unsigned int X,STEP;
	unsigned char BPP, BYTES_BAZURAS[3];
	if ( bpp<24 )bpp*=8;
	if ( !data ) return;
	const unsigned char padding = ( ( 4 - ( ancho * (bpp/8) ) % 4) % 4 );
	unsigned char header[14], informacionheader[ 40 ];
	_Memset( header, 0, ( sizeof(unsigned char) * 14 ) );
	_Memset( informacionheader, 0, ( sizeof(unsigned char) * 40 ) );
	const unsigned int filesize = 14 + 40 + ancho * alto * (bpp/8) + padding * ancho;
	header[0] = 'B',header[1] = 'M';
	header[2] = filesize, header[3] = filesize >> 8, header[4] = filesize >> 16, header[5] = filesize >> 24;
	header[10] = 14 + 40;
	informacionheader[0] = 40;
	informacionheader[4] = ancho, informacionheader[5] = ancho >> 8, informacionheader[6] = ancho >> 16, informacionheader[7]  = ancho >> 24;
	informacionheader[8] = alto,  informacionheader[9] = alto >> 8, informacionheader[10] = alto >> 16,  informacionheader[11] = alto >> 24;
	informacionheader[12] = 1, informacionheader[14] = bpp;
	FILE *f = fopen( filename, "wb" );
	fwrite( header, 14, 1, f );
	fwrite( informacionheader, 40, 1, f );
	BPP = (bpp/8);
	for ( Y = alto-1; Y >=0 ; --Y){
		for ( X = 0; X < ancho; ++X) STEP = ( Y * ancho + X ) * BPP, fwrite( &data[ STEP ], BPP, 1, f );
		fwrite( BYTES_BAZURAS, padding, 1, f );
	}
	fclose(f),f=NULL;
	return;
}


void GuardarBufferV( const char Name[] ){
	SaveBMP( Name, (unsigned char*)vbuff, wbuff, hbuff, 32 );
}





// Apartado de dibujado.

void Punto( int x, int y, int c ){
	vbuff[ y * wbuff + x ] = c;
}

#define _MAX(A,B) ( (A) > (B) ? (A) : (B) )


void Linea( int x0, int y0, int x1, int y1, int c ){
	int LEN;

	float SLPX = ( x1 - x0 );
	float SLPY = ( y1 - y0 );

	LEN = _MAX( abs(SLPX), abs(SLPY) );

	SLPX = SLPX / LEN;
	SLPY = SLPY / LEN;

	float X = x0;
	float Y = y0;

	for (int i = 0; i < LEN; ++i)
	{
		Punto( X, Y, c );
		X+=SLPX;
		Y+=SLPY;
	}
}


RGBA_ _RGBA_(unsigned char R, unsigned char G, unsigned char B, unsigned char A ){
	RGBA_ _C;
	_C.ARGB[0] = R;
	_C.ARGB[1] = G;
	_C.ARGB[2] = B;
	_C.ARGB[3] = A;
	return _C;
}



void LineaLerp( int x0, int y0, int x1, int y1, RGBA_ c0, RGBA_ c1 ){
	int LEN;

	float SLPX = ( x1 - x0 );
	float SLPY = ( y1 - y0 );

	LEN = _MAX( abs(SLPX), abs(SLPY) );

	SLPX = SLPX / LEN;
	SLPY = SLPY / LEN;

	float X = x0;
	float Y = y0;

	float R0 = c0.ARGB[0] & 0xff;
	float G0 = c0.ARGB[1] & 0xff;
	float B0 = c0.ARGB[2] & 0xff;
	float A0 = c0.ARGB[3] & 0xff;
	
	float R1 = c1.ARGB[0] & 0xff;
	float G1 = c1.ARGB[1] & 0xff;
	float B1 = c1.ARGB[2] & 0xff;
	float A1 = c1.ARGB[3] & 0xff;


	R1 = (R1-R0) / LEN;
	G1 = (G1-G0) / LEN;
	B1 = (B1-B0) / LEN;
	A1 = (A1-A0) / LEN;

	for (int i = 0; i < LEN; ++i)
	{
		// Punto( X, Y, *(int*)&c0.ARGB );
		unsigned char R_,G_,B_,A_;
		R_ = (unsigned char)R0;
		G_ = (unsigned char)G0;
		B_ = (unsigned char)B0;
		A_ = (unsigned char)A0;
		Punto( X, Y, ( R_<<16 | G_<<8 | B_<<0 | A_<<24 ) );
		X+=SLPX;
		Y+=SLPY;
		R0+=R1;
		G0+=G1;
		B0+=B1;
		A0+=A1;
	}
}



void Imagen2D( int x, int y, void *data, int w, int h ){

	register int *Dat = (int*)data;

	for (int i = 0; i < h; ++i)
	{
		for (int o = 0; o < w; ++o)
		{
			Punto( o+x,i+y, *Dat++ );
		}
	}
}


void ImageRenderLoad( ImageRender *X, const char Name[] ){
	FILE* f = fopen(Name,"rb");
	fread( &X->w, 1, sizeof(int), f );
	fread( &X->h, 1, sizeof(int), f );
	const unsigned int Len = X->w * X->h;
	X->d = (int*)malloc( Len * sizeof(int) );
	fread( X->d, 1, sizeof(int)*Len, f );
	fclose(f);
	f=NULL;
}


void ImageRenderFree( ImageRender *X ){
	free(X->d);
	X->d=NULL;
	X->w=X->h=0;
}


void ImageRenderDraw( ImageRender *X, int x0, int y0 ){
	register int *Dat = (int*)X->d;

	for (int i = 0; i < X->h; ++i)
	{
		for (int o = 0; o < X->w; ++o)
		{
			Punto( o+x0,i+y0, *Dat++ );
		}
	}
}


int __fastcall ImageRenderGetP( ImageRender *X, int x0, int y0 ){
	register int *Dat = (int*)X->d;
	if( (unsigned int)x0 >= X->w || (unsigned int)y0 >= X->h ) return 0;
	return Dat[ y0 * X->w + x0 ];
}



void __fastcall ImageRenderSetP( ImageRender *X, int x0, int y0, int c ){
	register int *Dat = (int*)X->d;
	if( (unsigned int)x0 >= X->w || (unsigned int)y0 >= X->h ) return;
	Dat[ y0 * X->w + x0 ] = c;
}


void ImageRenderDrawRCT( ImageRender *X, int x0, int y0, int x1, int y1 ){
	if( x1 < x0 ) x1^=x0, x0^=x1, x1^=x0;
	if( y1 < y0 ) y1^=y0, y0^=y1, y1^=y0;
	int x_,y_;
	for (int y = y0; y < y1; ++y)
	{
		y_=( X->h * y / abs(y1-y0) );
		for (int x = x0; x < x1; ++x)
		{
			x_=( X->w * x / abs(x1-x0) );
			Punto( x,y,ImageRenderGetP( X,x_,y_) );
		}
	}
}



void LineaTexture( int x0, int y0, int x1, int y1, int u0, int v0, int u1, int v1, ImageRender *X ){
	int LEN;

	float SLPX = ( x1 - x0 );
	float SLPY = ( y1 - y0 );
	
	float SLPU = ( u1 - u0 );
	float SLPV = ( v1 - v0 );

	LEN = _MAX( abs(SLPX), abs(SLPY) );

	SLPX = SLPX / LEN;
	SLPY = SLPY / LEN;
	
	SLPU = SLPU / LEN;
	SLPV = SLPV / LEN;

	float X_ = x0;
	float Y_ = y0;
	
	float U_ = u0;
	float V_ = v0;

	for (int i = 0; i < LEN; ++i)
	{
		Punto( X_, Y_, ImageRenderGetP( X, U_,V_) );
		X_+=SLPX;
		Y_+=SLPY;
		U_+=SLPU;
		V_+=SLPV;
	}
}



void __attribute__((constructor)) CerrarBuffer( void ){

	free( vbuff );

	vbuff = NULL;

	wbuff = hbuff = 0;

}