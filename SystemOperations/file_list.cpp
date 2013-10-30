#include "file_list.h"

#include <Windows.h>
#include <locale.h>

int GetFileList(string root_dir, vector<string> &files_list) {
	if (root_dir.at(root_dir.size()-1) != '\\') {
		root_dir += "\\*";
	}
	else {
		root_dir += '*';
	}
	HANDLE h_dir;
	WIN32_FIND_DATA file_inf;
	char file_name[1024];
	wchar_t dir_name[1000];
	mbstowcs(dir_name,root_dir.c_str(),999);
	h_dir = FindFirstFile(dir_name, &file_inf);
	if (h_dir == INVALID_HANDLE_VALUE) 
		return 0;
	setlocale(LC_ALL, "");  //localize the charset of mbs, making the mbstowcs&wcstombs succeed.
	while(FindNextFile(h_dir, &file_inf)) {
		if (file_inf.cFileName[0] == '.') {
			continue;
		}
		if (file_inf.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {  //subdirectories
			wcstombs(file_name,(const wchar_t*)file_inf.cFileName,259);
			string subdir_name = root_dir.substr(0, root_dir.size()-1) + file_name;
			if (!GetFileList(subdir_name, files_list)) {
				return 0;
			}			
		} 
		else if(!(file_inf.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)) {  //unhidden files
			wcstombs(file_name,(const wchar_t*)file_inf.cFileName,259);
			string absolute_address = root_dir.substr(0, root_dir.size()-1) + file_name;
			files_list.push_back(absolute_address);
		}		
	}
	FindClose(h_dir);
	return 1;
}