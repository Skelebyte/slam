#include "audio_listener.hpp"
#include "audio_manager.hpp"

using namespace slam;
using namespace slam::audio;
using namespace slam::err;

AudioListener::AudioListener(bool setAsMainListener) {
  if (setAsMainListener) {
    AudioManager::SetListener(this);
  }
}

void AudioListener::Destroy() { DESTROY(); }

void AudioListener::Update() {
  IS_DESTROYED();

  transform.Process();

  // ma_engine_listener_set_direction(AudioManager::GetEngine(), 0,
  //                                  -transform.GetInheritedPosition().x, 0,
  //                                  -transform.GetInheritedPosition().z);

  ma_engine_listener_set_position(
      AudioManager::GetEngine(), 0,
      AudioManager::GetListener()->transform.GetInheritedPosition().x,
      AudioManager::GetListener()->transform.GetInheritedPosition().y,
      AudioManager::GetListener()->transform.GetInheritedPosition().z);
  ma_engine_listener_set_direction(
      AudioManager::GetEngine(), 0,
      AudioManager::GetListener()->transform.InheritedForward().x,
      AudioManager::GetListener()->transform.InheritedForward().y,
      AudioManager::GetListener()->transform.InheritedForward().z);
}

// not quite working still. sounds like the sound is playing from 0,0,0