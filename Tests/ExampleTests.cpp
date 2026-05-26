#include <CPPStarter/CPPStarter.h>
#include <NanoTest/NanoTest.h>

using namespace nano;

auto greetsByName = test("GreetsByName") = []
{ check(CPPStarter::greet("world") == "Hello, world!"); };

auto greetsEmpty = test("GreetsEmpty") = []
{ check(CPPStarter::greet("") == "Hello, !"); };
