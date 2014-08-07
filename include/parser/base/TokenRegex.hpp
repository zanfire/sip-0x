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

    public:

      TokenRegex(std::string const& regex) : TokenRegex(regex, regex){
      }

      TokenRegex(std::string const& name, std::string regex) : TokenAbstract(name) {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenRegex");

        LOG_DEBUG(_logger, "Creating TokenRegex%p with regex: %s.", this, regex.c_str());

        try {
          _regex = std::regex("^(" + regex + ")");
        }
        catch (std::regex_error e) {
          LOG_ERROR(_logger, "Regex %s contains an error (%s).\nRegex:%s", name.c_str(), e.what(), regex.c_str());
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
          LOG_DEBUG(_logger, "Regex matched, found %d occurrences.", pieces_match.size());
          if (pieces_match.size() >= 1 && pieces_match.position() == 0) {
            //std::string piece = sub_match.str(); // TODO: length instead of string.
            iss.seekg(init_pos + pieces_match.length());
            return ReadResult(true, init_pos, pieces_match.length());
          }
          else {
            LOG_DEBUG(_logger, "Regexp failed constrains, count %d, pos: %d.", pieces_match.size(), pieces_match.position());
          }
        }
        else {
          //LOG_DEBUG(_logger, "Regexp match no occurrence found.");
        }

        return ReadResult();
      }

      virtual FactoryContext* create_factory(void) const override {
        return new FactoryContext();
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENREGEX_HPP__

