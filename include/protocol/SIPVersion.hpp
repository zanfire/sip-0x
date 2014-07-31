#if !defined(SIP0X_PROTOCOL_SIPVERSION_HPP__)
#define SIP0X_PROTOCOL_SIPVERSION_HPP__

namespace Sip0x
{
  namespace Protocol
  {
    struct SIPVersion {
      int major;
      int minor;

      virtual int write(std::ostream& stream) const {
        stream << "SIP/";
        stream << major;
        stream << '.';
        stream << minor;
        return 1;
      }
    };
  }
}

#endif // SIP0X_PROTOCOL_SIPVERSION_HPP__