A video player engine for Ogre3D using FFmpeg. Includes a demo application using SDL2 for audio output.

License
=======

MIT license (see License.txt)

Features
========

 - Uses Ogre's resource system to open the video file, so it could be coming from an archive, or a network resource, etc.
 - Writes the video to an Ogre texture, which can be used however you want (on an overlay, or somewhere in the scene, etc)
 - Complete A/V sync solution.
 - Multithreaded decoding.
 - Works with a variety of FFmpeg versions, including the Libav fork. 
 - Audio resampling support (using ffmpeg's swresample / libav's avresample library): can convert audio to the user's desired sample rate, sample format and channel layout.
 - Basic playback control support: play/pause, seeking.
 - No audio library dependency. Audio is handled by a MovieAudioFactory, which can be implemented by the user. If no MovieAudioFactory is given, videos are played without sound. An example MovieAudioFactory using SDL_audio is included in the demo. 
 - Fun fact: Also works with audio-only files, so you can use it as a streaming audio player, if you want.

Dependencies
============

Video player engine dependencies:

 - FFmpeg
 - Ogre 1.9+
 - boost_thread

Dependencies for the demo:

 - SDL2 for audio output
 - OIS for keyboard controls

Building
========

The demo can be built the usual cmake way:

<pre>
mkdir build
cd build
cmake ..
make
</pre>

Running
=======

Place your video files in the build folder, then run the demo using a filename as argument:

./ogre-ffmpeg-videoplayer-demo big_buck_bunny.avi

Playback controls:
 - Space: Play/Pause
 - Left/Right: Seek by 5 seconds.
 - Down/Up: Seek by 30 seconds.
