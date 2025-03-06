#ifndef WINDOW_H
#define WINDOW_H

#include "Util/Sfml_Util.h"
#include <algorithm>
#include <vector>

#define W_TITLE "Tower Defense SFML"

class Window : public sf::RenderWindow
{
public:
  Window( void );

  ~Window( void );

  void addContent( const sf::Drawable* window_content );

  void removeContent( const sf::Drawable* window_content );

  void drawContents( void );

private:
  std::vector<const sf::Drawable*> contents;
};

#endif // WINDOW_H