#include "Object.h"

void Object::init_buffer_objects()
{
    // position buffer
    glGenBuffers(1, &position_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(aiVector3D) * pmesh_->mNumVertices,
        pmesh_->mVertices,
        GL_STATIC_DRAW
    );

    // color buffer
    if (pmesh_->mColors[0] != NULL)
    {
        is_color = true;

        glGenBuffers(1, &color_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
        glBufferData(
            GL_ARRAY_BUFFER,
            sizeof(aiColor4D) * pmesh_->mNumVertices,
            pmesh_->mColors[0],
            GL_STATIC_DRAW
        );
    }
    else
    {
        is_color = false;
    }

    // index buffers per face
    faces.clear();

    for (unsigned int i = 0; i < pmesh_->mNumFaces; ++i)
    {
        const aiFace& ai_face = pmesh_->mFaces[i];

        Face face;
        face.num_indices = ai_face.mNumIndices;

        glGenBuffers(1, &face.index_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, face.index_buffer);
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            sizeof(unsigned int) * ai_face.mNumIndices,
            ai_face.mIndices,
            GL_STATIC_DRAW
        );

        faces.push_back(face);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

glm::mat4 Object::get_model_matrix() const
{
    glm::mat4 mat_model = glm::mat4(1.0f);

    glm::mat4 mat_translate = glm::translate(glm::mat4(1.0f), vec_translate_);
    glm::mat4 mat_rotate = glm::mat4_cast(quat_rotate_);
    glm::mat4 mat_scale = glm::scale(glm::mat4(1.0f), vec_scale_);

    mat_model = mat_translate * mat_rotate * mat_scale;

    return mat_model;
}

void Object::draw(int loc_a_position, int loc_a_color)
{
    // position attribute
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
    glVertexAttribPointer(
        loc_a_position,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        0
    );
    glEnableVertexAttribArray(loc_a_position);

    // color attribute
    if (is_color)
    {
        glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
        glVertexAttribPointer(
            loc_a_color,
            4,
            GL_FLOAT,
            GL_FALSE,
            0,
            0
        );
        glEnableVertexAttribArray(loc_a_color);
    }
    else
    {
        glDisableVertexAttribArray(loc_a_color);
        glVertexAttrib4f(loc_a_color, 1.0f, 1.0f, 1.0f, 1.0f);
    }

    // draw each face
    for (const Face& face : faces)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, face.index_buffer);
        glDrawElements(
            GL_TRIANGLES,
            face.num_indices,
            GL_UNSIGNED_INT,
            0
        );
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}