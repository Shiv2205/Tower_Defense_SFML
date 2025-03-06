#include "Window.h"

Window::Window( void ) : sf::RenderWindow( sf::VideoMode( { SCREEN_W, SCREEN_H } ), W_TITLE )
{
  this->setVerticalSyncEnabled( true );
}

Window::~Window( void )
{
}

void Window::addContent( const sf::Drawable& window_content )
{
  this->contents.push_back( window_content );
}

void Window::removeContent( const sf::Drawable& window_content )
{
  auto begin  = this->contents.begin();
  auto end    = this->contents.end();
  auto target = std::find( begin, end, window_content );

  if ( end != target )
  {
    this->contents.erase( target );
  }
}

void Window::drawContents( void )
{
  for ( const sf::Drawable& content : this->contents )
  {
    this->draw( content );
  }
}