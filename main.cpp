#include "assimp-converter.h"
#include <iostream>

int main(void)
{
	AssimpModel kaoru("kaoru.fbx");

	unsigned int bone_max = kaoru.get_bone_cnt();

	//for (unsigned int i = 0; i < bone_max; ++i)
	//	std::cout << kaoru.get_bone_name(i).c_str() << std::endl;

	rewind(stdin);
	getchar();
}