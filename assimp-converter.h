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
	float4x4 init_matrix;
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

	const float3 & get_position(const unsigned int & mesh_num, const unsigned int & vtx_num) const;
	const float3 & get_normal(const unsigned int & mesh_num, const unsigned int & vtx_num) const;
	const float2 & get_texcoord(const unsigned int & mesh_num, const unsigned int & vtx_num) const;

private:
	bool ProcessNode(aiNode * node);
	bool ProcessMesh(PrivateMesh & mesh, aiMesh * assimp_mesh);
	void ProcessPositions(PrivateMesh & mesh, aiMesh * assimp_mesh);
	void ProcessNormals(PrivateMesh & mesh, aiMesh * assimp_mesh);
	void ProcessTexCoords(PrivateMesh & mesh, aiMesh * assimp_mesh);
};