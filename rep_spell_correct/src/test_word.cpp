#include"../inc/manageword.h"

int main(int argc, char **argv)
{
  std::string filename=argv[1];
  ManageWord test;
  test.read_word(filename);

  return 0;
}
