#include "Selector.h"

Selector::Selector( void ) : color( sf::Color( 255, 255, 255, 200 ) ), pos( Position( 0, 0 ) )
{
  this->selector.setPrimitiveType( sf::PrimitiveType::Triangles );
  this->selector.resize( 6 );

  for ( u_32 i = 0; i < 6; i++ )
  {
    this->selector[ i ].color = this->color;
  }

  InitVertices( &this->selector[ 0 ], this->pos );
}

Selector::~Selector( void )
{
}

Position Selector::getPos() const
{
  return this->pos;
}

void Selector::setPos( const Position& pos )
{
  this->pos = pos;
  InitVertices( &this->selector[ 0 ], this->pos );
}

void Selector::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  // apply the transform
  states.transform *= getTransform();

  // draw the scenery vertex array
  target.draw( this->selector, states );
}
