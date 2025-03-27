#include "TileCritters.h"
#include "Map/Cell/Path.h"

                                    // ! REPLACE WITH this->getWaveNumber()
TileCritters::TileCritters( void ) : CritterGroup( 4, { 0, 0 } ), TileLayer( getCritterTexPath(), CRITTER_TEX_POS, CRITTER_TEX_SIZE )
{
}

bool TileCritters::Load( void )
{
  bool layer_loaded = TileLayer::Load();
  
  if ( ! layer_loaded )
  {
    return false;
  }
  
  sf::VertexArray critter_tiles;
  critter_tiles.setPrimitiveType( sf::PrimitiveType::Triangles );
  critter_tiles.resize( ( this->getWaveNumber() * 2 ) * 6 );

  this->setLayerVertices( critter_tiles );

  return true;
}

void TileCritters::WaveInit()
{
  int size = this->getCritters().size();

  for ( int i = 0; i < size; i++ )
  {
    InitCritterPos( i );
  }
}

void TileCritters::WaveMove()
{
  int size = this->getCritters().size();

  for ( int i = 0; i < size; i++ )
  {
    sf::Vertex* critter_vts = this->getLayerVertex( (u_32)( i * 6 ) );
    MoveCritter( critter_vts, i );
  }
}

void TileCritters::InitCritterPos( int critter_idx )
{
  int      offset_x = 0;
  int      offset_y = 0;
  Position entry    = this->getEntryPoint();

  this->CalculateOffset( offset_x, offset_y );
  int row = entry.row + ( offset_y * ( critter_idx + 1 ) );
  int col = entry.col + ( offset_x * ( critter_idx + 1 ) );

  Position crit_pos( row, col );

  this->RegisterTile( critter_idx * 6, crit_pos );
}

void TileCritters::MoveCritter( sf::Vertex* critter_vts, int critter_idx )
{
  static Path lobby_cell;

  Critter* curr_critter = this->getCritters().at( critter_idx ); // Pointer to current Critter
  Position entry_pos    = this->getEntryPoint();                 // Retrieve Entry position
  Position critter_pos  = curr_critter->getPosition();           // Retrieve position of current Critter
  float    move_speed   = curr_critter->getSpeed() / 5.f;        // Calculate move speed of current Critter
  Vec_2f   increment    = { 0, 0 };                              // Vector to store increment by which Critter should move

  Position target_pos;

  if ( Position( 0, 0 ) == critter_pos )
  {
    if ( nullptr == curr_critter->getCurrCell() )
    { // * Dock Critters at lobby Path cell on init
      curr_critter->setCurrCell( &lobby_cell );
      lobby_cell.setNextPath( this->getEntryCell() );
    }
    target_pos = entry_pos;
  }
  else
  {
    target_pos = curr_critter->getCurrCell()->getNext();
  }

  if ( Position( 0, 0 ) == critter_pos )
  { // ? If position is default, move Critter towards entry cell
    int x = 0, y = 0;
    this->CalculateOffset( x, y );
    float direction_x = x * -1.0f;
    float direction_y = y * -1.0f;

    increment = { direction_x, direction_y };
  }
  else
  { // ? If not default, calculate direction based on current position
    CalculateIncrement( critter_pos, target_pos, increment );
  }

  for ( int i = 0; i < 6; i++ )
  { // ? Increment position of Critter vertices
    critter_vts[ i ].position += { ( increment.x * move_speed ), ( increment.y * move_speed ) };
  }

  if ( IsCritterOnCell( critter_vts[ 0 ].position, target_pos ) )
  { // ? Is the Critter on the target cell
    curr_critter->setPosition( target_pos );
    curr_critter->setCurrCell( curr_critter->getCurrCell()->getNextPath() );
  }
}

const std::string TileCritters::getCritterTexPath( void ) const
{
  std::string tex_path        = CRITTER_TEXTURE;
  int         wave_num        = this->getWaveNumber();
  int         critter_res_num = 6;                              //? Number of Critter resources in res/ folder
  int         critter_res_idx = ( wave_num % critter_res_num ); //? Index of the Critter resource

  if ( critter_res_idx == 0 )
  {
    critter_res_idx = critter_res_num;
  }

  tex_path += std::to_string( critter_res_idx ) + ".png";

  return tex_path;
}

TileCritters::~TileCritters( void ) {}

void TileCritters::CalculateOffset( int& offset_x, int& offset_y ) const
{
  Position entry        = this->getEntryPoint();
  u_32     row          = entry.row;
  u_32     col          = entry.col;
  Vec_2u   layer_bounds = TileLayer::getBoundaries();

  if ( col == 0 )
  { // * Left
    offset_x = -1;
    offset_y = 0;
  }
  else if ( col == layer_bounds.x )
  { // * Right
    offset_x = 1;
    offset_y = 0;
  }
  else if ( row == 0 )
  { // * Up
    offset_x = 0;
    offset_y = -1;
  }
  else if ( row == layer_bounds.y )
  { // * Down
    offset_x = 0;
    offset_y = 1;
  }
}

void TileCritters::CalculateIncrement( const Position& curr_pos, const Position& next_pos, Vec_2f& increment ) const
{
  // ? Move Logic
  if ( next_pos.col < curr_pos.col )
  { // * Left
    increment = { -1, 0 };
  }
  else if ( next_pos.col > curr_pos.col )
  { // * Right
    increment = { 1, 0 };
  }
  else if ( next_pos.row < curr_pos.row )
  { // * Up
    increment = { 0, -1 };
  }
  else if ( next_pos.row > curr_pos.row )
  { // * Down
    increment = { 0, 1 };
  }
}
