

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




void __attribute__((constructor)) CerrarBuffer( void ){

	free( vbuff );

	vbuff = NULL;

}