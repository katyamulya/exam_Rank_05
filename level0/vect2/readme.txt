Operators (16 functions):
+   vector + vector
-   vector - vector
*   vector * scalar  v * 2
*	scalar * vector  2 * v

+=
-=
*=

++v  increment x and y, then return updated object
v++  return old object, then increment x and y
--v  decrement x and y, then return updated object
v--  return old object, then decrement x and y

unary -  -v: {x, y} -> {-x, -y}

==
!=

[]  no bound checking is required
<<


Operator []:

int &operator[](int index);
const int &operator[](int index) const;