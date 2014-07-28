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
        char buf[254];
        stream.write("SIP/", 4);
        _itoa_s(major, buf, sizeof(buf), 10);
        stream.write(buf, strlen(buf));
        stream.put('.');
        _itoa_s(minor, buf, sizeof(buf), 10);
        stream.write(buf, strlen(buf));
        return 1;
      }
    };
  }
}

#endif // SIP0X_PROTOCOL_SIPVERSION_HPP__