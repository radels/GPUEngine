#include"OpenGL.h"

namespace ge
{
  namespace ogl
  {
    void CommandContainer::reset(){
      this->command = NULL;
      this->ref     = false;
    }
    void CommandContainer::free(){
      if(this->command&&!this->ref)delete this->command;
      this->reset();
    }
    void CommandContainer::apply(){
      if(this->command)this->command->apply();
    }
    void CommandList::apply(){
      for(unsigned i=0;i<this->commands.size();++i)
        this->commands[i]->apply();
    }
  }//ogl
}//ge
