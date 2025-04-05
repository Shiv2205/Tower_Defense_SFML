#include "MiniEngine.h"
#include <SFML/Graphics.hpp>


// Define Global variables
bool      reload       = true;
bool      draw_path    = false;
bool      is_entry_set = false;
bool      is_exit_set  = false;
bool      validate_map = false;
bool      map_is_valid = false;
GameState game_state   = PATH_BUILDER;
//circle 
sf::CircleShape Engine::range_circle;
bool Engine::show_range = false;
int Engine::selected_tower_range = 0;
bool Engine::tower_selected = false;


Window      Engine::game_window;
sf::Font    Engine::font; // Text
sf::Text    Engine::my_text( font, "Map Creator", 26 );
TileMap     Engine::my_map;                        // Subjects
MapObserver Engine::map_obs;                       // Observers
Selector    Engine::selector;                      // Cell Selector
Dimension   Engine::map_dim = Dimension( 25, 25 ); // Set Map dimensions

void Engine::gameInit( void )
{
  TileLayer::setBoundaries( { map_dim.width, map_dim.height } ); //? Set the boundaries for all layers which completely overlap Map
  TileLayerFactory layer_factory;

  loadFont( font );
  my_text.setPosition( { ( map_dim.width * 32.f ), 0.f } );

  // Add TileLayers to TileMap
  my_map.getLayerReg()->addToRegistry( TileType::PATH );
  my_map.getLayerReg()->addToRegistry( TileType::TOWERS );
  my_map.getLayerReg()->addToRegistry( TileType::CRITTERS );

  // Attach Observers
  my_map.attach( &map_obs );

  // Set Map dimensions
  my_map.setDimensions( map_dim );

  // Attach Drawables
  game_window.addContent( &my_map );
  game_window.addContent( my_map.getLayerReg()->getLayerOf<TilePath*>() );
  game_window.addContent( my_map.getLayerReg()->getLayerOf<TileTowers*>() );
  game_window.addContent( my_map.getLayerReg()->getLayerOf<TileCritters*>() );
  game_window.addContent( &selector );
  game_window.addContent( &my_text );
}

void Engine::gameLoop( void )
{
  while ( game_window.isOpen() )
  {
    while ( const std::optional event = game_window.pollEvent() )
    {
      if ( event->is<sf::Event::Closed>() )
      {
        game_window.close();
      }
      if ( const auto* released_key = event->getIf<sf::Event::KeyReleased>() )
      {
        keyboardListener( released_key );
      }
    }

    if ( game_state == GameState::TEST_CRITTERS )
    {
      gameFlowTck();
    }

    game_window.clear( sf::Color::Black );

    game_window.drawContents();
if (show_range)
{
    Position pos = selector.getPos();
    float tile_size = 32.f;

    float range = static_cast<float>(selected_tower_range);
    float center_x = pos.col * tile_size + tile_size / 2;
    float center_y = pos.row * tile_size + tile_size / 2;

    range_circle.setRadius(range);
    range_circle.setOrigin({ range, range });
    range_circle.setPosition({ center_x, center_y });

    range_circle.setFillColor(sf::Color(255, 0, 0, 80));  // Semi-transparent red
    range_circle.setOutlineColor(sf::Color::Red);
    range_circle.setOutlineThickness(2.f);

    game_window.draw(range_circle);
}

    game_window.display();
  }

  // Detach Map Observer
  my_map.detach( &map_obs );
}

void Engine::loadFont( sf::Font& font )
{
  if ( ! font.openFromFile( font_path ) )
  {
    LOG( "Error loading font" );
  }
}

void Engine::keyboardListener( const sf::Event::KeyReleased* released_key )
{
  sf::Keyboard::Scancode key_code = released_key->scancode;

  movementHandler( key_code );

  mapCreatorTck( key_code );

  reload = true;
}

void Engine::mapCreatorTck( const sf::Keyboard::Scancode& key_code )
{

  switch ( game_state )
  {
  case PATH_BUILDER:
    buildPathHandler( key_code );
    break;

  case TOWER_OPS:
    // TODO: Show Tower Options menu
    addTowerHandler( key_code );
    break;

  case VALIDATE:
    map_is_valid = my_map.ValidatePath();
    std::cout << "Map is " << ( map_is_valid ? "valid" : "not valid" ) << std::endl;
    break;

  default:
    break;
  }

  switch ( game_state )
  {
  case PATH_BUILDER:
    if ( ( is_exit_set ) && ( is_entry_set ) )
    {
      game_state = GameState::TOWER_OPS;
    }
    break;

  case TOWER_OPS:
    if ( validate_map )
    {
      game_state = GameState::VALIDATE;
    }
    break;

  case VALIDATE:
    if ( map_is_valid )
    {
      game_state = GameState::TEST_CRITTERS;
    }
    break;

  default:
    break;
  }
}

void Engine::buildPathHandler( const sf::Keyboard::Scancode& key_code )
{
  Position new_pos( selector.getPos() );
  bool     is_arrow_key = key_code == UP || key_code == DOWN || key_code == LEFT || key_code == RIGHT;

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
      my_map.setExit( new_pos );
      draw_path   = false;
      is_exit_set = true;
    }
  }
}

void Engine::addTowerHandler(const sf::Keyboard::Scancode& key_code)
{
    Position new_pos( selector.getPos() );

    // Select tower and show range circle
    if ( key_code == ICE )
    {
        selected_tower_range = IceTower().getRange();
        show_range = true;
        tower_selected = true;
    }
    else if ( key_code == POISON )
    {
        selected_tower_range = PoisonTower().getRange();
        show_range = true;
        tower_selected = true;
    }
    else if ( key_code == ELECTRIC )
    {
        selected_tower_range = ElectricTower().getRange();
        show_range = true;
        tower_selected = true;
    }

    // Confirm placement with ENTER
    else if ( key_code == ENTER && tower_selected )
    {
        bool placed = false;

        if (selected_tower_range == IceTower().getRange())
            placed = my_map.AddTower(new_pos, new IceTower());
        else if (selected_tower_range == PoisonTower().getRange())
            placed = my_map.AddTower(new_pos, new PoisonTower());
        else if (selected_tower_range == ElectricTower().getRange())
            placed = my_map.AddTower(new_pos, new ElectricTower());

        if (!placed)
            LOG("Invalid position for Tower: " + new_pos.show());

        // Turn off range circle after placing
        show_range = false;
        tower_selected = false;
    }

    else if ( VALIDATE_MAP == key_code )
    {
        validate_map = true;
    }
}


void Engine::movementHandler( const sf::Keyboard::Scancode& key_code )
{
  Dimension limits = my_map.getDimensions();
  Position  new_pos( selector.getPos() );

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
}

void Engine::gameFlowTck( void ) 
{
  switch (game_state)
  {
    case TEST_CRITTERS:
    my_map.getLayerReg()->getLayerOf<TileCritters*>()->WaveMove();
    break;
  
  default:
    break;
  }
}