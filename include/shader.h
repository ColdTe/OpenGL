#ifndef SHADER_H
#define SHADER_H
#include<filesystem>
#include<sstream>
#include<fstream>
#include<string>

class Shader{
  private:
    std::string fstr{};
    std::string vstr{};
    std::ifstream vfile;
    std::ifstream ffile;
    std::stringstream ss;
    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int shaderProgram;
    std::stringstream vShaderStream;
    std::stringstream fShaderStream;
  public:
    Shader(std::filesystem::path vertexPath, std::filesystem::path fragmentPath){
     vfile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
     ffile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
     try{
      vfile.open(vertexPath);
      vShaderStream << vfile.rdbuf();
      vfile.close();
      ffile.open(fragmentPath);

      fShaderStream << ffile.rdbuf();
      ffile.close();
      fstr = fShaderStream.str();
      vstr = vShaderStream.str();
      }
     catch(const std::ifstream::failure &e){
       std::cout << "ERROR::SHADER::FILE::NOT_SUCCESSFULLY_READ\n";
     }
      const char* fcstr = fstr.c_str();
      const char* vcstr = vstr.c_str();
     vertexShader = glCreateShader(GL_VERTEX_SHADER);
      glShaderSource(vertexShader,1,&vcstr,NULL);
      glCompileShader(vertexShader);
      int success;
      char infoLog[512];
      glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
      if(!success){
        glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
        std::cout << "VERTEX::SHADER::COMPILATION::ERROR\n" << infoLog << '\n';
      } 
      fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(fragmentShader,1,&fcstr,NULL);
      glCompileShader(fragmentShader);
      glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
      if(!success){
        glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
        std::cout << "FRAGMENT::SHADER::COMPILATION::ERROR\n" << infoLog << '\n' ;
         }
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram,vertexShader);
        glAttachShader(shaderProgram,fragmentShader);
        glLinkProgram(shaderProgram);
        glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
        if(!success){
          glGetProgramInfoLog(shaderProgram,512,NULL,infoLog);
          std::cout << "SHADER::PROGRAM::COMPILATION::ERROR\n" << infoLog << '\n';
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
    void useProgram() const {
      glUseProgram(shaderProgram);
    }
    void setBool(const std::string &name, bool value) const { glUniform1i(glGetUniformLocation(shaderProgram,name.c_str()), (int)value); }
    
    void setInt(const std::string &name, int value) const { glUniform1i(glGetUniformLocation(shaderProgram,name.c_str()),value);}
    
    void setFloat(const std::string &name, float value) const { glUniform1f(glGetUniformLocation(shaderProgram,name.c_str()),(int)value);
    
    }
    void deleteProgram() const {
      glDeleteProgram(shaderProgram);
    }
};

#endif
