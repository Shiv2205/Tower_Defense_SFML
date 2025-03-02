#include "main.h"

int main()
{
  auto window = sf::RenderWindow( sf::VideoMode( { SCREEN_W, SCREEN_H } ), "CMake SFML Project" );
  window.setVerticalSyncEnabled( true );
  // window.setFramerateLimit(144);

  // Text
  sf::Font font;
  loadFont( font );
  sf::Text my_text( font, "Hello World", 26 );

  // Image
  // sf::Texture img_texture;
  // loadTexture( img_texture, img_path );
  // sf::Sprite my_sprite( img_texture );

  // sf::Vector2i position( 0, 128 );
  // sf::Vector2i size( 32, 32 );
  // sf::IntRect  sprite_rect( position, size );
  // my_sprite.setTextureRect( sprite_rect );

  Dimension map_dim( 20, 20 );
  TileMap   my_map( map_dim );
  Vec_2f    map_pos;

  //map_pos.x = 0; //( SCREEN_W - ( map_dim.width * 32 ) ) / 2;
  //map_pos.y = 0; //( SCREEN_H - ( map_dim.height * 32 ) ) / 2;
  //my_map.setPosition( map_pos );

  // Selector
  sf::VertexArray selector;
  selector.setPrimitiveType( sf::PrimitiveType::Triangles );
  selector.resize( 6 );

  sf::Vertex* selector_vts = &selector[ 0 ];
  sf::Color   selector_color( 255, 255, 255, 200 );
  Position    selector_pos( 0, 6 );
  for ( u_32 i = 0; i < 6; i++ )
  {
    selector_vts[ i ].color = selector_color;
  }
  InitVertices( selector_vts, selector_pos );
  

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

  if ( ! my_map.LoadScenery() )
  {
    return EXIT_FAILURE;
  }

  std::string user_in = "";
  while ( window.isOpen() )
  {
    event_handler( window, user_in );

    window.clear( sf::Color::Black );

    // window.draw(my_text);
    window.draw( my_map );
    window.draw( selector );
    window.display();
  }
}

void event_handler( sf::RenderWindow& window, std::string& user_in )
{
  while ( const std::optional event = window.pollEvent() )
  {
    if ( event->is<sf::Event::Closed>() )
    {
      window.close();
    }
    if ( const auto* text_entered = event->getIf<sf::Event::TextEntered>() )
    {
      if ( text_entered->unicode < 128 )
      {
        user_in += static_cast<char>( text_entered->unicode );
      }
      std::cout << "User Typed: " << user_in << std::endl;
    }
  }
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