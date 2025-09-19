/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                        +       +          */
/*      File: RMDLMathUtils.cpp            +++     +++		**/
/*                                        +       +          */
/*      By: Laboitederemdal      **        +       +        **/
/*                                       +           +       */
/*      Created: 19/09/2025 20:12:07      + + + + + +   * ****/
/*                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <Math/RMDLMathUtils.hpp>

namespace math
{
    simd::float3 add(const simd::float3& a, const simd::float3& b)
    {
        return { a.x + b.x, a.y + b.y, a.z + b.z };
    }

    simd::float4x4 makeIdentity()
    {
        using simd::float4;
        return (simd_float4x4) {
            (float4) { 1.f, 0.f, 0.f, 0.f },
            (float4) { 0.f, 1.f, 0.f, 0.f },
            (float4) { 0.f, 0.f, 1.f, 0.f },
            (float4) { 0.f, 0.f, 0.f, 1.f } };
    }

    simd::float4x4 makeOrtho(float left, float right, float top, float bottom, float near, float far)
    {
        using simd::float4;
        simd_float4x4 m = (simd_float4x4) {
            (float4) { 2.f/(right - left), 0.f, 0.f, 0.f }, // col 0
            (float4) { 0.f, 2.f/(top - bottom), 0.f, 0.f }, // col 1
            (float4) { 0.f, 0.f, -2.f/(far - near), 0.f },  // col 2
            (float4) { -(right+left)/(right-left), -(top+bottom)/(top-bottom), -(far+near)/(far-near), 1.f } // col 3
        };
        return m;
    }

    simd::float4x4 makePerspective(float fovRadians, float aspect, float znear, float zfar)
    {
        using simd::float4;
        float ys = 1.f / tanf(fovRadians * 0.5f);
        float xs = ys / aspect;
        float zs = zfar / (znear - zfar);
        return simd_matrix_from_rows((float4) { xs, 0.0f, 0.0f, 0.0f },
                                    (float4) { 0.0f, ys, 0.0f, 0.0f },
                                    (float4) { 0.0f, 0.0f, zs, znear * zs },
                                    (float4) { 0, 0, -1, 0 });
    }

    simd::float4x4 makeXRotate(float angleRadians)
    {
        using simd::float4;
        const float a = angleRadians;
        return simd_matrix_from_rows((float4) { 1.0f, 0.0f, 0.0f, 0.0f },
                                    (float4) { 0.0f, cosf(a), sinf(a), 0.0f },
                                    (float4) { 0.0f, -sinf(a), cosf(a), 0.0f },
                                    (float4) { 0.0f, 0.0f, 0.0f, 1.0f });
    }

    simd::float4x4 makeYRotate(float angleRadians)
    {
        using simd::float4;
        const float a = angleRadians;
        return simd_matrix_from_rows((float4) { cosf(a), 0.0f, sinf(a), 0.0f },
                                    (float4) { 0.0f, 1.0f, 0.0f, 0.0f },
                                    (float4) { -sinf(a), 0.0f, cosf(a), 0.0f },
                                    (float4) { 0.0f, 0.0f, 0.0f, 1.0f });
    }

    simd::float4x4 makeZRotate(float angleRadians)
    {
        using simd::float4;
        const float a = angleRadians;
        return simd_matrix_from_rows((float4) { cosf(a), sinf(a), 0.0f, 0.0f },
                                    (float4) { -sinf(a), cosf(a), 0.0f, 0.0f },
                                    (float4) { 0.0f, 0.0f, 1.0f, 0.0f },
                                    (float4) { 0.0f, 0.0f, 0.0f, 1.0f });
    }

    simd::float4x4 makeTranslate(const simd::float3& v)
    {
        using simd::float4;
        const float4 col0 = { 1.0f, 0.0f, 0.0f, 0.0f };
        const float4 col1 = { 0.0f, 1.0f, 0.0f, 0.0f };
        const float4 col2 = { 0.0f, 0.0f, 1.0f, 0.0f };
        const float4 col3 = { v.x, v.y, v.z, 1.0f };
        return simd_matrix(col0, col1, col2, col3);
    }

    simd::float4x4 makeScale(const simd::float3& v)
    {
        using simd::float4;
        return simd_matrix((float4) { v.x, 0, 0, 0 },
                        (float4) { 0, v.y, 0, 0 },
                        (float4) { 0, 0, v.z, 0 },
                        (float4) { 0, 0, 0, 1.0 });
    }

    simd::float4x3 discardTranslation(const simd::float4x4& m)
    {
        return simd_matrix(m.columns[0].xyz, m.columns[1].xyz, m.columns[2].xyz, m.columns[3].xyz);
    }
}