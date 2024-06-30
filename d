[1mdiff --git a/CMakeLists.txt b/CMakeLists.txt[m
[1mindex be81a65..6d4dd02 100644[m
[1m--- a/CMakeLists.txt[m
[1m+++ b/CMakeLists.txt[m
[36m@@ -31,8 +31,11 @@[m [mset(RENDERER_SOURCES[m
     src/renderer/primitives/point.cpp[m
     src/renderer/primitives/line.h[m
     src/renderer/primitives/line.cpp[m
[32m+[m[32m    src/renderer/graph/graph.cpp[m
[32m+[m[32m    src/renderer/graph/graph.cpp[m
     src/renderer/transform.h[m
[31m-    src/renderer/sceneProvider.h)[m
[32m+[m[32m    src/renderer/sceneProvider.h[m
[32m+[m[32m    src/utils/constants.cpp)[m
 [m
 add_library(renderer ${RENDERER_SOURCES})[m
 [m
[1mdiff --git a/resources/shaders/emmit_sin.geom b/resources/shaders/emmit_sin.geom[m
[1mindex 3e62a30..2c9a35d 100644[m
[1m--- a/resources/shaders/emmit_sin.geom[m
[1m+++ b/resources/shaders/emmit_sin.geom[m
[36m@@ -3,7 +3,7 @@[m
 layout(points) in;[m
 layout(points, max_vertices = 32) out;[m
 [m
[31m-uniform float time;[m
[32m+[m[32muniform float uTime;[m
 [m
 in VS_OUT {[m
     vec4 color;[m
[36m@@ -17,14 +17,13 @@[m [mconst float y_scale = 0.85;[m
 [m
 void main() {[m
     fragColor = gs_in[0].color;[m
[31m-[m
     float fVertices = float(vertices);[m
     float unit = 2 / fVertices;[m
     float offset = -0.5 * unit * fVertices + 0.5 * unit;[m
 [m
     for (int i = 0; i < vertices; i++) {[m
         float x = offset + (i * unit);[m
[31m-        float y = y_scale * sin(x_scale * x + time);[m
[32m+[m[32m        float y = y_scale * sin(x_scale * x + uTime);[m
         gl_Position = gl_in[0].gl_Position + vec4(x, y, 0.0, 0.0);[m
         EmitVertex();[m
     }[m
[1mdiff --git a/src/renderer/primitives/line.cpp b/src/renderer/primitives/line.cpp[m
[1mindex d3a8274..a619edd 100644[m
[1m--- a/src/renderer/primitives/line.cpp[m
[1m+++ b/src/renderer/primitives/line.cpp[m
[36m@@ -1,5 +1,6 @@[m
 [m
 #include "line.h"[m
[32m+[m[32m#include "../../utils/constants.cpp"[m
 [m
 #include <GL/gl.h>[m
 #include <glm/ext/matrix_float4x4.hpp>[m
[36m@@ -30,8 +31,8 @@[m [mLine::Line(glm::vec3 start, glm::vec3 end)[m
 [m
 void Line::Draw(const glm::mat4 &PV) {[m
   shader.Use();[m
[31m-  shader.SetMat4Uniform(Shader::Keywords::MVP, CalculateMVP(PV));[m
[31m-  shader.SetVec4Uniform(Shader::Keywords::Color, color);[m
[32m+[m[32m  shader.SetMat4Uniform(constants::shader::MVP, CalculateMVP(PV));[m
[32m+[m[32m  shader.SetVec4Uniform(constants::shader::color, color);[m
   glBindVertexArray(VAO);[m
 [m
   glDrawArrays(GL_LINES, 0, 2);[m
[1mdiff --git a/src/renderer/primitives/point.cpp b/src/renderer/primitives/point.cpp[m
[1mindex a6ba315..010bea6 100644[m
[1m--- a/src/renderer/primitives/point.cpp[m
[1m+++ b/src/renderer/primitives/point.cpp[m
[36m@@ -3,15 +3,14 @@[m
 #include <GL/gl.h>[m
 #include <glm/ext/matrix_float4x4.hpp>[m
 #include <glm/ext/vector_float3.hpp>[m
[32m+[m[32m#include "../../utils/constants.cpp"[m
 [m
 const std::string VERTEX_SHADER_PATH{"../resources/shaders/point.vert"};[m
 const std::string FRAGMENT_SHADER_PATH{"../resources/shaders/point.frag"};[m
[31m-const std::string GEOMETRY_SHADER_PATH{"../resources/shaders/emmit_sin.geom"};[m
 [m
 [m
 Point::Point()[m
[31m-    : Primitive(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH,[m
[31m-                GEOMETRY_SHADER_PATH) {[m
[32m+[m[32m    : Primitive(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH) {[m
 [m
   glGenVertexArrays(1, &VAO);[m
   glGenBuffers(1, &VBO);[m
[36m@@ -32,8 +31,8 @@[m [mPoint::Point()[m
 void Point::Draw(const glm::mat4 &PV) {[m
 [m
   shader.Use();[m
[31m-  shader.SetMat4Uniform(Shader::Keywords::MVP, CalculateMVP(PV));[m
[31m-  shader.SetVec4Uniform(Shader::Keywords::Color, color);[m
[32m+[m[32m  shader.SetMat4Uniform(constants::shader::MVP, CalculateMVP(PV));[m
[32m+[m[32m  shader.SetVec4Uniform(constants::shader::color, color);[m
   glBindVertexArray(VAO);[m
 [m
   glPointSize(size);[m
[1mdiff --git a/src/renderer/primitives/square.cpp b/src/renderer/primitives/square.cpp[m
[1mindex 65e6f73..d2d92ba 100644[m
[1m--- a/src/renderer/primitives/square.cpp[m
[1m+++ b/src/renderer/primitives/square.cpp[m
[36m@@ -1,6 +1,8 @@[m
 #include "square.h"[m
 #include "primitives/primitive.h"[m
 [m
[32m+[m[32m#include "../../utils/constants.cpp"[m
[32m+[m
 #include <glm/ext/matrix_float4x4.hpp>[m
 #include <glm/ext/vector_float3.hpp>[m
 [m
[36m@@ -28,8 +30,8 @@[m [mSquare::Square() : Primitive(VERTEX_SHADER_PATH, FRAG_SHADER_PATH) {[m
 void Square::Draw(const glm::mat4 &PV) {[m
 [m
   shader.Use();[m
[31m-  shader.SetMat4Uniform(Shader::Keywords::MVP, CalculateMVP(PV));[m
[31m-  shader.SetVec4Uniform(Shader::Keywords::Color, color);[m
[32m+[m[32m  shader.SetMat4Uniform(constants::shader::MVP, CalculateMVP(PV));[m
[32m+[m[32m  shader.SetVec4Uniform(constants::shader::color, color);[m
   glBindVertexArray(VAO);[m
 [m
   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);[m
[1mdiff --git a/src/renderer/primitives/triangle.cpp b/src/renderer/primitives/triangle.cpp[m
[1mindex f5c41f9..796acff 100644[m
[1m--- a/src/renderer/primitives/triangle.cpp[m
[1m+++ b/src/renderer/primitives/triangle.cpp[m
[36m@@ -1,4 +1,5 @@[m
 #include "triangle.h"[m
[32m+[m[32m#include "../../utils/constants.cpp"[m
 [m
 const std::string VERTEX_SHADER_PATH{"../resources/shaders/triangle.vert"};[m
 const std::string FRAG_SHADER_PATH{"../resources/shaders/triangle.frag"};[m
[36m@@ -18,12 +19,12 @@[m [mTriangle::Triangle() : Primitive(VERTEX_SHADER_PATH, FRAG_SHADER_PATH) {[m
 }[m
 [m
 void Triangle::Draw(const glm::mat4 &PV) {[m
[31m-[m
   shader.Use();[m
[31m-  shader.SetMat4Uniform(Shader::Keywords::MVP, CalculateMVP(PV));[m
[31m-  shader.SetVec4Uniform(Shader::Keywords::Color, color);[m
[32m+[m[32m  shader.SetMat4Uniform(constants::shader::MVP, CalculateMVP(PV));[m
[32m+[m[32m  shader.SetVec4Uniform(constants::shader::color, color);[m
 [m
   glBindVertexArray(VAO);[m
[32m+[m
   glDrawArrays(GL_TRIANGLES, 0, 3);[m
 [m
   glBindVertexArray(0);[m
[1mdiff --git a/src/renderer/renderer.cpp b/src/renderer/renderer.cpp[m
[1mindex d92f36f..8121881 100644[m
[1m--- a/src/renderer/renderer.cpp[m
[1m+++ b/src/renderer/renderer.cpp[m
[36m@@ -20,6 +20,8 @@[m
 #include "primitives/primitive.h"[m
 #include "sceneProvider.h"[m
 [m
[32m+[m[32m#include "../utils/constants.cpp"[m
[32m+[m
 #include <iostream>[m
 #include <memory>[m
 #include <ostream>[m
[36m@@ -56,7 +58,7 @@[m [mbool Renderer::Initialize() {[m
   glViewport(0, 0, start_width, start_height);[m
   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);[m
 [m
[31m-  canvas = std::shared_ptr(SceneProvider::GetWorkingScene());[m
[32m+[m[32m  root = std::shared_ptr(SceneProvider::GetWorkingScene());[m
 [m
   ui = GUI();[m
 [m
[36m@@ -69,6 +71,8 @@[m [mbool Renderer::Initialize() {[m
   return true;[m
 }[m
 [m
[32m+[m[32mglm::vec4 color;[m
[32m+[m
 void Renderer::Update() {[m
 [m
   float aspect = Renderer::start_width / Renderer::start_height;[m
[36m@@ -86,7 +90,8 @@[m [mvoid Renderer::Update() {[m
 [m
   glClear(GL_COLOR_BUFFER_BIT);[m
 [m
[31m-  RenderScene(canvas);[m
[32m+[m[32m  RenderScene(root);[m
[32m+[m[32m  ui.DrawColorWindow(color);[m
 [m
   ImGui::Render();[m
   ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());[m
[36m@@ -97,8 +102,8 @@[m [mvoid Renderer::Update() {[m
 [m
 void Renderer::RenderScene(const std::shared_ptr<Primitive> &root) {[m
   auto PV = projection * view;[m
[32m+[m[32m  root->shader.SetFloatUniform(constants::shader::time, glfwGetTime());[m
   root->DrawRecursive(PV);[m
[31m-  root->shader.SetFloatUniform("time", glfwGetTime());[m
 }[m
 [m
 bool Renderer::CreateWindow() {[m
[1mdiff --git a/src/renderer/renderer.h b/src/renderer/renderer.h[m
[1mindex f0be068..d45558c 100644[m
[1m--- a/src/renderer/renderer.h[m
[1m+++ b/src/renderer/renderer.h[m
[36m@@ -31,7 +31,7 @@[m [mprivate:[m
   bool CreateWindow();[m
   void RenderScene(const std::shared_ptr<Primitive> &root);[m
 [m
[31m-  std::shared_ptr<Primitive> canvas;[m
[32m+[m[32m  std::shared_ptr<Primitive> root;[m
 };[m
 [m
 void framebuffer_size_callback(GLFWwindow *window, int width, int height);[m
[1mdiff --git a/src/renderer/sceneProvider.h b/src/renderer/sceneProvider.h[m
[1mindex fa0d490..dabae33 100644[m
[1m--- a/src/renderer/sceneProvider.h[m
[1m+++ b/src/renderer/sceneProvider.h[m
[36m@@ -1,3 +1,4 @@[m
[32m+[m[32m#include "graph/graph.h"[m
 #include "primitives/line.h"[m
 #include "primitives/point.h"[m
 #include "primitives/primitive.h"[m
[36m@@ -45,14 +46,8 @@[m [mstatic std::unique_ptr<Primitive> SceneProvider::GetSamleScene() {[m
 }[m
 [m
 static std::unique_ptr<Primitive> SceneProvider::GetWorkingScene() {[m
[31m-  auto root = std::make_unique<Point>();[m
[32m+[m[32m  auto root = std::make_unique<Graph>();[m
   root->color = glm::vec4(0.0f);[m
   root->size = 10;[m
[31m-[m
[31m-  // auto point = std::make_shared<Point>();[m
[31m-  // point->transform.position += glm::vec3(0, 0.5, 0);[m
[31m-  // point->color = glm::vec4(0.0f);[m
[31m-  // point->size = 5;[m
[31m-  // root->AddChild(point);[m
   return root;[m
 }[m
[1mdiff --git a/src/renderer/shader.cpp b/src/renderer/shader.cpp[m
[1mindex 7623562..3486006 100644[m
[1m--- a/src/renderer/shader.cpp[m
[1m+++ b/src/renderer/shader.cpp[m
[36m@@ -2,6 +2,7 @@[m
 #include "glm/gtc/type_ptr.hpp"[m
 [m
 #include <GL/gl.h>[m
[32m+[m[32m#include <GLFW/glfw3.h>[m
 #include <cassert>[m
 #include <fstream>[m
 #include <iostream>[m
[1mdiff --git a/src/renderer/shader.h b/src/renderer/shader.h[m
[1mindex a260ced..b74ec65 100644[m
[1m--- a/src/renderer/shader.h[m
[1m+++ b/src/renderer/shader.h[m
[36m@@ -34,11 +34,4 @@[m [mprivate:[m
 [m
   static std::string *ReadShader(const std::string &pathToShader);[m
   void CheckLinking(unsigned int id) const;[m
[31m-[m
[31m-public:[m
[31m-  class Keywords {[m
[31m-  public:[m
[31m-    static constexpr char MVP[] = "MVP";[m
[31m-    static constexpr char Color[] = "uColor";[m
[31m-  };[m
 };[m
