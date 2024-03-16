#include <raylib.h>

int main(void) {
  InitWindow(800, 600, "coque");
  TraceLog(LOG_INFO, "Window opened");
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("coque", 400, 300, 12, RAYWHITE);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
