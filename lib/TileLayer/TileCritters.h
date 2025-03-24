#ifndef TILECRITTERS_H
#define TILECRITTERS_H

#include "Critters/CrittersGroup.h"
#include "Util/Sfml_Util.h"
#include <cmath>

class TileCritters : public CritterGroup, public sf::Drawable, public sf::Transformable
{
public:
  TileCritters( void );

  void WaveInit();
  void WaveMove();

  void InitCritterWave( sf::Vertex* critter_vts, int critter_idx, Vec_2u coord = { 0, 0 } );
  void MoveCritterWave( sf::Vertex* critter_vts, int critter_idx );

  ~TileCritters( void );

private:
  void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
  void CalculateOffset( int& offset_x, int& offset_y );
  void CalculateIncrement( const Position& curr_pos, const Position& next_pos, Vec_2f& increment );

  sf::VertexArray critter_tiles;
  sf::Texture     layer_texture;
};

#endif // TILECRITTERS_H