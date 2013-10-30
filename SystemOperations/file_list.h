#ifndef FILE_LIST_H__
#define FILE_LIST_H__

#include <string>
#include <vector>

using std::string;
using std::vector;

//input: the root directory.
//output: the absolute addresses of files in the root directory, 
//			including the files in the subdirectories.
//return: 0: error; 1: success.
int GetFileList(string root_dir, vector<string> &files_list);

#endif // FILE_LIST_H__
