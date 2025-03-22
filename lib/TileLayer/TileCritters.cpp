#include "TileCritters.h"
#include "Map/Cell/Path.h"

TileCritters::TileCritters( void ) : CritterGroup( 1, { 0, 0 } )
{
  this->critter_tiles.setPrimitiveType( sf::PrimitiveType::Triangles );
  this->critter_tiles.resize( ( this->getWaveNumber() * 2 ) * 6 );

  std::string layer_tex_path = "res/Custom/Enemy 15-1.png";
  Vec_2i      tile_pos       = { 0, 0 };
  Vec_2i      tile_size      = { 32, 32 };

  sf::IntRect tex_rect( tile_pos, tile_size );

  bool loaded = this->layer_texture.loadFromFile( layer_tex_path, false, tex_rect );
}

void TileCritters::WaveInit()
{
  int size = this->getCritters().size();

  for ( int i = 0; i < size; i++ )
  {
    sf::Vertex* critter_vts = &this->critter_tiles[ i * 6 ];
    InitCritterWave( critter_vts, i );
  }
}

void TileCritters::WaveMove()
{
  int size = this->getCritters().size();

  for ( int i = 0; i < size; i++ )
  {
    sf::Vertex* critter_vts = &this->critter_tiles[ i * 6 ];
    MoveCritterWave( critter_vts, i );
  }
}

void TileCritters::InitCritterWave( sf::Vertex* critter_vts, int critter_idx, Vec_2u coord )
{
  Vec_2i     tile_size = { 32, 32 };
  const u_32 x         = coord.x; // Coordinate x of the Top Left Corner of texture cell
  const u_32 y         = coord.y; // Coordinate y of the Top Left Corner of texture cell
  int        offset_x  = 0;
  int        offset_y  = 0;
  Position   entry     = this->getEntryPoint();

  this->CalculateOffset( offset_x, offset_y );
  int row = entry.row + ( offset_y * ( critter_idx + 1 ) );
  int col = entry.col + ( offset_x * ( critter_idx + 1 ) );

  critter_vts[ 0 ].position = Vec_2f( col * tile_size.x, row * tile_size.y );
  critter_vts[ 1 ].position = Vec_2f( ( col + 1 ) * tile_size.x, row * tile_size.y );
  critter_vts[ 2 ].position = Vec_2f( col * tile_size.x, ( row + 1 ) * tile_size.y );
  critter_vts[ 3 ].position = Vec_2f( col * tile_size.x, ( row + 1 ) * tile_size.y );
  critter_vts[ 4 ].position = Vec_2f( ( col + 1 ) * tile_size.x, row * tile_size.y );
  critter_vts[ 5 ].position = Vec_2f( ( col + 1 ) * tile_size.x, ( row + 1 ) * tile_size.y );

  critter_vts[ 0 ].texCoords = Vec_2f( x * tile_size.x, y * tile_size.y );
  critter_vts[ 1 ].texCoords = Vec_2f( ( x + 1 ) * tile_size.x, y * tile_size.y );
  critter_vts[ 2 ].texCoords = Vec_2f( x * tile_size.x, ( y + 1 ) * tile_size.y );
  critter_vts[ 3 ].texCoords = Vec_2f( x * tile_size.x, ( y + 1 ) * tile_size.y );
  critter_vts[ 4 ].texCoords = Vec_2f( ( x + 1 ) * tile_size.x, y * tile_size.y );
  critter_vts[ 5 ].texCoords = Vec_2f( ( x + 1 ) * tile_size.x, ( y + 1 ) * tile_size.y );
}

void TileCritters::MoveCritterWave( sf::Vertex* critter_vts, int critter_idx )
{
  Vec_2i   tile_size = { 32, 32 };
  Position entry_pos = this->getEntryPoint();

  Critter* curr_critter = this->getCritters().at( critter_idx );
  Position critter_pos  = curr_critter->getPosition();

  if ( critter_pos == Position( 0, 0 ) )
  {
    curr_critter->setPosition( entry_pos );
    curr_critter->setCurrCell( this->getEntryCell() );
  }

  if ( ( critter_vts[ 0 ].position.x == critter_pos.col * 32 ) ||
  ( critter_vts[ 0 ].position.y == critter_pos.row * 32 ) )
  {
    LOG("Vertex:" << critter_vts[ 0 ].position.x);
    LOG("Pos:" << critter_pos.col * 32);
    curr_critter->setPosition( curr_critter->getCurrCell()->getNext() );
    curr_critter->setCurrCell( curr_critter->getCurrCell()->getNextPath() );

    LOG(curr_critter->getPosition().show());
  }

  Vec_2f increment  = { 0, 0 };
  float  move_speed = curr_critter->getSpeed()/10.f;

  CalculateIncrement( critter_vts->position, critter_pos, increment );

  critter_vts[ 0 ].position += { ( increment.x * move_speed ), ( increment.y * move_speed ) };
  critter_vts[ 1 ].position += { ( increment.x * move_speed ), ( increment.y * move_speed ) };
  critter_vts[ 2 ].position += { ( increment.x * move_speed ), ( increment.y * move_speed ) };
  critter_vts[ 3 ].position += { ( increment.x * move_speed ), ( increment.y * move_speed ) };
  critter_vts[ 4 ].position += { ( increment.x * move_speed ), ( increment.y * move_speed ) };
  critter_vts[ 5 ].position += { ( increment.x * move_speed ), ( increment.y * move_speed ) };
}

TileCritters::~TileCritters( void )
{
}

void TileCritters::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  // apply the transform
  states.transform *= getTransform();

  // apply the texture
  states.texture = &this->layer_texture;

  // draw the vertex array
  target.draw( this->critter_tiles, states );
}

void TileCritters::CalculateOffset( int& offset_x, int& offset_y )
{
  Position entry = this->getEntryPoint();
  u_32     row   = entry.row;
  u_32     col   = entry.col;

  if ( col == 0 )
  {
    offset_x = -1;
    offset_y = 0;
  }
  else if ( col == 24 )
  {
    offset_x = 1;
    offset_y = 0;
  }
  if ( row == 0 )
  {
    offset_x = 0;
    offset_y = -1;
  }
  else if ( row == 24 )
  {
    offset_x = 0;
    offset_y = 1;
  }
}

void TileCritters::CalculateIncrement( const Vec_2f& vtx_pos, const Position& curr_pos, Vec_2f& increment )
{
  if ( vtx_pos.x > ( curr_pos.col * 32 ) )
  {
    increment = { -1, 0 };
  }
  else if ( vtx_pos.x < ( curr_pos.col * 32 ) )
  {
    increment = { 1, 0 };
  }
  else if ( vtx_pos.y > ( curr_pos.row * 32 ) )
  {
    increment = { 0, -1 };
  }
  else if ( vtx_pos.y < ( curr_pos.row * 32 ) )
  {
    increment = { 0, 1 };
  }
}