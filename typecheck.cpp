#include <iostream>
#include <cstdio>
#include <cstring>

#include "ast.hpp"
#include "symtab.hpp"
#include "primitive.hpp"
#include "assert.h"
using namespace std;

#include <typeinfo>

class Typecheck : public Visitor
{
private:
  FILE* m_errorfile;
  SymTab* m_st;

  // The set of recognized errors
  enum errortype {
      no_main,
      nonvoid_main,
      dup_proc_name,
      dup_var_name,
      proc_undef,
      call_type_mismatch,
      narg_mismatch,
      expr_type_err,
      var_undef,
      ifpred_err,
      whilepred_err,
      incompat_assign,
      who_knows,
      ret_type_mismatch,
      array_index_error,
      no_array_var,
      arg_type_mismatch,
      expr_pointer_arithmetic_err,
      expr_abs_error,
      expr_addressof_error,
      invalid_deref,
      const_assign,
      array_assign,
      one_d_array_assign,
      two_d_array_assign,
      wrong_array_base_type,
      init_type_failed,
      forpred_err,
      list_differnt_type,
      tdlist_differnt_type,
      incre_type,
      dot_access_not_struct,
      not_a_struct_member,
      not_supported_feature,
      empty_list,
      not_ret_type,
      tdlist_differnt_length,
      switch_case_diff_type,
      switch_not_base,
      main_not_outmost,
      no_error
    };

  // Print the error to file and exit
  void t_error(errortype e, Attribute a) {
    fprintf( m_errorfile,"on line number %d, ", a.lineno );
    printf( "on line number %d, ", a.lineno );

    switch(e) {
    case no_main:
      fprintf( m_errorfile, "error: no main\n" );
      printf( "error: no main\n" );
      exit( 2 );
    case nonvoid_main:
      fprintf( m_errorfile, "error: the Main procedure has arguments\n" );
      printf( "error: the Main procedure has arguments\n" );
      exit( 3 );
    case dup_proc_name:
      fprintf( m_errorfile, "error: duplicate procedure names in same scope\n" );
      printf( "error: duplicate procedure names in same scope\n" );
      exit( 4 );
    case dup_var_name:
      fprintf( m_errorfile, "error: duplicate variable names in same scope\n" );
      printf( "error: duplicate variable names in same scope\n" );
      exit( 5 );
    case proc_undef:
      fprintf( m_errorfile, "error: call to undefined procedure\n" );
      printf( "error: call to undefined procedure\n" );
      exit( 6 );
    case var_undef:
      fprintf( m_errorfile, "error: undefined variable\n" );
      printf( "error: undefined variable\n" );
      exit( 7 );
    case narg_mismatch:
      fprintf( m_errorfile, "error: procedure call has different number of args than declartion\n" );
      printf( "error: procedure call has different number of args than declartion\n" );
      exit( 8 );
    case arg_type_mismatch:
      fprintf( m_errorfile, "error: argument type mismatch\n" );
      printf( "error: argument type mismatch\n" );
      exit( 9 );
    case ret_type_mismatch:
      fprintf( m_errorfile, "error: type mismatch in return statement\n" );
      printf( "error: type mismatch in return statement\n" );
      exit( 10 );
    case call_type_mismatch:
      fprintf( m_errorfile, "error: type mismatch in procedure call args\n" );
      printf( "error: type mismatch in procedure call args\n" );
      exit( 11 );
    case ifpred_err:
      fprintf( m_errorfile, "error: predicate of if statement is not boolean\n" );
      printf( "error: predicate of if statement is not boolean\n" );
      exit( 12 );
    case whilepred_err:
      fprintf( m_errorfile, "error: predicate of while statement is not boolean\n" );
      printf( "error: predicate of while statement is not boolean\n" );
      exit( 13 );
    case array_index_error:
      fprintf( m_errorfile, "error: array index not integer\n" );
      printf( "error: array index not integer\n" );
      exit( 14 );
    case no_array_var:
      fprintf( m_errorfile, "error: attempt to index non-array variable\n" );
      printf( "error: attempt to index non-array variable\n" );
      exit( 15 );
    case incompat_assign:
      fprintf( m_errorfile, "error: type of expr and var do not match in assignment\n" );
      printf( "error: type of expr and var do not match in assignment\n" );
      exit( 16 );
    case expr_type_err:
      fprintf( m_errorfile, "error: incompatible types used in expression\n" );
      printf( "error: incompatible types used in expression\n" );
      exit( 17 );
    case expr_abs_error:
      fprintf( m_errorfile, "error: absolute value can only be applied to integers and strings\n" );
      printf( "error: absolute value can only be applied to integers and strings\n" );
      exit( 17 );
    case expr_pointer_arithmetic_err:
      fprintf( m_errorfile, "error: invalid pointer arithmetic\n" );
      printf( "error: invalid pointer arithmetic\n" );
      exit( 18 );
    case expr_addressof_error:
      fprintf( m_errorfile, "error: AddressOf can only be applied to integers, chars, and indexed strings\n" );
      printf( "error: AddressOf can only be applied to integers, chars, and indexed strings\n" );
      exit( 19 );
    case invalid_deref:
      fprintf( m_errorfile, "error: Deref can only be applied to integer pointers and char pointers\n" );
      printf( "error: Deref can only be applied to integer pointers and char pointers\n" );
      exit( 20 );
    case const_assign:
      fprintf( m_errorfile, "error: trying to assign to a const type\n" );
      printf( "error: trying to assign to a const type\n" );
      exit( 21 );
    case array_assign:
      fprintf( m_errorfile, "error: trying to assign a value to the array\n" );
      printf( "error: trying to assign a value to the array\n" );
      exit( 22 );
    case one_d_array_assign:
      fprintf( m_errorfile, "error: wrong length or wrong type in one dimension array assign\n" );
      printf( "error: wrong length or wrong type in one dimension array assign\n" );
      exit( 23 );
    case two_d_array_assign:
      fprintf( m_errorfile, "error: wrong length or wrong type in two dimensions array assign\n" );
      printf( "error: wrong length or wrong type in two dimensions array assign\n" );
      exit( 24 );
    case wrong_array_base_type:
      fprintf( m_errorfile, "error: trying to make a array of unsupported type\n" );
      printf( "error: trying to make a array of unsupported type\n" );
      exit( 25 );
    case init_type_failed:
      fprintf( m_errorfile, "error: unsupported type in init\n" );
      printf( "error: unsupported type in init\n" );
      exit( 26 );
    case forpred_err:
      fprintf( m_errorfile, "error: condition is not boolean in for loop\n" );
      printf( "error: condition is not boolean in for loop\n" );
      exit( 27 );
    case list_differnt_type:
      fprintf( m_errorfile, "error: trying to init a list contains differetn types\n" );
      printf( "error: trying to init a list contains differetn types\n" );
      exit( 28 );
    case tdlist_differnt_type:
      fprintf( m_errorfile, "error: trying to init a 2d list contains differetn types\n" );
      printf( "error: trying to init a 2d list contains differetn types\n" );
      exit( 29 );
    case incre_type:
      fprintf( m_errorfile, "error: trying to use self change operator in unsupported type\n" );
      printf( "error: trying to use self change operator in unsupported type\n" );
      exit( 30 );
    case dot_access_not_struct:
      fprintf( m_errorfile, "error: use dot operator on a variable that's not struct\n" );
      printf( "error: use dot operator on a variable that's not struct\n" );
      exit( 31 );
    case not_a_struct_member:
      fprintf( m_errorfile, "error: variable does not have this member\n" );
      printf( "error: variable does not have this member\n" );
      exit( 32 );
    case not_supported_feature:
      fprintf( m_errorfile, "error: trying to use a not-yet supported feature\n" );
      printf( "error: trying to use a not-yet supported feature\n" );
      exit( 33 );
    case empty_list:
      fprintf( m_errorfile, "error: trying to assign a empty list to something\n" );
      printf( "error: trying to assign a empty list to something\n" );
      exit( 34 );
    case not_ret_type:
      fprintf( m_errorfile, "error: return type must not be a pointer type\n" );
      printf( "error: return type must not be a pointer type\n" );
      exit( 35 );
    case tdlist_differnt_length:
      fprintf( m_errorfile, "error: 2d list with list of different length\n" );
      printf( "error: 2d list with list of different length\n" );
      exit( 36 );
    case switch_case_diff_type:
      fprintf( m_errorfile, "error: in switch statment, case has differnt type\n" );
      printf( "error: in switch statment, case has differnt type\n" );
      exit( 37 );
    case switch_not_base:
      fprintf( m_errorfile, "error: trying to switch a non-base type\n" );
      printf( "error: trying to switch a non-base type\n" );
      exit( 37 );
    case main_not_outmost:
      fprintf( m_errorfile, "error: main not declare in outermost scope\n" );
      printf( "error: main not declare in outermost scope\n" );
      exit( 38 );
    default:
      fprintf( m_errorfile, "error: no good reason\n" );
      printf( "error: no good reason\n" );
      exit( 39 );
    }
  }

  bool is_non_const_number_type( Basetype type ) {
    return ( type == bt_integer || type == bt_long || type == bt_short );
  }

  bool is_number_type( Basetype type ){
    return ( type == bt_integer || type == bt_long || type == bt_short ||
             type == bt_const_int || type == bt_const_long || type == bt_const_short );
  }


  bool is_array_type( Basetype type ) {
    return ( type == bt_int_array || type == bt_char_array || type == bt_bool_array ||
         type == bt_long_array || type == bt_short_array || is_2d_array_type( type ) );
  }

  bool is_2d_array_type( Basetype type ) {
    return  ( type == bt_2d_int_array || type == bt_2d_char_array ||
              type == bt_2d_bool_array ||
              type == bt_2d_long_array || type == bt_2d_short_array );
  }

  bool is_pure_pointer_type( Basetype type ) {
    return ( type == bt_intptr || type == bt_charptr || type == bt_boolptr ||
             type == bt_shortptr || type == bt_longptr );
  }

  bool is_pointer_type( Basetype type ) {
    return ( is_pure_pointer_type( type ) || is_array_type( type ) ||
             is_2d_array_type( type ) );
  }


  bool is_const_type( Basetype type ) {
    return ( type == bt_const_int || type == bt_const_char || type == bt_const_bool ||
             type == bt_const_long || type == bt_const_short);
  }

  bool is_return_type( Basetype type ) {
    return ( is_const_type( type ) || is_number_type( type ) ||
             type == bt_boolean || type == bt_char);
  }

  // helper function to check if the type of array and list macthes
  // only check the basetype, does not check the dimension
  bool check_array_and_list( Basetype type1, Basetype type2 ) {
    if ( ( type1 == bt_int_array || type1 == bt_short_array || type1 == bt_long_array ) &&
         ( type2 == bt_int_list || type2 == bt_short_list || type2 == bt_long_list ) ){
    } else if ( type1 == bt_bool_array && type2 == bt_bool_list ) {
    } else if ( type1 == bt_char_array && type2 == bt_char_list ) {
    } else if ( ( type1 == bt_2d_int_array || type1 == bt_2d_short_array ||
                  type1 == bt_2d_long_array ) &&
                ( type2 == bt_2d_int_list || type2 == bt_2d_short_list ||
                  type2 == bt_2d_long_list ) ) {
    } else if ( type1 == bt_2d_bool_array && type2 == bt_2d_bool_list ) {
    } else if ( type1 == bt_2d_char_array && type2 == bt_2d_char_list ) {
    } else {
      return false;
    }
    return true;
  }

  // type1 must be one of char, bool, long, short, int
  // does not suuport pointer init in for decl
  errortype checkSimpleAssign( Basetype type1, Basetype type2 ) {
    // const type can not be on the left of assign
    if ( is_const_type( type1 ) ) {
      return const_assign;
    }
    if( is_number_type( type1 ) && is_number_type( type2 ) ) {
      return no_error;
    } else if ( ( type1 == bt_boolean &&
                  ( type2 == bt_boolean || type2 == bt_const_bool ) ) ||
                (  type1 == bt_char  &&
                  ( type2 == bt_char || type2 == bt_const_char ) ) ) {
      return no_error;
    }

    return init_type_failed;
  }

  errortype checkSimpleAssignWP( Basetype type1, Basetype type2 ) {
    // const type can be on the lhs other than decl
    if ( is_const_type( type1 ) ) {
      return const_assign;
    }
    // type1 must be one of char, bool, long, short, int or pointer
    // does not suuport pointer init in for decl
    if( is_number_type( type1 ) && is_number_type( type2 ) ) {
      return no_error;
    } else if ( is_pure_pointer_type( type1 ) && type2 == bt_void) {
      return no_error;
    } else if ( ( type1 == bt_boolean &&
                  ( type2 == bt_boolean || type2 == bt_const_bool ) ) ||
                (  type1 == bt_char  &&
                   ( type2 == bt_char || type2 == bt_const_char ) ) ) {
      return no_error;
    }

    return init_type_failed;
  }

  // All possible assign
  // array itself can not be assign after decl
  // long, int, short to long, int, short
  // NULL/bt_void to pointer ( not array )
  // list to array
  // same enum to enum
  // same type to same type ( except NULL and array )
  // can not assign anything to const except in decl
  errortype checkAssign( Basetype type1, char* struct_name1,
                         int first_length1, int second_length1,
                         Basetype type2, char* struct_name2,
                         int first_length2, int second_length2,
                         bool decl) {
    if ( is_array_type( type1 ) ) {
      //assign to a array only happens in declaration
      if ( !decl ) {
        return array_assign;
      }
      if ( second_length1 == -1 ) {
        // 1d array, check if first dimension size gives
        //
        // type [ x ]
        //
        if ( first_length1 == 0 ) {
          // first dimension size is not given, as long as second type
          // is a one d array with same type it will be fine
          //
          // type []
          //
          if ( !check_array_and_list( type1, type2 ) ||
               first_length2 <=0 || second_length2 != -1 ) {
            return one_d_array_assign;
          }
          return no_error;
        } else if ( first_length1 > 0 ) {
          // 1d array, length is given
          //
          // type [ first_length ]
          //
          if ( !check_array_and_list( type1, type2 ) ||
               first_length1 != first_length2 || second_length2 != -1) {
            // either type not match or length not match
            return one_d_array_assign;
          }
          return no_error;
        }
      } else if ( second_length1 > 0 ) {
        // 2d array, chek if first length is given
        //
        // type [ x ] [ x ]
        //
        if ( first_length1 == 0 ) {
          // 2d array without giving the first length
          //
          // type [] [ second_length ]
          //
          if ( !check_array_and_list( type1, type2 ) ||
               second_length1 != second_length2 ||
               first_length2 <=0 ) {
            return two_d_array_assign;
          }
          return no_error;
        } else if ( first_length1 > 0 ) {
          //2d array, first length is given
          //
          // type [ first_length ] [ second_length ]
          //
          if ( !check_array_and_list( type1, type2 ) ||
               second_length1 != second_length2 ||
               first_length1 != first_length2 ) {
            return two_d_array_assign;
          }
          return no_error;
        }
      } else {
        return array_assign;
      }
    }
    // ok, done with the array check, now let's check the pointer type
    if ( is_pure_pointer_type( type1 ) ) {
      if ( type2 == bt_void ){
      } else if ( type2 == type1 ) {
      } else {
        return incompat_assign;
      }
      return no_error;
    }

    // ok, check the enum and struct type
    if ( type1 == bt_enum || type1 == bt_struct) {
      // only valid if type2 if of same enum type of number type
      if ( type2 != type1 || strcmp( struct_name1, struct_name2 ) != 0 ) {
        return incompat_assign;
      }
      return no_error;
    }

    // check assignment to const type
    if ( is_const_type( type1 ) && !decl) {
      return const_assign;
    }

    // check the 5 regular type
    if ( ( is_number_type( type1 ) && is_number_type( type2 ) ) ||
         ( ( type1 == bt_boolean || type1 == bt_const_bool ) &&
           ( type2 == bt_boolean || type2 == bt_const_bool ) ) ||
         ( ( type1 == bt_char || type1 == bt_const_char ) &&
           ( type2 == bt_char || type2 == bt_const_char ) ) ) {
      return no_error;
    }

    // check string assign case
    if ( type1 == bt_string && type2 == bt_string ) {
      return no_error;
    }
    return incompat_assign;
  }


  Basetype dereference_type ( Basetype type ){
    switch ( type ) {
    case bt_intptr:
    case bt_int_array:
      return bt_integer;
    case bt_string:
    case bt_charptr:
    case bt_char_array:
      return bt_char;
    case bt_boolptr:
    case bt_bool_array:
      return bt_boolean;
    case bt_longptr:
    case bt_long_array:
      return bt_long;
    case bt_shortptr:
    case bt_short_array:
      return bt_short;
    case bt_2d_int_array:
      return bt_int_array;
    case bt_2d_char_array:
      return bt_char_array;
    case bt_2d_bool_array:
      return bt_bool_array;
    case bt_2d_short_array:
      return bt_short_array;
    case bt_2d_long_array:
      return bt_long_array;
    default:
      return bt_undef;
    }
  }

  Basetype baseToList( Basetype type ) {
    switch ( type ) {
    case bt_integer: return bt_int_list;
    case bt_long: return bt_long_list;
    case bt_short: return bt_short_list;
    case bt_char: return bt_char_list;
    case bt_boolean: return bt_bool_list;
    case bt_empty : return bt_empty_list;
    default: return bt_undef;
    }
  }

  Basetype listToTDList( Basetype type ) {
    switch ( type ) {
    case bt_int_list: return bt_2d_int_list;
    case bt_long_list: return bt_2d_long_list;
    case bt_short_list: return bt_2d_short_list;
    case bt_char_list: return bt_2d_char_list;
    case bt_bool_list: return bt_2d_bool_list;
    case bt_empty_list : return bt_2d_empty_list;
    default: return bt_undef;
    }
  }

  Basetype double_dereference_type ( Basetype type ) {
    switch ( type ) {
    case bt_2d_int_array:
      return bt_integer;
    case bt_2d_bool_array:
      return bt_boolean;
    case bt_2d_char_array:
      return bt_char;
    case bt_2d_long_array:
      return bt_long;
    case bt_2d_short_array:
      return bt_short;
    default:
      return bt_undef;
    }
  }

  Basetype type_to_array( Basetype type, int dimension ) {
    if ( dimension == 1 ) {
      switch ( type )  {
      case bt_integer : return bt_int_array;
      case bt_long : return bt_long_array;
      case bt_short: return bt_short_array;
      case bt_char : return bt_char_array;
      case bt_boolean : return bt_bool_array;
      default : return bt_undef;
      }
    } else if ( dimension == 2 ) {
      switch ( type )  {
      case bt_integer : return bt_2d_int_array;
      case bt_long : return bt_2d_long_array;
      case bt_short: return bt_2d_short_array;
      case bt_char : return bt_2d_char_array;
      case bt_boolean : return bt_2d_bool_array;
      default : return bt_undef;
      }
    }else {
      return bt_undef;
    }
  }

  // Check that there is one and only one main
  void check_for_one_main( ProgramImpl* p ) {
    Symbol * s = m_st->lookup( "main" );

    if ( s == NULL || s->m_basetype != bt_procedure ){
      this->t_error(no_main, p->m_attribute);
    }
  }

  // Create a symbol for the procedure and check there is none already
  // existing, procedure go to the upper scope, value in the procedure
  // go to the lower scope
  void add_proc_symbol(ProcedureImpl* p){
    std::list<Decl_ptr>::iterator iter;
    char * name = strdup( p->m_symname->spelling() );
    Symbol *s = new Symbol();

    if ( strcmp( name, "main" ) == 0 && !m_st->isOuterMostScope() ){
      // main must be outer most scope
      this->t_error( main_not_outmost, p->m_attribute );
    }

    // add the parameter type to the symbol
    for (iter = p->m_decl_list->begin(); iter != p->m_decl_list->end(); ++iter){
      s->m_arg_type.push_back(static_cast<Decl_variable *>(*iter)->m_type->m_attribute.m_basetype);
    }

    // set the basetype and return type for the procedure
    s->m_basetype = bt_procedure;
    s->m_return_type = p->m_type->m_attribute.m_basetype;

    //check if proc is main, if it is make sure it takes no argument
    if ( strcmp( name, "main" ) == 0 ) {
      if ( s->m_arg_type.size() != 0 )
        this->t_error( nonvoid_main, p->m_attribute );
    }
    if( !m_st->insert( name, s ) )
      this->t_error( dup_proc_name, p->m_attribute );
  }

  // Add symbol table information for all the declarations following
  void add_decl_symbol(Decl_variable* p) {
    // all cases that need to be taking care of
    // one dimentation array with/without length
    // two dimentation array with/without length
    // regular decl of variable
    Basetype type = p->m_type->m_attribute.m_basetype;
    char* struct_name = ( p->m_type->m_attribute.m_struct_name != NULL ) ?
      strdup ( p->m_type->m_attribute.m_struct_name ) : NULL ;
    int first_length = p->m_primitive_1->m_data;
    int second_length = p->m_primitive_2->m_data;
    Basetype real_type;
    char* real_struct_name;
    int real_first_length;
    int real_second_length;

    char* name;
    Symbol* s;

    //get all of the symname out
    std::list<SymName_ptr> name_list;
    std::list<Expr_ptr> assign_list;
    std::list<AssignPair_ptr>::iterator pairIter;
    std::list<SymName_ptr>::iterator symIter;
    std::list<Expr_ptr>::iterator exprIter;

    if ( p->m_assignpair_list != NULL ) {
      for ( pairIter = p->m_assignpair_list->begin();
            pairIter != p->m_assignpair_list->end();
            ++pairIter ) {
        name_list.push_back( static_cast<AssignPairImpl*>( *pairIter )->m_symname );
        assign_list.push_back( static_cast<AssignPairImpl*>( *pairIter )->m_expr );
      }
    }
    exprIter = assign_list.begin();
    //check the array decl type is integer
    if ( first_length == -1 && second_length == -1 ) {
      // current type if the real type
    } else if ( first_length != -1 && second_length == -1 ) {
      // it is actually a one d array, transfer the type
      type = type_to_array( type, 1 );
    } else if ( first_length != -1 && second_length != -1  ) {
      type = type_to_array( type, 2 );
    }
    if ( type == bt_undef ) {
      this->t_error( wrong_array_base_type, p->m_attribute );
    }
    // go through the pair list, check the assign and add them to symtab
    for ( symIter = name_list.begin();
          symIter != name_list.end();
          symIter++ ) {
      real_struct_name = ( ( *exprIter )->m_attribute.m_struct_name != NULL ) ?
        strdup ( ( *exprIter )->m_attribute.m_struct_name ) : NULL;
      real_type = ( *exprIter != NULL ) ?
        ( *exprIter )->m_attribute.m_basetype : bt_undef;
      real_first_length = ( *exprIter != NULL ) ?
        ( *exprIter )->m_attribute.m_length1 : -1 ;
      real_second_length = ( *exprIter != NULL ) ?
        ( *exprIter )->m_attribute.m_length2 : -1 ;

      if ( ( *exprIter )->m_attribute.m_basetype != bt_empty ) {
        // there are assign come with the declare, check if assignment if valid
        errortype error_message;
        error_message = checkAssign( type, struct_name, first_length, second_length,
                                     real_type, real_struct_name,
                                     real_first_length, real_second_length,
                                     true );
        if ( error_message != no_error ){
          this->t_error( error_message, p->m_attribute );
        }
      }
      //assign is valid, now add this variable to the symbol table
      name = strdup( (*symIter)->spelling() );
      s = new Symbol();
      s->m_basetype = type;
      s->m_type_name = ( struct_name != NULL ) ? strdup( struct_name ) : NULL;
      s->m_length1 = real_first_length;
      s->m_length2 = real_second_length;

      if(! m_st->insert(name,s)){
        this->t_error(dup_var_name, p->m_attribute);
      }
      exprIter++;
    }

    if ( struct_name != NULL ) {
      delete struct_name;
    }
    if ( real_struct_name != NULL ) {
      delete real_struct_name;
    }
  }

  // Check that the return statement of a procedure has the appropriate type
  void check_proc(ProcedureImpl *p) {
    Basetype correct_type = p->m_type->m_attribute.m_basetype;
    Basetype real_type = static_cast<Return_statImpl *>
      (p->m_return_stat)->m_expr->m_attribute.m_basetype;
    if ( !is_return_type( correct_type ) ){
      this->t_error(not_ret_type, p->m_attribute);
    }

    // taking care of const case too
    if( is_number_type( correct_type ) && is_number_type( real_type ) ) {
    } else if ( is_pure_pointer_type( correct_type ) && real_type == bt_void) {
    }
    else if ( ( ( correct_type == bt_boolean || correct_type == bt_const_bool  )&&
                  ( real_type == bt_boolean || real_type == bt_const_bool ) ) ||
                (  ( correct_type == bt_char || correct_type == bt_const_char ) &&
                   ( real_type == bt_char || real_type == bt_const_char ) ) ) {
    } else {
      this->t_error(ret_type_mismatch,p->m_attribute);
    }
  }

  // Create a symbol for the procedure and check there is none already
  // existing
  void check_call(CallImpl *p){
    // check if procedure exist and it is a procedure
    // chek number of argument matches
    // type of arguments matches
    // p's type if the function's return type
    std::list<Expr_ptr>::iterator iter;
    Symbol * s = m_st->lookup(p->m_symname->spelling());
    if(s==NULL)
      this->t_error(proc_undef, p->m_attribute);
    if(p->m_expr_list->size()!=s->m_arg_type.size())
      this->t_error(narg_mismatch, p->m_attribute);

    std::vector<Basetype>::iterator iter2 = s->m_arg_type.begin();
    for(iter = p->m_expr_list->begin(); iter!=p->m_expr_list->end(); ++iter){
      Basetype type1 = (*iter)->m_attribute.m_basetype;
      Basetype type2 = *(iter2);
      if(type1!=type2){
        if ( is_number_type( type1 ) && is_number_type( type2 )){
        } else if ( ( ( type1 == bt_boolean || type1 == bt_const_bool  )&&
                 ( type2 == bt_boolean || type2 == bt_const_bool ) ) ||
               (  ( type1 == bt_char || type1 == bt_const_char ) &&
                  ( type2 == bt_char || type2 == bt_const_char ) ) ){
        } else if ( is_pure_pointer_type( type1 ) && type2 == bt_void){
        } else {
          this->t_error(arg_type_mismatch, p->m_attribute);
        }
      }
      ++iter2;
    }
  }

  // For checking that this expressions type is boolean used in if/else and
  // while visits
  void check_pred(Expr* p, int index) {
    if( p->m_attribute.m_basetype != bt_boolean &&
        p->m_attribute.m_basetype != bt_const_bool ){
      if ( index == 1 ) {
        this->t_error( ifpred_err, p->m_attribute );
      } else if ( index == 2 ){
        this->t_error( whilepred_err, p->m_attribute );
      } else {
        this->t_error( forpred_err, p->m_attribute );
      }
    }
  }

  void check_assignment(Assignment* p) {
    // use helper function checkAssign
    Basetype type1 = p->m_lhs->m_attribute.m_basetype;
    char* struct_name1 = ( p->m_lhs->m_attribute.m_struct_name != NULL ) ?
      strdup( p->m_lhs->m_attribute.m_struct_name ) : NULL;
    Basetype type2 = p->m_expr->m_attribute.m_basetype;
    char* struct_name2 = ( p->m_expr->m_attribute.m_struct_name != NULL ) ?
      strdup( p->m_expr->m_attribute.m_struct_name ) : NULL;

    errortype error_message;
    error_message = checkAssign( type1, struct_name1, -1, -1,
                                 type2, struct_name2, -1, -1, false);

    if( error_message != no_error ) {
      this->t_error( error_message, p->m_attribute );
    }

    if ( struct_name1 != NULL ) {
      delete struct_name1;
    }
    if ( struct_name2 != NULL ) {
      delete struct_name2;
    }
  }

  void check_string_assignment(String_assignment* p) {
    if(p->m_lhs->m_attribute.m_basetype!=bt_string)
      this->t_error(incompat_assign, p->m_attribute);
  }

  void check_array_access(ArrayAccess* p) {
    Symbol * s = m_st->lookup( p->m_symname->spelling() );
    if ( s == NULL ) {
      this->t_error(var_undef, p->m_attribute);
    }
    if ( s->m_basetype != bt_string && !is_pointer_type( s->m_basetype ) ) {
      this->t_error(expr_type_err, p->m_attribute);
    }
    if( !is_number_type( p->m_expr->m_attribute.m_basetype ) ) {
      this->t_error(array_index_error, p->m_attribute);
    }
    if ( s->m_basetype == bt_string ) {
      p->m_attribute.m_basetype = bt_char;
    } else {
      p->m_attribute.m_basetype = dereference_type( s->m_basetype );
    }
  }
  void check_2d_array_access(ArrayDoubleAccess* p) {
    Symbol * s = m_st->lookup( p->m_symname->spelling() );
    if ( s == NULL ) {
      this->t_error(var_undef, p->m_attribute);
    }
    Basetype type = s->m_basetype;
    if ( !is_2d_array_type( type ) ){
      this->t_error(expr_type_err, p->m_attribute);
    }
    if( !is_number_type( p->m_expr_1->m_attribute.m_basetype ) ||
        !is_number_type( p->m_expr_2->m_attribute.m_basetype ) ) {
      this->t_error(array_index_error, p->m_attribute);
    }
    p->m_attribute.m_basetype = double_dereference_type( type );
  }

  void check_array_element(ArrayElement* p) {
    Symbol * s = m_st->lookup( p->m_symname->spelling() );
    if ( s == NULL ) {
      this->t_error(var_undef, p->m_attribute);
    }
    if ( s->m_basetype != bt_string && !is_pointer_type( s->m_basetype ) ) {
      this->t_error(expr_type_err, p->m_attribute);
    }
    if ( !is_number_type( p->m_expr->m_attribute.m_basetype ) ) {
      this->t_error(array_index_error, p->m_attribute);
    }
    if ( s->m_basetype == bt_string ) {
      p->m_attribute.m_basetype = bt_char;
    } else {
      p->m_attribute.m_basetype = dereference_type( s->m_basetype );
    }
  }

  void check_2d_array_element( ArrayDoubleElement* p ) {
    Symbol * s = m_st->lookup( p->m_symname->spelling() );
    if ( s == NULL ) {
      this->t_error(var_undef, p->m_attribute);
    }
    Basetype type = s->m_basetype;
    if ( !is_2d_array_type( type ) ){
      this->t_error(expr_type_err, p->m_attribute);
    }
    if(!is_number_type( p->m_expr_1->m_attribute.m_basetype ) ||
       !is_number_type( p->m_expr_2->m_attribute.m_basetype ) ) {
      this->t_error(array_index_error, p->m_attribute);
    }
    p->m_attribute.m_basetype = double_dereference_type( type );
  }

  // For checking boolean operations(and, or ...)
  void checkset_boolexpr(Expr* parent, Expr* child1, Expr* child2) {
    Basetype type1 = child1->m_attribute.m_basetype;
    Basetype type2 = child2->m_attribute.m_basetype;
    if ( ( type1 != bt_boolean && type1 != bt_const_bool ) ||
         ( type2 != bt_boolean && type2 != bt_const_bool) ) {
      this->t_error(expr_type_err, parent->m_attribute);
    }
    parent->m_attribute.m_basetype = bt_boolean;
  }

  // For checking arithmetic expressions( times, divide...)
  void checkset_arithexpr(Expr* parent, Expr* child1, Expr* child2) {
    // times and divide only valid in number type
    // long > int > char
    // result going to the higher type
    Basetype type1 = child1->m_attribute.m_basetype;
    Basetype type2 = child2->m_attribute.m_basetype;
    if ( is_number_type( type1 ) && is_number_type( type2 ) ){
      if ( type1 == bt_long && type2 == bt_long ) {
        parent->m_attribute.m_basetype = bt_long;
      } else if ( type1 == bt_integer || type2 == bt_integer ) {
        parent->m_attribute.m_basetype = bt_integer;
      } else {
        parent->m_attribute.m_basetype = bt_short;
      }
    } else {
      this->t_error(expr_type_err, parent->m_attribute);
    }
  }

  // Called by plus and minus: in these cases we allow pointer arithmetics
  void checkset_arithexpr_or_pointer(Expr* parent, Expr* child1, Expr* child2) {
    // can operate on two numbers
    // can operate on one pointer and one number
    // long > int > short, the result will go to bigger type
    // although in current design they are all 32 bits
    // Todo, support add in 2d array
    Basetype type1 = child1->m_attribute.m_basetype;
    Basetype type2 = child2->m_attribute.m_basetype;
    if ( is_number_type( type1 ) && is_number_type( type2 ) ) {
      if ( type1 == bt_long || type1 == bt_const_long ||
           type2 == bt_long || type2 == bt_const_long ) {
        parent->m_attribute.m_basetype = bt_long;
      } else if ( type1 == bt_integer || type1 == bt_const_int ||
                  type2 == bt_integer || type2 == bt_const_int ) {
        parent->m_attribute.m_basetype = bt_integer;
      } else {
        parent->m_attribute.m_basetype = bt_short;
      }
    } else if ( is_pointer_type( type1 ) && is_number_type( type2 ) ) {
      parent->m_attribute.m_basetype = type1;
    } else if ( is_number_type( type1 ) && is_pointer_type( type2 ) ) {
      parent->m_attribute.m_basetype = type2;
    } else {
      this->t_error(expr_type_err, parent->m_attribute);
    }
  }

  // For checking relational(less than , greater than, ...)
  void checkset_relationalexpr(Expr* parent, Expr* child1, Expr* child2) {
    // can compare two numbers or two same type of pointer
    Basetype type1 = child1->m_attribute.m_basetype;
    Basetype type2 = child2->m_attribute.m_basetype;
    if ( is_number_type( type1 ) && is_number_type( type2 ) ) {
    } else if ( is_pointer_type( type1 ) && is_pointer_type( type2 )  &&
                type1 == type2 ) {
    } else {
      this->t_error( expr_type_err, parent->m_attribute );
    }
    parent->m_attribute.m_basetype = bt_boolean;
  }


  // For checking equality ops(equal, not equal)
  // add const support
  void checkset_equalityexpr(Expr* parent, Expr* child1, Expr* child2) {
    Basetype type1 = child1->m_attribute.m_basetype;
    Basetype type2 = child2->m_attribute.m_basetype;
    if ( type1 == type2 ) {
    } else if ( type1 == bt_const_bool && type2 == bt_boolean ) {
    } else if ( type2 == bt_const_bool && type1 == bt_boolean ) {
    } else if ( type1 == bt_const_char && type2 == bt_char ) {
    } else if ( type2 == bt_const_char && type1 == bt_char ) {
    } else if ( is_number_type( type1 ) && is_number_type( type2 ) ){
    } else if ( is_pointer_type( type1 ) && type2 == bt_void ) {
    } else if ( is_pointer_type( type2 ) && type1 == bt_void ) {
    } else {
      this->t_error( expr_type_err, parent->m_attribute );
    }
    parent->m_attribute.m_basetype = bt_boolean;
  }

  // For checking not
  void checkset_not(Expr* parent, Expr* child) {
    if ( child->m_attribute.m_basetype != bt_boolean &&
         child->m_attribute.m_basetype != bt_const_bool ) {
      this->t_error( expr_type_err, parent->m_attribute );
    }
    parent->m_attribute.m_basetype = bt_boolean;
  }

  // For checking unary minus
  void checkset_uminus(Expr* parent, Expr* child) {
    if(child->m_attribute.m_basetype != bt_integer)
      this->t_error(expr_type_err, parent->m_attribute);
    parent->m_attribute.m_basetype = bt_integer;
  }

  void checkset_addressof(Expr* parent, Lhs* child) {
    Basetype type = child->m_attribute.m_basetype;
    switch ( type ) {
    case bt_const_int:
    case bt_integer:
      parent->m_attribute.m_basetype = bt_intptr; break;
    case bt_intptr:
    case bt_int_array:
      parent->m_attribute.m_basetype = bt_2d_int_array; break;
    case bt_boolean:
    case bt_const_bool:
      parent->m_attribute.m_basetype = bt_boolptr; break;
    case bt_boolptr:
    case bt_bool_array:
      parent->m_attribute.m_basetype = bt_2d_bool_array; break;
    case bt_char:
    case bt_const_char:
      parent->m_attribute.m_basetype = bt_charptr; break;
    case bt_charptr:
    case bt_char_array:
      parent->m_attribute.m_basetype = bt_2d_char_array; break;
    case bt_long:
    case bt_const_long:
      parent->m_attribute.m_basetype = bt_longptr; break;
    case bt_longptr:
    case bt_long_array:
      parent->m_attribute.m_basetype = bt_2d_long_array; break;
    case bt_short:
    case bt_const_short:
      parent->m_attribute.m_basetype = bt_shortptr; break;
    case bt_shortptr:
    case bt_short_array:
      parent->m_attribute.m_basetype = bt_2d_short_array; break;
    default:
      this->t_error(expr_addressof_error, parent->m_attribute);
    }
  }

  void checkset_deref_expr(Deref* parent,Expr* child) {
    Basetype type = child->m_attribute.m_basetype;
    type = dereference_type( type );
    if ( type == bt_undef ) {
      this->t_error(invalid_deref, parent->m_attribute);
    }
    parent->m_attribute.m_basetype = type;
  }

  // Check that if the right-hand side is an lhs, such as in case of
  // addressof
  void checkset_deref_lhs(DerefVariable* p) {
    Symbol * s = m_st->lookup( p->m_symname->spelling() );
    if ( s == NULL ) {
      this->t_error( var_undef, p->m_attribute );
    }
    Basetype type = dereference_type( s->m_basetype );
    if ( type == bt_undef ) {
      this->t_error(invalid_deref, p->m_attribute);
    }
    p->m_attribute.m_basetype = type;
  }

  void checkset_variable(Variable* p) {
    Symbol * s = m_st->lookup( p->m_symname->spelling() );
    if ( s == NULL ) {
      this->t_error( var_undef, p->m_attribute );
    }
    p->m_attribute.m_basetype = s->m_basetype;
  }

  void checkset_Ident(Ident* p) {
    Symbol * s = m_st->lookup( p->m_symname->spelling() );
    if ( s == NULL ) {
      this->t_error( var_undef, p->m_attribute );
    }
    p->m_attribute.m_basetype = s->m_basetype;
  }

  void addEnum_define( Enum_defineImpl * e ) {
    Symbol * s;
    char * name;
    if ( e->m_primitive->m_data == 1 ) {
      //enum has a type name
      s = new Symbol();
      s->m_basetype = bt_enum_type;
      name = strdup( e->m_symname_1->spelling() );
      if( !m_st->insert( name,s ) ) {
        this->t_error(dup_var_name, e->m_attribute);
      }
    }

    //now add the enum list to the symtab
    std::list<SymName_ptr>::iterator iter;
    for( iter = e->m_symname_list_2->begin();
         iter != e->m_symname_list_2->end();
         iter++) {
      s = new Symbol();
      s->m_basetype = bt_enum;
      if ( e->m_primitive->m_data == 1 ) {
        s->m_type_name = strdup ( e->m_symname_1->spelling() );
      } else {
        s->m_type_name = new char[ 13 ];
        strcpy( s->m_type_name, "no_enum_name" );
      }
      name = strdup( ( *iter )->spelling() );
      if( !m_st->insert( name, s) ) {
        this->t_error(dup_var_name, e->m_attribute);
      }
    }

  }

  void process_Proc_symbol( ProcedureImpl *p ) {
    std::list<Decl_ptr>::iterator iter;
    char * name;
    Symbol *s = new Symbol();
    int size =0;
    for (iter = p->m_decl_list->begin(); iter != p->m_decl_list->end(); ++iter){
      static_cast<Decl_variable*>(*iter)->m_type->accept(this);
    }
    p->m_type->accept(this);
  }

public:
  void default_rule(Visitable* p){
    static_cast<Program*>(p)->m_attribute.m_scope = m_st->get_scope();
    p->visit_children(this);
  }

  Typecheck(FILE* errorfile, SymTab* st) {
    m_errorfile = errorfile;
    m_st = st;
  }

  void visitProgramImpl( ProgramImpl *p ) { 
    default_rule( p );
    check_for_one_main( p );
  }

  void visitOut_enum_define( Out_enum_define *p ) { 
    default_rule( p );
  }

  void visitOut_decl( Out_decl *p ) { 
    default_rule( p );
  }

  void visitOut_procedure( Out_procedure *p ) { 
    default_rule( p );
  }

  void visitOut_struct_define( Out_struct_define *p ) { 
    default_rule( p );
  }

  void visitAssignPairImpl( AssignPairImpl *p ) { 
    default_rule( p );
  }

  void visitEnum_defineImpl( Enum_defineImpl *p ) { 
    default_rule( p );
    addEnum_define( p );
  }

  void visitDecl_variable( Decl_variable *p ) { 
    default_rule( p );
    add_decl_symbol( p );
  }

  void visitDecl_function( Decl_function *p ) {
    // shouldn't be called anyway
    // removed from parser
    default_rule( p );
  }

  void visitProcedureImpl( ProcedureImpl *p ) { 
    process_Proc_symbol( p );
    p->m_attribute.m_scope = m_st->get_scope();
    add_proc_symbol( p );
    m_st->open_scope();
    default_rule( p );
    m_st->close_scope();
    check_proc( p );
  }

  void visitStruct_defineImpl( Struct_defineImpl *p ) { 
    // default_rule( p );
    // should not add struct's member to symtab table
    // add the name as type
    char * name = strdup( p->m_symname->spelling() );
    Symbol * s = new Symbol() ;
    s->m_basetype = bt_struct_type;
    int offset = 0;

    // symbol need to store the type and name information
    // use map might be a good idea
    // go through the deal
    for( auto iter = p->m_short_decl_list->begin();
         iter != p->m_short_decl_list->end();
         iter++ ) {
      // check if name is being used
      auto it = s->m_map.find( dynamic_cast< Short_declImpl* >
                               ( *iter )->m_symname->spelling() );
      if ( it != s->m_map.end() ) {
        this->t_error(dup_var_name, p->m_attribute);
      }

      // create the pair to store the offset and type
      std::pair< Basetype, int > member_info( dynamic_cast< Short_declImpl* >
                                              ( *iter )->m_type->m_attribute.m_basetype,
                                              offset );

      // add the deal to map one by one
      name = strdup( dynamic_cast< Short_declImpl* >( *iter )->m_symname->spelling() );
      s->m_map[ name ] = member_info;
      offset += 4;
    }

    if(! m_st->insert(name,s)){
      this->t_error(dup_var_name, p->m_attribute);
    }
  }

  void visitCallImpl( CallImpl *p ) {
    default_rule( p );
    check_call( p );
  }

  void visitCaseImpl( CaseImpl *p ) { 
    default_rule( p );
  }

  void visitPProcedure( PProcedure *p ) { 
    default_rule( p );
  }

  void visitPStat( PStat *p ) { 
    default_rule( p );
  }

  void visitInit_new( Init_new *p ) { 
    // add the symbol to current scope
    default_rule( p );
    char * name = strdup( p->m_symname->spelling() );
    Symbol * s = new Symbol();
    s->m_basetype = p->m_type->m_attribute.m_basetype;
    if(! m_st->insert(name,s)){
      this->t_error(dup_var_name, p->m_attribute);
    }
    // check assign type match exist, if exist, check the type match
    if ( p->m_expr->m_attribute.m_basetype != bt_empty ) {
      errortype err = checkSimpleAssign( p->m_type->m_attribute.m_basetype,
                                         p->m_expr->m_attribute.m_basetype);
      if ( err != no_error ) {
        this->t_error( err, p->m_attribute );
      }
    }
  }

  void visitInit_old( Init_old *p ) { 
    // check if variable exist
    default_rule( p );
    Symbol * s = m_st->lookup( p->m_symname->spelling() );
    if ( s == NULL ) {
      this->t_error(var_undef, p->m_attribute);
    }

    // check assign type match exist, if exist, check the type match
    if ( p->m_expr->m_attribute.m_basetype != bt_empty ) {
      errortype err = checkSimpleAssign( s->m_basetype,
                                         p->m_expr->m_attribute.m_basetype);
      if ( err != no_error ) {
        this->t_error( err, p->m_attribute );
      }
    }
  }

  void visitNStat( NStat *p ) {
    default_rule( p );
  }

  void visitRStat( RStat *p ) { 
    default_rule( p );
  }

  void visitAssignment( Assignment *p ) { 
    default_rule( p );
    check_assignment( p );
  }

  void visitString_assignment( String_assignment *p ) { 
    default_rule( p );
    check_string_assignment( p );
  }

  // check lhs's type and function return type matches
  // pointer is allowed
  void visitFunction_assignment( Function_assignment *p ) { 
    default_rule( p );
    // get the return type of function
    Symbol * s = m_st->lookup( dynamic_cast<CallImpl*>
                               ( p->m_call)->m_symname->spelling() );
    if ( s == NULL ) {
      this->t_error( proc_undef, p->m_attribute );
    }

    errortype err = checkSimpleAssignWP( p->m_lhs->m_attribute.m_basetype,
                         s->m_return_type );
    if ( err != no_error ) {
      this->t_error( err, p->m_attribute );
    }
  }

  void visitSIncre( SIncre *p ) { 
    default_rule( p );
  }

  void visitFunction_call( Function_call *p ) { 
    default_rule( p );
  }

  // check if expr is bool
  void visitIf_no_else( If_no_else *p ) {
    m_st->open_scope();
    default_rule( p );
    m_st->close_scope();
    check_pred( p->m_expr, 1 );
  }

  void visitIf_with_else( If_with_else *p ) { 
    m_st->open_scope();
    default_rule( p );
    m_st->close_scope();
    check_pred( p->m_expr, 1 );
  }

  void visitWhile_loop( While_loop *p ) { 
    m_st->open_scope();
    default_rule( p );
    m_st->close_scope();
    check_pred( p->m_expr, 2 );
  }

  void visitDo_while( Do_while *p ) { 
    m_st->open_scope();
    default_rule( p );
    m_st->close_scope();
    check_pred( p->m_expr, 2 );
  }

  void visitFor_loop( For_loop *p ) {
    m_st->open_scope();
    default_rule( p );
    m_st->close_scope();
    check_pred( p->m_expr, 3 );
  }

  void visitSwitch( Switch *p ) {
    default_rule( p );
    Basetype switchType = p->m_expr->m_attribute.m_basetype;
    Basetype caseType;
    // switch type must be one of the basetype
    if ( !is_return_type( p->m_expr->m_attribute.m_basetype ) ) {
      this->t_error( switch_not_base, p->m_attribute );
    }
    // check all cases has the same type as the switcher
    for ( auto iter = p->m_case_list->begin();
          iter != p->m_case_list->end();
          iter++ ) {
      caseType = dynamic_cast< CaseImpl* >( *iter )->m_expr->m_attribute.m_basetype;
      if ( checkSimpleAssign( switchType,caseType ) != no_error) {
        this->t_error( switch_case_diff_type, p->m_attribute );
      }
    }
  }

  void visitBreak( Break *p ) { 
    default_rule( p );
  }

  void visitContinue( Continue *p ) { 
    default_rule( p );
  }

  void visitStat_struct_define( Stat_struct_define *p ) {
    default_rule( p );
  }

  void visitStat_enum_define( Stat_enum_define *p ) { 
    default_rule( p );
  }

  void visitStat_decl( Stat_decl *p ) {
    default_rule( p );
  }

  void visitShort_declImpl( Short_declImpl *p ) {
    char * name = strdup( p->m_symname->spelling() );
    Symbol * s = new Symbol();
    s->m_basetype = p->m_type->m_attribute.m_basetype;
    if(!m_st->insert(name,s))
      this->t_error(dup_proc_name, p->m_attribute);
  }

  void visitReturn_statImpl( Return_statImpl *p ) { 
    default_rule( p );
  }

  void visitTInt( TInt *p ) {
    default_rule( p );
    p->m_attribute.m_basetype = bt_integer;
  }

  void visitTChar( TChar *p ) {
    default_rule( p );
    p->m_attribute.m_basetype = bt_char;
  }

  void visitTBool( TBool *p ) {
    default_rule( p );
    p->m_attribute.m_basetype = bt_boolean;
  }

  void visitTShort( TShort *p ) {
    default_rule( p );
    p->m_attribute.m_basetype = bt_short;
  }

  void visitTVoid( TVoid *p ) {
    default_rule( p );
    p->m_attribute.m_basetype = bt_void;
  }

  void visitTLong( TLong *p ) {
    default_rule( p );
    p->m_attribute.m_basetype = bt_long;
  }

  void visitTStruct( TStruct *p ) {
    default_rule( p );
    p->m_attribute.m_basetype = bt_struct;
  }

  void visitTEnum( TEnum *p ) {
    default_rule( p );
    p->m_attribute.m_basetype = bt_enum;
  }

  void visitTCInt( TCInt *p ) {
    default_rule( p );
    p->m_attribute.m_basetype = bt_const_int;
  }

  void visitTCChar( TCChar *p ) {
    default_rule( p );
    p->m_attribute.m_basetype = bt_const_char;
  }

  void visitTCBool( TCBool *p ) {
    default_rule( p );
    p->m_attribute.m_basetype = bt_const_bool;
  }

  void visitTCShort( TCShort *p ) {
    default_rule( p );
    p->m_attribute.m_basetype = bt_const_short;
  }

  void visitTCLong( TCLong *p ) {
    default_rule( p );
    p->m_attribute.m_basetype = bt_const_long;
  }

  void visitTCharPtr( TCharPtr *p ) {
    default_rule( p );
    p->m_attribute.m_basetype = bt_charptr;
  }

  void visitTIntPtr( TIntPtr *p ) {
    default_rule( p );
    p->m_attribute.m_basetype = bt_intptr;
  }

  void visitTBoolPtr( TBoolPtr *p ) {
    default_rule( p );
    p->m_attribute.m_basetype = bt_boolptr;
  }

  void visitTShortPtr( TShortPtr *p ) {
    default_rule( p );
    p->m_attribute.m_basetype = bt_shortptr;
  }

  void visitTVoidPtr( TVoidPtr *p ) {
    default_rule( p );
    p->m_attribute.m_basetype = bt_voidptr;
  }

  void visitTLongPtr( TLongPtr *p ) {
    default_rule( p );
    p->m_attribute.m_basetype = bt_longptr;
  }

  void visitTIntArray( TIntArray *p ) {
    default_rule( p );
    p->m_attribute.m_basetype = bt_int_array;
  }

  void visitTCharArray( TCharArray *p ) {
    default_rule( p );
    p->m_attribute.m_basetype = bt_char_array;
  }

  void visitTBoolArray( TBoolArray *p ) {
    default_rule( p );
    p->m_attribute.m_basetype = bt_bool_array;
  }

  void visitTShortArray( TShortArray *p ) {
    default_rule( p );
    p->m_attribute.m_basetype = bt_short_array;
  }

  void visitTLongArray( TLongArray *p ) {
    default_rule( p );
    p->m_attribute.m_basetype = bt_long_array;
  }

  void visitTTDIntArray( TTDIntArray *p ) {
    default_rule( p );
    p->m_attribute.m_basetype = bt_2d_int_array;
  }

  void visitTTDCharArray( TTDCharArray *p ) {
    default_rule( p );
    p->m_attribute.m_basetype = bt_2d_char_array;
  }

  void visitTTDBoolArray( TTDBoolArray *p ) {
    default_rule( p );
    p->m_attribute.m_basetype = bt_2d_bool_array;
  }

  void visitTTDShortArray( TTDShortArray *p ) {
    default_rule( p );
    p->m_attribute.m_basetype = bt_2d_short_array;
  }

  void visitTTDLongArray( TTDLongArray *p ) {
    default_rule( p );
    p->m_attribute.m_basetype = bt_2d_long_array;
  }

  void visitTString( TString *p ) {
    default_rule( p );
    p->m_attribute.m_basetype = bt_string;
  }

  void visitNo_type( No_type *p ) {
    default_rule( p );
    p->m_attribute.m_basetype = bt_undef;
  }

  // check if all expr in list are of same type
  void visitListImpl( ListImpl *p ) {
    default_rule( p );
    // if length of list is 0, type is bt_empty_list
    Basetype type;
    // init was -1 means not a list/array
    p->m_attribute.m_length1 = 0;
    auto iter = p->m_expr_list->begin();
    if ( p->m_expr_list->size() == 0 ) {
      type = bt_empty;
    } else {
      type = ( *iter )->m_attribute.m_basetype;
    }
    for ( ;
          iter != p->m_expr_list->end();
          iter++ ) {
      // all expr must be same type
      if ( type != ( *iter )->m_attribute.m_basetype ) {
        this->t_error( list_differnt_type, p->m_attribute );
      }
      p->m_attribute.m_length1++;
    }

    // all element is same type, list would be type of that list
    p->m_attribute.m_basetype = baseToList( type );
    if ( p->m_attribute.m_basetype == bt_empty_list ) {
      this->t_error( empty_list, p->m_attribute );
    }
  }

  void visitIncre_op( Incre_op *p ) { 
    default_rule( p );
  }

  void visitIncre_t_add( Incre_t_add *p ) { 
    default_rule( p );
    if ( !is_non_const_number_type( p->m_lhs->m_attribute.m_basetype ) ) {
      this->t_error( incre_type, p->m_attribute );
    }
  }

  void visitIncre_t_min( Incre_t_min *p ) { 
    default_rule( p );
    if ( !is_non_const_number_type( p->m_lhs->m_attribute.m_basetype ) ) {
      this->t_error( incre_type, p->m_attribute );
    }
  }

  void visitIncre_add_t( Incre_add_t *p ) { 
    default_rule( p );
    if ( !is_non_const_number_type( p->m_lhs->m_attribute.m_basetype ) ) {
      this->t_error( incre_type, p->m_attribute );
    }
  }

  void visitIncre_min_t( Incre_min_t *p ) {
    default_rule( p );
    if ( !is_non_const_number_type( p->m_lhs->m_attribute.m_basetype ) ) {
      this->t_error( incre_type, p->m_attribute );
    }
  }

  // lhs must be number, rhs can be const/nonconst number
  void visitAnd_assign( And_assign *p ) {
    default_rule( p );
    if( !is_non_const_number_type( p->m_lhs->m_attribute.m_basetype ) ) {
      this->t_error( incre_type, p->m_attribute );
    }
  }

  void visitXor_assign( Xor_assign *p ) { 
    default_rule( p );
    if( !is_non_const_number_type( p->m_lhs->m_attribute.m_basetype ) ) {
      this->t_error( incre_type, p->m_attribute );
    }
  }

  void visitOr_assign( Or_assign *p ) {
    default_rule( p );
    if( !is_non_const_number_type( p->m_lhs->m_attribute.m_basetype )  ) {
      this->t_error( incre_type, p->m_attribute );
    }
  }

  void visitSl_assign( Sl_assign *p ) {
    default_rule( p );
    if ( !is_non_const_number_type( p->m_lhs->m_attribute.m_basetype ) ) {
      this->t_error( incre_type, p->m_attribute );
    }
  }

  void visitSr_assign( Sr_assign *p ) {
    default_rule( p );
    if ( !is_non_const_number_type( p->m_lhs->m_attribute.m_basetype ) ) {
      this->t_error( incre_type, p->m_attribute );
    }
  }

  void visitTimes_assign( Times_assign *p ) { 
    default_rule( p );
    if ( !is_non_const_number_type( p->m_lhs->m_attribute.m_basetype ) ) {
      this->t_error( incre_type, p->m_attribute );
    }
  }

  void visitDiv_assign( Div_assign *p ) { 
    default_rule( p );
    if ( !is_non_const_number_type( p->m_lhs->m_attribute.m_basetype ) ) {
      this->t_error( incre_type, p->m_attribute );
    }
  }

  void visitRem_assign( Rem_assign *p ) { 
    default_rule( p );
    if ( !is_non_const_number_type( p->m_lhs->m_attribute.m_basetype ) ) {
      this->t_error( incre_type, p->m_attribute );
    }
  }

  // pointer can be lhs
  void visitAdd_assign( Add_assign *p ) { 
    default_rule( p );
    if ( !( is_non_const_number_type( p->m_lhs->m_attribute.m_basetype ) ||
            is_pointer_type( p->m_lhs->m_attribute.m_basetype ) )||
         !is_number_type( p->m_expr->m_attribute.m_basetype ) ) {
      this->t_error( incre_type, p->m_attribute );
    }
  }

  // pointer can be lhs
  void visitMinus_assign( Minus_assign *p ) { 
    default_rule( p );
    if ( !( is_non_const_number_type( p->m_lhs->m_attribute.m_basetype ) ||
            is_pointer_type( p->m_lhs->m_attribute.m_basetype )) ||
         !is_number_type( p->m_expr->m_attribute.m_basetype ) ) {
      this->t_error( incre_type, p->m_attribute );
    }
  }

  void visitEq( Eq *p ) {
    default_rule( p );
    checkset_equalityexpr( p, p->m_expr_1, p->m_expr_2 );
  }

  void visitNeq( Neq *p ) { 
    default_rule( p );
    checkset_equalityexpr( p, p->m_expr_1, p->m_expr_2 );
  }

  void visitAnd( And *p ) {
    default_rule( p );
    checkset_boolexpr( p, p->m_expr_1, p->m_expr_2 );
  }

  void visitTimes( Times *p ) { 
    default_rule( p );
    checkset_arithexpr( p, p->m_expr_1, p->m_expr_2 );
  }

  void visitArithAnd( ArithAnd *p ) { 
    default_rule( p );
    checkset_arithexpr( p, p->m_expr_1, p->m_expr_2 );
  }

  void visitArithOr( ArithOr *p ) { 
    default_rule( p );
    checkset_arithexpr( p, p->m_expr_1, p->m_expr_2 );
  }

  void visitArithXor( ArithXor *p ) { 
    default_rule( p );
    checkset_arithexpr( p, p->m_expr_1, p->m_expr_2 );
  }

  void visitRem( Rem *p ) { 
    default_rule( p );
    checkset_arithexpr( p, p->m_expr_1, p->m_expr_2 );
  }
  void visitShiftL( ShiftL *p ) { 
    default_rule( p );
    checkset_arithexpr( p, p->m_expr_1, p->m_expr_2 );
  }

  void visitShiftR( ShiftR *p ) { 
    default_rule( p );
    checkset_arithexpr( p, p->m_expr_1, p->m_expr_2 );
  }

  void visitDiv( Div *p ) { 
    default_rule( p );
    checkset_arithexpr( p, p->m_expr_1, p->m_expr_2 );
  }

  void visitCompare( Compare *p ) { 
    default_rule( p );
  }

  void visitGt( Gt *p ) {
    default_rule( p );
    checkset_relationalexpr( p, p->m_expr_1, p->m_expr_2 );
  }

  void visitGteq( Gteq *p ) {
    default_rule( p );
    checkset_relationalexpr( p, p->m_expr_1, p->m_expr_2 );
  }

  void visitLt( Lt *p ) { 
    default_rule( p );
    checkset_relationalexpr( p, p->m_expr_1, p->m_expr_2 );
  }

  void visitLteq( Lteq *p ) { 
    default_rule( p );
    checkset_relationalexpr( p, p->m_expr_1, p->m_expr_2 );
  }

  void visitMinus( Minus *p ) { 
    default_rule( p );
    checkset_arithexpr_or_pointer( p, p->m_expr_1, p->m_expr_2 );
  }

  void visitNoteq( Noteq *p ) { 
    default_rule( p );
    checkset_relationalexpr( p, p->m_expr_1, p->m_expr_2 );
  }

  void visitOr( Or *p ) { 
    default_rule( p );
    checkset_boolexpr( p, p->m_expr_1, p->m_expr_2 );
  }

  void visitPlus( Plus *p ) { 
    default_rule( p );
    checkset_arithexpr_or_pointer( p, p->m_expr_1, p->m_expr_2 );
  }

  void visitNot( Not *p ) {
    default_rule( p );
    checkset_not( p, p->m_expr );
  }

  void visitUminus( Uminus *p ) {
    default_rule( p );
    checkset_uminus( p, p->m_expr );
  }

  void visitIdent( Ident *p ) {
    default_rule( p );
    checkset_Ident( p );
  }

  void visitArrayAccess( ArrayAccess *p ) {
    default_rule( p );
    check_array_access( p );
  }

  void visitArrayDoubleAccess( ArrayDoubleAccess *p ) {
    default_rule( p );
    check_2d_array_access( p );
  }

  void visitDotAccess( DotAccess *p ) {
    default_rule( p );
    // check if it is a struct
    if ( p->m_lhs->m_attribute.m_basetype != bt_struct ) {
      this->t_error( dot_access_not_struct, p->m_attribute );
    }

    // find the symbol for the struct type
    Symbol * s = m_st->lookup( p->m_lhs->m_attribute.m_struct_name );

    // this check seems unnecessary, but let's just keep it here
    if ( s->m_basetype != bt_struct_type ) {
      this->t_error( dot_access_not_struct, p->m_attribute );
    }

    // check if rhs is a member of struct
    auto it = s->m_map.find( p->m_symname->spelling() );
    if ( it == s->m_map.end() ) {
      // rhs is not a member of the struct
      this->t_error( not_a_struct_member, p->m_attribute );
    }
    p->m_attribute.m_basetype = it->second.first;
  }

  // currently don't support this
  // will add this feature when I implement struct *
  void visitArrowAccess( ArrowAccess *p ) {
    default_rule( p );
    this->t_error( not_supported_feature, p->m_attribute );
  }

  void visitIntLit( IntLit *p ) { 
    default_rule( p );
    p->m_attribute.m_basetype = bt_integer;
  }

  void visitCharLit( CharLit *p ) { 
    default_rule( p );
    p->m_attribute.m_basetype = bt_char;
  }

  void visitBoolLit( BoolLit *p ) { 
    default_rule( p );
    p->m_attribute.m_basetype = bt_boolean;
  }

  void visitStringLit( StringLit *p ) { 
    default_rule( p );
    p->m_attribute.m_basetype = bt_string;
  }

  void visitNullLit( NullLit *p ) { 
    default_rule( p );
    p->m_attribute.m_basetype = bt_void;
  }

  void visitDeref( Deref *p ) { 
    default_rule( p );
    checkset_deref_expr( p, p->m_expr );
  }

  void visitAddressOf( AddressOf *p ) {
    default_rule( p );
    checkset_addressof( p, p->m_lhs );
  }

  void visitEList( EList *p ) {
    default_rule( p );
    p->m_attribute.m_basetype = p->m_list->m_attribute.m_basetype;
    p->m_attribute.m_length1 = p->m_list->m_attribute.m_length1;
  }

  void visitETDList( ETDList *p ) { 
    default_rule( p );
    // check if all list are same list type
    if ( p->m_list_list->size() == 0 ) {
      this->t_error( not_supported_feature, p->m_attribute );
    }

    auto iter = p->m_list_list->begin();;
    Basetype type = ( *iter )->m_attribute.m_basetype;
    // length1 of list will be length2 of 2d list
    int length2 = ( *iter )->m_attribute.m_length1;
    int length1 = 0;
    for( ;
         iter != p->m_list_list->end();
         iter++ ) {
      if ( type != ( *iter )->m_attribute.m_basetype ) {
        // 2d list of different type of list
        this->t_error( tdlist_differnt_type, p->m_attribute );
      }
      if ( length2 != ( *iter )->m_attribute.m_length1 ) {
        this->t_error( tdlist_differnt_length, p->m_attribute );
      }
      length1++;
    }

    p->m_attribute.m_basetype = listToTDList ( type );
    p->m_attribute.m_length1 = length1;
    p->m_attribute.m_length2 = length2;
    if ( p->m_attribute.m_basetype == bt_2d_empty_list ) {
      this->t_error( empty_list, p->m_attribute );
    }
  }

  void visitECall( ECall *p ) { 
    default_rule( p );
    // get the return type of the function
    Symbol * s = m_st->lookup( dynamic_cast<CallImpl*>( p->m_call )->m_symname->spelling() );
    p->m_attribute.m_basetype = s->m_return_type;
  }

  void visitEmpty( Empty *p ) { 
    default_rule( p );
    p->m_attribute.m_basetype = bt_empty;
  }

  void visitVariable( Variable *p ) { 
    default_rule( p );
    checkset_variable( p );
  }

  void visitDerefVariable( DerefVariable *p ) { 
    default_rule( p );
    checkset_deref_lhs( p );
  }

  void visitArrayElement( ArrayElement *p ) { 
    default_rule( p );
    check_array_element( p );
  }

  void visitArrayDoubleElement( ArrayDoubleElement *p ) { 
    default_rule( p );
    check_2d_array_element( p );
  }

  void visitArrowElement( ArrowElement *p ) { 
    default_rule( p );
    this->t_error( not_supported_feature, p->m_attribute );
  }

  void visitDotElement( DotElement *p ) { 
    default_rule( p );
    // check if it is a struct
    if ( p->m_lhs->m_attribute.m_basetype != bt_struct ) {
      this->t_error( dot_access_not_struct, p->m_attribute );
    }

    // find the symbol for the struct type
    Symbol * s = m_st->lookup( p->m_lhs->m_attribute.m_struct_name );

    // this check seems unnecessary, but let's just keep it here
    if ( s->m_basetype != bt_struct_type ) {
      this->t_error( dot_access_not_struct, p->m_attribute );
    }

    // check if rhs is a member of struct
    auto it = s->m_map.find( p->m_symname->spelling() );
    if ( it == s->m_map.end() ) {
      // rhs is not a member of the struct
      this->t_error( not_a_struct_member, p->m_attribute );
    }
    p->m_attribute.m_basetype = it->second.first;
  }

  // Special cases
  void visitPrimitive(Primitive* p) {}
  void visitSymName(SymName* p) {}
  void visitStringPrimitive(StringPrimitive* p) {}
};


void dopass_typecheck(Program_ptr ast, SymTab* st)
{
  Typecheck* typecheck = new Typecheck(stderr, st);
  ast->accept(typecheck); // Walk the tree with the visitor above
  delete typecheck;
}
