#if !defined(TEST_PROTOTYPES_H__)
#define TEST_PROTOTYPES_H__

#include "parser/Parser.hpp"

using namespace sip0x::parser;
using namespace sip0x::utils;
using namespace std;

void run_test(TokenAbstract& token, std::string input, bool expected, bool factory = false);
bool run_sip(std::string input);


// Test tokens common.
void test_token_regexconststrings();

void test_token_ipv4();
// Test tokens sip.
void test_token_sipuri();

void test_token_sip_message();

void test_occurrences();

void test_sipmessages_from_file(char const* path, bool break_on_error);

#endif 