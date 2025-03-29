#include "TileLayerRegistry.h"
#include "Factory/TileLayerFactory.h"
#include "TileLayer/TileCritters.h"
#include "TileLayer/TileLayer.h"
#include "TileLayer/TilePath.h"
#include "TileLayer/TileTowers.h"

TileLayerRegistry::TileLayerRegistry( void ) {}

TileLayerRegistry::~TileLayerRegistry( void )
{
  for ( auto* layer : this->layers )
  {
    delete layer;
  }
}

template <typename T> T TileLayerRegistry::getLayerOf( void )
{
  static_assert( std::is_pointer_v<T>, "Target type must be a pointer type" );
  static_assert( std::is_base_of_v<TileLayer, std::remove_pointer_t<T>>, "Target must be TileLayer or derived" );

  for ( TileLayer* layer : this->layers )
  {
    if ( T result = dynamic_cast<T>( layer ) )
    {
      return result;
    }
  }
  return nullptr;
}

void TileLayerRegistry::addToRegistry( const TileType& layer_type )
{
  TileLayerFactory layer_factory;
  this->layers.push_back( layer_factory.create( layer_type ) );
}

bool TileLayerRegistry::LoadLayers( void ) const
{
  bool layers_loaded = false;

  for ( TileLayer* layer : this->layers )
  {
    layers_loaded = layer->Load();

    if ( ! layers_loaded )
    {
      return false;
    }
  }

  return true;
}

//? Explicit instantiations
template TilePath*     TileLayerRegistry::getLayerOf<TilePath*>();
template TileTowers*   TileLayerRegistry::getLayerOf<TileTowers*>();
template TileCritters* TileLayerRegistry::getLayerOf<TileCritters*>();