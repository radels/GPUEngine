#pragma once

#include<geCore/Function.h>

namespace ge{
  namespace core{
    class GECORE_EXPORT AtomicFunctionInput{
      public:
        bool changed                = false;
        Function::Ticks updateTicks = 0    ;
        std::shared_ptr<Function>function = nullptr;
        AtomicFunctionInput(
            std::shared_ptr<Function>const&fce         = nullptr,
            Function::Ticks                updateTicks = 0      ,
            bool                           changed     = false  );
        virtual ~AtomicFunctionInput();
    };

    class StatementFactory;

    class GECORE_EXPORT AtomicFunction: public Function{
      public:
        using InputList  = std::vector<AtomicFunctionInput>;
        using InputIndex = InputList::size_type;
      protected:
        InputList                _inputs               ;
        unsigned long long       _checkTicks  = 0      ;
        unsigned long long       _updateTicks = 1      ;
        std::shared_ptr<Accessor>_outputData  = nullptr;
      public:
        AtomicFunction(
            std::shared_ptr<FunctionRegister>const&fr,
            FunctionRegister::FunctionID           id);
        AtomicFunction(
            std::shared_ptr<FunctionRegister>const&fr                       ,
            TypeRegister::DescriptionList const&   typeDescription          ,
            std::string                            name            = ""     ,
            std::shared_ptr<StatementFactory>const&factory         = nullptr);
        AtomicFunction(
            std::shared_ptr<FunctionRegister>const&fr    ,
            FunctionRegister::FunctionID           id    ,
            std::shared_ptr<Accessor>const&        output);
        virtual ~AtomicFunction();
        virtual void operator()();
        virtual bool bindInput (InputIndex i,std::shared_ptr<Function>const&function = nullptr);
        virtual bool bindOutput(             std::shared_ptr<Accessor>const&data     = nullptr);
        virtual inline bool hasInput (InputIndex  i   )const;
        virtual inline bool hasOutput(                )const;
        virtual inline std::shared_ptr<Accessor>const&getInputData (InputIndex i)const;
        virtual inline std::shared_ptr<Accessor>const&getOutputData(            )const;
        virtual inline Ticks getUpdateTicks()const;
        virtual inline Ticks getCheckTicks ()const;
        virtual inline void setUpdateTicks(Ticks ticks);
        virtual inline void setCheckTicks (Ticks ticks);
        virtual inline std::shared_ptr<Function>const&getInputFunction(InputIndex i)const;
        virtual inline std::string doc()const;
      protected:
        void _processInputs();
        virtual bool _do();
        inline bool _inputChanged(InputIndex  i    )const;
        inline bool _inputChanged(std::string input)const;
    };



    inline std::shared_ptr<Accessor>const&AtomicFunction::getOutputData()const{
      assert(this!=nullptr);
      return this->_outputData;
    }

    inline bool AtomicFunction::hasInput(InputIndex i)const{
      assert(this!=nullptr);
      return this->_inputs[i].function!=nullptr;
    }

    inline Function::Ticks AtomicFunction::getUpdateTicks()const{
      assert(this!=nullptr);
      return this->_updateTicks;
    }

    inline Function::Ticks AtomicFunction::getCheckTicks ()const{
      assert(this!=nullptr);
      return this->_checkTicks;
    }

    inline void AtomicFunction::setUpdateTicks(Function::Ticks ticks){
      assert(this!=nullptr);
      this->_checkTicks = ticks;
    }

    inline void AtomicFunction::setCheckTicks(Ticks ticks){
      assert(this!=nullptr);
      this->_updateTicks = ticks;
    }

    inline std::shared_ptr<Function>const&AtomicFunction::getInputFunction(InputIndex i)const{
      assert(this!=nullptr);
      assert(i<this->_inputs.size());
      return this->_inputs[i].function;
    }

    inline std::string AtomicFunction::doc()const{
      return"";
    }

    inline bool AtomicFunction::hasOutput()const{
      assert(this!=nullptr);
      return this->_outputData!=nullptr;
    }

    inline std::shared_ptr<Accessor>const&AtomicFunction::getInputData(InputIndex i)const{
      assert(this!=nullptr);
      assert(i<this->_inputs.size());
      assert(this->_inputs[i].function!=nullptr);
      return this->_inputs[i].function->getOutputData();
    }

    inline bool AtomicFunction::_inputChanged(InputIndex i)const{
      assert(this!=nullptr);
      assert(i<this->_inputs.size());
      return this->_inputs[i].changed;
    }

    inline bool AtomicFunction::_inputChanged(std::string input)const{
      assert(this!=nullptr);
      assert(this->_functionRegister!=nullptr);
      return this->_inputChanged(this->_functionRegister->getInputIndex(this->_id,input));
    }

 
  }
}
