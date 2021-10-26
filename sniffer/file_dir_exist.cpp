#include "file_dir_exist.h"
#include <iostream>
#include <sys/stat.h>

bool file_exist(const char *filename ) {
  struct stat buffer;
  std::cout << "filename: " << filename << std::endl;
  if ( stat( filename, &buffer ) ) return true ;
  return false ;
}
bool dir_exist(const char *dirname ) {
  if ( chdir(dirname) ==0 ) return true ;
  return false ;
}
