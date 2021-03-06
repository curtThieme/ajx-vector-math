#ifndef AJX_MATRIX2D
#define AJX_MATRIX2D

#include <boost/operators.hpp>
#include "constants.h"
#include "vec2d.h"
#include <cmath>

namespace ajx {

    template <class T>
    class matrix2d : boost::operators< matrix2d<T> > {
        public:

      	matrix2d() {
      		col1 = ajx::vec2d<T>::VectorWith(0, 0);
          col2 = ajx::vec2d<T>::VectorWith(0, 0);
      	};

      	matrix2d(const T &t1,const T &t2,const T &t3,const T &t4) {
  				col1 = ajx::vec2d<T>::VectorWith(t1, t2);
          col2 = ajx::vec2d<T>::VectorWith(t3, t4);
 			  };

   			matrix2d(const ajx::vec2d<T> &v1, const ajx::vec2d<T> &v2)
   			{
   				col1 = v1;
   				col2 = v2;
   			};

   			~matrix2d(){

   			};

   			void ZeroLeftCol()
   			{
   				this->col1 = this->col1 * 0;
   			}

        void ZeroRightCol()
        {
          this->col2 = this->col2 * 0;
        }

        void Transpose()
        {
          T temp = this->col1.y();
          this->col1 = ajx::vec2d<T>::VectorWith(col1.x(), col2.x());
          this->col2 = ajx::vec2d<T>::VectorWith(temp, col2.y());
        }

        bool operator==(const matrix2d<T>& x) const {
          if (this->col1 != x.col1) return false;
          if (this->col2 != x.col2) return false;
          return true;
        };

        matrix2d<T>& operator+=(const matrix2d<T>&x)
        {
          this->col1 += x.col1;
          this->col2 += x.col2;
          return *this;
        }

        matrix2d<T>& operator-=(const matrix2d<T>& x) {
          this->col1 -= x.col1;
          this->col2 -= x.col2;
          return *this;
        };

        matrix2d<T>& operator*=(const matrix2d<T>& x)
        {
          T m11 = (this->col1.x() * x.col1.x()) + (this->col2.x() * x.col1.y());
          T m12 = (this->col1.x() * x.col2.x()) + (this->col2.x() * x.col2.y());
          T m21 = (this->col1.y() * x.col1.x()) + (this->col2.y() * x.col1.y());
          T m22 = (this->col1.y() * x.col2.x()) + (this->col2.y() * x.col2.y());
          this->col1 = ajx::vec2d<T>::VectorWith(m11, m21);
          this->col2 = ajx::vec2d<T>::VectorWith(m12, m22);
          return *this;
        }

        matrix2d<T>& ToThePowerOf(const T& x)
        {
          const matrix2d<T> myVal(this->col1, this->col2);
          for (int i = 0; i < x-1; i++)
          {
            *this *= myVal;
          }
          return *this;
        }


        vec2d<T> column1() const { return col1;}
        vec2d<T> column2() const { return col2;}



        protected:
        	vec2d<T> col1;
        	vec2d<T> col2;
    };
}

#endif
