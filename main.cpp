#include "Application.h"
#include "VideoPlayer.h"

int main(int argc, char *argv[]) {

  Application app;
  app.run ();


  VideoPlayer player;
  player.playVideo ("");
  while (player.isPlaying ())
  {
    player.update ();
    if (!app.render ())
      break;
  }

  return 0;
}
