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
  std::move(callback).Run(wish_);
}

void FortuneCookieReceiver::CloseStream(CloseStreamCallback callback) {
  LOG(INFO)
    << id_
    << " recieved CloseStream request.";
  std::move(callback).Run("ok");
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
