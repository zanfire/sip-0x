#if !defined(SIP0X_PARSER_PARSERRESULT_HPP__)
#define SIP0X_PARSER_PARSERRESULT_HPP__

#include <string>
#include <cstdint>
#include <vector>

namespace sip0x
{
  namespace parser
  {
    //! Structure containing the parser result.
    class ParserResult {
    public:
      enum ParserEventType {
        TYPE_NOTICE,
        TYPE_WARNING,
        TYPE_ERROR
      };

      struct ParserEvent {
        ParserEventType type;
        uint32_t position;
        std::string message;
      };
    private:
      //! True when parser is in a success state.
      bool _success;
      //! Current parser position.
      uint32_t _pos = 0;
      //! 
      uint32_t _len = 0;
      //! Events.
      std::vector<ParserEvent> _events;

    public:
      ParserResult(void);
      ParserResult(bool success, uint32_t pos, uint32_t len);
      virtual ~ParserResult(void);
      //! Return true if success.
      bool success(void);
      
      //! Get position relative to the input.
      uint32_t position(void) { return _pos; }
      //! Get length of content relative to the input.
      uint32_t length(void) { return _len; }

      // ??
      void set_position(int pos);
      //! Push a parser event in the result.
      //! If you push an ERROR type event the success state will be forced to false.
      void push_event(ParserEventType type, int pos, std::string message);
      //! Returns the events vector.
      std::vector<ParserEvent>& get_events(void) { return _events; }
      //! Returns the first error occurrence from index.
      ParserEvent get_error(int start_index = 0);
    protected:
      //! Returns if events array contains one or more event of given type.
      bool contains_events(ParserEventType type);
    };
 }
}

#endif // SIP0X_PARSER_PARSERRESULT_HPP__
