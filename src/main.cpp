#include "main.h"

void buildPath( Map& my_map );

enum GameState
{
  MAP_INIT,
  PATH_BUILDER
};

int main()
{
  auto window = sf::RenderWindow( sf::VideoMode( { SCREEN_W, SCREEN_H } ), "Tower Defense SFML" );
  window.setVerticalSyncEnabled( true );
  // window.setFramerateLimit(144);

  GameState game_state = PATH_BUILDER;

  // Text
  sf::Font font;
  loadFont( font );
  sf::Text my_text( font, "Map Creator", 26 );
  my_text.setPosition( { 640.f, 0.f } );

  Dimension map_dim( 20, 20 );
  TileMap   my_map( map_dim );
  Vec_2f    map_pos;

  // Selector
  Selector selector;

  // buildPath( my_map );

  if ( ! my_map.LoadScenery() )
  {
    return EXIT_FAILURE;
  }

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
    if ( reload )
    {
      reload = false;
    }
    window.draw( my_map );
    window.draw( selector );
    window.display();
  }
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

  case ENTER:
    LOG( "Enter pressed" );
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
    if ( ! my_map.LoadScenery() )
    {
      LOG( "Failed to load map" );
    }
    break;

  default:
    break;
  }

  if ( ( key_code == UP || key_code == DOWN || key_code == LEFT || key_code == RIGHT ) && ( draw_path ) )
  {
    if ( ! my_map.MakePath( new_pos ) )
    {
      LOG( "Invalid position: " + new_pos.show() );
    }
    if ( ! my_map.LoadScenery() )
    {
      LOG( "Failed to load map" );
    }
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

void buildPath( Map& my_map )
{
  Position entry( 0, 6 );
  if ( ! my_map.MakePath( entry, true ) )
  {
    LOG( "Invalid position: " + entry.show() );
  }

  Position exit( 14, 19 );
  if ( ! my_map.MakePath( exit, false, true ) )
  {
    LOG( "Invalid position: " + exit.show() );
  }

  for ( u_32 i = 1; i < 15; i++ )
  {
    Position path( i, 6 );
    if ( ! my_map.MakePath( path ) )
    {
      LOG( "Invalid position: " + path.show() );
    }
  }

  for ( u_32 i = 7; i < 19; i++ )
  {
    Position path( 14, i );
    if ( ! my_map.MakePath( path ) )
    {
      LOG( "Invalid position: " + path.show() );
    }
  }
}

// map_pos.x = 0; //( SCREEN_W - ( map_dim.width * 32 ) ) / 2;
// map_pos.y = 0; //( SCREEN_H - ( map_dim.height * 32 ) ) / 2;
// my_map.setPosition( map_pos );