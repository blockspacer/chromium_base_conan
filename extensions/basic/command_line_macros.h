#pragma once

// USAGE
//
// GET_SWITCH_AS_SIZE_T(&warnBigRegistrySize_, ::switches::kWarnBigRegistrySize);
//
#define GET_SWITCH_AS_SIZE_T(VAR, FLAG_NAME)                                   \
  [&]() {                                                                      \
    const base::CommandLine* internal_command_line                             \
      = base::CommandLine::ForCurrentProcess();                                \
    if (internal_command_line->HasSwitch(FLAG_NAME)) {                         \
      auto ascii_value                                                         \
        = internal_command_line->GetSwitchValueASCII(FLAG_NAME);               \
      if (!base::StringToSizeT(ascii_value, VAR))                              \
      {                                                                        \
        LOG(WARNING)                                                           \
          << "Invalid value for " << FLAG_NAME                                 \
          << " Fallback to " << *VAR;                                          \
      }                                                                        \
    }                                                                          \
  }()

// USAGE
//
// GET_SWITCH_AS_INT(&warnBigRegistrySize_, ::switches::kWarnBigRegistrySize);
//
#define GET_SWITCH_AS_INT(VAR, FLAG_NAME)                                      \
  [&]() {                                                                      \
    const base::CommandLine* internal_command_line                             \
      = base::CommandLine::ForCurrentProcess();                                \
    if (internal_command_line->HasSwitch(FLAG_NAME)) {                         \
      auto ascii_value                                                         \
        = internal_command_line->GetSwitchValueASCII(FLAG_NAME);               \
      if (!base::StringToInt(ascii_value, VAR))                                \
      {                                                                        \
        LOG(WARNING)                                                           \
          << "Invalid value for " << FLAG_NAME                                 \
          << " Fallback to " << *VAR;                                          \
      }                                                                        \
    }                                                                          \
  }()
