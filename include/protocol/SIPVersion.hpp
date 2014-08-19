#if !defined(SIP0X_PROTOCOL_SIPVERSION_HPP__)
#define SIP0X_PROTOCOL_SIPVERSION_HPP__

namespace sip0x
{
  struct SIPVersion {
    int major = 0;
    int minor = 0;

    virtual std::string to_string(void) const {
      return "SIP/" + std::to_string(major) + '.' + std::to_string(minor);
    }

    virtual int write(std::ostream& stream) const {
      stream << "SIP/";
      stream << major;
      stream << '.';
      stream << minor;
      return 1;
    }
  };
}

#endif // SIP0X_PROTOCOL_SIPVERSION_HPP__