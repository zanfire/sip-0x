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

      TokenRegex(std::string regex) : TokenAbstract(), _regex(regex) {
        _logger = LoggerManager::get_logger("Sip0x.Parser.TokenRegex");

        DEBUG(_logger, "Creating TokenRegex%p with regex: %s.", this, regex.c_str());
      }


      virtual ~TokenRegex(void) {
        DEBUG(_logger, "Deleting TokenRegex@%p.", this);
      }


      // Read the expected token.
      // returns true if encountered the expected token.  
      virtual ReadResult handle_read(std::istringstream& iss) override {
        std::smatch pieces_match;
        std::string input;
        iss >> input;

        DEBUG(_logger, "Regex processing input: \"%s\".", input.c_str());

        if (std::regex_search(input, pieces_match, _regex)) {
          DEBUG(_logger, "Regex matched, found %d occurrences.", pieces_match.size());
          if (pieces_match.size() >= 1 && pieces_match.position() == 0) {
            std::ssub_match sub_match = pieces_match[0];

            std::string piece = sub_match.str();
            DEBUG(_logger, "Consuming token \"%s\", len %d.", piece.c_str(), piece.length());


            return ReadResult(true, piece);
          }
          else {
            DEBUG(_logger, "Regexp failed constrains, count %d, pos: %d.", pieces_match.size(), pieces_match.position());
          }
          // Consume ...
        }
        else {
          DEBUG(_logger, "Regexp match no occurrence found.");
        }

        // abort
        return ReadResult(false);
      }
    };
  }
}

#endif // SIP0X_PARSER_TOKENREGEX_HPP__

