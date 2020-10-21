#include<iostream>
#include<m_raylib.h>
#include<GL/glew.h>
#include<imgui.h>
#include<imgui_impl_glfw.h>
#include<imgui_impl_opengl3.h>

using namespace std;

ImGuiIO io;
bool show_demo = true;
bool show_another_window = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

Camera2D camera {0};

int main(){
  const int game_screen_width = 800;
  const int game_screen_height = 450;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  InitWindow(game_screen_width, game_screen_height, "raylib [core] example - basic window");
  SetTargetFPS(60);

  camera = {0};
  camera.offset = v2{0, 0};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  GLFWwindow *window = static_cast<GLFWwindow*>(GetCoreWindowHandle());
  glewInit();

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  io = ImGui::GetIO(); (void)io;

  ImGui::StyleColorsDark();

  const char* glsl_version = "#version 130";
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  while (!WindowShouldClose()){

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::ShowDemoWindow(&show_demo);

    {
      static float f = 0.0f;
      static int counter = 0;

      ImGui::Begin("Hello, world!");

      ImGui::Text("This is some useful text.");
      ImGui::Checkbox("Demo Window", &show_demo);
      ImGui::Checkbox("Another Window", &show_another_window);

      ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
      ImGui::ColorEdit3("clear color", (float*)&clear_color);

      if (ImGui::Button("Button"))
	counter++;
      ImGui::SameLine();
      ImGui::Text("counter = %d", counter);

      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
      ImGui::End();
    }

    if (show_another_window)
      {
	ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
	ImGui::Text("Hello from another window!");
	if (ImGui::Button("Close Me"))
	  show_another_window = false;
	ImGui::End();
      }


    /* 
       NOTE[kevin]:
       this approach have draw layer issue 
       between raylib renderer and imgui renderer.
       raylib drawable item/object always draw on top of imgui
       drawable item/object/widget/window.
    */
    // BeginDrawing();
    // ClearBackground(RAYWHITE);

    // DrawText("Congrats! You created your first window!", 190, 200, 20, BLUE);
    // DrawText("Howdy!", 0, 0, 20, BLUE);

    // ImGui::Render();
    // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // EndDrawing();


    BeginDrawing();
    ClearBackground(RAYWHITE);

    /*
      NOTE[kevin]:
      use of mode2d here seems like solve draw layer issue.
      but there is still another problem if we use letter box 
      for window scaling.
    */
    BeginMode2D(camera);
    DrawText("Congrats! You created your first window!", 190, 200, 20, BLUE);
    DrawText("Howdy!", 0, 0, 20, BLUE);
    EndMode2D();

    DrawText("Congrats! You created your first window!", 190, 240, 20, RED);
    DrawText("Howdy!", 0, 40, 20, RED);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    EndDrawing();
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  CloseWindow();
  return 0;
}
