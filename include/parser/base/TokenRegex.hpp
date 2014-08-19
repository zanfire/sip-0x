#if !defined(SIP0X_PARSER_TOKENREGEX_HPP__)
#define SIP0X_PARSER_TOKENREGEX_HPP__

#include <string>
#include <regex>

#include "parser/base/TokenAbstract.hpp"

#include "utils/log/LoggerManager.hpp"
#include "utils/log/Logger.hpp"


namespace Sip0x
{
  namespace Parser
  {
    /// This parser expects a specific token and return an instance. 
    class TokenRegex : public TokenAbstract {

    protected:
      std::regex _regex;
      bool _create_factory = true;

    public:

      TokenRegex(std::string const& regex) : TokenRegex(regex, regex){
      }

      TokenRegex(std::string const& name, std::string regex, bool create_factory = true) : 
        TokenAbstract(name), 
        _create_factory(create_factory) {
#if defined(ENABLE_PARSER_LOGGING)
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenRegex");
        LOG_DEBUG(_logger, "Creating TokenRegex%p with regex: %s.", this, regex.c_str());
#endif
        try {
          _regex = std::regex("^(" + regex + ")");
        }
        catch (std::regex_error e) {
#if defined(ENABLE_PARSER_LOGGING)
          LOG_ERROR(_logger, "Regex %s contains an error (%s).\nRegex:%s", name.c_str(), e.what(), regex.c_str());
#endif
        }
      }


      virtual ~TokenRegex(void) {
      }


      // Read the expected token.
      // returns true if encountered the expected token.  
      virtual ReadResult handle_read(Sip0x::Utils::InputTokenStream& iss, FactoryContext* /*ctx*/) const override {
        //std::smatch pieces_match;
        std::cmatch pieces_match;
        int init_pos = iss.pos();
        char const* input = iss.get_cstr();

        //LOG_DEBUG(_logger, "Regex processing input: \"%s\".", input);

        //if (std::regex_search(input, pieces_match, _regex)) {
        if (std::regex_search(input, pieces_match, _regex)) {
#if defined(ENABLE_PARSER_LOGGING)
          LOG_DEBUG(_logger, "Regex matched, found %d occurrences.", pieces_match.size());
#endif
          if (pieces_match.size() >= 1 && pieces_match.position() == 0) {
            //std::string piece = sub_match.str(); // TODO: length instead of string.
            iss.seekg(init_pos + pieces_match.length());
            return ReadResult(true, init_pos, pieces_match.length());
          }
          else {
#if defined(ENABLE_PARSER_LOGGING)
            LOG_DEBUG(_logger, "Regexp failed constrains, count %d, pos: %d.", pieces_match.size(), pieces_match.position());
#endif
          }
        }
        else {
          //LOG_DEBUG(_logger, "Regexp match no occurrence found.");
        }

        return ReadResult();
      }

      virtual FactoryContext* create_factory(void) const override {
        if (_create_factory) {
          return new FactoryContext();
        }
        else {
          return nullptr;
        }
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENREGEX_HPP__

