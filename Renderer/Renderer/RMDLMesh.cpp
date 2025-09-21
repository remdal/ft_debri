/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                        +       +          */
/*      File: RMDLMesh.cpp            +++     +++			**/
/*                                        +       +          */
/*      By: Laboitederemdal      **        +       +        **/
/*                                       +           +       */
/*      Created: 21/09/2025 10:20:43      + + + + + +   * ****/
/*                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//#include <MetalKit/MetalKit.h>
#include <ModelIO/ModelIO.h>

#include <set>
#include <unordered_map>

#include <Utils/hpp/RMDLMesh.hpp>

MeshBuffer::MeshBuffer()
: m_pBuffer( nullptr )
, m_offset( 0 )
, m_length( 0 )
, m_argumentIndex( 0 )
{ 
}

inline MeshBuffer::MeshBuffer(MTL::Buffer* pBuffer,
                              NS::UInteger offset,
                              NS::UInteger length,
                              NS::UInteger argumentIndex )
: m_pBuffer(pBuffer->retain())
, m_offset(offset)
, m_length(length)
, m_argumentIndex(argumentIndex)
{
}

MeshBuffer::MeshBuffer(const MeshBuffer& rhs)
: m_pBuffer( rhs.m_pBuffer->retain() )
, m_length( rhs.m_length )
, m_offset( rhs.m_offset )
, m_argumentIndex( rhs.m_argumentIndex )
{
}

MeshBuffer& MeshBuffer::operator=(MeshBuffer& rhs)
{
    m_pBuffer = rhs.m_pBuffer->retain();
    m_length = rhs.m_length;
    m_offset = rhs.m_offset;
    m_argumentIndex = rhs.m_argumentIndex;
    return (*this);
}

MeshBuffer::MeshBuffer(MeshBuffer&& rhs)
: m_pBuffer( rhs.m_pBuffer->retain() )
, m_length( rhs.m_length )
, m_offset( rhs.m_offset )
, m_argumentIndex( rhs.m_argumentIndex )
{
    rhs.m_pBuffer->release();
    rhs.m_pBuffer = nullptr;
}

MeshBuffer& MeshBuffer::operator=(MeshBuffer&& rhs)
{
    m_pBuffer = rhs.m_pBuffer->retain();
    rhs.m_pBuffer->release();
    rhs.m_pBuffer = nullptr;
    
    m_length = rhs.m_length;
    m_offset = rhs.m_offset;
    m_argumentIndex = rhs.m_argumentIndex;
    return (*this);
}

MeshBuffer::~MeshBuffer()
{
    m_pBuffer->release();
    m_pBuffer = nullptr;
}

#pragma mark - Submesh Implementation

Submesh::Submesh()
: m_primitiveType( MTL::PrimitiveTypeTriangle )
, m_indexType( MTL::IndexTypeUInt16 )
, m_indexCount( 0 )
, m_indexBuffer(nullptr, (NS::UInteger)0, (NS::UInteger)0)
{
    
}

Submesh::Submesh(MTL::PrimitiveType primitiveType,
                        MTL::IndexType indexType,
                        NS::UInteger indexCount,
                        const MeshBuffer& indexBuffer,
                        const SubmeshTextureArray& pTextures)
: m_primitiveType(primitiveType)
, m_indexType(indexType)
, m_indexCount(indexCount)
, m_indexBuffer(indexBuffer)
, m_pTextures( pTextures )
{
    for ( auto&& pTexture : m_pTextures )
    {
        pTexture->retain();
    }
}

inline Submesh::Submesh(MTL::PrimitiveType primitiveType,
                        MTL::IndexType indexType,
                        NS::UInteger indexCount,
                        const MeshBuffer& indexBuffer)
: m_primitiveType(primitiveType)
, m_indexType(indexType)
, m_indexCount(indexCount)
, m_indexBuffer(indexBuffer)
{
    for ( size_t i = 0; i < 3; ++i )
    {
        m_pTextures[i] = nullptr;
    }
}

Submesh::Submesh(const Submesh& rhs)
: m_primitiveType( rhs.m_primitiveType )
, m_indexType( rhs.m_indexType )
, m_indexCount( rhs.m_indexCount )
, m_indexBuffer( rhs.m_indexBuffer )
, m_pTextures( rhs.m_pTextures )
{
    for ( size_t i = 0; i < 3; ++i )
    {
        m_pTextures[i]->retain();
    }
}

Submesh& Submesh::operator=(Submesh& rhs)
{
    m_primitiveType = rhs.m_primitiveType;
    m_indexType = rhs.m_indexType;
    m_indexCount = rhs.m_indexCount;
    m_indexBuffer = rhs.m_indexBuffer;
    m_pTextures = rhs.m_pTextures;
    
    for ( size_t i = 0; i < 3; ++i )
    {
        m_pTextures[i]->retain();
    }
    
    return (*this);
}

Submesh::Submesh(Submesh&& rhs)
: m_primitiveType( rhs.m_primitiveType )
, m_indexType( rhs.m_indexType )
, m_indexCount( rhs.m_indexCount )
, m_indexBuffer( rhs.m_indexBuffer )
, m_pTextures( rhs.m_pTextures )
{
    for ( size_t i = 0; i < 3; ++i )
    {
        m_pTextures[i]->retain();
        rhs.m_pTextures[i]->release();
        rhs.m_pTextures[i] = nullptr;
    }
}

Submesh& Submesh::operator=(Submesh&& rhs)
{
    m_primitiveType = rhs.m_primitiveType;
    m_indexType = rhs.m_indexType;
    m_indexCount = rhs.m_indexCount;
    m_indexBuffer = rhs.m_indexBuffer;
    m_pTextures = rhs.m_pTextures;
    
    for ( size_t i = 0; i < 3; ++i )
    {
        m_pTextures[i]->retain();
        rhs.m_pTextures[i]->release();
        rhs.m_pTextures[i] = nullptr;
    }
    
    return (*this);

}

Submesh::~Submesh()
{
    for ( auto&& pTexture : m_pTextures )
    {
        pTexture->release();
    }
}

#pragma mark - Mesh Implementation

Mesh::Mesh()
{
}

inline Mesh::Mesh(const std::vector<Submesh>& submeshes,
                  const std::vector<MeshBuffer>& vertexBuffers)
: m_submeshes(submeshes)
, m_vertexBuffers(vertexBuffers)
{
    
}

inline Mesh::Mesh(const Submesh& submesh,
                  const std::vector<MeshBuffer> & vertexBuffers)
: m_vertexBuffers(vertexBuffers)
{
    m_submeshes.emplace_back(submesh);
}

Mesh::Mesh(const Mesh& rhs)
: m_submeshes( rhs.m_submeshes)
, m_vertexBuffers( rhs.m_vertexBuffers )
{
    
}

Mesh& Mesh::operator=(const Mesh& rhs)
{
    m_submeshes = rhs.m_submeshes;
    m_vertexBuffers = rhs.m_vertexBuffers;
    return (*this);
}

Mesh::Mesh(Mesh&& rhs)
: m_submeshes( rhs.m_submeshes)
, m_vertexBuffers( rhs.m_vertexBuffers )
{
    
}

Mesh& Mesh::operator=(Mesh&& rhs)
{
    m_submeshes = rhs.m_submeshes;
    m_vertexBuffers = rhs.m_vertexBuffers;
    return (*this);
}

Mesh::~Mesh()
{
}
