#include "FileSys.h"
#include "ITek.h"

filesystem g_Files;

file_t filesystem::GetFileByName(char* name)
{
	auto _name = name;
	for (int i = cur_ent - 1; i >= 0; i--)
	{
		if (!(strcmp(_name, names[i])))
			return file[i];
	}
}

void filesystem::LoadTEK(char* tekname)
{
	int found = 0;

	ITek::DispackTEKToFilesWithNames(tekname, &file[cur_ent], found, names[cur_ent], 100);
	cur_ent += found;
	Sleep(2);
}

void filesystem::LoadAll()
{
	//LoadTEK("pokero.tek");
	LoadTEK("basics.tek");
	//LoadTEK("weapons.tek");
	//LoadTEK("ui.tek");
	LoadTEK("imap.tek");
	LoadTEK("travian.tek");
}

void filesystem::ListLoadedFiles()
{
	for (int i = 0; i < cur_ent; i++)
	{
		printf("%d\t| %s\n",i, names[i]);
	}
}

file_t filesystem::GetFileByID(unsigned id)
{
	return file[id];
}

unsigned filesystem::GetIDByName(char* name)
{
	for (int i = cur_ent - 1; i >= 0; i--)
	{
		if (!(strcmp(name, names[i])))
			return i;
	}


}