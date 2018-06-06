//
// Created by Hython on 2018/4/26.
//

#include <Shader.h>
#include <glad/glad.h>

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath, const std::string &geomPath) {
    std::string vertexCode;
    std::string fragmentCode;

    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    int success;
    char infoLog[512];


    try{
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode= vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }catch(std::ifstream::failure& e){
        std::cout<< "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex,1,&vShaderCode, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cout<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"<< infoLog<<std::endl;
    }
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment,1,&fShaderCode, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(vertex,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(fragment,512, nullptr,infoLog);
        std::cout<<"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"<< infoLog<<std::endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    unsigned int geometry;
    if(!geomPath.empty()){
        std::string geomCode;
        std::ifstream gShaderFile;
        gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try{
            gShaderFile.open(geomPath);
            std::stringstream gShaderStream;
            gShaderStream << gShaderFile.rdbuf();
            gShaderFile.close();
            geomCode = gShaderStream.str();
        }catch (std::ifstream::failure& e){
            std::cout<< "ERROR::GSHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
        }
        const char* gShaderCode = geomCode.c_str();

        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry,1,&gShaderCode, nullptr);
        glCompileShader(geometry);
        glGetShaderiv(geometry,GL_COMPILE_STATUS,&success);
        if(!success){
            glGetShaderInfoLog(geometry,512, nullptr,infoLog);
            std::cout<<"ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n"<< infoLog<<std::endl;
        }
        glAttachShader(ID, geometry);
    }

    glLinkProgram(ID);
    glGetProgramiv(ID,GL_LINK_STATUS,&success);
    if(!success){
        glGetProgramInfoLog(ID,512, nullptr,infoLog);
        std::cout<<"ERROR::SHADER::PROGRAM::LINKING_FAILED\n"<<infoLog<<std::endl;
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if(!geomPath.empty()){
        glDeleteShader(geometry);
    }
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID,name.c_str()),(int)value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID,name.c_str()),value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID,name.c_str()),value);
}
