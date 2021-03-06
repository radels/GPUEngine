#include<geUtil/CameraObject.h>

#include <limits>
#include<sstream>
#include<iostream>
#include<fstream>
#include<cstdlib>
#include <streambuf>

using namespace ge::util;

CameraObject::CameraObject(unsigned const Size[2],float Near,float Far,float Fovy){
  this->_size[0]      = Size[0];//sets width of viewport/window
  this->_size[1]      = Size[1];//sets height of viewport/window
  this->_near         = Near;//near plane
  this->_far          = Far;//far plane
  this->_fovy         = Fovy;//field of view
  this->_viewRotation = glm::mat4(1.f);//sets view rotation matrix
  this->_position     = glm::vec3(0.f);//sets position
  this->_computeProjection();//compute projection matrix 
}
void CameraObject::_computeProjection(){
  if(this->_far==std::numeric_limits<float>::infinity()){//is far inifinty?
    float top=glm::tan(glm::radians(this->_fovy/2))*this->_near;//top border of viewport
    float bottom=-top;//bottom border of viewport
    float right=(top*(float)this->_size[0])/(float)this->_size[1];//right border of viewport
    float left=-right;//left border of viewport
    //0. column
    this->_projection[0][0]=2*this->_near/(right-left);
    this->_projection[0][1]=0;
    this->_projection[0][2]=0;
    this->_projection[0][3]=0;
    //1. column
    this->_projection[1][0]=0;
    this->_projection[1][1]=2*this->_near/(top-bottom);
    this->_projection[1][2]=0;
    this->_projection[1][3]=0;
    //2. column
    this->_projection[2][0]=(right+left)/(right-left);
    this->_projection[2][1]=(top+bottom)/(top-bottom);
    this->_projection[2][2]=-1;
    this->_projection[2][3]=-1;
    //3. column
    this->_projection[3][0]=0;
    this->_projection[3][1]=0;
    this->_projection[3][2]=-2*this->_near;
    this->_projection[3][3]=0;
  }else//far is finite
    this->_projection=glm::perspective(
        glm::radians<float>(this->_fovy),//field of view
        (float)this->_size[0]/(float)this->_size[1],//aspect ratio
        this->_near,//near plane
        this->_far);//far plane
}
void CameraObject::left(float Dx){
  this->_position-=Dx*glm::vec3(glm::row(this->_viewRotation,0));
}
void CameraObject::right(float Dx){
  this->_position+=Dx*glm::vec3(glm::row(this->_viewRotation,0));
}
void CameraObject::down(float Dy){
  this->_position-=Dy*glm::vec3(glm::row(this->_viewRotation,1));
}
void CameraObject::up(float Dy){
  this->_position+=Dy*glm::vec3(glm::row(this->_viewRotation,1));
}
void CameraObject::forward(float Dz){
  this->_position-=Dz*glm::vec3(glm::row(this->_viewRotation,2));
}
void CameraObject::back(float Dz){
  this->_position+=Dz*glm::vec3(glm::row(this->_viewRotation,2));
}
void CameraObject::setSize(unsigned const size[2]){
  this->_size[0]      = size[0];
  this->_size[1]      = size[1];
  this->_computeProjection();
}
void CameraObject::setFovy(float Fovy){
  this->_fovy=Fovy;
  this->_computeProjection();
}
void CameraObject::setNear(float Near){
  this->_near=Near;
  this->_computeProjection();
}
void CameraObject::setFar(float Far){
  this->_far=Far;
  this->_computeProjection();
}
void CameraObject::setNearFar(float Near,float Far){
  this->_near=Near;
  this->_far=Far;
  this->_computeProjection();
}
void CameraObject::fpsCamera(float Rx,float Ry,float Rz){
  this->_viewRotation=
    (glm::rotate(glm::mat4(1.),Rz,glm::vec3(0,0,1))*
     (glm::rotate(glm::mat4(1.),Rx,glm::vec3(1,0,0))*
      glm::rotate(glm::mat4(1.),Ry,glm::vec3(0,1,0))));
}
void CameraObject::setView(float*P,float*Look,float*V){
  for(int k=0;k<3;++k)this->_position[k]=P[k];
  glm::vec3 Z=glm::normalize(glm::vec3(-Look[0],-Look[1],-Look[2]));
  glm::vec3 Y=glm::normalize(glm::vec3(V[0],V[1],V[2]));
  glm::vec3 X=glm::normalize(glm::cross(Y,Z));
  for(int k=0;k<3;++k)this->_viewRotation[k][0]=X[k];
  for(int k=0;k<3;++k)this->_viewRotation[k][1]=Y[k];
  for(int k=0;k<3;++k)this->_viewRotation[k][2]=Z[k];
  for(int k=0;k<3;++k)this->_viewRotation[k][3]=0;
  for(int k=0;k<3;++k)this->_viewRotation[3][k]=0;
  this->_viewRotation[3][3]=1;
}
void CameraObject::getView(glm::mat4*V){
  *V=this->_viewRotation*glm::translate(glm::mat4(1.f),-this->_position);
  /*glm::mat4 ViewTranslate=glm::translate(glm::mat4(1.f),this->Position);
    return this->ViewRotation*ViewTranslate;*/
}
void CameraObject::getViewRoration(glm::mat4*V){
  *V=this->_viewRotation;
}

void CameraObject::getProjection(glm::mat4*P){
  this->_computeProjection();
  *P=this->_projection;
  //return this->Projection;
}
glm::mat4 CameraObject::getView(){
  return this->_viewRotation*glm::translate(glm::mat4(1.f),-this->_position);
}
glm::mat4 CameraObject::getViewRoration(){
  return this->_viewRotation;
}
glm::mat4 CameraObject::getProjection(){
  this->_computeProjection();
  return this->_projection;
}
glm::vec3 CameraObject::getPosition(){
  return this->_position;
}
void CameraObject::setPosition(glm::vec3 p){
  this->_position=p;
}
glm::vec3 CameraObject::getVector(int k){
  return glm::vec3(glm::row(this->_viewRotation,k));
}
float CameraObject::getFovy(){
  return this->_fovy;
}
float CameraObject::getNear(){
  return this->_near;
}
float CameraObject::getFar(){
  return this->_far;
}
std::string CameraObject::toString(){
  std::stringstream ss;
  ss<<this->_size[0]<<" ";
  ss<<this->_size[1]<<" ";
  ss<<this->_fovy<<" ";
  ss<<this->_near<<" ";
  ss<<this->_far<<" ";
  ss<<this->_position[0]<<" "<<this->_position[1]<<" "<<this->_position[2]<<" ";
  for(unsigned i=0;i<16;++i){
    ss<<glm::value_ptr(this->_viewRotation)[i];
    if(i<15)ss<<" ";
  }
  return ss.str();
}
void CameraObject::saveToFile(std::string file){
  std::ofstream out(file.c_str());
  out<<this->toString();
  out.close();
}

void CameraObject::loadFromString(std::string data){
  std::size_t pos=0;
  pos=data.find(" ");
  this->_size[0]=std::atoi(data.substr(0,pos).c_str());
  data=data.substr(pos+1);pos=data.find(" ");
  this->_size[1]=std::atoi(data.substr(0,pos).c_str());

  data=data.substr(pos+1);pos=data.find(" ");
  this->_fovy=(float)std::atof(data.substr(0,pos).c_str());

  data=data.substr(pos+1);pos=data.find(" ");
  this->_near=(float)std::atof(data.substr(0,pos).c_str());

  data=data.substr(pos+1);pos=data.find(" ");
  this->_far=(float)std::atof(data.substr(0,pos).c_str());

  data=data.substr(pos+1);pos=data.find(" ");
  this->_position[0]=(float)std::atof(data.substr(0,pos).c_str());
  data=data.substr(pos+1);pos=data.find(" ");
  this->_position[1]=(float)std::atof(data.substr(0,pos).c_str());
  data=data.substr(pos+1);pos=data.find(" ");
  this->_position[2]=(float)std::atof(data.substr(0,pos).c_str());

  for(unsigned i=0;i<15;++i){
    data=data.substr(pos+1);pos=data.find(" ");
    glm::value_ptr(this->_viewRotation)[i]=(float)std::atof(data.substr(0,pos).c_str());
  }
  data=data.substr(pos+1);
  glm::value_ptr(this->_viewRotation)[15]=(float)std::atof(data.c_str());
  this->_computeProjection();
}
void CameraObject::loadFromFile(std::string file){
  std::ifstream t(file.c_str());
  std::string str;

  t.seekg(0, std::ios::end);   
  str.reserve(t.tellg());
  t.seekg(0, std::ios::beg);

  str.assign((std::istreambuf_iterator<char>(t)),
      std::istreambuf_iterator<char>());
  t.close();
  this->loadFromString(str);
}





glm::vec3 CameraObject::getPickVector(unsigned x,unsigned y){
  float dy=2.f*(float)x/(float)this->_size[0]-1.f;
  float dx=2.f*(float)y/(float)this->_size[1]-1.f;

  float ratio=(float)this->_size[0]/(float)this->_size[1];
  float tangle=tanf(this->_fovy/2.f);
  glm::vec3 X= glm::vec3(glm::row(this->_viewRotation,0));
  glm::vec3 Y= glm::vec3(glm::row(this->_viewRotation,1));
  glm::vec3 Z=-glm::vec3(glm::row(this->_viewRotation,2));

  X*=ratio*tangle*dy;
  Y*=-1*tangle*dx;
  return glm::normalize(X+Y+Z);
}


