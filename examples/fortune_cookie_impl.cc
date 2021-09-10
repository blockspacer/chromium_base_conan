#include "fortune_cookie_impl.h"

#include <base/logging.h>

#include <iostream>

namespace examples {

FortuneCookieReceiver::FortuneCookieReceiver(
  mojo::PendingReceiver<mojom::FortuneCookie> receiver)
  : receiver_(this, std::move(receiver))
{
  receiver_.set_disconnect_handler(base::BindOnce(
    &FortuneCookieReceiver::OnError,
    base::Unretained(this)));
}

FortuneCookieReceiver::~FortuneCookieReceiver() {
  // Once a mojo::Receiver<T> is destroyed,
  // it is guaranteed that no more method calls
  // are dispatched to the implementation
  // and the connection error handler
  // (if registered) won't be called.
  OnError();
}

void FortuneCookieReceiver::SetWish(const std::string& wish) {
  wish_ = wish;
}

void FortuneCookieReceiver::SetId(const std::string& id) {
  id_ = id;
}

void FortuneCookieReceiver::Crack(CrackCallback callback) {
  LOG(INFO)
    << id_
    << " recieved Crack request.";
  std::move(callback).Run(wish_
    + (who_.empty()
       ? ""
       : ". Wish for " + who_));
}

void FortuneCookieReceiver::CloseStream(CloseStreamCallback callback) {
  LOG(INFO)
    << id_
    << " recieved CloseStream request.";
  std::move(callback).Run("ok");
}

void FortuneCookieReceiver::SetName(const std::string& who,
  SetNameCallback callback)
{
  LOG(INFO)
    << id_
    << " recieved SetName request.";
  const bool is_valid = who_ != who;
  who_ = who;
  std::move(callback).Run(is_valid);
}

void FortuneCookieReceiver::FillRects(
  base::Optional<std::vector<::examples::mojom::RectPtr>> elements,
  const std::vector<uint64_t>& uuid,
  base::Optional<
    base::flat_map<uint64_t,
    ::examples::mojom::RectPtr>> maybe_map,
  uint64_t hint,
  FillRectsCallback callback)
{
  ALLOW_UNUSED_LOCAL(elements);
  ALLOW_UNUSED_LOCAL(uuid);
  ALLOW_UNUSED_LOCAL(maybe_map);
  ALLOW_UNUSED_LOCAL(hint);

  ::examples::mojom::Department dpt
    = ::examples::mojom::Department::kDev;

  LOG(INFO)
    << id_
    << " recieved FillRects request.";
  std::move(callback).Run(std::move(dpt));
}

void FortuneCookieReceiver::AttachFingerPrint(
  uint64_t id,
  const std::vector<uint8_t>& finger_print,
  AttachFingerPrintCallback callback)
{
  LOG(INFO)
    << id_
    << " recieved FillRects request.";

  /// \todo do smth
  bool ok = true;

  std::move(callback).Run(std::move(ok));
}

void FortuneCookieReceiver::SetCallbackOnError(base::RepeatingClosure callback) {
  errorCallback_ = callback;
}

void FortuneCookieReceiver::OnError()
{
  LOG(INFO)
    << id_
    << " OnError: ";
  if (errorCallback_) {
    errorCallback_.Run();
  }
}

FortuneCookieRemote::FortuneCookieRemote(
  mojo::PendingRemote<mojom::FortuneCookie> remote)
{
  remote_.Bind(std::move(remote));

  remote_.set_disconnect_handler(base::BindOnce(
    &FortuneCookieRemote::OnError,
    base::Unretained(this)));
}

FortuneCookieRemote::~FortuneCookieRemote() {
  // Once a mojo::Remote<T> is destroyed,
  // it is guaranteed that pending callbacks
  // as well as the connection error handler (if registered)
  // won't be called.
  OnError();
}

void FortuneCookieRemote::SetCallbackOnError(base::RepeatingClosure callback) {
  errorCallback_ = callback;
}

void FortuneCookieRemote::SetId(const std::string& id) {
  id_ = id;
}

void FortuneCookieRemote::OnError()
{
  LOG(INFO)
    << id_
    << " OnError: ";
  if (errorCallback_) {
    errorCallback_.Run();
  }
}

void FortuneCookieRemote::SendCloseStream()
{
  remote_->CloseStream(base::BindOnce(
    &FortuneCookieRemote::OnCloseStreamAnswer,
    base::Unretained(this)));
}

void FortuneCookieRemote::OnCloseStreamAnswer(const std::string& data) {
  LOG(INFO)
    << id_
    << " OnCloseStreamAnswer: "
    << data;
}
void FortuneCookieRemote::SendFillRects()
{
  /// \todo send smth
  base::Optional<std::vector<::examples::mojom::RectPtr>> elements{
    base::nullopt};
  std::vector<uint64_t> uuid{7,3};
  base::Optional<
    base::flat_map<uint64_t,
    ::examples::mojom::RectPtr>> maybe_map{base::nullopt};
  uint64_t hint{0};

  remote_->FillRects(
    std::move(elements),
    std::move(uuid),
    std::move(maybe_map),
    std::move(hint),
    base::BindOnce(
      &FortuneCookieRemote::OnFillRectsAnswer,
      base::Unretained(this)));
}

void FortuneCookieRemote::OnFillRectsAnswer(
  ::examples::mojom::Department data)
{
  LOG(INFO)
    << id_
    << " OnFillRectsAnswer"
    << data;
}

base::Promise<bool> FortuneCookieRemote::SendSetName(
  const std::string& data)
{
  using Resolver
    = ::base::ManualPromiseResolver<
        bool, ::base::NoReject
      >;
  Resolver promiseResolver(FROM_HERE);
  remote_->SetName(data, base::BindOnce(
    &FortuneCookieRemote::OnSetNameAnswer,
    base::Unretained(this),
    basic::rvalue_cast(promiseResolver.GetResolveCallback())));
  return promiseResolver.promise();
}

void FortuneCookieRemote::OnSetNameAnswer(
  base::OnceCallback<void(bool)>&& resolveCallback,
  bool data)
{
  LOG(INFO)
    << id_
    << " OnSetNameAnswer: "
    << std::to_string(data);
  basic::rvalue_cast(resolveCallback).Run(data);
}

void FortuneCookieRemote::SendCrack()
{
  remote_->Crack(base::BindOnce(
    &FortuneCookieRemote::OnCrackAnswer,
    base::Unretained(this)));
}

void FortuneCookieRemote::OnCrackAnswer(const std::string& data) {
  LOG(INFO)
    << id_
    << " OnCrackAnswer: "
    << data;
}

}  // namespace examples
