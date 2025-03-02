#include "TileMap.h"

TileMap::TileMap( void ) : Map()
{
}

TileMap::TileMap( const Dimension& dimensions )
    : Map( dimensions ), scene_tex_loaded( false ), path_tex_loaded( false )
{
}

TileMap::~TileMap( void )
{
}

bool TileMap::LoadScenery( void )
{
  this->scene_tex_loaded = this->LoadSceneryTexture();
  this->path_tex_loaded  = this->LoadPathTexture();

  if ( ! scene_tex_loaded || ! path_tex_loaded )
  {
    return false;
  }

  Dimension map = this->getDimensions();

  this->scene_vertices.setPrimitiveType( sf::PrimitiveType::Triangles );
  this->path_vertices.setPrimitiveType( sf::PrimitiveType::Triangles );
  this->scene_vertices.resize( map.width * map.height * 6 );
  this->path_vertices.resize( map.width * map.height * 6 );

  for ( u_32 row = 0; row < map.height; row++ )
  {
    for ( u_32 col = 0; col < map.width; col++ )
    {
      Position target_pos( row, col );
      Cell*    target_cell = this->FetchCell( target_pos );

      if ( Cell_Type::SCENERY == target_cell->getCellType() )
      {
        sf::Vertex* cell_vertices = &this->scene_vertices[ ( row + ( col * map.height ) ) * 6 ];

        // Set position of the 2 triangles' vertices to form Cell
        InitVertices( cell_vertices, target_pos );
      }
      else if ( Cell_Type::PATH == target_cell->getCellType() )
      {
        sf::Vertex* cell_vertices = &this->path_vertices[ ( row + ( col * map.height ) ) * 6 ];

        // Set position of the 2 triangles' vertices to form Cell
        InitVertices( cell_vertices, target_pos );
      }
    }
  }

  return true;
}

void TileMap::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  // apply the transform
  states.transform *= getTransform();

  // apply the scenery texture
  states.texture = &this->scene_texture;

  // draw the scenery vertex array
  target.draw( this->scene_vertices, states );

  // apply the path texture
  states.texture = &this->path_texture;

  // draw the path vertex array
  target.draw( this->path_vertices, states );
}

bool TileMap::LoadSceneryTexture( void )
{
  if ( ! this->scene_tex_loaded )
  {
    Vec_2i tile_size = { 32, 32 };
    Vec_2i position  = { 0, 128 };

    sf::IntRect tex_rect( position, tile_size );

    return this->scene_texture.loadFromFile( SCENERY_TEXTURE, false, tex_rect );
  }

  return this->scene_tex_loaded;
}

bool TileMap::LoadPathTexture( void )
{
  if ( ! this->path_tex_loaded )
  {
    Vec_2i tile_size = { 32, 32 };
    Vec_2i position  = { 0, 128 };

    sf::IntRect tex_rect( position, tile_size );

    return this->path_texture.loadFromFile( PATH_TEXTURE, false, tex_rect );
  }

  return this->path_tex_loaded;
}