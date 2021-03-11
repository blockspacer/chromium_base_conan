# see component("base") in BUILD.gn
list(APPEND COMPONENT_BASE_SOURCES_LINUX_UNPROCESSED
  "nix/mime_util_xdg.cc"
  "nix/mime_util_xdg.h"
  "nix/xdg_util.cc"
  "nix/xdg_util.h"
  "system/sys_info_linux.cc"
)

list(APPEND COMPONENT_BASE_SOURCES ${COMPONENT_BASE_SOURCES_LINUX_UNPROCESSED})
