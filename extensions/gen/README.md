# About

Store chromium-generated files here

See:
* https://chromium.googlesource.com/chromium/src/out/+/749a640e1cbafdb45b5257069da94178f5c49ae6/Debug?autodive=0
* https://chromium.googlesource.com/chromium/src/+/refs/heads/main/mojo/public/interfaces/bindings/tests/ping_service.mojom

## mojo

wget https://chromium.googlesource.com/chromium/src/out/+archive/749a640e1cbafdb45b5257069da94178f5c49ae6/Debug/gen/mojo.tar.gz

extract to extensions/gen/mojo

rm extensions/gen/mojo/public/cpp/bindings/mojo_buildflags.h

## ipc

wget https://chromium.googlesource.com/chromium/src/out/+archive/749a640e1cbafdb45b5257069da94178f5c49ae6/Debug/gen/ipc.tar.gz

extract to extensions/gen/ipc

rm extensions/gen/ipc/ipc_buildflags.h

wget https://chromium.googlesource.com/chromium/src/+/f89fc2ac30e582dfe9e334baf19ef8e535eea30d/services/tracing/public/cpp/perfetto/macros.h

mv macros.h extensions/services/tracing/public/cpp/perfetto/macros.h

