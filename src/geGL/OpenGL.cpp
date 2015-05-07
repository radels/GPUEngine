#include <geGL/OpenGL.h>

namespace ge
{
  namespace gl
  {

    void CommandContainer::reset(){
      this->command = NULL;
      this->ref     = false;
    }

    void CommandContainer::free(){
      if(this->command&&!this->ref)delete this->command;
      this->reset();
    }


    void CommandContainer::apply()
    {
      if(this->command)this->command->apply();
    }

    void CommandList::apply()
    {
      for(unsigned i=0;i<this->commands.size();++i)
        this->commands[i]->apply();
    }

    CommandList::CommandList(bool outOfOrder){
      this->outOfOrder=outOfOrder;
    }
    void CommandList::add(Command*commands){
      this->commands.push_back(commands);
    }


    void CommandIf::apply(){
      this->statement->apply();
      if(this->statement->isTrue){
        if(this->trueBranch)this->trueBranch->apply();
      }else{
        if(this->falseBranch)this->falseBranch->apply();
      }
    }
    //stepable while, semistepable while, deepstepable command
    void CommandWhile::apply(){
      if(!this->body)return;
      for(;;){
        this->statement->apply();
        if(!this->statement->isTrue)break;
        this->body->apply();
      }
    }
  }//ogl
}//ge
