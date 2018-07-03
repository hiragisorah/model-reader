#include "assimp-converter.h"
#include <iostream>

static unsigned int indent = 0;

void ShowChildren(AssimpModel & model, int n)
{
	indent++;
	for (unsigned int i = 0; i < model.get_bone_child_cnt(n); ++i)
	{
		for(unsigned int x = 0; x < indent; ++x)
			std::cout << "  ";

		std::cout << model.get_bone_child_id(n, i) << std::endl;

		ShowChildren(model, model.get_bone_child_id(n, i));
	}
	indent--;
}

int main(void)
{
	AssimpModel kaoru("kaoru.fbx");

	ShowChildren(kaoru, 0);

	rewind(stdin);
	getchar();
}