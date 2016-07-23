#include <iostream>
#include <cstdio>
#include <cstring>

#include "ast.hpp"
#include "symtab.hpp"
#include "primitive.hpp"
#include "assert.h"

// WRITEME: The default attribute propagation rule
#define default_rule(X) X

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
      invalid_deref
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
      default:
        fprintf(m_errorfile, "error: no good reason\n");
        exit(21);
      }
  }

  // Helpers
  // WRITEME: You might want write some hepler functions.

  // Type Checking
  // WRITEME: You need to implement type-checking for this project

  // Check that there is one and only one main
  void check_for_one_main(ProgramImpl* p)
  {
  }

  // Create a symbol for the procedure and check there is none already
  // existing
  void add_proc_symbol(ProcImpl* p)
  {
  }

  // Add symbol table information for all the declarations following
  void add_decl_symbol(DeclImpl* p)
  {
  }

  // Check that the return statement of a procedure has the appropriate type
  void check_proc(ProcImpl *p)
  {
  }

  // Check that the declared return type is not an array
  void check_return(Return *p)
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
  }

  void check_string_assignment(StringAssignment* p)
  {
  }

  void check_array_access(ArrayAccess* p)
  {
  }

  void check_array_element(ArrayElement* p)
  {
  }

  // For checking boolean operations(and, or ...)
  void checkset_boolexpr(Expr* parent, Expr* child1, Expr* child2)
  {
  }

  // For checking arithmetic expressions(plus, times, ...)
  void checkset_arithexpr(Expr* parent, Expr* child1, Expr* child2)
  {
  }

  // Called by plus and minus: in these cases we allow pointer arithmetics
  void checkset_arithexpr_or_pointer(Expr* parent, Expr* child1, Expr* child2)
  {
  }

  // For checking relational(less than , greater than, ...)
  void checkset_relationalexpr(Expr* parent, Expr* child1, Expr* child2)
  {
  }

  // For checking equality ops(equal, not equal)
  void checkset_equalityexpr(Expr* parent, Expr* child1, Expr* child2)
  {
  }

  // For checking not
  void checkset_not(Expr* parent, Expr* child)
  {
  }

  // For checking unary minus
  void checkset_uminus(Expr* parent, Expr* child)
  {
  }

  void checkset_absolute_value(Expr* parent, Expr* child)
  {
  }

  void checkset_addressof(Expr* parent, Lhs* child)
  {
  }

  void checkset_deref_expr(Deref* parent,Expr* child)
  {
  }

  // Check that if the right-hand side is an lhs, such as in case of
  // addressof
  void checkset_deref_lhs(DerefVariable* p)
  {
  }

  void checkset_variable(Variable* p)
  {
  }


public:

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

  }

  void visitTChar( TChar *p ) { 

  }

  void visitTBool( TBool *p ) { 

  }

  void visitTShort( TShort *p ) { 

  }

  void visitTVoid( TVoid *p ) { 

  }

  void visitTLong( TLong *p ) { 

  }

  void visitTStruct( TStruct *p ) { 

  }

  void visitTEnum( TEnum *p ) { 

  }

  void visitTCInt( TCInt *p ) { 

  }

  void visitTCChar( TCChar *p ) { 

  }

  void visitTCBool( TCBool *p ) { 

  }

  void visitTCShort( TCShort *p ) { 

  }

  void visitTCLong( TCLong *p ) { 

  }

  void visitTCharPtr( TCharPtr *p ) { 

  }

  void visitTIntPtr( TIntPtr *p ) { 

  }

  void visitTBoolPtr( TBoolPtr *p ) { 

  }

  void visitTShortPtr( TShortPtr *p ) { 

  }

  void visitTVoidPtr( TVoidPtr *p ) { 

  }

  void visitTLongPtr( TLongPtr *p ) { 

  }

  void visitTIntArray( TIntArray *p ) { 

  }

  void visitTCharArray( TCharArray *p ) { 

  }

  void visitTBoolArray( TBoolArray *p ) { 

  }

  void visitTShortArray( TShortArray *p ) { 

  }

  void visitTLongArray( TLongArray *p ) { 

  }

  void visitTTDIntArray( TTDIntArray *p ) { 

  }

  void visitTTDCharArray( TTDCharArray *p ) { 

  }

  void visitTTDBoolArray( TTDBoolArray *p ) { 

  }

  void visitTTDShortArray( TTDShortArray *p ) { 

  }

  void visitTTDLongArray( TTDLongArray *p ) { 

  }

  void visitTString( TString *p ) { 

  }

  void visitNo_type( No_type *p ) { 

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
