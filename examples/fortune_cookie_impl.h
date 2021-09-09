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

#include "examples/fortune_cookie.mojom.h"

namespace examples {

class FortuneCookieReceiver : public mojom::FortuneCookie {
 public:
  FortuneCookieReceiver(
    mojo::PendingReceiver<mojom::FortuneCookie> receiver);

  ~FortuneCookieReceiver() override;

  void SetCallbackOnError(base::RepeatingClosure callback);

  void SetWish(const std::string& wish);

  void SetId(const std::string& id);

 private:
  void OnError();

 private:
  // sends answer
  void Crack(CrackCallback callback) override;

  // sends answer
  void CloseStream(CloseStreamCallback callback) override;

 private:
  std::string id_{"Unknown"};

  base::RepeatingClosure errorCallback_;

  mojo::Receiver<mojom::FortuneCookie> receiver_;

  std::string wish_{"A dream you have will come true."};

  DISALLOW_COPY_AND_ASSIGN(FortuneCookieReceiver);
};

class FortuneCookieRemote {
 public:
  FortuneCookieRemote(
    mojo::PendingRemote<mojom::FortuneCookie> remote);

  ~FortuneCookieRemote();

  void SetCallbackOnError(base::RepeatingClosure callback);

  void SetId(const std::string& id);

  void SendCrack();

  void SendCloseStream();

 private:
  void OnCloseStreamAnswer(const std::string& data);

  void OnCrackAnswer(const std::string& data);

  void OnError();

 private:
  mojo::Remote<mojom::FortuneCookie> remote_;

  std::string id_{"Unknown"};

  base::RepeatingClosure errorCallback_;

  DISALLOW_COPY_AND_ASSIGN(FortuneCookieRemote);
};

}  // namespace examples
