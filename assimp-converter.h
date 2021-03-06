#pragma once

#include <iostream>
#include <vector>

struct aiMesh;
struct aiNode;

struct uint4
{
	float x, y, z, w;
};

struct float4
{
	float x, y, z, w;
};

struct float3
{
	float x, y, z;
};

struct float2
{
	float x, y;
};

struct float4x4
{
	union
	{
		float m[4][4] = {};
		float4 m4[4];
	};
};

struct Bone
{
	float4x4 matrix_;
	std::string name_;

	int parent_id_;
	std::vector<int> children_id_;
};

struct VertexBoneData
{
	unsigned int id_[4];
	float weight_[4];
};

struct BoneData
{
	unsigned int bone_id;
	float weight_;
};

class AssimpModel
{
private:
	struct PrivateMesh
	{
		struct Vertex
		{
			float3 position_;
			float3 normal_;
			float2 texcoord_;

			VertexBoneData bone_;
		};

		std::vector<Vertex> vertices_;
		std::vector<unsigned int> indices_;
		std::string name_;
	};

public:
	AssimpModel(std::string file_name);

private:
	bool Init(std::string file_name);

private:
	std::vector<PrivateMesh> mesh_list_;
	float4x4 global_inverse_matrix_;
	std::vector<Bone> bones_;

private:
	aiNode * const FindNodeRecursiveByName(aiNode * const node, const std::string & name) const;
	const int GetBoneIdByName(const std::string & name);

public:
	const unsigned int get_mesh_cnt(void) const;
	const unsigned int get_vtx_cnt(const unsigned int & mesh_num) const;
	const unsigned int get_index_cnt(const unsigned int & mesh_num) const;
	const unsigned int get_bone_cnt(void) const;
	const std::string & get_mesh_name(const unsigned int & mesh_num) const;
	const float3 & get_position(const unsigned int & mesh_num, const unsigned int & vtx_num) const;
	const float3 & get_normal(const unsigned int & mesh_num, const unsigned int & vtx_num) const;
	const float2 & get_texcoord(const unsigned int & mesh_num, const unsigned int & vtx_num) const;
	const float4x4 & get_bone_matrix(const unsigned int & mesh_num, const unsigned int & bone_num) const;
	const std::string & get_bone_name(const unsigned int & bone_num) const;
	const int get_bone_id(const std::string name);
	const unsigned int & get_bone_id(const unsigned int & mesh_num, const unsigned int & vtx_num, const unsigned int & bone_index) const;
	const int & get_bone_parent_id(const unsigned int & bone_id) const;
	const unsigned int get_bone_child_cnt(const unsigned int & bone_id) const;
	const int & get_bone_child_id(const unsigned int & bone_id, const unsigned int & child_id) const;
	const float & get_bone_weight(const unsigned int & mesh_num, const unsigned int & vtx_num, const unsigned int & bone_index) const;

private:
	bool ProcessNode(aiNode * node);
	bool ProcessMesh(PrivateMesh & mesh, aiMesh * assimp_mesh);
	void ProcessPositions(PrivateMesh & mesh, aiMesh * assimp_mesh);
	void ProcessNormals(PrivateMesh & mesh, aiMesh * assimp_mesh);
	void ProcessTexCoords(PrivateMesh & mesh, aiMesh * assimp_mesh);
	void ProcessBones(PrivateMesh & mesh, aiMesh * assimp_mesh);
};