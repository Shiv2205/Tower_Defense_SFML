#include "main.h"
#include "critterDriver.h"

int main()
{
  
  // window.setFramerateLimit(144);
  critterDemo();

  Engine::gameInit();

  Engine::gameLoop();

  return EXIT_SUCCESS;
}



// Vec_2f    map_pos;
// map_pos.x = 0; //( SCREEN_W - ( map_dim.width * 32 ) ) / 2;
// map_pos.y = 0; //( SCREEN_H - ( map_dim.height * 32 ) ) / 2;
// my_map.setPosition( map_pos );