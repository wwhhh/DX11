#pragma once

class Vector2f
{
public:
	Vector2f( );
	Vector2f( float x, float y );
	Vector2f( const Vector2f& Vector );

	// vector operations
	void Clamp( );
	void MakeZero( );
	void Normalize( );
	float Magnitude( );

	// assignment
	Vector2f& operator= ( const Vector2f& Vector );

	// accessors
	float operator[] ( int iPos ) const;
	float& operator[] ( int iPos );

	// boolean comparison
	bool operator== ( const Vector2f& Vector ) const;
	bool operator!= ( const Vector2f& Vector ) const;

	// arithmetic operations
	Vector2f operator+ ( const Vector2f& Vector ) const;
	Vector2f operator- ( const Vector2f& Vector ) const;
	Vector2f operator* ( const Vector2f& Vector ) const;
	Vector2f operator* ( float fScalar ) const;
	Vector2f operator/ ( float fScalar ) const;
	Vector2f operator- ( ) const;

	// arithmetic updates
	Vector2f& operator+= ( const Vector2f& Vector );
	Vector2f& operator-= ( const Vector2f& Vector );
	Vector2f& operator*= ( float fScalar );
	Vector2f& operator/= ( float fScalar );

public:
	float x;
	float y;
};
