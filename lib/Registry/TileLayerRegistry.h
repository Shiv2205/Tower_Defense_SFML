#ifndef TILELAYERREGISTRY_H
#define TILELAYERREGISTRY_H

#include <type_traits>
#include <vector>

//? Forward Declare
enum class TileType;
class TileLayer;
class TilePath;
class TileTowers;
class TileCritters;

class TileLayerRegistry
{
public:
  TileLayerRegistry( void );
  ~TileLayerRegistry( void );

  template <typename T> T getLayerOf( void );

  void addToRegistry( const TileType& layer_type );

  bool LoadLayers( void ) const;

private:
  std::vector<TileLayer*> layers;
};


extern template TilePath* TileLayerRegistry::getLayerOf<TilePath*>();
extern template TileTowers* TileLayerRegistry::getLayerOf<TileTowers*>();
extern template TileCritters* TileLayerRegistry::getLayerOf<TileCritters*>();

#endif // TILELAYERREGISTRY_H