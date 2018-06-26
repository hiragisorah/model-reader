#pragma once

#include <iostream>
#include <vector>

#include <assimp\scene.h>
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>

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
	float4x4 init_matrix_;
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
		std::vector<Bone> bones_;
	};

public:
	AssimpModel(std::string file_name);

private:
	Assimp::Importer importer_;
	
private:
	bool Init(std::string file_name);

private:
	std::vector<PrivateMesh> mesh_list_;
	float4x4 global_inverse_matrix_;

public:
	const unsigned int get_mesh_cnt(void) const;
	const unsigned int get_vtx_cnt(const unsigned int & mesh_num) const;
	const unsigned int get_index_cnt(const unsigned int & mesh_num) const;
	const unsigned int get_bone_cnt(const unsigned int & mesh_num) const;
	const float3 & get_position(const unsigned int & mesh_num, const unsigned int & vtx_num) const;
	const float3 & get_normal(const unsigned int & mesh_num, const unsigned int & vtx_num) const;
	const float2 & get_texcoord(const unsigned int & mesh_num, const unsigned int & vtx_num) const;
	const float4x4 & get_bone_init_matrix(const unsigned int & mesh_num, const unsigned int & bone_num) const;
	const unsigned int & get_bone_id(const unsigned int & mesh_num, const unsigned int & vtx_num, const unsigned int & bone_index) const;
	const float & get_bone_weight(const unsigned int & mesh_num, const unsigned int & vtx_num, const unsigned int & bone_index) const;

private:
	bool ProcessNode(aiNode * node);
	bool ProcessMesh(PrivateMesh & mesh, aiMesh * assimp_mesh);
	void ProcessPositions(PrivateMesh & mesh, aiMesh * assimp_mesh);
	void ProcessNormals(PrivateMesh & mesh, aiMesh * assimp_mesh);
	void ProcessTexCoords(PrivateMesh & mesh, aiMesh * assimp_mesh);
	void ProcessBones(PrivateMesh & mesh, aiMesh * assimp_mesh);
};