#include "messageparser.h"

using namespace messageParser;

int main(int argc, char* argv[])
{
    std::string message_path;
    std::cout << "Enter the path to the message file: ";
    std::getline(std::cin, message_path);
 
    MessageParser parser;
    parser.parser(message_path);
    return 0;
}
