#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

#include <cstddef>
#include <string>

// SymScope is declared in SymTab.cpp
class SymScope;

enum Basetype
{
    bt_undef,

    bt_integer,
    bt_const_int,
    bt_int_array,
    bt_int_list,
    bt_2d_int_array,
    bt_2d_int_list,
    bt_intptr,
    bt_boolean,
    bt_const_bool,
    bt_bool_array,
    bt_bool_list,
    bt_2d_bool_array,
    bt_2d_bool_list,
    bt_boolptr,
    bt_char,
    bt_const_char,
    bt_char_array,
    bt_char_list,
    bt_2d_char_array,
    bt_2d_char_list,
    bt_charptr,
    bt_short,
    bt_const_short,
    bt_short_array,
    bt_short_list,
    bt_2d_short_array,
    bt_2d_short_list,
    bt_shortptr,
    bt_void,
    bt_voidptr,
    bt_long,
    bt_const_long,
    bt_long_array,
    bt_long_list,
    bt_2d_long_array,
    bt_2d_long_list,
    bt_longptr,
    bt_struct,
    bt_enum,
    bt_procedure,
    bt_ptr,             // Used by nullptr
    bt_string,
    bt_struct_type,
    bt_enum_type,
    bt_empty,
    bt_empty_list
};


class Attribute
{
  public:
  Basetype m_basetype;       // Type of the subtree
  int m_place;               // Register where this value is stored
  std::string m_struct_name; //struct or enum name
  int m_length1;             //first dimension length of array/list
  int m_length2;             //second dimension length of array/list
  SymScope* m_scope;         // The scope of the current symbol
  int lineno;                // Line number on which that ast node resides

  Attribute() {
    m_basetype = bt_undef;
    lineno = 0;
    m_scope = NULL;
    m_struct_name  = "";
    m_length1 = -1;
    m_length2 = -1;
    int m_place = -1;   // Should never actually be negative
  }
};

#endif //ATTRIBUTE_HPP

