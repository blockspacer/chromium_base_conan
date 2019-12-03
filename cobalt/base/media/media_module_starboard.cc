// Copyright 2015 The Cobalt Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <memory>

#include "cobalt/media/media_module.h"

#include "base/compiler_specific.h"
#include "cobalt/math/size.h"
#include "cobalt/media/base/media_log.h"
#include "cobalt/media/decoder_buffer_allocator.h"
#include "cobalt/media/player/web_media_player_impl.h"
#include "cobalt/media/shell_media_platform_starboard.h"
#include "cobalt/system_window/system_window.h"
#include "nb/memory_scope.h"
#include "starboard/media.h"
#include "starboard/string.h"
#include "starboard/window.h"

namespace cobalt {
namespace media {

namespace {

class CanPlayTypeHandlerStarboard : public CanPlayTypeHandler {
 public:
  std::string CanPlayType(bool is_progressive, const std::string& mime_type,
                          const std::string& key_system) override {
    if (is_progressive) {
      // |mime_type| is something like:
      //   video/mp4
      //   video/webm
      //   video/mp4; codecs="avc1.4d401e"
      //   video/webm; codecs="vp9"
      // We do a rough pre-filter to ensure that only video/mp4 is supported as
      // progressive.
      if (SbStringFindString(mime_type.c_str(), "video/mp4") == 0 &&
          SbStringFindString(mime_type.c_str(), "application/x-mpegURL") == 0) {
        return "";
      }
    }
    SbMediaSupportType type =
        SbMediaCanPlayMimeAndKeySystem(mime_type.c_str(), key_system.c_str());
    switch (type) {
      case kSbMediaSupportTypeNotSupported:
        return "";
      case kSbMediaSupportTypeMaybe:
        return "maybe";
      case kSbMediaSupportTypeProbably:
        return "probably";
    }
    NOTREACHED();
    return "";
  }
};

class MediaModuleStarboard : public MediaModule {
 public:
  MediaModuleStarboard(system_window::SystemWindow* system_window,
                       render_tree::ResourceProvider* resource_provider,
                       const Options& options)
      : options_(options),
        system_window_(system_window),
        media_platform_(resource_provider) {}

  std::unique_ptr<WebMediaPlayer> CreateWebMediaPlayer(
      WebMediaPlayerClient* client) override {
    TRACK_MEMORY_SCOPE("Media");
    SbWindow window = kSbWindowInvalid;
    if (system_window_) {
      window = system_window_->GetSbWindow();
    }
    return std::unique_ptr<WebMediaPlayer>(new media::WebMediaPlayerImpl(
        window, client, this, &decoder_buffer_allocator_,
        options_.allow_resume_after_suspend, new media::MediaLog));
  }

  system_window::SystemWindow* system_window() const override {
    return system_window_;
  }

  void OnSuspend() override { media_platform_.Suspend(); }

  void OnResume(render_tree::ResourceProvider* resource_provider) override {
    media_platform_.Resume(resource_provider);
  }

 private:
  const Options options_;
  system_window::SystemWindow* system_window_;
  DecoderBufferAllocator decoder_buffer_allocator_;
  ShellMediaPlatformStarboard media_platform_;
};

}  // namespace

std::unique_ptr<MediaModule> MediaModule::Create(
    system_window::SystemWindow* system_window,
    render_tree::ResourceProvider* resource_provider, const Options& options) {
  TRACK_MEMORY_SCOPE("Media");
  return std::unique_ptr<MediaModule>(
      new MediaModuleStarboard(system_window, resource_provider, options));
}

std::unique_ptr<CanPlayTypeHandler> MediaModule::CreateCanPlayTypeHandler() {
  return std::unique_ptr<CanPlayTypeHandler>(new CanPlayTypeHandlerStarboard);
}

}  // namespace media
}  // namespace cobalt
