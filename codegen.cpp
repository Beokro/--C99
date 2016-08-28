#include <cassert>
#include <typeinfo>
#include <string>
#include <iostream>

#include "ast.hpp"
#include "symtab.hpp"
#include "primitive.hpp"
using namespace std;


class Codegen : public Visitor
{
private:
  FILE* m_outputfile;
  SymTab *m_st;
  int nest_level = 0;

  // Basic size of a word (integers and booleans) in bytes
  static const int wordsize = 4;

  int label_count; // Access with new_label

  // Helpers
  // This is used to get new unique labels (cleverly names label1, label2, ...)
  int new_label()
  {
    return label_count++;
  }

  void set_text_mode()
  {
    fprintf(m_outputfile, ".text\n\n");
  }

  void set_data_mode()
  {
    fprintf(m_outputfile, ".data\n\n");
  }

  // PART 1:
  // 1) get arithmetic expressions on integers working:
  //  you wont really be able to run your code,
  //  but you can visually inspect it to see that the correct
  //  chains of opcodes are being generated.
  // 2) get procedure calls working:
  //  if you want to see at least a very simple program compile
  //  and link successfully against gcc-produced code, you
  //  need to get at least this far
  // 3) get boolean operation working
  //  before we can implement any of the conditional control flow
  //  stuff, we need to have booleans worked out.
  // 4) control flow:
  //  we need a way to have if-elses and while loops in our language.
  // 5) arrays: just like variables, but with an index

  // Hint: the symbol table has been augmented to track an offset
  //  with all of the symbols.  That offset can be used to figure
  //  out where in the activation record you should look for a particuar
  //  variable


  ///////////////////////////////////////////////////////////////////////////////
  //
  //  function_prologue
  //  function_epilogue
  //
  //  Together these two functions implement the callee-side of the calling
  //  convention.  A stack frame has the following layout:
  //
  //                         <- SP (before pre-call / after epilogue)
  //  high -----------------
  //       | actual arg 1  |
  //       |    ...        |
  //       | actual arg n  |
  //       -----------------
  //       |  Return Addr  |
  //       =================
  //       | temporary 1   | <- SP (when starting prologue)
  //       |    ...        |
  //       | temporary n   |
  //   low ----------------- <- SP (when done prologue)
  //
  //
  //              ||
  //              ||
  //             \  /
  //              \/
  //
  //
  //  The caller is responsible for placing the actual arguments
  //  and the return address on the stack. Actually, the return address
  //  is put automatically on the stack as part of the x86 call instruction.
  //
  //  On function entry, the callee
  //
  //  (1) allocates space for the callee's temporaries on the stack
  //
  //  (2) saves callee-saved registers (see below) - including the previous activation record pointer (%ebp)
  //
  //  (3) makes the activation record pointer (frmae pointer - %ebp) point to the start of the temporary region
  //
  //  (4) possibly copies the actual arguments into the temporary variables to allow easier access
  //
  //  On function exit, the callee:
  //
  //  (1) pops the callee's activation record (temporay area) off the stack
  //
  //  (2) restores the callee-saved registers, including the activation record of the caller (%ebp)
  //
  //  (3) jumps to the return address (using the x86 "ret" instruction, this automatically pops the
  //      return address off the stack
  //
  //////////////////////////////////////////////////////////////////////////////
  //
  // Since we are interfacing with code produced by GCC, we have to respect the
  // calling convention that GCC demands:
  //
  // Contract between caller and callee on x86:
  //    * after call instruction:
  //           o %eip points at first instruction of function
  //           o %esp+4 points at first argument
  //           o %esp points at return address
  //    * after ret instruction:
  //           o %eip contains return address
  //           o %esp points at arguments pushed by caller
  //           o called function may have trashed arguments
  //           o %eax contains return value (or trash if function is void)
  //           o %ecx, %edx may be trashed
  //           o %ebp, %ebx, %esi, %edi must contain contents from time of call
  //    * Terminology:
  //           o %eax, %ecx, %edx are "caller save" registers
  //           o %ebp, %ebx, %esi, %edi are "callee save" registers
  ////////////////////////////////////////////////////////////////////////////////

  // generate assembly code for compare operator like
  // ==, !=, >, >= ....
  void gen_compare( string op ) {
    string temp = op + " %%dl\n";
    fprintf( m_outputfile, "pop  %%ebx\n" );
    fprintf( m_outputfile, "pop  %%eax\n" );
    fprintf(m_outputfile, "cmp %%ebx, %%eax\n");
    fprintf( m_outputfile, "%s", temp.c_str() );
    fprintf( m_outputfile, "movzbl %%dl, %%eax\n" );
    fprintf( m_outputfile, "pushl %%eax\n\n" );
  }

  // generate assembly code for binary arithmetic operator like
  // +, -, *, / .....
  void gen_binary( string op ) {
    string temp = op + " %%ebx, %%eax\n";
    fprintf( m_outputfile, "pop %%ebx\n" );
    fprintf( m_outputfile, "pop %%eax\n" );
    fprintf( m_outputfile, "%s", temp.c_str() );
    fprintf( m_outputfile, "pushl %%eax\n\n" );
  }

  // generate assembly code for literatures like
  // char literature, int literature ...
  void gen_lit( int val ) {
    string temp = "pushl $"+std::to_string( val )+"\n";
    fprintf( m_outputfile,"%s", temp.c_str() );
  }

  void emit_prologue(SymName *name, unsigned int size_locals, unsigned int num_args)
  {
    // declare the function as global
    string temp = ".global "+string(name->spelling())+"\n";
    fprintf(m_outputfile, "%s", temp.c_str());
    // start of defination
    temp = string(name->spelling()) + ":\n";
    fprintf(m_outputfile, "%s", temp.c_str());
    // save the ebp and make it point to start of the temporary region
    fprintf(m_outputfile, "pushl %%ebp\n");
    fprintf(m_outputfile, "movl %%esp, %%ebp\n");
    // create the space for all variable in this procedure
    // esp point to the end of the procedure space
    temp = "sub $" + std::to_string(size_locals) +", %esp\n\n";
    fprintf(m_outputfile, "%s", temp.c_str());
  }

  void emit_epilogue()
  {
    // resotre the callee save registers
    fprintf(m_outputfile, "pop %%edi\n");
    fprintf(m_outputfile, "pop %%esi\n");
    fprintf(m_outputfile, "pop %%ebx\n");
    // restore ebp and esp
    fprintf(m_outputfile, "movl %%ebp, %%esp\n");
    fprintf(m_outputfile, "pop %%ebp\n");
    // end of procedure, retunr to caller if it exist
    fprintf(m_outputfile, "ret\n\n");
  }

  void visit_stat_can_return( std::list<Stat_can_return_ptr> *stat_list ) {
    nest_level++;
    for( auto iter = stat_list->begin();
         iter != stat_list->end();
         ++iter ){
      ( *iter )->accept( this );
    }
    nest_level--;
  }

public:

  Codegen(FILE* outputfile, SymTab* st)
  {
    m_outputfile = outputfile;
    m_st = st;
    label_count = 0;
  }
  
  void visitProgramImpl( ProgramImpl *p ) {
    set_text_mode();
    p->visit_children(this);
  }

  void visitOut_enum_define( Out_enum_define *p ) {
    p->visit_children(this);
  }

  void visitOut_decl( Out_decl *p ) {
    p->visit_children(this);
  }

  void visitOut_procedure( Out_procedure *p ) {
    p->visit_children(this);
  }

  void visitOut_struct_define( Out_struct_define *p ) {
    p->visit_children(this);
  }

  void visitAssignPairImpl( AssignPairImpl *p ) {

  }

  void visitEnum_defineImpl( Enum_defineImpl *p ) {

  }

  void visitDecl_variable( Decl_variable *p ) {

  }

  void visitDecl_function( Decl_function *p ) {

  }

  void visitShort_declImpl( Short_declImpl *p ) {

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
    p->visit_children(this);
  }

  void visitPStat( PStat *p ) {
    p->visit_children(this);
  }

  void visitInit_new( Init_new *p ) {

  }

  void visitInit_old( Init_old *p ) {

  }

  void visitNStat( NStat *p ) {
    p->visit_children(this);
  }

  void visitRStat( RStat *p ) {
    p->visit_children(this);
  }

  void visitAssignment( Assignment *p ) {

  }

  void visitString_assignment( String_assignment *p ) {

  }

  void visitFunction_assignment( Function_assignment *p ) {

  }

  void visitSIncre( SIncre *p ) {
    p->visit_children(this);
  }

  void visitFunction_call( Function_call *p ) {

  }

  // Control flow
  void visitIf_no_else( If_no_else *p ) {
    // check the if condition
    p->m_expr->accept(this);
    string labelNum = std::to_string(new_label());
    fprintf(m_outputfile, "pop %%eax\n");
    fprintf(m_outputfile, "cmp $0, %%eax\n");
    string instruction = "je if_end" + labelNum+"\n\n";
    fprintf(m_outputfile, "%s",instruction.c_str());
    // output the statement in if block
    visit_stat_can_return( p->m_stat_can_return_list );
    instruction = "if_end" + labelNum+":\n\n";
    fprintf(m_outputfile, "%s",instruction.c_str());
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
    p->visit_children( this );
    gen_compare( "sete" );
  }

  void visitNeq( Neq *p ) {
    p->visit_children( this );
    gen_compare( "setne" );
  }

  void visitAnd( And *p ) {
    // to do, the output should only be 0 or 1
    p->visit_children( this );
    gen_binary( "and" );
  }

  void visitTimes( Times *p ) {
    p->visit_children( this );
    gen_binary( "impl" );
  }

  void visitArithAnd( ArithAnd *p ) {
    p->visit_children( this );
    gen_binary( "impl" );
  }

  void visitArithOr( ArithOr *p ) {
    p->visit_children( this );
    gen_binary( "or" );
  }

  void visitArithXor( ArithXor *p ) {
    p->visit_children( this );
    gen_binary( "xor" );
  }

  void visitRem( Rem *p ) {
    p->visit_children(this);
    fprintf( m_outputfile, "#doing remain\n" );
    fprintf( m_outputfile, "pop %%ebx\n" );
    fprintf( m_outputfile, "pop %%eax\n" );
    fprintf( m_outputfile, "cdq\n" );
    fprintf( m_outputfile, "idiv %%ebx\n" );
    fprintf( m_outputfile, "pushl %%edx\n\n" );
  }

  void visitShiftL( ShiftL *p ) {
    p->visit_children( this );
    gen_binary( "shl" );
  }

  void visitShiftR( ShiftR *p ) {
    p->visit_children( this );
    gen_binary( "shr" );
  }

  void visitDiv( Div *p ) {
    p->visit_children(this);
    fprintf( m_outputfile, "#doing divide\n" );
    fprintf( m_outputfile, "pop %%ebx\n" );
    fprintf( m_outputfile, "pop %%eax\n" );
    fprintf( m_outputfile, "cdq\n" );
    fprintf( m_outputfile, "idiv %%ebx\n" );
    fprintf( m_outputfile, "pushl %%eax\n\n" );
  }

  void visitCompare( Compare *p ) {
    //todo, remove this from here, typechecker and cdef
    p->visit_children( this );
  }

  void visitGt( Gt *p ) {
    p->visit_children( this );
    gen_compare( "setg" );
  }

  void visitGteq( Gteq *p ) {
    p->visit_children( this );
    gen_compare( "setge" );
  }

  void visitLt( Lt *p ) {
    p->visit_children( this );
    gen_compare( "setl" );
  }

  void visitLteq( Lteq *p ) {
    p->visit_children( this );
    gen_compare( "setle" );
  }

  void visitMinus( Minus *p ) {
    p->visit_children( this );
    gen_binary( "shr" );
  }

  void visitNoteq( Noteq *p ) {
    p->visit_children( this );
    gen_binary( "subl" );
  }

  void visitOr( Or *p ) {
    // todo, output should only be 0 or 1
    p->visit_children( this );
    gen_binary( "or" );
  }

  void visitPlus( Plus *p ) {
    p->visit_children( this );
    gen_binary( "addl" );
  }

  void visitNot( Not *p ) {
    p->visit_children(this);
    fprintf( m_outputfile, "pop %%eax\n" );
    fprintf( m_outputfile, "mov $1, %%ebx\n" );
    fprintf( m_outputfile, "xor %%ebx, %%eax\n" );
    fprintf( m_outputfile, "pushl %%eax\n" );
  }

  void visitUminus( Uminus *p ) {
    p->visit_children(this);
    fprintf( m_outputfile, "pop %%eax\n" );
    fprintf( m_outputfile, "neg %%eax\n" );
    fprintf( m_outputfile, "pushl %%eax\n" );
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
    p->visit_children(this);
  }

  void visitIntLit( IntLit *p ) {
    p->visit_children(this);
    gen_lit( p->m_primitive->m_data );
  }

  void visitCharLit( CharLit *p ) {
    p->visit_children(this);
    gen_lit( p->m_primitive->m_data );
  }

  void visitBoolLit( BoolLit *p ) {
    p->visit_children(this);
    gen_lit( p->m_primitive->m_data );
  }

  void visitStringLit( StringLit *p ) {

  }

  void visitNullLit( NullLit *p ) {
    p->visit_children(this);
    gen_lit( 0 );
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


void dopass_codegen(Program_ptr ast, SymTab* st)
{
    Codegen* codegen = new Codegen(stdout, st);
    ast->accept(codegen);
    delete codegen;
}
