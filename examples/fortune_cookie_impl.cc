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
