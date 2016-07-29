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
      array_assign
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

  // Helpers
  // WRITEME: You might want write some hepler functions.
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

  bool is_pointer_type( Basetype type ) {
    if ( type == bt_intptr || type == bt_charptr || type == bt_boolptr ||
         type == bt_shortptr || type == bt_longptr || is_array_type( type ) ||
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

  // Check that there is one and only one main
  void check_for_one_main( ProgramImpl* p ) {
    Symbol * s = m_st->lookup( "main" );

    if ( s == NULL || s->m_basetype != bt_procedure ){
      this->t_error(no_main, p->m_attribute);
    }
  }

  // Create a symbol for the procedure and check there is none already
  // existing
  void add_proc_symbol(ProcedureImpl* p){

  }

  // Add symbol table information for all the declarations following
  void add_decl_symbol(Decl_variable* p)
  {
  }

  // Check that the return statement of a procedure has the appropriate type
  void check_proc(ProcedureImpl *p)
  {
  }

  // Check that the declared return type is not an array
  void check_return(Return_statImpl *p)
  {
  }

  // Create a symbol for the procedure and check there is none already
  // existing
  void check_call(Call *p)
  {
  }

  // For checking that this expressions type is boolean used in if/else and
  // while visits
  void check_pred(Expr* p)
  {
  }

  void check_assignment(Assignment* p)
  {
    Basetype type1 = p->m_lhs->m_attribute.m_basetype;
    Basetype type2 = p->m_expr->m_attribute.m_basetype;
    if ( is_const_type( type1 ) ) {
      this->t_error(const_assign, p->m_attribute);
    } else if ( is_array_type( type1 ) ) {
      this->t_error(array_assign, p->m_attribute);
    } if ( type1 == bt_struct && type2 == bt_struct) { 
      // need a way to store the struct's type
      // p->m_lhs->m_stringprimitive->) {
      
    }
  }

  void check_string_assignment(String_assignment* p)
  {
    if(p->m_lhs->m_attribute.m_basetype!=bt_string)
      this->t_error(incompat_assign, p->m_attribute);
  }

  void check_array_access(ArrayAccess* p)
  {
    Symbol * s = m_st->lookup( p->m_symname->spelling() );
    if ( s == NULL ) {
      this->t_error(var_undef, p->m_attribute);
    }
    if ( s->m_basetype != bt_string || is_pointer_type( s->m_basetype ) ) {
      this->t_error(expr_type_err, p->m_attribute);
    }
    if(p->m_expr->m_attribute.m_basetype!=bt_integer) {
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
    if(!is_number_type( p->m_expr_1->m_attribute.m_basetype ) ||
       !is_number_type( p->m_expr_2->m_attribute.m_basetype ) ) {
      this->t_error(array_index_error, p->m_attribute);
    }
    p->m_attribute.m_basetype = double_dereference_type( type );
  }

  void check_array_element(ArrayElement* p)
  {
    Symbol * s = m_st->lookup( p->m_symname->spelling() );
    if ( s == NULL ) {
      this->t_error(var_undef, p->m_attribute);
    }
    if ( s->m_basetype != bt_string || is_pointer_type( s->m_basetype ) ) {
      this->t_error(expr_type_err, p->m_attribute);
    }
    if(p->m_expr->m_attribute.m_basetype!=bt_integer) {
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
    switch ( type ) {
    case bt_int_array:
    case bt_intptr:
      parent->m_attribute.m_basetype = bt_integer; break;
    case bt_2d_int_array:
      parent->m_attribute.m_basetype = bt_intptr; break;
    case bt_bool_array:
    case bt_boolptr:
      parent->m_attribute.m_basetype = bt_boolean; break;
    case bt_2d_bool_array:
      parent->m_attribute.m_basetype = bt_boolptr; break;
    case bt_char_array:
    case bt_charptr:
      parent->m_attribute.m_basetype = bt_char; break;
    case bt_2d_char_array:
      parent->m_attribute.m_basetype = bt_charptr; break;
    case bt_short_array:
    case bt_shortptr:
      parent->m_attribute.m_basetype = bt_short; break;
    case bt_2d_short_array:
      parent->m_attribute.m_basetype = bt_shortptr; break;
    case bt_long_array:
    case bt_longptr:
      parent->m_attribute.m_basetype = bt_long; break;
    case bt_2d_long_array:
      parent->m_attribute.m_basetype = bt_longptr; break;
    case bt_voidptr:
      parent->m_attribute.m_basetype = bt_void; break;
    default:
      this->t_error(invalid_deref, parent->m_attribute);
    }
  }

  // Check that if the right-hand side is an lhs, such as in case of
  // addressof
  void checkset_deref_lhs(DerefVariable* p) {
    Symbol * s = m_st->lookup( p->m_symname->spelling() );
    if ( s == NULL ) {
      this->t_error( var_undef, p->m_attribute );
    }
    Basetype type = s->m_basetype;
    if ( type == bt_int_array || type == bt_intptr) {
      p->m_attribute.m_basetype = bt_integer;
    } else if ( type == bt_2d_int_array) {
      p->m_attribute.m_basetype = bt_intptr;
    } else if ( type == bt_bool_array || type == bt_boolptr) {
      p->m_attribute.m_basetype = bt_boolean;
    } else if ( type == bt_2d_bool_array) {
      p->m_attribute.m_basetype = bt_boolptr;
    } else if ( type == bt_char_array || type == bt_charptr) {
      p->m_attribute.m_basetype = bt_char;
    } else if ( type == bt_2d_char_array) {
      p->m_attribute.m_basetype = bt_boolptr;
    } else if ( type == bt_short_array || type == bt_shortptr) {
      p->m_attribute.m_basetype = bt_short;
    } else if ( type == bt_2d_short_array) {
      p->m_attribute.m_basetype = bt_shortptr;
    } else if ( type == bt_long_array || type == bt_longptr) {
      p->m_attribute.m_basetype = bt_long;
    } else if ( type == bt_2d_long_array) {
      p->m_attribute.m_basetype = bt_longptr;
    } else if ( type == bt_voidptr) {
      p->m_attribute.m_basetype = bt_void;
    } else {
      this->t_error( invalid_deref, p->m_attribute );
    }
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
