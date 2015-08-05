#if !defined(SIP0X_PARSER_FACTORYCONTEXT_HPP__)
#define SIP0X_PARSER_FACTORYCONTEXT_HPP__

#include <string>
#include <vector>

namespace sip0x
{
  namespace parser
  {
    class TokenAbstract;

    //! This is the base class of FactoryContext mechanism.
    //! This mechanism allow each token create own factory and decode a tokens to an object.
    //!
    class FactoryContext {
    public:
      //! Text processed by this factory.
      std::string _text;
      //! Childs
      std::vector<FactoryContext*> _children;
    public:
      //! Default ctro
      FactoryContext(void) = default;
      
      virtual ~FactoryContext(void) {
        for (auto f : _children) {
          delete f;
        }
      }

      void create(std::string const& text) {
        _text = text;
        impl_create();
      }
      
      //! Append a child to this factory.
      void add_child(FactoryContext* child) {
        // try to keep the factory tree small and more predictable.
        if (_text.compare(child->_text) == 0) {
          for (auto c : child->_children) {
            _children.push_back(c);
          }
          child->_children.clear();
          delete child;
        }
        else {
          _children.push_back(child);
        }
      }
      //! Returns processed text.
      std::string text(void) { return _text; }
      
    protected:
      virtual void impl_create(void) {}
    };
  }
}

#endif // SIP0X_PARSER_FACTORYCONTEXT_HPP__
