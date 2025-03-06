#include "Sfml_Util.h"

void InitVertices( sf::Vertex* cell_vts, const Position& cell_pos, Vec_2u coord )
{
  Vec_2i     tile_size = { 32, 32 };
  const u_32 x         = coord.x; // Coordinate x of the Top Left Corner of texture cell
  const u_32 y         = coord.y; // Coordinate y of the Top Left Corner of texture cell
  u_32       row       = cell_pos.row;
  u_32       col       = cell_pos.col;

  cell_vts[ 0 ].position = Vec_2f( col * tile_size.x, row * tile_size.y );
  cell_vts[ 1 ].position = Vec_2f( ( col + 1 ) * tile_size.x, row * tile_size.y );
  cell_vts[ 2 ].position = Vec_2f( col * tile_size.x, ( row + 1 ) * tile_size.y );
  cell_vts[ 3 ].position = Vec_2f( col * tile_size.x, ( row + 1 ) * tile_size.y );
  cell_vts[ 4 ].position = Vec_2f( ( col + 1 ) * tile_size.x, row * tile_size.y );
  cell_vts[ 5 ].position = Vec_2f( ( col + 1 ) * tile_size.x, ( row + 1 ) * tile_size.y );

  cell_vts[ 0 ].texCoords = Vec_2f( x * tile_size.x, y * tile_size.y );
  cell_vts[ 1 ].texCoords = Vec_2f( ( x + 1 ) * tile_size.x, y * tile_size.y );
  cell_vts[ 2 ].texCoords = Vec_2f( x * tile_size.x, ( y + 1 ) * tile_size.y );
  cell_vts[ 3 ].texCoords = Vec_2f( x * tile_size.x, ( y + 1 ) * tile_size.y );
  cell_vts[ 4 ].texCoords = Vec_2f( ( x + 1 ) * tile_size.x, y * tile_size.y );
  cell_vts[ 5 ].texCoords = Vec_2f( ( x + 1 ) * tile_size.x, ( y + 1 ) * tile_size.y );
}

void loadFont( sf::Font& font, const std::string& font_path )
{
  if ( ! font.openFromFile( font_path ) )
  {
    LOG( "Error loading font" );
  }
}

void loadTexture( sf::Texture& texture, const std::string& texture_path )
{
  if ( ! texture.loadFromFile( texture_path ) )
  {
    LOG( "Error loading texture" );
  }
}