#pragma once

#include<geGL/OpenGLFunctionTable.h>

namespace ge{
  namespace gl{
    namespace opengl{
      template<typename T>
        class TrapTableDecorator: public T{
          public:
            template<typename...ARGS>
              TrapTableDecorator(ARGS&&...args):T(args...){}
            virtual~TrapTableDecorator(){}
          protected:
            virtual bool m_init(){
              if(!T::m_init())return false;
#include<geGL/Generated/TrapCalls.h>
              return true;
            }
            void m_printMissingFunctionErrorAndExit(std::string fceName)const{
              std::cerr<<"ERROR: function: "<<fceName<<" == nullptr"<<std::endl;
              std::exit(1);
            }
#include<geGL/Generated/TrapImplementation.h>
        };

    }
  }
}

