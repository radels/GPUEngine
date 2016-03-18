#pragma once

#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<memory>
#include<sstream>
#include<cstring>
#include<geCore/dtemplates.h>
#include<geCore/Export.h>
#include<geCore/syntaxTree.h>
#include<geCore/tokenization.h>

namespace ge{
  namespace core{

    class GECORE_EXPORT Syntax{
      public:
        NodeContext ctx;
        SyntaxNode::Node st_root=nullptr;
        std::string start;
        std::map<std::string,std::shared_ptr<Symbol>>name2Nonterm;
        std::map<Token::Type,std::shared_ptr<Symbol>>name2Term   ;

        std::shared_ptr<SyntaxNode>root = nullptr;
        std::shared_ptr<SyntaxNode>currentNode = nullptr;

        std::shared_ptr<Symbol>const&_addNonterm(std::string    name);
        std::shared_ptr<Symbol>const&_addTerm   (Token::Type const&type);

        Range<TokenIndex> _range;
        std::shared_ptr<Tokenization>_tokenization;
      public:
        Syntax(std::string start);
        Syntax(std::string start,std::shared_ptr<Tokenization>const&tokenization);
        Syntax(std::string lexSource,std::string synSource);
        void addRule(std::vector<std::string>params);
        ~Syntax();
        void begin();
        std::pair<NodeContext::Status,SyntaxNode::Node>parse(std::string data);
        void end();

        SyntaxNode::Node getSyntaxTree()const;
        void runStart();
        NodeContext::Status runContinue();

        template<typename...>
          void addToken();
        template<typename...ARGS>
          void addToken(Token const&token,ARGS...args);

        void computeLengths();
        std::string str()const;
    };

    template<typename...>
      void Syntax::addToken(){
      }

    template<typename...ARGS>
      void Syntax::addToken(Token const&token,ARGS...args){
        this->ctx.addToken(token);
        this->addToken(args...);
      }
  }
}
