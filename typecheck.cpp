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
      no_error
    };

  // Print the error to file and exit
  void t_error(errortype e, Attribute a) {
    fprintf(m_errorfile,"on line number %d, ", a.lineno);

    switch(e) {
      case no_main:
        fprintf(m_errorfile, "error: no main\n");
        exit(2);
      case nonvoid_main:
        fprintf(m_errorfile, "error: the Main procedure has arguments\n");
        exit(3);
      case dup_proc_name:
        fprintf(m_errorfile, "error: duplicate procedure names in same scope\n");
        exit(4);
      case dup_var_name:
        fprintf(m_errorfile, "error: duplicate variable names in same scope\n");
        exit(5);
      case proc_undef:
        fprintf(m_errorfile, "error: call to undefined procedure\n");
        exit(6);
      case var_undef:
        fprintf(m_errorfile, "error: undefined variable\n");
        exit(7);
      case narg_mismatch:
        fprintf(m_errorfile, "error: procedure call has different number of args than declartion\n");
        exit(8);
      case arg_type_mismatch:
        fprintf(m_errorfile, "error: argument type mismatch\n");
        exit(9);
      case ret_type_mismatch:
        fprintf(m_errorfile, "error: type mismatch in return statement\n");
        exit(10);
      case call_type_mismatch:
        fprintf(m_errorfile, "error: type mismatch in procedure call args\n");
        exit(11);
      case ifpred_err:
        fprintf(m_errorfile, "error: predicate of if statement is not boolean\n");
        exit(12);
      case whilepred_err:
        fprintf(m_errorfile, "error: predicate of while statement is not boolean\n");
        exit(13);
      case array_index_error:
        fprintf(m_errorfile, "error: array index not integer\n");
        exit(14);
      case no_array_var:
        fprintf(m_errorfile, "error: attempt to index non-array variable\n");
        exit(15);
      case incompat_assign:
        fprintf(m_errorfile, "error: type of expr and var do not match in assignment\n");
        exit(16);
      case expr_type_err:
        fprintf(m_errorfile, "error: incompatible types used in expression\n");
        exit(17);
      case expr_abs_error:
        fprintf(m_errorfile, "error: absolute value can only be applied to integers and strings\n");
        exit(17);
      case expr_pointer_arithmetic_err:
        fprintf(m_errorfile, "error: invalid pointer arithmetic\n");
        exit(18);
      case expr_addressof_error:
        fprintf(m_errorfile, "error: AddressOf can only be applied to integers, chars, and indexed strings\n");
        exit(19);
      case invalid_deref:
        fprintf(m_errorfile, "error: Deref can only be applied to integer pointers and char pointers\n");
        exit(20);
    case const_assign:
      fprintf(m_errorfile, "error: trying to assign to a const type\n");
      exit(21);
    case array_assign:
      fprintf(m_errorfile, "error: trying to assign a value to the array\n");
      exit(22);
      default:
        fprintf(m_errorfile, "error: no good reason\n");
        exit(21);
      }
  }


  bool is_number_type( Basetype type ){
    if ( type == bt_integer || type == bt_long || type == bt_short ||
         type == bt_const_int || type == bt_const_long || type == bt_const_short) {
      return true;
    }
    return false;
  }


  bool is_array_type( Basetype type ) {
    if ( type == bt_int_array || type == bt_char_array || type == bt_bool_array ||
         type == bt_long_array || type == bt_short_array || is_2d_array_type( type ) ) {
      return true;
    }
    return false;
  }

  bool is_2d_array_type( Basetype type ) {
    if ( type == bt_2d_int_array || type != bt_2d_char_array || type != bt_2d_bool_array ||
         type != bt_2d_long_array || type != bt_2d_short_array ) {
      return true;
    }
    return false;
  }

  bool is_pure_pointer_type( Basetype type ) {
    if ( type == bt_intptr || type == bt_charptr || type == bt_boolptr ||
         type == bt_shortptr || type == bt_longptr ) {
      return true;
    }
    return false;
  }

  bool is_pointer_type( Basetype type ) {
    if ( is_pure_pointer_type( type ) || is_array_type( type ) ||
         is_2d_array_type( type ) ) {
      return true;
    }
    return false;
  }


  bool is_const_type( Basetype type ) {
    if ( type == bt_const_int || type == bt_const_char || type == bt_const_bool ||
         type == bt_const_long || type == bt_const_short) {
      return true;
    }
    return false;
  }

  bool is_return_type( Basetype type ) {
    if ( is_const_type( type ) || is_number_type( type ) ||
         type == bt_boolean || type == bt_char) {
      return true;
    }
    return false;
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

  // All possible assign
  // array itself can not be assign after decl
  // long, int, short to long, int, short
  // NULL/bt_void to pointer ( not array )
  // list to array
  // same enum to enum
  // same type to same type ( except NULL and array )
  // can not assign anything to const except in decl
  errortype checkAssign( Basetype type1, string struct_name1,
                         int first_length1, int second_length1,
                         Basetype type2, string struct_name2,
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
      if ( type2 != type1 || struct_name1 != struct_name2 ) {
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
    string struct_name = p->m_type->m_attribute.m_struct_name;
    int first_length = p->m_primitive_1->m_data;
    int second_length = p->m_primitive_2->m_data;
    Basetype real_type;
    string real_struct_name;
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
    for ( pairIter = p->m_assignpair_list->begin();
          pairIter != p->m_assignpair_list->end();
          ++pairIter ) {
      name_list.push_back( static_cast<AssignPairImpl*>( *pairIter )->m_symname );
      assign_list.push_back( static_cast<AssignPairImpl*>( *pairIter )->m_expr );
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

      real_struct_name = ( *exprIter )->m_attribute.m_struct_name;
      real_type = ( *exprIter )->m_attribute.m_basetype;
      real_first_length = ( *exprIter )->m_attribute.m_length1;
      real_second_length = ( *exprIter )->m_attribute.m_length2;

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
      s->m_type_name = struct_name;
      s->m_length1 = real_first_length;
      s->m_length2 = real_second_length;

      if(! m_st->insert(name,s)){
        this->t_error(dup_var_name, p->m_attribute);
      }
      exprIter++;
    }

  }

  // Check that the return statement of a procedure has the appropriate type
  void check_proc(ProcedureImpl *p) {
    Basetype correct_type= p->m_type->m_attribute.m_basetype;
    Basetype real_type = static_cast<Return_statImpl *>(p->m_return_stat)->m_expr->m_attribute.m_basetype;
    if ( !is_return_type( correct_type ) ){
      this->t_error(ret_type_mismatch, p->m_attribute);
    }

    if ( is_number_type( correct_type ) && is_number_type( real_type ) ) {
    } else if ( is_pure_pointer_type( correct_type ) && real_type == bt_void) {
    } else if ( correct_type == real_type ){
    } else {
      this->t_error(ret_type_mismatch,p->m_attribute);
    }

  }

  // Right now let's say the reutrn type must be a base type
  // Pointer and array is not allowed
  // return a const type is allowed but it won't make a difference
  void check_return(Return_statImpl *p)
  {
    if ( !is_return_type( p->m_expr->m_attribute.m_basetype ) ) {
      this->t_error(ret_type_mismatch, p->m_attribute);
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
        } if ( is_pure_pointer_type( type1 ) && type2 == bt_void){
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
    if(p->m_attribute.m_basetype!=bt_boolean){
      if ( index == 1 ) {
        this->t_error( ifpred_err, p->m_attribute );
      } else {
        this->t_error( whilepred_err, p->m_attribute );
      }
    }
  }

  void check_assignment(Assignment* p) {
    // use helper function checkAssign
    Basetype type1 = p->m_lhs->m_attribute.m_basetype;
    std::string struct_name1 = p->m_lhs->m_attribute.m_struct_name;
    Basetype type2 = p->m_expr->m_attribute.m_basetype;
    std::string struct_name2 = p->m_expr->m_attribute.m_struct_name;

    errortype error_message;
    error_message = checkAssign( type1, struct_name1, -1, -1,
                                 type2, struct_name2, -1, -1, false);

    if( error_message != no_error ) {
      this->t_error( error_message, p->m_attribute );
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
    if ( s->m_basetype != bt_string || is_pointer_type( s->m_basetype ) ) {
      this->t_error(expr_type_err, p->m_attribute);
    }
    if( !is_number_type( p->m_expr->m_attribute.m_basetype ) ) {
      this->t_error(array_index_error, p->m_attribute);
    }
    p->m_attribute.m_basetype = dereference_type( p->m_attribute.m_basetype );
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
    if ( s->m_basetype != bt_string || is_pointer_type( s->m_basetype ) ) {
      this->t_error(expr_type_err, p->m_attribute);
    }
    if ( !is_number_type( p->m_expr->m_attribute.m_basetype ) ) {
      this->t_error(array_index_error, p->m_attribute);
    }
    p->m_attribute.m_basetype = dereference_type( p->m_attribute.m_basetype );
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
    if(is_number_type( p->m_expr_1->m_attribute.m_basetype ) ||
       is_number_type( p->m_expr_2->m_attribute.m_basetype ) ) {
      this->t_error(array_index_error, p->m_attribute);
    }
    p->m_attribute.m_basetype = double_dereference_type( type );
  }

  // For checking boolean operations(and, or ...)
  void checkset_boolexpr(Expr* parent, Expr* child1, Expr* child2) {
    Basetype type1 = child1->m_attribute.m_basetype;
    Basetype type2 = child2->m_attribute.m_basetype;
    if ( type1 != bt_boolean || type2 != bt_boolean ) {
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
      if ( type1 == bt_long || type2 == bt_long ) {
        parent->m_attribute.m_basetype = bt_long;
      } else if ( type1 == bt_integer || type2 == bt_integer ) {
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
      this->t_error(expr_type_err, parent->m_attribute);
    }
    parent->m_attribute.m_basetype = bt_boolean;
  }

  // For checking equality ops(equal, not equal)
  void checkset_equalityexpr(Expr* parent, Expr* child1, Expr* child2) {
    Basetype type1 = child1->m_attribute.m_basetype;
    Basetype type2 = child2->m_attribute.m_basetype;
    if ( type1 == type2 ) {
    } else if ( is_number_type( type1 ) && is_number_type( type2 ) ){
    } else if ( is_pointer_type( type1 ) && type2 == bt_voidptr ) {
    } else if ( is_pointer_type( type2 ) && type1 == bt_voidptr ) {
    } else {
      this->t_error(expr_type_err, parent->m_attribute);
    }
    parent->m_attribute.m_basetype = bt_boolean;
  }

  // For checking not
  void checkset_not(Expr* parent, Expr* child) {
    if ( child->m_attribute.m_basetype != bt_boolean ) {
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
    case bt_integer:
      parent->m_attribute.m_basetype = bt_intptr; break;
    case bt_intptr:
    case bt_int_array:
      parent->m_attribute.m_basetype = bt_2d_int_array; break;
    case bt_boolean:
      parent->m_attribute.m_basetype = bt_boolptr; break;
    case bt_boolptr:
    case bt_bool_array:
      parent->m_attribute.m_basetype = bt_2d_bool_array; break;
    case bt_char:
      parent->m_attribute.m_basetype = bt_charptr; break;
    case bt_charptr:
    case bt_char_array:
      parent->m_attribute.m_basetype = bt_2d_char_array; break;
    case bt_long:
      parent->m_attribute.m_basetype = bt_longptr; break;
    case bt_longptr:
    case bt_long_array:
      parent->m_attribute.m_basetype = bt_2d_long_array; break;
    case bt_short:
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
    Basetype type = s->m_basetype;
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
    default_rule(p);
    check_for_one_main(p);
  }

  void visitOut_enum_define( Out_enum_define *p ) { 

  }

  void visitOut_decl( Out_decl *p ) { 

  }

  void visitOut_procedure( Out_procedure *p ) { 

  }

  void visitOut_struct_define( Out_struct_define *p ) { 

  }

  void visitAssignPairImpl( AssignPairImpl *p ) { 

  }

  void visitEnum_defineImpl( Enum_defineImpl *p ) { 

  }

  void visitDecl_variable( Decl_variable *p ) { 

  }

  void visitDecl_function( Decl_function *p ) { 

  }

  void visitProcedureImpl( ProcedureImpl *p ) { 

  }

  void visitStruct_defineImpl( Struct_defineImpl *p ) { 

  }

  void visitCallImpl( CallImpl *p ) { 

  }

  void visitCaseImpl( CaseImpl *p ) { 

  }

  void visitPProcedure( PProcedure *p ) { 

  }

  void visitPStat( PStat *p ) { 

  }

  void visitInit_new( Init_new *p ) { 

  }

  void visitInit_old( Init_old *p ) { 

  }

  void visitNStat( NStat *p ) { 

  }

  void visitRStat( RStat *p ) { 

  }

  void visitAssignment( Assignment *p ) { 

  }

  void visitString_assignment( String_assignment *p ) { 

  }

  void visitFunction_assignment( Function_assignment *p ) { 

  }

  void visitSIncre( SIncre *p ) { 

  }

  void visitFunction_call( Function_call *p ) { 

  }

  void visitIf_no_else( If_no_else *p ) { 

  }

  void visitIf_with_else( If_with_else *p ) { 

  }

  void visitWhile_loop( While_loop *p ) { 

  }

  void visitDo_while( Do_while *p ) { 

  }

  void visitFor_loop( For_loop *p ) { 

  }

  void visitSwitch( Switch *p ) { 

  }

  void visitBreak( Break *p ) { 

  }

  void visitContinue( Continue *p ) { 

  }

  void visitStat_struct_define( Stat_struct_define *p ) { 

  }

  void visitStat_enum_define( Stat_enum_define *p ) { 

  }

  void visitStat_decl( Stat_decl *p ) { 

  }

  void visitReturn_statImpl( Return_statImpl *p ) { 

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

  void visitListImpl( ListImpl *p ) {

  }

  void visitIncre_op( Incre_op *p ) { 

  }

  void visitIncre_t_add( Incre_t_add *p ) { 

  }

  void visitIncre_t_min( Incre_t_min *p ) { 

  }

  void visitIncre_add_t( Incre_add_t *p ) { 

  }

  void visitIncre_min_t( Incre_min_t *p ) { 

  }

  void visitAnd_assign( And_assign *p ) { 

  }

  void visitXor_assign( Xor_assign *p ) { 

  }

  void visitOr_assign( Or_assign *p ) { 

  }

  void visitSl_assign( Sl_assign *p ) { 

  }

  void visitSr_assign( Sr_assign *p ) { 

  }

  void visitTimes_assign( Times_assign *p ) { 

  }

  void visitDiv_assign( Div_assign *p ) { 

  }

  void visitRem_assign( Rem_assign *p ) { 

  }

  void visitAdd_assign( Add_assign *p ) { 

  }

  void visitMinus_assign( Minus_assign *p ) { 

  }

  void visitEq( Eq *p ) { 

  }

  void visitNeq( Neq *p ) { 

  }

  void visitAnd( And *p ) { 

  }

  void visitTimes( Times *p ) { 

  }

  void visitArithAnd( ArithAnd *p ) { 

  }

  void visitArithOr( ArithOr *p ) { 

  }

  void visitArithXor( ArithXor *p ) { 

  }

  void visitRem( Rem *p ) { 

  }

  void visitShiftL( ShiftL *p ) { 

  }

  void visitShiftR( ShiftR *p ) { 

  }

  void visitDiv( Div *p ) { 

  }

  void visitCompare( Compare *p ) { 

  }

  void visitGt( Gt *p ) { 

  }

  void visitGteq( Gteq *p ) { 

  }

  void visitLt( Lt *p ) { 

  }

  void visitLteq( Lteq *p ) { 

  }

  void visitMinus( Minus *p ) { 

  }

  void visitNoteq( Noteq *p ) { 

  }

  void visitOr( Or *p ) { 

  }

  void visitPlus( Plus *p ) { 

  }

  void visitNot( Not *p ) { 

  }

  void visitUminus( Uminus *p ) { 

  }

  void visitIdent( Ident *p ) { 

  }

  void visitArrayAccess( ArrayAccess *p ) { 

  }

  void visitArrayDoubleAccess( ArrayDoubleAccess *p ) { 

  }

  void visitDotAccess( DotAccess *p ) { 

  }

  void visitArrowAccess( ArrowAccess *p ) { 

  }

  void visitIntLit( IntLit *p ) { 

  }

  void visitCharLit( CharLit *p ) { 

  }

  void visitBoolLit( BoolLit *p ) { 

  }

  void visitStringLit( StringLit *p ) { 

  }

  void visitNullLit( NullLit *p ) { 

  }

  void visitDeref( Deref *p ) { 

  }

  void visitAddressOf( AddressOf *p ) { 

  }

  void visitEList( EList *p ) { 

  }

  void visitETDList( ETDList *p ) { 

  }

  void visitECall( ECall *p ) { 

  }

  void visitEmpty( Empty *p ) { 

  }

  void visitVariable( Variable *p ) { 

  }

  void visitDerefVariable( DerefVariable *p ) { 

  }

  void visitArrayElement( ArrayElement *p ) { 

  }

  void visitArrayDoubleElement( ArrayDoubleElement *p ) { 

  }

  void visitArrowElement( ArrowElement *p ) { 

  }

  void visitDotElement( DotElement *p ) { 

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
