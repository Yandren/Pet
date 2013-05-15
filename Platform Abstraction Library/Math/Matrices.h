#ifndef __MATRICES_H
#define __MATRICES_H


template<class type> class Vec2
{
public:

  Vec2<type>()
  {
    this->U = 0;
    this->V = 0;
  }

  Vec2<type>(type u, type v)
  {
    this->U = u;
    this->V = v;
  }

  float Length() 
  {
    return (float) (sqrt((this->U * this->U) + (this->V * this->V)));
  }

  void Normalize()
  {
    float length = Length();
    if (length != 0.0f)
    {
      this->U /= length;
      this->V /= length;
    }
  }

  type* Flatten() 
  {
    type* retArray = new type[2];
    retArray[0] = this->U;
    retArray[1] = this->V;
    return retArray;
  }

  Vec2<type> operator +(Vec2<type> v)
  {
    Vec2<type> retVec;
    retVec.U = this->U + v.U;
    retVec.V = this->V + v.V;
    return retVec;
  }

  Vec2<type> operator +(type scalar)
  {
    Vec2<type> retVec;
    retVec.U = this->U + scalar;
    retVec.V = this->V + scalar;
    return retVec;
  }

  Vec2<type> operator -(Vec2<type> v)
  {
    Vec2<type> retVec;
    retVec.U = this->U - v.U;
    retVec.V = this->V - v.V;
    return retVec;
  }

  Vec2<type> operator -(type scalar) 
  {
    Vec2<type> retVec;
    retVec.U = this->U - scalar;
    retVec.V = this->V - scalar;
    return retVec;
  }

  Vec2<type> operator *(type scalar)
  {
    Vec2<type> retVec;
    retVec.U = this->U * scalar;
    retVec.V = this->V * scalar;
    return retVec;
  }

  Vec2<type> operator *(Vec2<type> v) 
  {
    Vec2<type> retVec;
    retVec.U = this->U * v.U;
    retVec.V = this->V * v.V;
    return retVec;
  }

  Vec2<type> operator /(type scalar)
  {
    Vec2<type> retVec;
    retVec.U = this->U / scalar;
    retVec.V = this->V / scalar;
    return retVec;
  }

  Vec2<type> operator /(Vec2<type> v) 
  {
    Vec2<type> retVec;
    retVec.U = this->U / v.U;
    retVec.V = this->V / v.V;
    return retVec;
  }

  void operator +=(Vec2<type> v) 
  {
    this->U += v.U;
    this->V += v.V;
  }

  void operator +=(type scalar)
  {
    this->U += scalar;
    this->V += scalar;
  }

  void operator -=(Vec2<type> v)
  {
    this->U -= v.U;
    this->V -= v.V;
  }

  void operator -=(type scalar) 
  {
    this->U -= scalar;
    this->V -= scalar;
  }

  void operator *=(type scalar)
  {
    this->U *= scalar;
    this->V *= scalar;
  }

  void operator /=(type scalar)
  {
    this->U /= scalar;
    this->V /= scalar;
  }

  void operator =(Vec2<type> v) 
  {
    this->U = v.U;
    this->V = v.V;
  }

  Vec2<type> operator -() 
  {
    Vec2<type> retVec;
    retVec.U = -this->U;
    retVec.V = -this->V;
    return retVec;
  }

  bool operator>(Vec2<type> v)
  {
    if (this->U > v.U && this->V > v.V)
      return true;

    return false;
  }

  bool operator<(Vec2<type> v)
  {
    if (this->U < v.U && this->V < v.V)
      return true;

    return false;
  }

  type & operator [](int i)
  {
    return elements[i];
  }

  const type & operator [](int i) const
  {
    return elements[i];
  }

  union 
  {
    struct 
    {
      type U, V;
    };
    type elements[2];
  };
};

template<class type> class Vec3
{
public:

  Vec3<type>()
  {
    this->X = 0;
    this->Y = 0;
    this->Z = 0;
  }

  Vec3<type>(type x, type y, type z)
  {
    this->X = x;
    this->Y = y;
    this->Z = z;
  }

  Vec3<type>(Vec2<type> v, type z)
  {
    this->X = v.U;
    this->Y = v.V;
    this->Z = z;
  }

  float Length()
  {
    return (float) (sqrt((this->X * this->X) + (this->Y * this->Y) + (this->Z * this->Z)));
  }

  void Normalize() 
  {
    float length = Length();
    if (length != 0.0f)
    {
      this->X /= length;
      this->Y /= length;
      this->Z /= length;
    }
  }

  void Cross(Vec3<type> v1, Vec3<type> v2)
  {
    this->X = ((v1.Y * v2.Z) - (v1.Z * v2.Y));
    this->Y = ((v1.Z * v2.X) - (v1.X * v2.Z));
    this->Z = ((v1.X * v2.Y) - (v1.Y * v2.X));
  }

  type Dot(Vec3<type> v)
  {
    return (this->X * v.X) + (this->Y * v.Y) + (this->Z * v.Z);
  }

  type* Flatten()
  {
    type* retArray = new type[3];
    retArray[0] = this->X;
    retArray[1] = this->Y;
    retArray[2] = this->Z;
    return retArray;
  }

  Vec2<type> XY() 
  {
    return Vec2<type > (this->X, this->Y);
  }

  Vec2<type> YZ()
  {
    return Vec2<type > (this->Y, this->Z);
  }

  Vec2<type> XZ()
  {
    return Vec2<type > (this->X, this->Z);
  }

  Vec3<type> operator +(Vec3<type> v) 
  {
    Vec3<type> retVec;
    retVec.X = this->X + v.X;
    retVec.Y = this->Y + v.Y;
    retVec.Z = this->Z + v.Z;
    return retVec;
  }

  Vec3<type> operator +(type scalar)
  {
    Vec3<type> retVec;
    retVec.X = this->X + scalar;
    retVec.Y = this->Y + scalar;
    retVec.Z = this->Z + scalar;
    return retVec;
  }

  Vec3<type> operator -(Vec3<type> v)
  {
    Vec3<type> retVec;
    retVec.X = this->X - v.X;
    retVec.Y = this->Y - v.Y;
    retVec.Z = this->Z - v.Z;
    return retVec;
  }

  Vec3<type> operator -(type scalar)
  {
    Vec3<type> retVec;
    retVec.X = this->X - scalar;
    retVec.Y = this->Y - scalar;
    retVec.Z = this->Z - scalar;
    return retVec;
  }

  Vec3<type> operator *(type scalar) 
  {
    Vec3<type> retVec;
    retVec.X = this->X * scalar;
    retVec.Y = this->Y * scalar;
    retVec.Z = this->Z * scalar;
    return retVec;
  }

  Vec3<type> operator *(Vec3<type> v) 
  {
    Vec3<type> retVec;
    retVec.X = this->X * v.X;
    retVec.Y = this->Y * v.Y;
    retVec.Z = this->Z * v.Z;
    return retVec;
  }

  Vec3<type> operator /(type scalar)
  {
    Vec3<type> retVec;
    retVec.X = this->X / scalar;
    retVec.Y = this->Y / scalar;
    retVec.Z = this->Z / scalar;
    return retVec;
  }

  Vec3<type> operator /(Vec3<type> v) 
  {
    Vec3<type> retVec;
    retVec.X = this->X / v.X;
    retVec.Y = this->Y / v.Y;
    retVec.Z = this->Z / v.Z;
    return retVec;
  }

  void operator +=(Vec3<type> v)
  {
    this->X += v.X;
    this->Y += v.Y;
    this->Z += v.Z;
  }

  void operator +=(type scalar)
  {
    this->X += scalar;
    this->Y += scalar;
    this->Z += scalar;
  }

  void operator -=(Vec3<type> v) 
  {
    this->X -= v.X;
    this->Y -= v.Y;
    this->Z -= v.Z;
  }

  void operator -=(type scalar)
  {
    this->X -= scalar;
    this->Y -= scalar;
    this->Z -= scalar;
  }

  void operator *=(type scalar) 
  {
    this->X *= scalar;
    this->Y *= scalar;
    this->Z *= scalar;
  }

  void operator /=(type scalar) 
  {
    this->X /= scalar;
    this->Y /= scalar;
    this->Z /= scalar;
  }

  void operator =(Vec3<type> v) 
  {
    this->X = v.X;
    this->Y = v.Y;
    this->Z = v.Z;
  }

  Vec3<type> operator -() 
  {
    Vec3<type> retVec;
    retVec.X = -this->X;
    retVec.Y = -this->Y;
    retVec.Z = -this->Z;
    return retVec;
  }

  bool operator>(Vec3<type> v) 
  {
    if (this->X > v.X && this->Y > v.Y && this->Z > v.Z)
      return true;

    return false;
  }

  bool operator<(Vec3<type> v)
  {
    if (this->X < v.X && this->Y < v.Y && this->Z < v.Z)
      return true;

    return false;
  }

  bool operator ==(Vec3<type> v)
  {
    if (this->X == v.X && this->Y == v.Y && this->Z == v.Z)
      return true;

    return false;
  }

  type & operator [](int i)
  {
    return elements[i];
  }

  const type & operator [](int i) const 
  {
    return elements[i];
  }

  union 
  {
    struct 
    {
      type X, Y, Z;
    };
    type elements[3];
  };
};

template<class type> class Vec4
{
public:
  Vec4<type>()
  {
    this->R = 0;
    this->G = 0;
    this->B = 0;
    this->A = 0;
  }

  Vec4<type>(type r, type g, type b, type a)
  {
    this->R = r;
    this->G = g;
    this->B = b;
    this->A = a;
  }

  Vec4<type>(Vec3<type> v, type a)
  {
    this->R = v.X;
    this->G = v.Y;
    this->B = v.Z;
    this->A = a;
  }

  type* Flatten()
  {
    type* retArray = new type[4];
    retArray[0] = this->R;
    retArray[1] = this->G;
    retArray[2] = this->B;
    retArray[3] = this->A;
    return retArray;
  }

  Vec3<type> XYZ()
  {
    return Vec3<type>(this->R, this->G, this->B);
  }

  type & operator [](int i)
  {
    return elements[i];
  }

  const type & operator [](int i) const
  {
    return elements[i];
  }

  union
  {
    struct
    {
      type R, G, B, A;
    };
    type elements[4];
  };
};



#endif