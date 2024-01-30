#ifndef __TarjetaVideo_H__
#define __TarjetaVideo_H__
#ifdef __cplusplus
extern "C"{
#endif


void CrearBuffer( const int w, const int h );
void CerrarBuffer( void );

void GuardarBufferV( const char Name[] );


// Apartado de ediciones.

void Punto( int x, int y, int c );

void Linea( int x0, int y0, int x1, int y1, int c );


#ifdef __cplusplus
}
#endif
#endif