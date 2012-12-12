#include "Application.h"
#include "VideoPlayer.h"

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " <Video resource name>" << std::endl;
    exit(0);
  }

  Application app;
  app.run ();

  VideoPlayer player;
  player.playVideo (argv[1]);
  while (player.isPlaying ())
  {
    player.update ();
    if (!app.render ())
      break;
  }

  return 0;
}
