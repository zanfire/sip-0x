#include "SIPParser.h"

#include "parser/SIPParser.hpp"
#include "utils/InputTokenStream.hpp"

using namespace System::Runtime::InteropServices;

namespace sip0xnet
{
  void SIPParser::Parse(String^ raw_message) {
    sip0x::Parser::SIPParser parser;

    int size = raw_message->Length;
    IntPtr ptrToNativeString = Marshal::StringToHGlobalAnsi(raw_message);
    // TODO: size could be WRONG !!! (utf8 ot ansi)
    sip0x::Utils::InputTokenStream iss((uint8_t*)ptrToNativeString.ToPointer(), size);
    std::shared_ptr<sip0x::SIPMessage> message = parser.parse(iss);
    
    if (message != nullptr) {
      // Transform to .NET rappresentation of that
      Console::WriteLine("Parsed!!!");
    }

    Marshal::FreeHGlobal(ptrToNativeString);
  }
}