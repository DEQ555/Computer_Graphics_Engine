#ifndef __TarjetaVideo_H__
#define __TarjetaVideo_H__
#ifdef __cplusplus
extern "C"{
#endif

void CrearBuffer( const int w, const int h );
void CerrarBuffer( void );

void GuardarBufferV( const char Name[] );


// Apartado de ediciones.
typedef struct{ unsigned char ARGB[4]; }RGBA_;

RGBA_ _RGBA_(unsigned char R, unsigned char G, unsigned char B, unsigned char A );

void Punto( int x, int y, int c );

void Linea( int x0, int y0, int x1, int y1, int c );

void LineaLerp( int x0, int y0, int x1, int y1, RGBA_ c0, RGBA_ c1 );

void Imagen2D( int x, int y, void *data, int w, int h );

typedef struct{
	int w,h;
	int* d;
}ImageRender;

void ImageRenderLoad( ImageRender *X, const char Name[] );
void ImageRenderFree( ImageRender *X );
void ImageRenderDraw( ImageRender *X, int x0, int y0 );


#ifdef __cplusplus
}
#endif
#endif