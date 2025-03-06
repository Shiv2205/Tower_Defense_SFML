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

bool TileMap::Load( void )
{
  this->scene_tex_loaded =
      this->LoadTexture( this->scene_tex_loaded, this->scene_texture, SCENERY_TEXTURE, { 0, 128 }, { 32, 32 }  );
  this->path_tex_loaded =
      this->LoadTexture( this->path_tex_loaded, this->path_texture, PATH_TEXTURE, { 0, 128 }, { 32, 32 }  );
  this->tower_tex_loaded =
      this->LoadTexture( this->tower_tex_loaded, this->tower_texture, TOWER_TEXTURE, { 0, 0 }, { 96, 32 } );

  if ( ! scene_tex_loaded || ! path_tex_loaded || ! tower_tex_loaded )
  {
    return false;
  }

  Dimension  map            = this->getDimensions();
  const u_32 NUM_GRID_CELLS = map.width * map.height * 6;

  this->scene_vertices.setPrimitiveType( sf::PrimitiveType::Triangles );
  this->path_vertices.setPrimitiveType( sf::PrimitiveType::Triangles );
  this->tower_vertices.setPrimitiveType( sf::PrimitiveType::Triangles );

  this->scene_vertices.resize( NUM_GRID_CELLS );
  this->path_vertices.resize( NUM_GRID_CELLS );
  this->tower_vertices.resize( NUM_GRID_CELLS );

  for ( u_32 row = 0; row < map.height; row++ )
  {
    for ( u_32 col = 0; col < map.width; col++ )
    {
      Position target_pos( row, col );
      Cell*    target_cell = this->FetchCell( target_pos );

      if ( Cell_Type::SCENERY == target_cell->getCellType() )
      {
        Scenery* scene_cell = static_cast<Scenery*>( target_cell );

        sf::Vertex* scene_cell_vertices = &this->scene_vertices[ ( row + ( col * map.height ) ) * 6 ];

        // Set position of the 2 triangles' vertices to form Cell
        InitVertices( scene_cell_vertices, target_pos );

        Tower* cell_tower = scene_cell->getTower();
        if ( nullptr != cell_tower )
        {
          sf::Vertex* tower_cell_vertices = &this->tower_vertices[ ( row + ( col * map.height ) ) * 6 ];
          std::string tower_name          = cell_tower->getName();

          if ( ICE_TOWER == tower_name )
          {
            InitVertices( tower_cell_vertices, target_pos );
          }
          else if ( POISON_TOWER == tower_name )
          {
            InitVertices( tower_cell_vertices, target_pos, { 1, 0 } );
          }
          else if ( ELEC_TOWER == tower_name )
          {
            InitVertices( tower_cell_vertices, target_pos, { 2, 0 } );
          }
        }
      }
      else if ( Cell_Type::PATH == target_cell->getCellType() )
      {
        sf::Vertex* path_cell_vertices = &this->path_vertices[ ( row + ( col * map.height ) ) * 6 ];

        // Set position of the 2 triangles' vertices to form Cell
        InitVertices( path_cell_vertices, target_pos );
      }
    }
  }

  return true;
}

void TileMap::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  // apply the transform
  states.transform *= getTransform();

  // apply the scenery texture and draw scenery vertex array
  this->drawComponent( this->scene_vertices, this->scene_texture, target, states );
  // apply the path texture and draw path vertex array
  this->drawComponent( this->path_vertices, this->path_texture, target, states );
  // apply the tower texture and draw tower vertex array
  this->drawComponent( this->tower_vertices, this->tower_texture, target, states );
}

void TileMap::drawComponent( const sf::VertexArray& vertices, const sf::Texture& texture,
                             sf::RenderTarget& target, sf::RenderStates states ) const
{
  // apply the texture
  states.texture = &texture;

  // draw the vertex array
  target.draw( vertices, states );
}

bool TileMap::LoadTexture( bool& is_tex_loaded, sf::Texture& texture, const char* tex_path,
                           const Vec_2i& position, const Vec_2i tile_size )
{
  if ( ! is_tex_loaded )
  {
    sf::IntRect tex_rect( position, tile_size );

    return texture.loadFromFile( tex_path, false, tex_rect );
  }
  else
  {
    return is_tex_loaded;
  }
}