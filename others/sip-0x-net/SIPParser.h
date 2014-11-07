// sip-0x-net.h

#pragma once

using namespace System;

namespace sip0xnet {

  public ref class SIPParser
  {
  private:
    SIPParser() {}

  public:
    static void Parse(String^ message);
  };
}
