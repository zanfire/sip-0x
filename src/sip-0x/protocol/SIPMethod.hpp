#if !defined(SIP0X_PROTOCOL_SIPMETHOD_HPP__)
#define SIP0X_PROTOCOL_SIPMETHOD_HPP__

#include <cstdint>
#include <vector>

namespace sip0x
{
  enum SIPMethod {
    SIPMETHOD_INVITE = 0,
    SIPMETHOD_ACK,
    SIPMETHOD_OPTIONS,
    SIPMETHOD_BYE,
    SIPMETHOD_CANCEL,
    SIPMETHOD_REGISTER, 
    SIPMETHOD_extension = -1
  };

  static SIPMethod convSIPMethodFromChars(char const* method) {
    if (strcmp(method, "INVITE") == 0) return SIPMETHOD_INVITE;
    else if (strcmp(method, "ACK") == 0) return SIPMETHOD_ACK;
    else if (strcmp(method, "OPTIONS") == 0) return SIPMETHOD_OPTIONS;
    else if (strcmp(method, "BYE") == 0) return SIPMETHOD_BYE;
    else if (strcmp(method, "CANCEL") == 0) return SIPMETHOD_CANCEL;
    else if (strcmp(method, "REGISTER") == 0) return SIPMETHOD_REGISTER;
    else return SIPMETHOD_extension;
  }

  static char const* convCharsFromSIPMethod(SIPMethod const& method) {
    if (method == SIPMETHOD_INVITE) return "INVITE";
    else if (method == SIPMETHOD_ACK) return "ACK";
    else if (method == SIPMETHOD_OPTIONS) return "OPTIONS";
    else if (method == SIPMETHOD_BYE) return "BYE";
    else if (method == SIPMETHOD_CANCEL) return "CANCEL";
    else if (method == SIPMETHOD_REGISTER) return "REGISTER";
    else return "?? extension ??";
  }

  static std::string to_string(SIPMethod const& method) {
    if (method == SIPMETHOD_INVITE) return "INVITE";
    else if (method == SIPMETHOD_ACK) return "ACK";
    else if (method == SIPMETHOD_OPTIONS) return "OPTIONS";
    else if (method == SIPMETHOD_BYE) return "BYE";
    else if (method == SIPMETHOD_CANCEL) return "CANCEL";
    else if (method == SIPMETHOD_REGISTER) return "REGISTER";
    else return "?? extension ??";
  }
}

#endif // SIP0X_PROTOCOL_SIPMETHOD_HPP__