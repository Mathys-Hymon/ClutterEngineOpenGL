#include "pch.h"  
#include <glad/glad.h>  
#include <sstream>  
#include <fstream>  
#include<Graphics/Renderer.h>  
#include<Core/ActorComponent/Actor.h>  
#include<Core/ActorComponent/Components/Graphics/SpriteComponent.h>  

using namespace clt;  

Renderer::Renderer()  
{  
   // Initialize GLAD to load OpenGL functions  
   if (gladLoadGL()) CLUTTER_LOG("GLAD initialised successfully")  
   else CLUTTER_ERROR("Cant initialise GLAD");  

   Assets::Get().SetRenderer(this);  

   // File paths for vertex and fragment shaders  
   const auto vert_file_path = "Content/Shaders/triangle.vert";  
   const auto frag_file_path = "Content/Shaders/triangle.frag";

   std::string vert_code;  
   std::string frag_code;  

   try  
   {  
       // Read shader files  
       std::ifstream vert_file(vert_file_path);  
       std::ifstream frag_file(frag_file_path);  
       std::stringstream vert_sstream, frag_sstream;  

       vert_sstream << vert_file.rdbuf();  
       frag_sstream << frag_file.rdbuf();  

       vert_file.close();  
       frag_file.close();  

       vert_code = vert_sstream.str();  
       frag_code = frag_sstream.str();  
   }  
   catch (std::exception e)  
   {  
       CLUTTER_ERROR("shader files failed to load");  
   }  

   auto vert_code_c_str = vert_code.c_str();  
   auto frag_code_c_str = frag_code.c_str();  

   GLuint vertexShader, fragShader, program;  

   GLint success;  
   GLchar info_log[512];  

   // Create and compile vertex shader  
   vertexShader = glCreateShader(GL_VERTEX_SHADER);  
   glShaderSource(vertexShader, 1, &vert_code_c_str, nullptr);  
   glCompileShader(vertexShader);  

   // Check for vertex shader compilation errors  
   glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);  
   if (!success)  
   {  
       glGetShaderInfoLog(vertexShader, 512, nullptr, info_log);  
       std::string error_message = "Vertex shader compilation failure, vertexShader = " + std::string(vert_code_c_str) + "\n" + std::string(info_log);  
       CLUTTER_ERROR(error_message.c_str());  
   }
   else CLUTTER_LOG("Vertex shader compiled succesfully");

   success = 0;  
   // Create and compile fragment shader  
   fragShader = glCreateShader(GL_FRAGMENT_SHADER);  
   glShaderSource(fragShader, 1, &frag_code_c_str, nullptr);  
   glCompileShader(fragShader);  

   // Check for fragment shader compilation errors  
   glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);  
   if (!success)
   {
       glGetShaderInfoLog(fragShader, 512, nullptr, info_log);
       std::string error_message = "Fragment shader compilation failure, fragShader = " + std::string(frag_code_c_str) + "\n" + std::string(info_log);
       CLUTTER_ERROR(error_message.c_str());
   }
   else CLUTTER_LOG("Fragment shader compiled succesfully");

   program = glCreateProgram();  

   glAttachShader(program, vertexShader);  
   glAttachShader(program, fragShader);  

   glLinkProgram(program);  

   glGetProgramiv(program, GL_LINK_STATUS, &success);  
   if (!success)
   {
       glGetProgramInfoLog(program, 512, nullptr, info_log);
       std::string error_message = "Program linking failure:\n" + std::string(info_log);
       CLUTTER_ERROR(error_message.c_str());
   }
   else CLUTTER_INFO("Shader Program linked");

   glDeleteShader(vertexShader);
   glDeleteShader(fragShader);

   glUseProgram(program);
}  

Renderer::~Renderer()  
{  
   Assets::Get().ClearTextures();  
}  

void Renderer::RegisterTextureUsage(Texture* pTexture)  
{  
   mBindedTextures.insert(pTexture);  
}  

void Renderer::AddGraphicComponent(GraphicComponent* pComp)  
{  
   int compDrawOrder = pComp->GetDrawOrder();  

   if (!mComponents.empty())  
   {  
       std::vector<GraphicComponent*>::iterator gc;  
       for (gc = mComponents.begin(); gc != mComponents.end(); gc++)  
       {  
           if (compDrawOrder < (*gc)->GetDrawOrder()) break;  
       }  
       mComponents.insert(gc, pComp);  
   }  
   else  
   {  
       mComponents.emplace_back(pComp);  
   }  
}  

void Renderer::RemoveGraphicComponent(GraphicComponent* pComp)  
{  
   std::vector<GraphicComponent*>::iterator gc;  
   gc = std::find(mComponents.begin(), mComponents.end(), pComp);  
   mComponents.erase(gc);  
}  

void Renderer::BeginDraw()  
{  
   glClearColor(0.1f, 0.1f, 0.1f, 1.0f);         // Define the background Color  
   glClear(GL_COLOR_BUFFER_BIT);                 // Clear the background color and depth  
   glDepthFunc(GL_LESS);  

   for (Texture* tex : mBindedTextures)  
   {  
       tex->Bind();  
   }  
}  

void Renderer::Draw()  
{  
   for (GraphicComponent* comp : mComponents)  
   {  
       comp->Draw(*this);  
   }  
}  

void Renderer::DrawSprite(const Actor& pActor, const Texture& pTexture, CRectangle pRect, Vector2 pOrigin) const  
{  
}  

void Renderer::EndDraw()  
{  
   for (Texture* tex : mBindedTextures)  
   {  
       tex->UnBind();  
   }  
}