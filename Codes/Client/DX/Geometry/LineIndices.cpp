#include "PCH.h"
#include "LineIndices.h"

LineIndices::LineIndices()
{
	i1 = 0;
	i2 = 0;
}

LineIndices::LineIndices( unsigned int I1, unsigned int I2 )
{
	i1 = I1;
	i2 = I2;
}

LineIndices::~LineIndices()
{
}

LineIndices& LineIndices::operator= ( const LineIndices& Line )
{
	i1 = Line.i1;
	i2 = Line.i2;

	return( *this );
}

void LineIndices::swap12( )
{
	unsigned int swap = i1;
	i1 = i2;
	i2 = swap;
}