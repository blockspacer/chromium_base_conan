#pragma once

#include "base/macros.h"

#include "mojo/public/cpp/bindings/associated_receiver.h"
#include "mojo/public/cpp/bindings/associated_remote.h"
#include "mojo/public/cpp/bindings/pending_associated_receiver.h"
#include "mojo/public/cpp/bindings/pending_associated_remote.h"
#include "mojo/public/cpp/bindings/associated_interface_ptr_info.h"
#include "mojo/public/cpp/bindings/scoped_interface_endpoint_handle.h"

#include "mojo/public/cpp/bindings/interface_ptr.h"
#include "mojo/public/cpp/bindings/lib/validation_errors.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/pending_remote.h"
#include "mojo/public/cpp/bindings/receiver.h"
#include "mojo/public/cpp/bindings/remote.h"
#include "mojo/public/cpp/bindings/self_owned_receiver.h"
#include "mojo/public/cpp/bindings/tests/bindings_test_base.h"
#include "mojo/public/cpp/bindings/tests/receiver_unittest.test-mojom.h"
#include "mojo/public/cpp/system/functions.h"
#include "mojo/public/interfaces/bindings/tests/ping_service.mojom.h"
#include "mojo/public/interfaces/bindings/tests/sample_interfaces.mojom.h"
#include "mojo/public/interfaces/bindings/tests/sample_service.mojom.h"

#include "mojom/fortune_cookie.mojom.h"

namespace examples {
class FortuneCookieImplAlpha : public mojom::FortuneCookie {
 public:
  FortuneCookieImplAlpha(
    mojo::PendingReceiver<mojom::FortuneCookie> receiver);
  ~FortuneCookieImplAlpha() override;

  void EatMe();

 private:
  // mojom::FortuneCookie impl
  void Crack(CrackCallback callback) override;

  mojo::Receiver<mojom::FortuneCookie> receiver_;

  DISALLOW_COPY_AND_ASSIGN(FortuneCookieImplAlpha);
};
}  // namespace examples
