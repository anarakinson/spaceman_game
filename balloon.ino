#include "balloon.h"

void Balloon::move() {
  if (millis() - move_timer >= 100) {
    move_timer = millis();

    int x = get_x();
    int y = get_y();
    --y;
    if (jitter_marker) { --x; }
    else { ++x; }
    if (millis() - jitter_timer >= 500) {
      jitter_timer = millis();
      jitter_marker = !jitter_marker;
    }
    set_x(x);
    set_y(y);
  }
}