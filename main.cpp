#include "assimp-converter.h"
#include <iostream>

int main(void)
{
	AssimpModel kaoru("kaoru.fbx");
	
	auto mesh_max = kaoru.get_mesh_cnt();

	for (int n = 0; n < mesh_max; ++n)
	{
		//auto bone_max = kaoru.get_bone_cnt(n);

		//std::cout << "bone name" << std::endl;
		//for (int i = 0; i < bone_max; ++i)
		//{
		//	std::cout << kaoru.get_bone_name(n, i).c_str() << std::endl;
		//}
	}

	rewind(stdin);
	getchar();
}