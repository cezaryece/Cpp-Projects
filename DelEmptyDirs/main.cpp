#include <dirent.h>
#include <iostream>
#include <sys/stat.h>
#include <fstream>
#include <sys/param.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

int walker(char* path)
{
	DIR * d;
	struct dirent *dir;
	char newpath[MAXPATHLEN];
	int empty;
	int res = 1;
	
	d = opendir(path);
	if (d == NULL)
	{
		cout << "d=NULL" << endl;
        if (chdir(path) != 0)
		{
            cout << endl << "UWAGA, nie mogę otworzyć <" << path << ">" << endl;
            sleep(2);
            return -1;
        }
	}
	
	while (dir = readdir(d))
	{
        if (strcmp(dir->d_name, ".") == 0) continue;   /* current dir */
        if (strcmp(dir->d_name, "..") == 0) continue;  /* parent dir  */
		
		strcpy(newpath, path);
        strcat(newpath, "/");
        strcat(newpath, dir->d_name);
		
		if (dir->d_type == DT_DIR)
		{
            empty = walker(newpath);
			if (empty == 1)
			{
                if (remove(newpath) == 0)
                    cout << "DEL " << newpath << endl;
                else cout << "FAILED DEL " << newpath << endl;
			}
			res = empty;
		}
		else
			res = 0;
	}
	closedir(d);
	return res;
}

int main(int argc, char *argv[])
{
	char dir[MAXPATHLEN];
	getcwd(dir, MAXPATHLEN);
	int res;
	res = walker(dir);
	exit(res);
}
