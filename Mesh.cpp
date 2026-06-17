#include "Mesh.h"

#include <cassert>
#include <cstring>
#include <iostream>

void Mesh::gen_gl_buffers()
{
    glGenBuffers(1, &position_buffer_);
    glGenBuffers(1, &color_buffer_);
    glGenBuffers(1, &normal_buffer_);
}

void Mesh::update_tv_indices()
{
    tv_indices_.clear();

    for (unsigned int i = 0; i < pmesh_->mNumFaces; ++i)
    {
        aiFace& ai_face = pmesh_->mFaces[i];
        assert(ai_face.mNumIndices >= 3);

        for (unsigned int idx = 0; idx < ai_face.mNumIndices - 2; ++idx)
        {
            tv_indices_.push_back(ai_face.mIndices[0]);
            tv_indices_.push_back(ai_face.mIndices[idx + 1]);
            tv_indices_.push_back(ai_face.mIndices[idx + 2]);
        }
    }
}

void Mesh::set_gl_position_buffer_()
{
    assert(pmesh_->HasPositions());

    std::vector<glm::vec3> tv_positions;

    for (std::size_t i = 0; i < tv_indices_.size(); ++i)
    {
        unsigned int v_idx = tv_indices_[i];
        aiVector3D p = pmesh_->mVertices[v_idx];

        tv_positions.push_back(glm::vec3(p.x, p.y, p.z));
    }

    glBindBuffer(GL_ARRAY_BUFFER, position_buffer_);
    glBufferData(GL_ARRAY_BUFFER,
        sizeof(glm::vec3) * tv_positions.size(),
        &tv_positions[0],
        GL_STATIC_DRAW);
}

void Mesh::set_gl_color_buffer_(unsigned int cs_idx)
{
    assert(pmesh_->HasVertexColors(cs_idx));

    std::vector<glm::vec3> tv_colors;

    for (std::size_t i = 0; i < tv_indices_.size(); ++i)
    {
        unsigned int v_idx = tv_indices_[i];
        aiColor4D c = pmesh_->mColors[cs_idx][v_idx];

        tv_colors.push_back(glm::vec3(c.r, c.g, c.b));
    }

    glBindBuffer(GL_ARRAY_BUFFER, color_buffer_);
    glBufferData(GL_ARRAY_BUFFER,
        sizeof(glm::vec3) * tv_colors.size(),
        &tv_colors[0],
        GL_STATIC_DRAW);

    is_color_ = true;
}

void Mesh::set_gl_normal_buffer_(ShadingType shading_type)
{
    std::vector<glm::vec3> tv_flat_normals;
    std::vector<glm::vec3> tv_smooth_normals;
    std::vector<glm::vec3> v_smooth_normals;

    v_smooth_normals.resize(pmesh_->mNumVertices);

    for (std::size_t i = 0; i < v_smooth_normals.size(); ++i)
        v_smooth_normals[i] = glm::vec3(0.0f, 0.0f, 0.0f);

    tv_flat_normals.resize(tv_indices_.size());

    for (std::size_t i = 0; i < tv_indices_.size(); i += 3)
    {
        unsigned int idx0 = tv_indices_[i];
        unsigned int idx1 = tv_indices_[i + 1];
        unsigned int idx2 = tv_indices_[i + 2];

        aiVector3D p0_ai = pmesh_->mVertices[idx0];
        aiVector3D p1_ai = pmesh_->mVertices[idx1];
        aiVector3D p2_ai = pmesh_->mVertices[idx2];

        glm::vec3 p0(p0_ai.x, p0_ai.y, p0_ai.z);
        glm::vec3 p1(p1_ai.x, p1_ai.y, p1_ai.z);
        glm::vec3 p2(p2_ai.x, p2_ai.y, p2_ai.z);

        glm::vec3 e1 = p1 - p0;
        glm::vec3 e2 = p2 - p0;

        glm::vec3 face_normal = glm::normalize(glm::cross(e1, e2));

        tv_flat_normals[i] = face_normal;
        tv_flat_normals[i + 1] = face_normal;
        tv_flat_normals[i + 2] = face_normal;

        v_smooth_normals[idx0] += face_normal;
        v_smooth_normals[idx1] += face_normal;
        v_smooth_normals[idx2] += face_normal;
    }

    for (std::size_t i = 0; i < v_smooth_normals.size(); ++i)
        v_smooth_normals[i] = glm::normalize(v_smooth_normals[i]);

    if (pmesh_->HasNormals())
    {
        for (unsigned int i = 0; i < pmesh_->mNumVertices; ++i)
        {
            aiVector3D n = pmesh_->mNormals[i];
            v_smooth_normals[i] = glm::normalize(glm::vec3(n.x, n.y, n.z));
        }
    }

    for (std::size_t i = 0; i < tv_indices_.size(); ++i)
    {
        unsigned int v_idx = tv_indices_[i];
        tv_smooth_normals.push_back(v_smooth_normals[v_idx]);
    }

    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer_);

    if (shading_type == kSmooth)
    {
        glBufferData(GL_ARRAY_BUFFER,
            sizeof(glm::vec3) * tv_smooth_normals.size(),
            &tv_smooth_normals[0],
            GL_STATIC_DRAW);
    }
    else
    {
        glBufferData(GL_ARRAY_BUFFER,
            sizeof(glm::vec3) * tv_flat_normals.size(),
            &tv_flat_normals[0],
            GL_STATIC_DRAW);
    }
}

void Mesh::set_gl_buffers(ShadingType shading_type)
{
    set_gl_position_buffer_();

    if (pmesh_->HasVertexColors(0))
        set_gl_color_buffer_(0);

    set_gl_normal_buffer_(shading_type);
}

void Mesh::draw(int loc_a_position, int loc_a_normal)
{
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer_);
    glEnableVertexAttribArray(loc_a_position);
    glVertexAttribPointer(loc_a_position,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        0);

    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer_);
    glEnableVertexAttribArray(loc_a_normal);
    glVertexAttribPointer(loc_a_normal,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        0);

    glDrawArrays(GL_TRIANGLES, 0, tv_indices_.size());

    glDisableVertexAttribArray(loc_a_position);
    glDisableVertexAttribArray(loc_a_normal);
}

void Mesh::print_info()
{
    std::cout << "print mesh info" << std::endl;

    std::cout << "num vertices " << pmesh_->mNumVertices << std::endl;

    for (unsigned int i = 0; i < pmesh_->mNumVertices; ++i)
    {
        aiVector3D vertex = pmesh_->mVertices[i];

        std::cout << "  vertex  ("
            << vertex.x << ", "
            << vertex.y << ", "
            << vertex.z << ")"
            << std::endl;

        if (pmesh_->mColors[0] != NULL)
        {
            aiColor4D color = pmesh_->mColors[0][i];

            std::cout << "  color  ("
                << color.r << ", "
                << color.g << ", "
                << color.b << ", "
                << color.a << ")"
                << std::endl;
        }
    }
}