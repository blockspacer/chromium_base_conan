#include "fortune_cookie_impl.h"

#include <iostream>

namespace examples {

FortuneCookieImplAlpha::FortuneCookieImplAlpha(
  mojo::PendingReceiver<mojom::FortuneCookie> receiver)
  : receiver_(this, std::move(receiver)) {}

FortuneCookieImplAlpha::~FortuneCookieImplAlpha() = default;

void FortuneCookieImplAlpha::EatMe() {
  std::cout << "Bon appetit.\n";
}

void FortuneCookieImplAlpha::Crack(CrackCallback callback) {
  std::cout << "crack now.\n";
  std::move(callback).Run("A dream you have will come true.");
}

}  // namespace examples
