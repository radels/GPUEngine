#include<geCore/syntaxTreeProcessor.h>

using namespace ge::core;

void SyntaxTreeProcessor::addCallback(
    std::string nonterm ,
    std::string ruleName,
    Callback    pre     ,
    Callback    post    ,
    void*       data    ){
  this->_callbacks[Key(nonterm,ruleName)]=Value(pre,post,data);
}

void SyntaxTreeProcessor::operator()(SyntaxNode::Node root)const{
  if(!root->isNonterm())return;
  auto n = std::dynamic_pointer_cast<NontermNode>(root);
  auto key = Key(n->getNonterm()->name,n->getNonterm()->getRuleName(n->side));
  auto ii = this->_callbacks.find(key);
  if(ii==this->_callbacks.end())return;
  if(std::get<PRE>(ii->second))std::get<PRE>(ii->second)(root,std::get<DATA>(ii->second));
  for(auto x:n->childs)
    this->operator()(x);
  if(std::get<POST>(ii->second))std::get<POST>(ii->second)(root,std::get<DATA>(ii->second));
}
