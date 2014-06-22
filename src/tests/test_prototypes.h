#if !defined(TEST_PROTOTYPES_H__)
#define TEST_PROTOTYPES_H__

#include "parser/Parser.hpp"

using namespace Sip0x::Parser;
using namespace Sip0x::Utils;
using namespace Sip0x::Utils::Log;
using namespace std;

void run_test(TokenAbstract& token, std::string input, bool expected);

// Test tokens common.
void test_token_regexconststrings();

void test_token_ipv4();
// Test tokens sip.
void test_token_sipuri();


void test_occurrences();

 
#endif 