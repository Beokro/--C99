#include <cassert>
#include <typeinfo>
#include <cstring>
#include <string>
#include <iostream>

#include "ast.hpp"
#include "symtab.hpp"
#include "primitive.hpp"
using namespace std;

#define DEBUG 1

// Todo, remove ARRAY node, they will never be used anyway
// Todo, Add string support, now the size can't be determine
// Todo, Handle the return array name which is a address case
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

  bool is_array_type( Basetype type ) {
    return ( type == bt_int_array || type == bt_char_array || type == bt_bool_array ||
             type == bt_long_array || type == bt_short_array );
  }

  bool is_2d_array_type( Basetype type ) {
    return  ( type == bt_2d_int_array || type == bt_2d_char_array ||
              type == bt_2d_bool_array ||
              type == bt_2d_long_array || type == bt_2d_short_array );
  }

  // generate assembly code for compare operator like
  // ==, !=, >, >= ....
  void gen_compare( string op ) {
    string temp = op + " %dl\n";
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
    string temp = op + " %ebx, %eax\n";
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

  // helper to get to the same lexical distance
  void get_same_level( int lexical_distance ) {
    if(lexical_distance!=0){
      string temp = "#lexical_distance is "+std::to_string(lexical_distance)+"\n";
      fprintf(m_outputfile, "%s",temp.c_str());
    }
    fprintf(m_outputfile, "movl %%ebp, %%ecx\n");
    for(int i =0; i<lexical_distance; i++){
      // keep going back until we at the same lexical level as the variabl
      fprintf(m_outputfile, "movl 0(%%ecx), %%ecx\n");
    }
  }

  void emit_prologue( SymName *name, unsigned int size_locals )
  {
    // declare the function as global
    string temp = ".global assem_"+string( name->spelling() )+"\n";
    fprintf( m_outputfile, "%s", temp.c_str() );
    // start of defination
    temp = "assem_" + string( name->spelling() ) + ":\n";
    fprintf( m_outputfile, "%s", temp.c_str() );
    // save the ebp and make it point to start of the temporary region
    fprintf( m_outputfile, "pushl %%ebp\n" );
    fprintf( m_outputfile, "movl %%esp, %%ebp\n" );
    // create the space for all variable in this procedure
    // esp point to the end of the local variable space
    temp = "sub $" + std::to_string( size_locals ) +", %esp\n\n";
    fprintf( m_outputfile, "%s", temp.c_str() );
  }

  void emit_epilogue() {
    // resotre the callee save registers
    fprintf( m_outputfile, "pop %%edi\n" );
    fprintf( m_outputfile, "pop %%esi\n" );
    fprintf( m_outputfile, "pop %%ebx\n" );
    // restore ebp and esp
    fprintf( m_outputfile, "movl %%ebp, %%esp\n" );
    fprintf( m_outputfile, "pop %%ebp\n" );
    // end of procedure, retunr to caller if it exist
    fprintf( m_outputfile, "ret\n\n" );
  }

  void emit_simple_prologue( unsigned int size_locals ) {
    string instruction = "sub $" + std::to_string( size_locals) + ", %esp\n\n";
    fprintf(m_outputfile, "pushl %%ebp\n");
    fprintf(m_outputfile, "movl %%esp, %%ebp\n");
    fprintf(m_outputfile, "%s", instruction.c_str());

  }

  void emit_simple_epilogue() {
    fprintf(m_outputfile, "movl %%ebp, %%esp\n");
    fprintf(m_outputfile, "pop %%ebp\n");
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

  void incre_helper( string op ) {
    string instruction = op + " $1, %eax\n";
    // expect the node push up the address of lhs
    fprintf( m_outputfile, "pop %%ebx\n" );
    // get the val of a and save it in %eax
    fprintf( m_outputfile, "movl 0(%%ebx), %%eax\n" );
    fprintf( m_outputfile, "%s", instruction.c_str() );
    fprintf( m_outputfile, "movl %%eax, 0(%%ebx)\n" );
  }

  void self_assign_helper( string op ) {
    string instruction = op + " 0(%eax), %ebx\n";
    // value of expr in %ebx, address of lhs in %eax
    fprintf( m_outputfile, "pop %%ebx\n" );
    fprintf( m_outputfile, "pop %%eax\n" );
    fprintf( m_outputfile, "%s", instruction.c_str() );
    fprintf( m_outputfile, "movl %%ebx, 0(%%eax)\n" );
  }

  void assignment_helper( Lhs * lhs, Expr * expr ) {
    Basetype lhs_type = lhs->m_attribute.m_basetype;
    string instruction = "";
    // accpet the lhs and expr so that address of lhs and value
    // of expr will be push to the stack
    lhs->accept( this );
    expr->accept( this );
    #ifdef DEBUG
    fprintf( m_outputfile, "\n#Start to assign\n" );
    #endif
    // value of expr in %ebx, address of lhs in %eax
    fprintf( m_outputfile, "pop %%ebx\n" );
    fprintf( m_outputfile, "pop %%eax\n" );
    // check if the type of expr to know the size of expr
    if ( expr->m_attribute.m_basetype != bt_char &&
         expr->m_attribute.m_basetype != bt_const_char ) {
      // size of the expr will be 4, just do a movl
      fprintf( m_outputfile, "movl %%ebx, 0(%%eax)\n" );
    } else {
      // size of the expr is 1, now there are 2 cases
      // if it is a char array or string, we need to use the movb
      // otherwise, movl is fine since we reserve 4 byte for char
      // and const char variable
      ArrayElement * test = dynamic_cast< ArrayElement* >( lhs );
      ArrayDoubleElement * test2 = dynamic_cast< ArrayDoubleElement* >( lhs );
      if ( ( ( lhs_type == bt_char || lhs_type == bt_const_char ) &&
             test != NULL || test2 != NULL) ||
           lhs_type == bt_string ) {
        fprintf( m_outputfile, "movb %%bl, 0(%%eax)\n" );
      } else {
        fprintf( m_outputfile, "movl %%ebx, 0(%%eax)\n" );
      }
    }
    #ifdef DEBUG
    fprintf( m_outputfile, "\n#End assign\n" );
    #endif
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

  void visitProcedureImpl( ProcedureImpl *p ) {
    // accpet the procedure define first so I can call them in this procedure
    PProcedure * procedure = NULL;
    for ( auto iter = p->m_pcontent_list->begin();
          iter != p->m_pcontent_list->end();
          iter++ ) {
      procedure = dynamic_cast< PProcedure * >( *iter );
      if ( procedure ) {
        procedure->accept( this );
      }
    }
    // emit prologue so that I have the ebp and esp at right place
    emit_prologue( p->m_symname,m_st->scopesize(p->m_attribute.m_scope) );

    // start to move arg to local
    // 0( $ebp ) is the old ebp, 4( $ebp ) is return address
    // the first argument is in 8( $ebp )
    int current = 8;
    int argu_offset = 0;
    string instruction1 = "";
    string instruction2 = "";
    fprintf( m_outputfile,"\n#Starting moving arg to local\n" );
    for( int i = 0; i < p->m_decl_list->size(); i++ ){
      // move the arg to ecx
      instruction1 = "movl "+std::to_string( current )+"(%ebp), %ecx\n";
      argu_offset = current-4;
      // move the arg to the local address space
      instruction2 = "movl %ecx, -"+std::to_string(argu_offset) + "(%ebp)\n";
      fprintf(m_outputfile, "%s", instruction1.c_str());
      fprintf(m_outputfile, "%s", instruction2.c_str());
      // increment the current offset 
      current+=4;
    }
    // save the callee save register
    fprintf( m_outputfile, "pushl %%ebx\n" );
    fprintf( m_outputfile, "pushl %%esi\n" );
    fprintf( m_outputfile, "pushl %%edi\n" );
    fprintf( m_outputfile,"#Ending moving arg to local\n\n" );

    // accept the regular statement except Procedure
    for ( auto iter = p->m_pcontent_list->begin();
          iter != p->m_pcontent_list->end();
          iter++ ) {
      if ( dynamic_cast< PProcedure * >( *iter ) == NULL ) {
        ( *iter )->accept( this );
      }
    }
    // accept the return statement
    p->m_return_stat->accept( this );
    emit_epilogue();
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
    Symbol * s = m_st->lookup( p->m_attribute.m_scope, p->m_symname->spelling() );
    Basetype type = s->m_basetype;
    // offset + relative_offset = real_offset from %ebp
    int offset = s->get_offset();
    int relative_offset = 0;
    int current_offset;
    int lexical_distance = m_st->lexical_distance( s->get_scope(), p->m_attribute.m_scope );
    string instruction = "";
    if ( p->m_expr->m_attribute.m_basetype == bt_empty ) {
      // does not assign to anything during init, just return
      return;
    }
    if ( is_array_type( type ) ) {
      // accept the expr so that value of list will be push to the stack
      // first pop will get the last element in array
      p->m_expr->accept( this );
      get_same_level( lexical_distance );
      // start to calculate the offset relative to current offset
      if ( type == bt_char_array ) {
        // size of char is 1
        relative_offset = s->m_length1;
      } else {
        // size of one element is 4
        relative_offset = s->m_length1 * 4;
      }
      instruction = "addl $-" + std::to_string( offset ) + ", %ecx\n";
      fprintf( m_outputfile, "%s",instruction.c_str() );
      /*
        int a [ 6 ] = { 0, 1, 2, 3, 4, 5 };
        000                    %ecx - 4
        001                    %ecx - 8
        010                    %ecx - 12
        011                    %ecx - 16
        100                    %ecx - 20
        101                    %ecx - 24

        about why is %ecx instead of %ebp, look at function get_same_level
        assume 101 is the address of a , 000 is address of a[ 5 ]
        we are going to pop 6 time to get all the expr, first pop
        will give us 5 because they are push to array in order
      */
      #ifdef DEBUG
      fprintf( m_outputfile, "\n#Start to move list to 1d array\n" );
      #endif
      if ( type != bt_char_array ) {
        current_offset = 4;
        for( current_offset; current_offset <= relative_offset; current_offset += 4 ) {
          fprintf( m_outputfile, "pop %%eax\n" );
          instruction = "movl %eax, -" + std::to_string( current_offset ) +"(%ecx)\n";
          fprintf( m_outputfile, "%s",instruction.c_str() );
        }
      } else {
        current_offset = 1;
        for( current_offset; current_offset <= relative_offset; current_offset += 1 ) {
          fprintf( m_outputfile, "pop %%eax\n" );
          instruction = "movb %al, -" + std::to_string( current_offset ) +"(%ecx)\n";
          fprintf( m_outputfile, "%s",instruction.c_str() );
        }
      }
      #ifdef DEBUG
      fprintf( m_outputfile, "\n#End move list to array\n" );
      #endif
      return;
    } else if ( is_2d_array_type( type ) ) {
      // accept the expr so that value of list will be push to the stack
      // first pop will get the last element in array
      p->m_expr->accept( this );
      get_same_level( lexical_distance );
      // start to calculate the offset relative to current offset
      if ( type == bt_2d_char_array ) {
        // size of char is 1
        relative_offset = s->m_length1 * s->m_length2;
      } else {
        // size of one element is 4
        relative_offset = s->m_length1 * s->m_length2 * 4;
      }
      instruction = "addl $-" + std::to_string( offset ) + ", %ecx\n";
      fprintf( m_outputfile, "%s",instruction.c_str() );
      /*
        int a [ 2 ][ 3 ] = { { 0, 1, 2 }, { 3, 4, 5 } };
        000                    %ecx - 4
        001                    %ecx - 8
        010                    %ecx - 12
        011                    %ecx - 16
        100                    %ecx - 20
        101                    %ecx - 24

        about why is %ecx instead of %ebp, look at function get_same_level
        assume 101 is the address of a , 000 is address of a[ 1 ][ 2 ]
        we are going to pop 6 time to get all the expr, first pop
        will give us 5 because they are push to array in order
      */
      #ifdef DEBUG
      fprintf( m_outputfile, "\n#Start to move list to 2d array\n" );
      #endif
      if ( type != bt_2d_char_array ) {
        current_offset = 4;
        for( current_offset; current_offset <= relative_offset; current_offset += 4 ) {
          fprintf( m_outputfile, "pop %%eax\n" );
          instruction = "movl %eax, -" + std::to_string( current_offset ) +"(%ecx)\n";
          fprintf( m_outputfile, "%s",instruction.c_str() );
        }
      } else {
        current_offset = 1;
        for( current_offset; current_offset <= relative_offset; current_offset += 1 ) {
          fprintf( m_outputfile, "pop %%eax\n" );
          instruction = "movb %al, -" + std::to_string( current_offset ) +"(%ecx)\n";
          fprintf( m_outputfile, "%s",instruction.c_str() );
        }
      }
      #ifdef DEBUG
      fprintf( m_outputfile, "\n#End move list to 2d array\n" );
      #endif
      return;
    } else {
      // variable is non-array, use the assignment_helper
      char * name_helper = strdup( p->m_symname->spelling() );
      Variable * v = new Variable( new SymName( name_helper ) );
      v->m_attribute.m_basetype = s->m_basetype;
      v->m_attribute.m_scope = p->m_attribute.m_scope;
      v->m_attribute.lineno = p->m_attribute.lineno;
      assignment_helper( v, p->m_expr );
    }
  }

  void visitEnum_defineImpl( Enum_defineImpl *p ) {
    // do nothing
  }

  void visitDecl_variable( Decl_variable *p ) {
    p->visit_children(this);
  }

  void visitDecl_function( Decl_function *p ) {
    // doesn't reallt matter since it won't be used anyway
  }

  void visitShort_declImpl( Short_declImpl *p ) {
    // don't have assign, do nothing
  }

  void visitStruct_defineImpl( Struct_defineImpl *p ) {
    // do nothing
  }

  void visitCallImpl( CallImpl *p ) {
    // we want to push the arguments in reverser order
    std::list< Expr_ptr >::iterator iter = p->m_expr_list->end();
    string instruction;
    iter--;
    for( iter; iter != p->m_expr_list->begin(); iter-- ) {
      ( *iter )->accept( this );
    }
    // get the first one
    if( p->m_expr_list->size()>0 )
      ( *iter )->accept( this );

    instruction = "call assem_" + string( p->m_symname->spelling() ) + "\n";
    fprintf( m_outputfile, "%s", instruction.c_str() );
    // the value of return will be in %eax already
  }

  void visitCaseImpl( CaseImpl *p ) {

  }

  void visitPProcedure( PProcedure *p ) {
    p->visit_children(this);
  }

  void visitPStat( PStat *p ) {
    p->m_stat->accept( this );
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
    assignment_helper( p->m_lhs, p->m_expr );
  }

  void visitString_assignment( String_assignment *p ) {
    // no string, do nothing
  }

  void visitFunction_assignment( Function_assignment *p ) {
    Basetype lhs_type = p->m_lhs->m_attribute.m_basetype;
    string instruction = "";
    // accpet the lhs and expr so that address of lhs and value
    // of expr will be push to the stack
    p->m_call->accept( this );
    // push the return of function call
    fprintf( m_outputfile, "pushl %%eax\n" );
    p->m_lhs->accept( this );
    #ifdef DEBUG
    fprintf( m_outputfile, "\n#Start to function assign\n" );
    #endif
    // return of function call in %eax, address of lhs in %ebx
    fprintf( m_outputfile, "pop %%ebx\n" );
    fprintf( m_outputfile, "pop %%eax\n" );
    // size of the expr is 1, now there are 2 cases
    // if it is a char, use movb since char is one byte, otherwise
    // use movl to move 4 byte
    if ( lhs_type == bt_char || lhs_type == bt_const_char ) {
      fprintf( m_outputfile, "movb %%al, 0(%%ebx)\n" );
    } else {
      fprintf( m_outputfile, "movl %%eax, 0(%%ebx)\n" );
    }

    #ifdef DEBUG
    fprintf( m_outputfile, "\n#End function assign\n" );
    #endif
  }

  void visitSIncre( SIncre *p ) {
    p->visit_children(this);
  }

  void visitFunction_call( Function_call *p ) {
    p->visit_children(this);
  }

  // Control flow
  void visitIf_no_else( If_no_else *p ) {
    emit_simple_prologue( m_st->scopesize(p->m_attribute.m_scope) );
    // check the if condition
    p->m_expr->accept( this );
    #ifdef DEBUG
    fprintf( m_outputfile, "\n#Start If no else\n" );
    #endif
    string labelNum = std::to_string( new_label() );
    fprintf( m_outputfile, "pop %%eax\n" );
    fprintf( m_outputfile, "cmp $0, %%eax\n" );
    string instruction = "je if_end" + labelNum+"\n\n";
    fprintf( m_outputfile, "%s",instruction.c_str() );

    // if contents
    visit_stat_can_return( p->m_stat_can_return_list );
    instruction = "if_end" + labelNum+":\n\n";
    fprintf( m_outputfile, "%s",instruction.c_str() );
    #ifdef DEBUG
    fprintf( m_outputfile, "#End If no else\n" );
    #endif
    emit_simple_epilogue();
  }

  void visitIf_with_else( If_with_else *p ) {
    emit_simple_prologue( m_st->scopesize(p->m_attribute.m_scope) );
    p->m_expr->accept(this);
    #ifdef DEBUG
    fprintf( m_outputfile, "\n#Start If with else\n" );
    #endif
    string labelNum = std::to_string(new_label());
    // check if condition
    fprintf(m_outputfile, "pop %%eax\n");
    fprintf(m_outputfile, "cmp $0, %%eax\n");

    // if condition not met, go to else branch
    string instruction = "je else" + labelNum+"\n\n";
    fprintf(m_outputfile, "%s",instruction.c_str());

    // if contents
    visit_stat_can_return( p->m_stat_can_return_list_1 );
    instruction = "jmp if_else_end" + labelNum+"\n\n";
    fprintf(m_outputfile, "%s",instruction.c_str());
    instruction = "else" + labelNum+":\n";
    fprintf(m_outputfile, "%s",instruction.c_str());

    // else contents
    visit_stat_can_return( p->m_stat_can_return_list_2 );
    instruction = "if_else_end" + labelNum+":\n\n";
    fprintf(m_outputfile, "%s",instruction.c_str());
    #ifdef DEBUG
    fprintf( m_outputfile, "#End if with else\n" );
    #endif
    emit_simple_epilogue();
  }

  void visitWhile_loop( While_loop *p ) {
    emit_simple_prologue( m_st->scopesize(p->m_attribute.m_scope) );
    p->m_expr->accept( this );
    #ifdef DEBUG
    fprintf( m_outputfile, "\n#Start While Loop\n" );
    #endif
    string labelNum = std::to_string(new_label());
    // check while condition
    fprintf(m_outputfile, "pop %%eax\n");
    fprintf(m_outputfile, "cmp $0, %%eax\n");
    string instruction = "je loop_end" + labelNum+"\n\n";
    fprintf(m_outputfile, "%s",instruction.c_str());

    // while contents
    instruction = "loop_start" + labelNum+":\n\n";
    fprintf(m_outputfile, "%s",instruction.c_str());
    visit_stat_can_return( p->m_stat_can_return_list );

    // check while conditions agagin, if not false, go back
    p->m_expr->accept(this);
    fprintf(m_outputfile, "pop %%eax\n");
    fprintf(m_outputfile, "cmp $0, %%eax\n");
    instruction = "jne loop_start" + labelNum+"\n\n";
    fprintf(m_outputfile, "%s",instruction.c_str());
    instruction = "loop_end" + labelNum+":\n\n";
    fprintf(m_outputfile, "%s",instruction.c_str());
    #ifdef DEBUG
    fprintf( m_outputfile, "#End while loop\n" );
    #endif
    emit_simple_epilogue();
  }

  void visitDo_while( Do_while *p ) {
    emit_simple_prologue( m_st->scopesize(p->m_attribute.m_scope) );
    #ifdef DEBUG
    fprintf( m_outputfile, "\n#Start do while\n" );
    #endif
    string labelNum = std::to_string(new_label());
    // while content
    string instruction = "loop_start" + labelNum+":\n\n";
    fprintf(m_outputfile, "%s",instruction.c_str());
    visit_stat_can_return( p->m_stat_can_return_list );

    // check while conditions, if not false, go back
    p->m_expr->accept(this);
    fprintf(m_outputfile, "pop %%eax\n");
    fprintf(m_outputfile, "cmp $0, %%eax\n");
    instruction = "jne loop_start" + labelNum+"\n\n";
    fprintf(m_outputfile, "%s",instruction.c_str());
    fprintf(m_outputfile, "%s",instruction.c_str());
    #ifdef DEBUG
    fprintf( m_outputfile, "#End do while\n" );
    #endif
    emit_simple_epilogue();
  }

  void visitFor_loop( For_loop *p ) {

  }

  void visitSwitch( Switch *p ) {

  }

  void visitBreak( Break *p ) {
    // need to keep a record of breakLabel
  }

  void visitContinue( Continue *p ) {
    // need to keep a record of continueLabel
  }

  void visitStat_struct_define( Stat_struct_define *p ) {
    // do nothing
  }

  void visitStat_enum_define( Stat_enum_define *p ) {
    // do nothing
  }

  void visitStat_decl( Stat_decl *p ) {
    p->visit_children(this);
  }

  void visitReturn_statImpl( Return_statImpl *p ) {
    #ifdef DEBUG
    fprintf( m_outputfile, "\n#Start return\n" );
    #endif
    p->visit_children(this);
    if( p->m_expr->m_attribute.m_basetype != bt_char &&
        p->m_expr->m_attribute.m_basetype != bt_const_char )
      fprintf( m_outputfile, "pop %%eax\n\n" );
    else{
      //lowest byte is the char
      fprintf( m_outputfile, "pop %%eax\n" );
      fprintf( m_outputfile, "movl $0xff,%%ebx\n" );
      fprintf( m_outputfile, "and %%ebx, %%eax\n\n" );
    }
  }

  void visitTInt( TInt *p ) {
    p->visit_children(this);
  }

  void visitTChar( TChar *p ) {
    p->visit_children(this);
  }

  void visitTBool( TBool *p ) {
    p->visit_children(this);
  }

  void visitTShort( TShort *p ) {
    p->visit_children(this);
  }

  void visitTVoid( TVoid *p ) {
    p->visit_children(this);
  }

  void visitTLong( TLong *p ) {
    p->visit_children(this);
  }

  void visitTStruct( TStruct *p ) {
    p->visit_children(this);
  }

  void visitTEnum( TEnum *p ) {
    p->visit_children(this);
  }

  void visitTCInt( TCInt *p ) {
    p->visit_children(this);
  }

  void visitTCChar( TCChar *p ) {
    p->visit_children(this);
  }

  void visitTCBool( TCBool *p ) {
    p->visit_children(this);
  }

  void visitTCShort( TCShort *p ) {
    p->visit_children(this);
  }

  void visitTCLong( TCLong *p ) {
    p->visit_children(this);
  }

  void visitTCharPtr( TCharPtr *p ) {
    p->visit_children(this);
  }

  void visitTIntPtr( TIntPtr *p ) {
    p->visit_children(this);
  }

  void visitTBoolPtr( TBoolPtr *p ) {
    p->visit_children(this);
  }

  void visitTShortPtr( TShortPtr *p ) {
    p->visit_children(this);
  }

  void visitTVoidPtr( TVoidPtr *p ) {
    p->visit_children(this);
  }

  void visitTLongPtr( TLongPtr *p ) {
    p->visit_children(this);
  }

  void visitTIntArray( TIntArray *p ) {
    p->visit_children(this);
  }

  void visitTCharArray( TCharArray *p ) {
    p->visit_children(this);
  }

  void visitTBoolArray( TBoolArray *p ) {
    p->visit_children(this);
  }

  void visitTShortArray( TShortArray *p ) {
    p->visit_children(this);
  }

  void visitTLongArray( TLongArray *p ) {
    p->visit_children(this);
  }

  void visitTTDIntArray( TTDIntArray *p ) {
    p->visit_children(this);
  }

  void visitTTDCharArray( TTDCharArray *p ) {
    p->visit_children(this);
  }

  void visitTTDBoolArray( TTDBoolArray *p ) {
    p->visit_children(this);
  }

  void visitTTDShortArray( TTDShortArray *p ) {
    p->visit_children(this);
  }

  void visitTTDLongArray( TTDLongArray *p ) {
    p->visit_children(this);
  }

  void visitTString( TString *p ) {
    p->visit_children(this);
  }

  void visitNo_type( No_type *p ) {
    p->visit_children(this);
  }

  void visitListImpl( ListImpl *p ) {
    p->visit_children(this);
  }

  void visitIncre_op( Incre_op *p ) {
    p->visit_children(this);
  }

  void visitIncre_t_add( Incre_t_add *p ) {
    // accept the lhs so the address of lhs will be
    // push to the stack and save it in %ebx
    p->m_lhs->accept( this );
    incre_helper( "addl" );
  }

  void visitIncre_t_min( Incre_t_min *p ) {
    p->m_lhs->accept( this );
    incre_helper( "subl" );
  }

  void visitIncre_add_t( Incre_add_t *p ) {
    p->m_lhs->accept( this );
    incre_helper( "addl" );
  }

  void visitIncre_min_t( Incre_min_t *p ) {
    p->m_lhs->accept( this );
    incre_helper( "subl" );
  }

  void visitAnd_assign( And_assign *p ) {
    // accept the child, expr and address of lhs
    // is pushed on stack 
    p->visit_children(this);
    self_assign_helper( "andl" );
  }

  void visitXor_assign( Xor_assign *p ) {
    p->visit_children(this);
    self_assign_helper( "xorl" );
  }

  void visitOr_assign( Or_assign *p ) {
    p->visit_children(this);
    self_assign_helper( "orl" );
  }

  void visitSl_assign( Sl_assign *p ) {
    // shift need special care
    p->visit_children(this);
    fprintf( m_outputfile, "pop %%ecx\n" );
    fprintf( m_outputfile, "pop %%eax\n" );
    fprintf( m_outputfile, "movl 0(%%eax), %%edi\n" );
    // shift can be used on 8 bit constant or register %cl
    fprintf( m_outputfile, "shl %%cl, %%edi\n" );
    fprintf( m_outputfile, "movl %%edi, 0(%%eax)\n\n" );
  }

  void visitSr_assign( Sr_assign *p ) {
    p->visit_children(this);
    fprintf( m_outputfile, "pop %%ecx\n" );
    fprintf( m_outputfile, "pop %%eax\n" );
    fprintf( m_outputfile, "movl 0(%%eax), %%edi\n" );
    // shift can be used on 8 bit constant or register %cl
    fprintf( m_outputfile, "shr %%cl, %%edi\n" );
    fprintf( m_outputfile, "movl %%edi, 0(%%eax)\n\n" );
  }

  void visitTimes_assign( Times_assign *p ) {
    p->visit_children(this);
    self_assign_helper( "imul" );
  }

  void visitDiv_assign( Div_assign *p ) {
    p->visit_children(this);
    fprintf( m_outputfile, "pop %%ebx\n" );
    fprintf( m_outputfile, "pop %%edi\n" );
    fprintf( m_outputfile, "movl 0(%%edi), %%eax\n" );
    fprintf( m_outputfile, "cdq\n" );
    fprintf( m_outputfile, "idiv %%ebx\n" );
    fprintf( m_outputfile, "movl %%eax, 0(%%edi)\n\n" );
  }

  void visitRem_assign( Rem_assign *p ) {
    p->visit_children(this);
    fprintf( m_outputfile, "pop %%ebx\n" );
    fprintf( m_outputfile, "pop %%edi\n" );
    fprintf( m_outputfile, "movl 0(%%edi), %%eax\n" );
    fprintf( m_outputfile, "cdq\n" );
    fprintf( m_outputfile, "idiv %%ebx\n" );
    fprintf( m_outputfile, "movl %%edx, 0(%%edi)\n\n" );
  }

  void visitAdd_assign( Add_assign *p ) {
    p->visit_children(this);
    self_assign_helper( "addl" );
  }

  void visitMinus_assign( Minus_assign *p ) {
    p->visit_children(this);
    // value of expr in %ebx, address of lhs in %eax
    fprintf( m_outputfile, "pop %%ebx\n" );
    fprintf( m_outputfile, "pop %%eax\n" );
    //save the value of lhs in %edx
    fprintf( m_outputfile, "movl 0(%%eax), %%edx\n" );
    fprintf( m_outputfile, "subl %%ebx, %%edx\n" );
    fprintf( m_outputfile, "movl %%edx, 0(%%eax)\n" );
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
    Symbol * s = m_st->lookup(p->m_attribute.m_scope, p->m_symname->spelling());
    int off_set = s->get_offset()+4;
    int lexical_distance = m_st->lexical_distance(s->get_scope(), p->m_attribute.m_scope);
    get_same_level( lexical_distance );
    string temp = "pushl -"+std::to_string(off_set)+"(%ecx)\n";
    fprintf(m_outputfile, "%s",temp.c_str());
  }

  void visitArrayAccess( ArrayAccess *p ) {
    // 2 cases, array or string
    Symbol * s = m_st->lookup( p->m_attribute.m_scope, p->m_symname->spelling() );
    Basetype type = s->m_basetype;
    int offset = s->get_offset();
    int lexical_distance = m_st->lexical_distance(s->get_scope(), p->m_attribute.m_scope);
    string instruction = "";
    // push the index to the stack
    p->visit_children( this );
    get_same_level( lexical_distance );
    // index now in %eax
    fprintf(m_outputfile, "pop %%eax\n");
    // if it is a array
    if ( type == bt_int_array || type == bt_bool_array || type == bt_long_array ||
         type ==  bt_short_array ) {
      // the end of their address is offset + 4 * size of array
      offset += 4 * s->m_length1;
      // index * 4 is the true offset
      fprintf(m_outputfile, "imul $4, %%eax\n");
    } else if ( type == bt_char_array ) {
      offset += s->m_length1;
      // since size of char is 1, no need to modify the index
    } // todo, add the string case
    fprintf( m_outputfile, "addl %%eax, %%ecx\n" );
    instruction = "pushl -" + std::to_string( offset )+ "(%ecx)\n";
    fprintf( m_outputfile, "%s", instruction.c_str() );
  }

  void visitArrayDoubleAccess( ArrayDoubleAccess *p ) {
    p->visit_children( this );
    Symbol * s = m_st->lookup( p->m_attribute.m_scope, p->m_symname->spelling() );
    Basetype type = s->m_basetype;
    int offset = s->get_offset();
    int lexical_distance = m_st->lexical_distance(s->get_scope(), p->m_attribute.m_scope);
    string instruction = "";
    get_same_level( lexical_distance );
    // array[ a ][ b ], ( a * m_length2 + b ) * sizeof( array[ 0 ][ 0 ] )
    fprintf( m_outputfile, "pop %%ebx\n" ); // %ebx = index b
    fprintf( m_outputfile, "pop %%eax\n" ); // %eax = index a
    // if it is a array
    if ( type == bt_2d_int_array || type == bt_2d_bool_array ||
         type == bt_2d_long_array || type == bt_2d_short_array ) {
      // the end of their address is offset + 4 * size of array
      offset += 4 * s->m_length1 * s->m_length2;
      // indexa * 4 * m_length2 + indexb * 4 is the true offset
      fprintf( m_outputfile, "imul $4, %%eax\n" );
      fprintf( m_outputfile, "imul $4, %%ebx\n" );
    } else if ( type == bt_2d_char_array ) {
      offset += s->m_length1 * s->m_length2;
      // since size of char is 1,
      // indexa * m_length2 + indexb is the true offset
    }
    instruction = "imul $" + std::to_string( s->m_length2 ) + ", %eax\n";
    fprintf( m_outputfile, "%s",instruction.c_str() );
    fprintf( m_outputfile, "addl %%eax, %%ecx\n" );
    fprintf( m_outputfile, "addl %%ebx, %%ecx\n" );
    instruction = "push -" + std::to_string( offset )+ "(%ecx)\n";
    fprintf( m_outputfile, "%s", instruction.c_str() );
  }

  void visitDotAccess( DotAccess *p ) {
    // ... = a.b
    p->visit_children( this );
    int lexical_distance = m_st->lexical_distance(p->m_lhs->m_attribute.m_scope,
                                                  p->m_attribute.m_scope);
    string instruction = "";
    Symbol * s_struct = m_st->lookup( p->m_lhs->m_attribute.m_struct_name );
    auto it = s_struct->m_map.find( string( p->m_symname->spelling() ) );
    // get the relative offset of a element in this struct
    int offset = it->second.second;
    get_same_level( lexical_distance );
    // address of a will be save in %eax
    #ifdef DEBUG
    fprintf( m_outputfile, "\n#Start dot access\n" );
    #endif
    fprintf( m_outputfile, "pop %%eax\n" );
    // use the offset( for b ) and address of a to push the value of a.b
    instruction = "pushl " + std::to_string( offset ) + "(%eax)\n";
    fprintf( m_outputfile, "%s", instruction.c_str() );
    #ifdef DEBUG
    fprintf( m_outputfile, "#End dot access\n" );
    #endif
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
    // no going to use it anyway
  }

  void visitNullLit( NullLit *p ) {
    p->visit_children(this);
    gen_lit( 0 );
  }

  void visitDeref( Deref *p ) {
    #ifdef DEBUG
    fprintf( m_outputfile, "\n#Start Deref rhs\n" );
    #endif
    // ... = *a
    // expect visit child will push up the value of a
    p->visit_children( this );
    fprintf( m_outputfile, "pop %%eax\n");
    // do a access get the value of *a, push it to the stack
    fprintf( m_outputfile, "pushl 0(%%eax)\n");
    #ifdef DEBUG
    fprintf( m_outputfile, "#End Deref rhs\n" );
    #endif
  }

  void visitAddressOf( AddressOf *p ) {
    // Lhs:DotElement ==>  Lhs SymName
    // visit lhs will push up the address
    p->visit_children(this);
  }

  void visitEList( EList *p ) {
    p->visit_children(this);
  }

  void visitETDList( ETDList *p ) {
    p->visit_children(this);
  }

  void visitECall( ECall *p ) {
    p->visit_children(this);
  }

  void visitEmpty( Empty *p ) {
    // do nothing
  }

  void visitVariable( Variable *p ) {
    Symbol * s = m_st->lookup( p->m_attribute.m_scope, p->m_symname->spelling() );
    Basetype type = s->m_basetype;
    int offset = 0;
    int lexical_distance = m_st->lexical_distance( s->get_scope(), p->m_attribute.m_scope );
    string instruction = "";
    #ifdef DEBUG
    fprintf( m_outputfile, "#start visit variable\n");
    #endif
    if ( type == bt_struct ) {
      // offset will be symbol offset + size of this struct
      offset = s->get_offset() + s->m_length1;
    } else {
      // otherwise offset will be symbol offset to 4
      offset = s->get_offset() + 4;
    }
    get_same_level( lexical_distance );
    // get the right address by adding offset to current base (%ecx)
    instruction = "addl $-" + std::to_string( offset ) + ", %ecx\n";
    fprintf( m_outputfile, "%s",instruction.c_str() );
    // push the address of this variable
    fprintf( m_outputfile, "pushl %%ecx\n");
    #ifdef DEBUG
    fprintf( m_outputfile, "#end visit variable\n");
    #endif
    return;
  }

  void visitDerefVariable( DerefVariable *p ) {
    // *a = ...
    // use the symname to get the symbol
    Symbol * s = m_st->lookup( p->m_attribute.m_scope, p->m_symname->spelling() );
    int off_set = s->get_offset()+4;
    int lexical_distance = m_st->lexical_distance( s->get_scope(), p->m_attribute.m_scope );
    string instruction = "";
    get_same_level( lexical_distance );
    // push up the value of a, or address of *a
    instruction = "pushl -" + std::to_string( off_set )+ "(%ecx)\n";
    fprintf( m_outputfile, "%s",instruction.c_str() );
  }

  // should push up the address of the array element
  void visitArrayElement( ArrayElement *p ) {
    // 2 cases, array or string
    p->visit_children( this );
    Symbol * s = m_st->lookup( p->m_attribute.m_scope, p->m_symname->spelling() );
    Basetype type = s->m_basetype;
    int offset = s->get_offset();
    int lexical_distance = m_st->lexical_distance(s->get_scope(), p->m_attribute.m_scope);
    string instruction = "";
    get_same_level( lexical_distance );
    fprintf(m_outputfile, "pop %%eax\n");
    // if it is a array
    if ( type == bt_int_array || type == bt_bool_array || type == bt_long_array ||
         type ==  bt_short_array ) {
      // the end of their address is offset + 4 * size of array
      offset += 4 * s->m_length1;
      // index * 4 is the true offset
      fprintf(m_outputfile, "imul $4, %%eax\n");
    } else if ( type == bt_char_array ) {
      offset += s->m_length1;
      // since size of char is 1, no need to modify the index
    } // todo, add the string case
    fprintf( m_outputfile, "addl %%eax, %%ecx\n" );
    instruction = "lea -" + std::to_string( offset )+ "(%ecx), %eax\n";
    fprintf( m_outputfile, "%s", instruction.c_str() );
    fprintf( m_outputfile, "pushl %%eax\n" );
  }

  void visitArrayDoubleElement( ArrayDoubleElement *p ) {
    p->visit_children( this );
    Symbol * s = m_st->lookup( p->m_attribute.m_scope, p->m_symname->spelling() );
    Basetype type = s->m_basetype;
    int offset = s->get_offset();
    int lexical_distance = m_st->lexical_distance(s->get_scope(), p->m_attribute.m_scope);
    string instruction = "";
    get_same_level( lexical_distance );
    // array[ a ][ b ], ( a * m_length2 + b ) * sizeof( array[ 0 ][ 0 ] )
    fprintf( m_outputfile, "pop %%ebx\n" ); // %ebx = index b
    fprintf( m_outputfile, "pop %%eax\n" ); // %eax = index a
    // if it is a array
    if ( type == bt_2d_int_array || type == bt_2d_bool_array ||
         type == bt_2d_long_array || type == bt_2d_short_array ) {
      // the end of their address is offset + 4 * size of array
      offset += 4 * s->m_length1 * s->m_length2;
      // indexa * 4 * m_length2 + indexb * 4 is the true offset
      fprintf( m_outputfile, "imul $4, %%eax\n" );
      fprintf( m_outputfile, "imul $4, %%ebx\n" );
    } else if ( type == bt_2d_char_array ) {
      offset += s->m_length1 * s->m_length2;
      // since size of char is 1,
      // indexa * m_length2 + indexb is the true offset
    }
    instruction = "imul $" + std::to_string( s->m_length2 ) + ", %eax\n";
    fprintf( m_outputfile, "%s",instruction.c_str() );
    fprintf( m_outputfile, "addl %%eax, %%ecx\n" );
    fprintf( m_outputfile, "addl %%ebx, %%ecx\n" );
    instruction = "lea -" + std::to_string( offset )+ "(%ecx), %eax\n";
    fprintf( m_outputfile, "%s", instruction.c_str() );
    fprintf( m_outputfile, "pushl %%eax\n" );
  }

  void visitArrowElement( ArrowElement *p ) {
    // won't be use anyway
  }

  void visitDotElement( DotElement *p ) {
    // a.b = ...
    p->visit_children( this );
    int lexical_distance = m_st->lexical_distance(p->m_lhs->m_attribute.m_scope,
                                                  p->m_attribute.m_scope);
    string instruction = "";
    Symbol * s_struct = m_st->lookup( p->m_lhs->m_attribute.m_struct_name );
    auto it = s_struct->m_map.find( string( p->m_symname->spelling() ) );
    // get the relative offset of a element in this struct
    int offset = it->second.second;
    get_same_level( lexical_distance );
    #ifdef DEBUG
    fprintf( m_outputfile, "\n#Start dot element\n");
    #endif
    // address of a will be save in %eax
    fprintf( m_outputfile, "pop %%eax\n" );
    // add the offset( for b ) to the address of a to get the
    // address of a.b
    instruction = "addl $" + std::to_string( offset ) + ", %eax\n";
    fprintf( m_outputfile, "%s", instruction.c_str() );
    // push the address of a.b to stack
    fprintf( m_outputfile, "pushl %%eax\n" );
    #ifdef DEBUG
    fprintf( m_outputfile, "#End dot element\n");
    #endif
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
