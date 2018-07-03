#include "assimp-converter.h"
#include <iostream>

int main(void)
{
	AssimpModel kaoru("kaoru.fbx");

	unsigned int bone_max = kaoru.get_bone_cnt();

	rewind(stdin);
	getchar();
}