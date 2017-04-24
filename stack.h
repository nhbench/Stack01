/***********************************************************************
* Header:
*    Vector
* Summary:
*    This class contains the notion of a vector: a container
*    that expands as more items are put inside.
*
*    This will contain the class definition of:
*        Vector         : A class that holds stuff
*        VectorIterator : An interator through Vector
* Author
*    Nathan Bench
************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>

// forward declaration for VectorIterator
template <class T>
class VectorIterator;

// forward declaration for VectorConstIterator
template <class T>
class VectorConstIterator;

/************************************************
 * VECTOR
 * A class that holds stuff
 ***********************************************/
template <class T>
class Vector
{
public:
   // default constructor : empty and kinda useless
   Vector() : numItems(0), vCapacity(0), data(NULL) {}

   // copy constructor : copy it
   Vector(const Vector & rhs) throw (const char *);
   
   // non-default constructor : pre-allocate
   Vector(int capacity) throw (const char *);
   
   // destructor : free everything
   ~Vector()        { if (vCapacity) delete [] data; }
   
   // is the container currently empty
   bool empty() const  { return numItems == 0;         }

   // remove all the items from the container
   void clear()        { numItems = 0;                 }

   // how many items can the vector currently contain?
   int capacity() const { return vCapacity;             }
   
   // how many items are currently in the container?
   int size() const    { return numItems;              }

   // add an item to the container
   void push_back(const T & t) throw (const char *);
   
   // look up an item using the array index operator '[]'
   T & operator [] (int index) throw (const char *);
   const T & operator [] (int index) const throw (const char *);
   
   // assignment operator '='
   Vector<T> & operator = (const Vector <T> & rhs);
   
   // return an iterator to the beginning of the vector
   VectorIterator <T> begin() { return VectorIterator<T>(data); }

   // return an iterator to the end of the vector
   VectorIterator <T> end() { return VectorIterator<T>(data + numItems);}
   
   // return a constant iterator to the beginning of the vector
   VectorConstIterator <T> cbegin() const { return VectorConstIterator<T>(data); }
   
   // return a constant iterator to the end of the vector
   VectorConstIterator <T> cend() const   { return VectorConstIterator<T>(data + numItems); }
   
private:
   T * data;          // dynamically allocated array of T
   int numItems;      // how many items are currently in the Vector?
   int vCapacity;      // how many items can I put on the Vector before full?
};


/*******************************************
 * VECTOR :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Vector <T> :: Vector(const Vector <T> & rhs) throw (const char *)
{
   assert(rhs.vCapacity >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.vCapacity == 0)
   {
      vCapacity = numItems = 0;
      data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.vCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   // copy over the capacity and size
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.vCapacity);
   vCapacity = rhs.vCapacity;
   numItems = rhs.numItems;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numItems; i++)
      data[i] = rhs.data[i];

   // the rest needs to be filled with the default value for T
   for (int i = numItems; i < vCapacity; i++)
      data[i] = T();
}

/**********************************************
 * VECTOR : NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "capacity"
 **********************************************/
template <class T>
Vector <T> :: Vector(int capacity) throw (const char *)
{
   assert(capacity >= 0);
   
   // do nothing if there is nothing to do
   if (vCapacity == 0)
   {
      this->vCapacity = this->numItems = 0;
      this->data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[capacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

      
   // copy over the stuff
   this->vCapacity = capacity;
   this->numItems = 0;

   // initialize the container by calling the default constructor
   for (int i = 0; i < vCapacity; i++)
      data[i] = T();
}

/***************************************************
 * VECTOR :: PUSH BACK
 * Insert an item on the end of the container
 **************************************************/
template <class T>
void Vector <T> :: push_back(const T & t) throw (const char *)
{
   // IF capacity == 0
   if (vCapacity == 0)
   {
      vCapacity = 1;
      try
      {
         data = new T[vCapacity];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: unable to allocate a new buffer for Vector";
      }
   }
   
   // IF max capacity AND numItems is not less than 0
   if (vCapacity == numItems && numItems > 0)
   {
      vCapacity *= 2;
      try
      {
         T* tempArray = new T[vCapacity];
         
         // copy
         for (int i = 0; i < numItems; i++)
         {
            tempArray[i] = data[i];
         }

         // free memory
         delete[] data;

         // point to tempArray
         data = tempArray;
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for Vector";
      }
   }
   
   // add an item to the end
   data[numItems++] = t;
}

/***************************************************
 * VECTOR :: []
 * Overload array index operator
 **************************************************/
template <class T>
T & Vector<T> :: operator [] (int index) throw (const char *)
{
   // return if index valid
   if (index >= 0 && index < numItems)
      return data[index];
   // throw invalid index
   throw "ERROR: Invalid index";
}

/***************************************************
 * VECTOR :: [] const
 * Overload array index operator
 **************************************************/
template <class T>
const T & Vector <T> :: operator [] (int index) const throw (const char *)
{
   // return if index valid
   if (index >= 0 && index < numItems)
      return data[index];
   // throw invalid index
   throw "ERROR: Invalid index";
}

/***************************************************
 * VECTOR :: =
 * Overload assignment operator
 **************************************************/
 template <class T>
Vector<T> & Vector <T> :: operator = (const Vector <T> & rhs)
{
   // don't copy yourself
   if (this != &rhs)
   {
      // clean up data
      if (data)
         delete [] data;
      
      // assign each member variable to right-hand-side
      vCapacity = rhs.vCapacity;
      numItems = rhs.numItems;
      
      // allocate new array
      try
      {
         data = new T[vCapacity];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for Vector";
      }
      // copy over values from rhs
      for (int i = 0; i < rhs.numItems; i++)
      {
         data[i] = rhs.data[i];
      }
      
      return *this;
   }
}

#endif // VECTOR_H

