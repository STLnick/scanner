#include <iostream>

void showHelp()
{
  std::cout << "~ ~ ~ ~ ~ [ Compilers ] ~ ~ ~ ~ ~" << std::endl
            << " ~ ~ ~ ~ ~ [ Scanner ] ~ ~ ~ ~ ~" << std::endl
            << std::endl
            << "The only flag used for this program is the one you already used!" << std::endl
            << "    -h  -> Help" << std::endl
            << std::endl
            << "**Run command structure**:" << std::endl
            << "  ./scanner               -> read from the keyboard until simulated EOF" << std::endl
            << "  ./scanner < [ _file_ ]  -> redirect from _file_ until simulated EOF, this tests keyboard input" << std::endl
            << "  ./scanner [ _file_ ]    -> read from _file_.fs" << std::endl
            << std::endl
            << "**NOTE** If you invoke scanner like the third and last example ( ./scanner [ _file_ ] )" << std::endl
            << "         then the file must be of extension '.fs'." << std::endl
            << "         More specifically, if you specify an extension it MUST BE '.fs'" << std::endl
            << "         and if no file extension is specified then scanner will look for [ _file_ ].fs" << std::endl
            << std::endl
            << "Examples of valid invocations:" << std::endl
            << "\t./scanner test3.fs" << std::endl
            << "\t./scanner test3  (Valid IF there is in fact a file 'test3.fs')" << std::endl
            << "Examples of _invalid_ invocations:" << std::endl
            << "\t./scanner test2.txt" << std::endl
            << "\t./scanner test2  (_Invalid_ IF there is NO file 'test2.fs')" << std::endl
            << std::endl;
}