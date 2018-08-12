#pragma once

class Vector2f;
class Vector3f;

class Vector4f
{
public:
	Vector4f( );
	Vector4f( float x, float y, float z, float w );
    Vector4f( const Vector3f& vector, float w );
	Vector4f( const Vector4f& Vector );

	// vector operations
	void Clamp( );
	float Dot( Vector4f& vector );
	void MakeZero( );
	void Normalize( );
	float Magnitude( );

	// Operators
	Vector4f& operator= ( const Vector4f& Vector );

	// member access
	float operator[] ( int iPos ) const;
	float& operator[] ( int iPos );

	// comparison
	bool operator== ( const Vector4f& Vector ) const;
	bool operator!= ( const Vector4f& Vector ) const;

	// arithmetic operations
	Vector4f operator+ ( const Vector4f& Vector ) const;
	Vector4f operator- ( const Vector4f& Vector ) const;
	Vector4f operator* ( float fScalar ) const;
    Vector4f operator* ( const Vector4f& Vector ) const;
	Vector4f operator/ ( float fScalar ) const;
    Vector4f operator/ ( const Vector4f& Vector ) const;
	Vector4f operator- ( ) const;

	// arithmetic updates
	Vector4f& operator+= ( const Vector4f& Vector );
	Vector4f& operator-= ( const Vector4f& Vector );
	Vector4f& operator*= ( float fScalar );
    Vector4f& operator*= ( const Vector4f& Vector );
	Vector4f& operator/= ( float fScalar );
    Vector4f& operator/= ( const Vector4f& Vector );

	unsigned int toARGB( );
	unsigned int toRGBA( );
	void fromARGB( unsigned int color );

	Vector3f xyz() const;
	Vector2f xy() const;

public:
	float x;
	float y;
	float z;
	float w;
};
