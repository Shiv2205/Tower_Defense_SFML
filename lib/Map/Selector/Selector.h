#ifndef SELECTOR_H
#define SELECTOR_H

#include "Util/Sfml_Util.h"
#include "Util/Util.h"

class Selector : public sf::Drawable, public sf::Transformable
{
public:
  Selector( void );

  ~Selector( void );

  Position getPos( void ) const;

  void setPos( const Position& pos );

private:
  void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

  sf::VertexArray selector;
  sf::Color       color;
  Position        pos;
};

#endif // SELECTOR_H