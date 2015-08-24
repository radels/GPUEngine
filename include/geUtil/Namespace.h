#pragma once

#include<iostream>
#include<vector>
#include<map>
#include<geCore/TypeRegister.h>

namespace ge{
  namespace util{
    namespace sim{
      class Namespace{
        protected:
          std::string _name  ;
          Namespace*  _parent;
          std::map<std::string,Namespace*>_name2Namespace   ;
          std::map<std::string,std::shared_ptr<ge::core::Accessor>> _name2Variable;
          std::string _toUpper(std::string str);
        public:
          Namespace(std::string name,Namespace*parent=NULL);
          virtual ~Namespace();
          bool empty();
          void setParent(Namespace*parent=NULL);
          void insertNamespace(std::string name,Namespace*nmspace);
          void insert(std::string name,std::shared_ptr<ge::core::Accessor>const&variable);
          void erase(std::string name);
          std::string toStr(unsigned indentation);
          Namespace*getNamespace(std::string name);
          std::shared_ptr<ge::core::Accessor>&getVariable(std::string name);
          bool contain(std::string name);
          template<typename TYPE>
            TYPE&get(std::string name){
              return (TYPE&)(*this->getVariable(name));
            }
          template<typename TYPE>
            TYPE&get(std::string name,TYPE def){
              if(!this->contain(name))return def;
              return (TYPE&)(*this->getVariable(name));
            }

      };
    }
  }
}
