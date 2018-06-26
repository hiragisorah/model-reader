#include "assimp-converter.h"

AssimpModel::AssimpModel(std::string file_name)
{
	if (!Init(file_name)) return;

	auto & root = this->importer_.GetScene()->mRootNode;

	for(int x = 0; x < 4; ++x)
		for(int y = 0; y < 4; ++y)
			this->global_inverse_matrix_.m[x][y] = root->mTransformation[x][y];

	ProcessNode(root);
}

bool AssimpModel::Init(std::string file_name)
{
	this->importer_.FreeScene();

	const aiScene * scene = this->importer_.ReadFile(file_name
		, aiPostProcessSteps::aiProcess_Triangulate
		| aiPostProcessSteps::aiProcess_MakeLeftHanded
		| aiPostProcessSteps::aiProcess_FlipUVs
	);

	if (scene == nullptr)
	{
		std::cout << this->importer_.GetErrorString() << std::endl;
		return false;
	}
	else
	{
		std::cout << file_name.c_str() << " exported." << std::endl;
		return true;
	}

	this->mesh_list_.clear();
}

const unsigned int AssimpModel::get_mesh_cnt(void) const
{
	return this->mesh_list_.size();
}

const unsigned int AssimpModel::get_vtx_cnt(const unsigned int & mesh_num) const
{
	return this->mesh_list_[mesh_num].vertices_.size();
}

const unsigned int AssimpModel::get_index_cnt(const unsigned int & mesh_num) const
{
	return this->mesh_list_[mesh_num].indices_.size();
}

const float3 & AssimpModel::get_position(const unsigned int & mesh_num, const unsigned int & vtx_num) const
{
	return this->mesh_list_[mesh_num].vertices_[vtx_num].position_;
}

const float3 & AssimpModel::get_normal(const unsigned int & mesh_num, const unsigned int & vtx_num) const
{
	return this->mesh_list_[mesh_num].vertices_[vtx_num].normal_;
}

const float2 & AssimpModel::get_texcoord(const unsigned int & mesh_num, const unsigned int & vtx_num) const
{
	return this->mesh_list_[mesh_num].vertices_[vtx_num].texcoord_;
}

bool AssimpModel::ProcessNode(aiNode * node)
{
	auto scene = this->importer_.GetScene();

	if (!scene->HasMeshes()) return false;

	this->mesh_list_.resize(this->mesh_list_.size() + node->mNumMeshes);

	for (unsigned int n = 0; n < node->mNumMeshes; ++n)
	{
		auto & mesh = this->mesh_list_[n];
		auto & assimp_mesh = scene->mMeshes[node->mMeshes[n]];
		this->ProcessMesh(mesh, assimp_mesh);
	}

	for (unsigned int n = 0; n < node->mNumChildren; ++n)
		this->ProcessNode(node->mChildren[n]);

	return true;
}

bool AssimpModel::ProcessMesh(PrivateMesh & mesh, aiMesh * assimp_mesh)
{
	if (!assimp_mesh->HasPositions()
		|| !assimp_mesh->HasNormals()
		|| !assimp_mesh->HasTextureCoords(0))
		return false;

	for (unsigned int n = 0; n < assimp_mesh->mNumFaces; ++n)
	{
		aiFace & face = assimp_mesh->mFaces[n];

		for (unsigned int i = 0; i < face.mNumIndices; ++i)
			mesh.indices_.emplace_back(face.mIndices[i]);
	}

	this->ProcessPositions(mesh, assimp_mesh);
	this->ProcessNormals(mesh, assimp_mesh);
	this->ProcessTexCoords(mesh, assimp_mesh);

	return true;
}

void AssimpModel::ProcessPositions(PrivateMesh & mesh, aiMesh * assimp_mesh)
{
	mesh.vertices_.resize(assimp_mesh->mNumVertices);

	for (int n = 0; n < assimp_mesh->mNumVertices; ++n)
	{
		auto & pos = mesh.vertices_[n].position_;
		auto & assimp_pos = assimp_mesh->mVertices[n];
		pos = { assimp_pos.x, assimp_pos.y, assimp_pos.z };
	}
}

void AssimpModel::ProcessNormals(PrivateMesh & mesh, aiMesh * assimp_mesh)
{
	for (int n = 0; n < assimp_mesh->mNumVertices; ++n)
	{
		auto & norm = mesh.vertices_[n].normal_;
		auto & assimp_norm = assimp_mesh->mNormals[n];
		norm = { assimp_norm.x, assimp_norm.y, assimp_norm.z };
	}
}

void AssimpModel::ProcessTexCoords(PrivateMesh & mesh, aiMesh * assimp_mesh)
{
	for (int n = 0; n < assimp_mesh->mNumVertices; ++n)
	{
		auto & uv = mesh.vertices_[n].texcoord_;
		auto & assimp_uv = assimp_mesh->mTextureCoords[0][n];
		uv = { assimp_uv.x, assimp_uv.y };
	}
}
