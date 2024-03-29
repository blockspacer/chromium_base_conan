# Lacros

## Background

Lacros is an architecture project to decouple the Chrome browser from the Chrome
OS window manager and system UI. The name comes from **L**inux **A**nd
**C**h**R**ome **OS**.

Googlers: [go/lacros](http://go/lacros) has internal docs.

## Technical details

On Chrome OS, the system UI (ash window manager, login screen, etc.) and the web
browser are the same binary. Lacros separates this functionality into two
binaries, henceforth known as ash-chrome (system UI) and lacros-chrome (web
browser).

The basic approach is to rename the existing binary to ash-chrome, with minimal
changes. We then take the linux-chrome binary, improve its Wayland support, make
it act like the web browser on Chrome OS, and ship that as the lacros-chrome
binary. This allows the two binaries to be released independently, with some
performance/resource costs. The API boundary initially will be semi-stable: it
will tolerate 1-2 milestones of version skew. We may allow larger amounts of
skew in the future.

Both binaries are built out of the chromium git repository. However, the
binaries might be built at different versions. For example, the version of
lacros built from the M-101 branch might run on top of the ash version built
from the M-100 branch.

Lacros can be imagined as "Linux chrome with more Wayland support". Lacros uses
[ozone](https://chromium.googlesource.com/chromium/src.git/+/master/ui/ozone)
as an abstraction layer for graphics and event handling. Ozone has a "backend"
with client-side support for the Wayland compositor protocol.

Chrome OS has a Wayland server implementation called
[exosphere](https://chromium.googlesource.com/chromium/src.git/+/master/components/exo).
It is used by ARC (to run Android apps) and Crostini (to run Linux apps).

Lacros will use exo as the Wayland server for graphics and event handling. Where
possible we use stable Wayland protocols. We also share Wayland protocol
extensions with ARC and Crostini (e.g.
[zaura-shell](https://chromium.googlesource.com/chromium/src.git/+/master/components/exo/wayland/protocol/aura-shell.xml).
Higher-level features (e.g. file picking) use Mojo IPC.

We call the new Mojo API surface "crosapi". It's similar in concept to Win32 or
Cocoa, but much smaller. It's also mostly asynchronous for performance reasons.
The API lives in
[//chromeos/crosapi](https://chromium.googlesource.com/chromium/src.git/+/master/chromeos/crosapi).
The ash-side implementation lives in
[//chrome/browser/ash/crosapi](https://chromium.googlesource.com/chromium/src.git/+/master/chrome/browser/ash/crosapi).

Code can be conditionally compiled into lacros via
BUILDFLAG(IS_CHROMEOS_LACROS).

## Filing bugs 

Lacros bugs should be filed under OS=Lacros

Bugs in the ash-chrome binary that only affect ash-chrome should be labeled OS=Chrome.

Bugs in the lacros-chrome binary that only affect lacros-chrome should be labeled OS=Lacros.

Bugs in the ash-chrome binary that affect lacros-chrome should be labeled with both OS=Chrome and OS=Lacros. 
These should not block ash-chrome releases in the short term, but should block ash-chrome releases in the long term.

Bug in the lacros-chrome binary that affects ash-chrome: should not be possible. If lacros-chrome causes bugs in ash-chrome, then there must be a corresponding bug in ash-chrome as well. 
The lacros-chrome bug should be labeled OS=Lacros and the ash-chrome bug should be labeled OS=Chrome. 

Cross-platform browser bugs e.g. Blink bug should set both OS=Lacros and OS=Chrome in the short term, since we are supporting both ash and lacros as browsers in the short term. 
Once Lacros launches, the plan to use Lacros vs Chrome will be finalized.


## GN var and C++ macros

*Note* that this will take effect once target_os flip of lacros-chrome is landed
with patch [crrev.com/c/2644407](https://crrev.com/c/2644407). For a short while
please keep using `BUILDFLAG(IS_CHROMEOS_ASH) || BUILDFLAG(IS_CHROMEOS_LACROS`
and `is_chromeos_ash || is_chromeos_lacros` to target both binaries.

Both lacros and ash are built with gn arg `target_os="chromeos"`. This means
that C++ macro defined(OS_CHROMEOS) and gn variable is_chromeos are set true for
both lacros and ash.

### Targeting ash or lacros
To target lacros or ash separately, use BUILDFLAG(IS_CHROMEOS_LACROS),
BUILDFLAG(IS_CHROMEOS_ASH) in C++ files and is_chromeos_lacros and
is_chromeos_ash in gn files.

Note that these are not defined globally and must be included manually.

To use the buildflags in C++ files, add #include "build/chromeos_buildflags.h"
and then also add "//build:chromeos_buildflags" to deps of the target that is
using the update C++ files inside gn files. See e.g. crrev.com/c/2494186.

To use the gn variables add `import("//build/config/chromeos/ui_mode.gni")`.

Doc for googlers:
[go/lacros-porting](http://go/lacros-porting) has tips on determining which
binary (lacros or ash) a feature should live in.

## Testing

Most test suites require ash-chrome to be running in order to provide a basic
Wayland server. This requires a special test runner:

`./build/lacros/test_runner.py test out/lacros/browser_tests --gtest_filter=BrowserTest.Title`

Some test suites require ash-chrome to provide both a Wayland server and a valid
mojo crosapi connection. This requires the test target
`lacros_chrome_browsertests`:

`./build/lacros/test_runner.py test out/lacros/lacros_chrome_browsertests --gtest_filter=ScreenManagerLacrosBrowserTest.*`

By default, the test runner downloads a prebuilt ash-chrome, add the
`--ash-chrome-path` command line argument to run the test against a locally
built version of Ash:

`./build/lacros/test_runner.py test --ash-chrome-path=out/ash/chrome out/lacros/lacros_chrome_browsertests --gtest_filter=ScreenManagerLacrosBrowserTest.*`

If you're sshing to your desktop, please prefix the command with
`./testing/xvfb.py`.

For sheriffs: Test failures that should have been caught by the CQ should be
treated like test failures on any other platform: investigated and fixed or
disabled. Use BUILDFLAG(IS_LACROS) to disable a test just for lacros. See the
[sheriffing how-to](http://go/chrome-sheriffing-how-to#test-failed).
