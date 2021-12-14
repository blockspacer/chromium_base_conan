#pragma once

#include "base/macros.h"

#include "basic/promise/post_promise.h"
#include "basic/promise/post_task_executor.h"
#include "basic/promise/do_nothing_promise.h"
#include "basic/promise/abstract_promise.h"
#include "basic/promise/helpers.h"
#include "basic/rvalue_cast.h"

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

#include "examples/mojom/fortune_cookie/fortune_cookie.mojom.h"

namespace examples {

// Used to receive the interface messages sent by Remote.
class FortuneCookieReceiver : public mojom::FortuneCookie {
 public:
  FortuneCookieReceiver(
    // Typed container to hold the other end of a Remote’s pipe.
    mojo::PendingReceiver<mojom::FortuneCookie> receiver);

  ~FortuneCookieReceiver() override;

  void SetCallbackOnError(base::RepeatingClosure callback);

  void SetWish(const std::string& wish);

  void SetId(const std::string& id);

 private:
  void OnError();

 private:
  // sends answer
  void Crack(
    CrackCallback callback) override;

  // sends answer
  void CloseStream(
    CloseStreamCallback callback) override;

  // sends answer
  void SetName(const std::string& who,
    SetNameCallback callback) override;

  // sends answer
  void FillRects(
    base::Optional<std::vector<::examples::mojom::RectPtr>> elements,
    const std::vector<uint64_t>& uuid,
    base::Optional<
      base::flat_map<uint64_t,
      ::examples::mojom::RectPtr>> maybe_map,
    uint64_t hint,
    FillRectsCallback callback) override;

  void AttachFingerPrint(
    uint64_t id,
    const std::vector<uint8_t>& finger_print,
    AttachFingerPrintCallback callback) override;

 private:
  std::string id_{"Unknown"};

  std::string who_{""};

  base::RepeatingClosure errorCallback_;

  // Wraps a message pipe endpoint that receives incoming messages.
  mojo::Receiver<mojom::FortuneCookie> receiver_;

  std::string wish_{"A dream you have will come true."};

  DISALLOW_COPY_AND_ASSIGN(FortuneCookieReceiver);
};

// Used to send messages described by the interface.
class FortuneCookieRemote {
 public:
  FortuneCookieRemote(
    // Typed container to hold the other end of a Receiver’s pipe.
    mojo::PendingRemote<mojom::FortuneCookie> remote);

  ~FortuneCookieRemote();

  void SetCallbackOnError(base::RepeatingClosure callback);

  void SetId(const std::string& id);

  void SendCrack();

  void SendCloseStream();

  void SendFillRects();

  base::Promise<bool> SendSetName(const std::string& data);

 private:
  void OnFillRectsAnswer(::examples::mojom::Department data);

  void OnSetNameAnswer(
    base::OnceCallback<void(bool)>&& resolveCallback,
    bool data);

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
