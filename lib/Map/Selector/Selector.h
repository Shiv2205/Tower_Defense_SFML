#ifndef SELECTOR_H
#define SELECTOR_H

#include "Util/Sfml_Util.h"
#include "Util/Util.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/VertexArray.hpp>

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