#include "main.h"

int main()
{
  auto window = sf::RenderWindow( sf::VideoMode( { SCREEN_W, SCREEN_H } ), "Tower Defense SFML" );
  window.setVerticalSyncEnabled( true );
  // window.setFramerateLimit(144);

  // Text
  sf::Font font;
  loadFont( font );
  sf::Text my_text( font, "Map Creator", 26 );
  my_text.setPosition( { 640.f, 0.f } );

  // Observers
  MapObserver map_obs;

  // Subjects
  TileMap my_map;

  // Attach Observers
  my_map.addObserver( &map_obs );

  // Cell Selector
  Selector selector;

  // Set Map dimensions
  Dimension map_dim( 25, 25 );
  my_map.setDimensions( map_dim );

  std::string user_in = "";
  while ( window.isOpen() )
  {
    while ( const std::optional event = window.pollEvent() )
    {
      if ( event->is<sf::Event::Closed>() )
      {
        window.close();
      }
      if ( const auto* released_key = event->getIf<sf::Event::KeyReleased>() )
      {
        keyboardListener( released_key, selector, my_map );
      }
    }

    // window.draw( my_text );
    window.clear( sf::Color::Black );

    window.draw( my_map );
    window.draw( selector );

    window.display();
  }

  my_map.removeObserver( &map_obs );
}

void keyboardListener( const sf::Event::KeyReleased* released_key, Selector& selector, TileMap& my_map )
{
  sf::Keyboard::Scancode key_code = released_key->scancode;
  Dimension              limits   = my_map.getDimensions();
  Position               new_pos( selector.getPos() );

  switch ( key_code )
  {
  case LEFT:
    if ( new_pos.col > 0 )
    {
      new_pos.col--;
      selector.setPos( new_pos );
    }
    break;

  case RIGHT:
    if ( new_pos.col < ( limits.width - 1 ) )
    {
      new_pos.col++;
      selector.setPos( new_pos );
    }
    break;

  case UP:
    if ( new_pos.row > 0 )
    {
      new_pos.row--;
      selector.setPos( new_pos );
    }
    break;

  case DOWN:
    if ( new_pos.row < ( limits.height - 1 ) )
    {
      new_pos.row++;
      selector.setPos( new_pos );
    }
    break;

  default:
    break;
  }

  switch ( game_state )
  {
  case PATH_BUILDER:
    buildPathHandler( key_code, my_map, new_pos );
    break;

  default:
    break;
  }

  reload = true;
}

void loadFont( sf::Font& font )
{
  if ( ! font.openFromFile( font_path ) )
  {
    LOG( "Error loading font" );
  }
}

void loadTexture( sf::Texture& texture, std::string texture_path )
{
  if ( ! texture.loadFromFile( texture_path ) )
  {
    LOG( "Error loading texture" );
  }
}

void buildPathHandler( const sf::Keyboard::Scancode& key_code, Map& my_map, const Position& new_pos )
{
  bool is_arrow_key = key_code == UP || key_code == DOWN || key_code == LEFT || key_code == RIGHT;

  if ( ( is_arrow_key ) && ( draw_path ) )
  {
    if ( ! my_map.MakePath( new_pos ) )
    {
      LOG( "Invalid position: " + new_pos.show() );
    }
  }
  else if ( ENTER == key_code )
  {
    if ( ! is_entry_set )
    {
      if ( ! my_map.MakePath( new_pos, true ) )
      {
        LOG( "Invalid position: " + new_pos.show() );
      }
      draw_path    = true;
      is_entry_set = true;
    }
    else if ( ! is_exit_set )
    {
      if ( ! my_map.MakePath( new_pos, false, true ) )
      {
        LOG( "Invalid position: " + new_pos.show() );
      }
      draw_path   = false;
      is_exit_set = true;
    }
  }
}

// Vec_2f    map_pos;
// map_pos.x = 0; //( SCREEN_W - ( map_dim.width * 32 ) ) / 2;
// map_pos.y = 0; //( SCREEN_H - ( map_dim.height * 32 ) ) / 2;
// my_map.setPosition( map_pos );