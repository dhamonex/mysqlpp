#ifndef __coldata1_hh__
#define __coldata1_hh__

#include <typeinfo>
#include <string>
#include "defs"
#include "type_info1.hh"
#include "const_string1.hh"
#include "null1.hh"

//! with_class = mysql_ColData

//: Exception structure thrown when a bad conversion takes place
struct BadConversion {
  const char*  type_name;  //:
  const string data;       //:
  size_t       retrieved;  //:
  size_t       actual_size;//:
  BadConversion(const char* tn, const char* d, size_t r, size_t a)
    : type_name(tn), data(d), retrieved(r), actual_size(a) {};
};

//: Base class for auto-converting column data.  Do not use directly. 
//
// A smart string. It will automatically convert it self to any of the
// basic C types. 
//
// When used with binary operators it will
// automatically convert it self to the type used on the other side of
// the operator if it is a basic type.
//
// However, be careful when using it with binary operators as. 
// 
// MysqlStr("12.86") + 2
// 
// will return 14 because 2 is an integer. What you wanted to say was 
//
// MysqlStr("12.86") + 2.0
//
// If this type of thing scares you define the micro NO_BINARY_OPERS
// to turn of this behavior.
//
// This class also has some basic information about the type of data
// stored in it.
//
// <bf>Do not use this class directly.</bf>
//  Use the typedef ColData or MutableColData instead.
template <class Str>
class mysql_ColData : public Str {
private:
  mysql_type_info _type;
public:
  mysql_ColData (mysql_type_info t = mysql_type_info::string_type) 
    : _type(t) {}
  mysql_ColData (const char *str, 
		 mysql_type_info t = mysql_type_info::string_type)
    : Str (str), _type(t) {}

  mysql_type_info type() {return _type;}
  //: Returns the current mysql type of current item

  bool quote_q() const {return _type.quote_q();}
  //: Returns true or false depending on if the data is of a type that
  //: should be quoted

  bool escape_q() const {return _type.escape_q();}
  //: Returns true of false depending on if the data is of a type that
  //: should be escaped
  
  template<class Type> Type conv (Type dummy) const;

  //!dummy: operator TYPE() const;
  //: Converts the column data to TYPE.
  // If all the charters are not read during the conversion to TYPE it
  // will through BadConversion.
  //
  // TYPE is defined for all the build in types.
  //
  // (Note, This is not an actual template)

  operator cchar*() const {return c_str();}
  operator  signed char() const {return conv((signed char)0);}
  operator  unsigned char() const {return conv((unsigned char)0);}
  operator  int() const {return conv((int)0);}
  operator  unsigned int() const {return conv((unsigned int)0);}
  operator  short int() const {return conv((short int)0);}
  operator  unsigned short int() const {return conv((unsigned short int)0);}
  operator  long int() const {return conv((long int)0);}
  operator  unsigned long int() const {return conv((unsigned long int)0);}
#ifndef NO_LONG_LONGS
  operator  long long int() const {return conv((long long int)0);}
  operator  unsigned long long int() const {return conv((unsigned long long int)0);}
#endif
  operator  float() const {return conv((float)0);}
  operator  double() const {return conv((double)0);}

  template <class T, class B> operator Null<T,B> () const;
};

//: The Type that is returned by constant rows
typedef mysql_ColData<const_string> ColData;
//: The Type that is returned by mutable rows
typedef mysql_ColData<string>       MutableColData;
//: For backwards compatibility. Do not use.
typedef ColData MysqlString;
//: For backwards compatibility. Do not use.
typedef ColData MysqlStr;

#endif
