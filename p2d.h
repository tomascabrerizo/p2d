#ifndef P2D_H
#define P2D_H
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <algorithm>

namespace p2d {

    //////////////////////////////////////////////
    // simple 2d vector class                   //
    //////////////////////////////////////////////
    template<class T>
    struct v2
    {
        T x;
        T y;
    };
    typedef v2<float> v2f;
    typedef v2<int32_t> v2i;
    typedef v2<uint32_t> v2ui;

    template<typename T>
    v2<T> operator-(const v2<T>& v0, const v2<T> v1)
    {
        return {v0.x - v1.x, v0.y - v1.y};
    }
    
    template<typename T>
    v2<T> operator+(const v2<T>& v0, const v2<T> v1)
    {
        return {v0.x + v1.x, v0.y + v1.y};
    }

    template<typename T>
    v2<T> operator*(const v2<T>& v, float s)
    {
        return {v.x * s, v.y * s};
    }
    
    template<typename T>
    v2<T> operator/(const v2<T>& v0, const v2<T>& v1)
    {
        return {v0.x / v1.x, v0.y / v1.y};
    }
    
    template<typename T>
    v2<T> abs(const v2<T>& v)
    {
        return {std::abs(v.x), std::abs(v.y)};
    }
    
    template <typename T>
    float dot(const v2<T>& v0, const v2<T>& v1)
    {
        return v0.x * v1.x + v0.y * v1.y;
    }   

    template<typename T>
    float length(const v2<T>& v)
    {
        return sqrtf(dot(v, v));
    }
    
    template<typename T>
    v2<T> normalize(v2<T> v)
    {
        return v / length(v);
    }

    //////////////////////////////////////////////
    // simple rect class                        //
    //////////////////////////////////////////////
    struct rect
    {
        v2f pos;
        v2f size;
    };
    
    bool point_vs_rect(const v2f& p, const rect& r)
    {
        return p.x >= r.pos.x && p.x < (r.pos.x + r.size.x) &&
               p.y >= r.pos.y && p.y < (r.pos.y + r.size.y);
    }

    bool rect_vs_rect(const rect& r0, const rect& r1)
    {
        return r0.pos.x <= (r1.pos.x + r1.size.x) && r1.pos.x <= (r0.pos.x + r0.size.x) &&
               r0.pos.y <= (r1.pos.y + r1.size.y) && r1.pos.y <= (r0.pos.y + r0.size.y);
    }

    bool ray_vs_rect(v2f p, v2f v, const rect& r, v2f* hit, v2f* normal)
    {
        v2f v_nt = (r.pos - p) / v; 
        v2f v_ft = (r.pos + r.size - p) / v;
        
        if(v_nt.x > v_ft.x) std::swap(v_nt.x, v_ft.x);
        if(v_nt.y > v_ft.y) std::swap(v_nt.y, v_ft.y);

        if(v_nt.x > v_ft.y || v_nt.y > v_ft.x) return false;
        
        const float nt = v_nt.x > v_nt.y ? v_nt.x : v_nt.y;
        const float ft = v_ft.x < v_ft.y ? v_ft.x : v_ft.y;

        if(nt >= 1 || ft <=0) return false;
        
        if(v_nt.x > v_nt.y)
        {
            if(v.x < 0)
                *normal = {1.0f, 0.0f};
            else
                *normal = {-1.0f, 0.0f};
        }
        else if(v_nt.x < v_nt.y)
        {
            if(v.y < 0)
                *normal = {0.0f, 1.0f};
            else
                *normal = {0.0f, -1.0f};
        }
        *hit = p + v*nt;
        return true;
    }

};

#endif
