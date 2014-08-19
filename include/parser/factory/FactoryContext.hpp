#if !defined(SIP0X_PARSER_FACTORYCONTEXT_HPP__)
#define SIP0X_PARSER_FACTORYCONTEXT_HPP__

#include <string>
#include <vector>

namespace sip0x
{
  namespace Parser
  {
    class TokenAbstract;

    class FactoryContext {
    public:
      std::string _text;
      std::vector<FactoryContext*> _children;
    public:

      FactoryContext(void) {}
      virtual ~FactoryContext(void) {
        for (auto f : _children) {
          delete f;
        }
      }

      virtual void create(std::string const& text) {
        _text = text;
      }
      virtual void destroy(void) {}

      void add_child(FactoryContext* child) { _children.push_back(child); }

      std::string text(void) { return _text; }
    };
  }
}

#endif // SIP0X_PARSER_FACTORYCONTEXT_HPP__
