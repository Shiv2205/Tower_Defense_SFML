#include "TileLayer.h"

u_32 TileLayer::num_vertices = 0;

TileLayer::TileLayer( void )
{
}

TileLayer::TileLayer( const std::string& tex_path, const Vec_2i& tile_pos, const Vec_2i& tile_size )
    : layer_tex_path( tex_path ), tile_pos( tile_pos ), tile_size( tile_size )
{
}

sf::Vertex* TileLayer::getLayerVertex( const u_32 index )
{
  return &this->layer_vertices[ index ];
}

const sf::Texture& TileLayer::getLayerTexture( void ) const
{
  return this->layer_texture;
}

bool TileLayer::isLayerTexLoaded( void ) const
{
  return this->layer_tex_loaded;
}

const std::string& TileLayer::getLayerTexPath() const
{
  return this->layer_tex_path;
}

u_32 TileLayer::getNumVertices( void )
{
  return TileLayer::num_vertices;
}

void TileLayer::setLayerVertices( const sf::VertexArray& layer_vertices )
{
  this->layer_vertices = layer_vertices;
}

void TileLayer::setLayerTexture( const sf::Texture& layer_texture )
{
  this->layer_texture = layer_texture;
}

void TileLayer::setLayerTexPath( const std::string& layer_tex_path )
{
  this->layer_tex_path = layer_tex_path;
}

void TileLayer::setNumVertices( const u_32& num_vertices )
{
  TileLayer::num_vertices = num_vertices;
}

bool TileLayer::LoadTexture( void )
{
  if ( ! this->layer_tex_loaded )
  {
    sf::IntRect tex_rect( this->tile_pos, this->tile_size );

    return this->layer_texture.loadFromFile( this->layer_tex_path, false, tex_rect );
  }
  else
  {
    return this->layer_tex_loaded;
  }
}

bool TileLayer::Load( void )
{
  this->layer_tex_loaded = this->LoadTexture();

  if ( ! this->layer_tex_loaded )
  {
    return false;
  }

  this->layer_vertices.setPrimitiveType( sf::PrimitiveType::Triangles );
  this->layer_vertices.resize( TileLayer::num_vertices );

  return true;
}

void TileLayer::RegisterTile( const u_32& vertex_idx, const Position& target_tile,
                              const std::string& tile_type )
{
  sf::Vertex* tile_vertices = &this->layer_vertices[ vertex_idx ];
  InitVertices(tile_vertices, target_tile);
}

void TileLayer::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  // apply the transform
  states.transform *= getTransform();

  // apply the texture
  states.texture = &this->layer_texture;

  // draw the vertex array
  target.draw( this->layer_vertices, states );
}

TileLayer::~TileLayer( void )
{
}