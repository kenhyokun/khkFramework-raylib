# Kevin Haryo Kuncoro
# kevinhyokun91@gmail.com

# don't forget to copy resources forlder into build folder to avoid crash because missing asset!

cmake_minimum_required(VERSION 2.8)

# set project files
file(GLOB curr_project_file "../contact_callback.cpp")
# file(GLOB curr_project_file "../imgui_demo_test.cpp")

file(GLOB khkFramework_project_file "../../khkFramework/*.cpp")
file(GLOB khkFramework_project_header "../../khkFramework/*.h")
file(GLOB raylib_project_header "../../third_party/raylib/*.h")
file(GLOB box2d_project_header "../../third_party/box2d/box2d/*.h")
file(GLOB tinyxml2_project_header "../../third_party/tinyxml2/*.h")
file(GLOB confini_project_header "../../third_party/confini/*.h")
file(GLOB json_project_header "../../third_party/json/*.hpp")
file(GLOB imgui_project_header "../../third_party/imgui/*.h")

# set include dir
include_directories("../../khkFramework/")
include_directories("../../third_party/box2d/")
include_directories("../../third_party/raylib/")
include_directories("../../third_party/tinyxml2/")
include_directories("../../third_party/confini/")
include_directories("../../third_party/json/")
include_directories("../../third_party/imgui/")

# set output name
set(project_name "main")

# raylib dependencies
find_library(lgl GL)
find_library(lpthread pthread)
find_library(lm m)
find_library(ldl dl)
find_library(lrt rt)
find_library(lx11 X11)

# imgui dependency
find_library(lglew GLEW)

# static library
find_library(lraylib NAMES "raylib" PATHS "../../third_party/raylib/" NO_DEFAULT_PATH)
find_library(lbox2d NAMES "box2d" PATHS "../../third_party/box2d/" NO_DEFAULT_PATH)
find_library(ltinyxml2 NAMES "tinyxml2" PATHS "../../third_party/tinyxml2/" NO_DEFAULT_PATH)
find_library(lconfini NAMES "confini" PATHS "../../third_party/confini/" NO_DEFAULT_PATH)
find_library(limgui NAMES "imgui" PATHS "../../third_party/imgui/" NO_DEFAULT_PATH)
find_library(lkhkFramework NAMES "khkFramework" PATHS "../../khkFramework/build/" NO_DEFAULT_PATH)

add_executable(${project_name} 
	${curr_project_file}
	${khkFramework_project_file}	
	${khkFramework_project_header}	
	${raylib_project_header}
	${box2d_project_header}
	${tinyxml2_project_header}
	${confini_project_header}
	${json_project_header}
	${imgui_project_header}
	)

target_link_libraries(${project_name} 
	${lraylib}
	${lbox2d}
	${ltinyxml2}
	${lconfini}
	${limgui}
	${lkhkFramework}
	${lgl}
	${lpthread}
	${lm}
	${ldl}
	${lrt}
	${lx11}
	${lglew}
	)
