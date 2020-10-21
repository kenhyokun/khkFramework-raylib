/*
  Kevin Haryo Kuncoro
  kevinhyokun91@gmail.com
*/
#include<GL/glew.h>
#include<iostream>
#include<string>
#include<BaseApp.h>
#include<Node.h>
#include<Component.h>
#include<B2D.h>
#include<imgui.h>
#include<imgui_impl_glfw.h>
#include<imgui_impl_opengl3.h>

using namespace std;
using namespace Component;

/*
  Game loop:
  - OnInit
  - OnUpdate
  - OnDraw
*/

ImGuiIO io;

struct App : BaseApp, ContactListener{

  App(int _window_width, int _window_height, string _title) :
    BaseApp(_window_width, _window_height, _title){}

  ~App(){
  }

  void OnInit() override {
    GLFWwindow *window = static_cast<GLFWwindow*>(GetCoreWindowHandle());
    if(window == NULL){
      cout<<"window null.."<<endl;
    }
    else{cout<<window<<endl;}

    glewInit();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // ImGuiIO& io = ImGui::GetIO(); (void)io;
    io = ImGui::GetIO(); (void)io;
    // io.DisplaySize = ImVec2(game_screen_width, game_screen_height);

    ImGui::StyleColorsDark();

    const char* glsl_version = "#version 130";
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);


  }

  bool show_demo = true;
  bool show_another_window = false;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  void OnUpdate() override {
    cout<<"mouse x:"<<mouse.x<<", mouse y:"<<mouse.y<<endl;
    cout<<"virtual mouse x:"<<virtual_mouse.x<<", virtual mouse y:"<<virtual_mouse.y<<endl;
    io.MousePos = ImVec2(virtual_mouse.x, virtual_mouse.y);
    cout<<"imgui mouse x:"<<io.MousePos.x<<", imgui mouse y:"<<io.MousePos.y<<endl;

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
  }

  void OnDraw() override {
    DrawText("Congrats! You created your first window!", 0, 0, 20, BLUE);
  }

  void OnDrawGUI() override{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

};

int main(){
  App app(800, 450, "My Game");
  app.Init();
  app.Run();

  return 0;
}
