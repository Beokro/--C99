#include "ast.hpp"
#include "symtab.hpp"
#include "primitive.hpp"

#include <cstdio>
#include <stack>

class Ast2dot : public Visitor
{
private:
  FILE *m_out;        // File for writting output
  int count;          // Used to give each node a uniq id
  std::stack<int> s;  // Stack for tracking parent/child pairs

public:

  Ast2dot(FILE* out)
  {
    count = 0;
    s.push(0);
    m_out = out;
    std::fprintf(m_out, "digraph G { page=\"8.5,11\"; size=\"7.5, 10\"; \n");
  }

  void finish()
  {
    std::fprintf(m_out, "}\n");
  }

  void add_edge(int p, int c)
  {
    std::fprintf(m_out, "\"%d\" -> \"%d\"\n", p, c);
  }

  void add_node(int c, const char* n)
  {
    std::fprintf(m_out, "\"%d\" [label=\"%s\"]\n" , c, n);
  }

  void draw(const char* n, Visitable* p)
  {
    count++;                         // Each node gets a unique number
    add_edge(s.top(), count);        // From parent to this
    add_node(count, n);              // Name the this node
    s.push(count);                   // This node is the parent
    p->visit_children(this);
    s.pop();                         // Restore old parent
  }

  void draw_symname(const char* n, SymName* p)
  {
    count++;                         // Each node gets a unique number
    add_edge(s.top(), count);        // From parent to this
    // Print symname strings
    std::fprintf(m_out, "\"%d\" [label=\"%s\\n\\\"%s\\\"\"]\n" , count, n, p->spelling());
  }

  void draw_primitive(const char* n, Primitive* p)
  {
    count++;                         // Each node gets a unique number
    add_edge(s.top(), count);        // From parent to this
    std::fprintf(m_out, "\"%d\" [label=\"%s\\n%d\"]\n" , count, n, p->m_data);
  }

  void draw_string_primitive(const char* n, StringPrimitive* p)
  {
    count++;                         // Each node gets a unique number
    add_edge(s.top(), count);        // From parent to this
    std::fprintf(m_out, "\"%d\" [label=\"%s\\n\\\"%s\\\"\"]\n" , count, n, p->m_string);
  }
  void visitProgramImpl(ProgramImpl *p) { draw("ProgramImpl", p); }
  void visitOut_enum_define(Out_enum_define *p) { draw("Out_enum_define", p); }
  void visitOut_decl(Out_decl *p) { draw("Out_decl", p); }
  void visitOut_procedure(Out_procedure *p) { draw("Out_procedure", p); }
  void visitOut_struct_define(Out_struct_define *p) { draw("Out_struct_define", p); }
  void visitEnum_defineImpl(Enum_defineImpl *p) { draw("Enum_defineImpl", p); }
  void visitDecl_variable(Decl_variable *p) { draw("Decl_variable", p); }
  void visitDecl_function(Decl_function *p) { draw("Decl_function", p); }
  void visitProcedureImpl(ProcedureImpl *p) { draw("ProcedureImpl", p); }
  void visitStruct_defineImpl(Struct_defineImpl *p) { draw("Struct_defineImpl", p); }
  void visitCallImpl(CallImpl *p) { draw("CallImpl", p); }
  void visitCaseImpl(CaseImpl *p) { draw("CaseImpl", p); }
  void visitPProcedure(PProcedure *p) { draw("PProcedure", p); }
  void visitPStat(PStat *p) { draw("PStat", p); }
  void visitInit_new(Init_new *p) { draw("Init_new", p); }
  void visitInit_old(Init_old *p) { draw("Init_old", p); }
  void visitNStat(NStat *p) { draw("NStat", p); }
  void visitRStat(RStat *p) { draw("RStat", p); }
  void visitAssignment(Assignment *p) { draw("Assignment", p); }
  void visitString_assignment(String_assignment *p) { draw("String_assignment", p); }
  void visitFunction_assignment(Function_assignment *p) { draw("Function_assignment", p); }
  void visitSIncre(SIncre *p) { draw("SIncre", p); }
  void visitFunction_call(Function_call *p) { draw("Function_call", p); }
  void visitIf_no_else(If_no_else *p) { draw("If_no_else", p); }
  void visitIf_with_else(If_with_else *p) { draw("If_with_else", p); }
  void visitWhile_loop(While_loop *p) { draw("While_loop", p); }
  void visitDo_while(Do_while *p) { draw("Do_while", p); }
  void visitFor_loop(For_loop *p) { draw("For_loop", p); }
  void visitSwitch(Switch *p) { draw("Switch", p); }
  void visitBreak(Break *p) { draw("Break", p); }
  void visitContinue(Continue *p) { draw("Continue", p); }
  void visitStat_struct_define(Stat_struct_define *p) { draw("Stat_struct_define", p); }
  void visitStat_enum_define(Stat_enum_define *p) { draw("Stat_enum_define", p); }
  void visitStat_decl(Stat_decl *p) { draw("Stat_decl", p); }
  void visitReturn(Return *p) { draw("Return", p); }
  void visitTInt(TInt *p) { draw("TInt", p); }
  void visitTChar(TChar *p) { draw("TChar", p); }
  void visitTBool(TBool *p) { draw("TBool", p); }
  void visitTShort(TShort *p) { draw("TShort", p); }
  void visitTVoid(TVoid *p) { draw("TVoid", p); }
  void visitTLong(TLong *p) { draw("TLong", p); }
  void visitTStruct(TStruct *p) { draw("TStruct", p); }
  void visitTEnum(TEnum *p) { draw("TEnum", p); }
  void visitTCharPtr(TCharPtr *p) { draw("TCharPtr", p); }
  void visitTIntPtr(TIntPtr *p) { draw("TIntPtr", p); }
  void visitTBoolPtr(TBoolPtr *p) { draw("TBoolPtr", p); }
  void visitTShortPtr(TShortPtr *p) { draw("TShortPtr", p); }
  void visitTVoidPtr(TVoidPtr *p) { draw("TVoidPtr", p); }
  void visitTLongPtr(TLongPtr *p) { draw("TLongPtr", p); }
  void visitTIntArray(TIntArray *p) { draw("TIntArray", p); }
  void visitTCharArray(TCharArray *p) { draw("TCharArray", p); }
  void visitTBoolArray(TBoolArray *p) { draw("TBoolArray", p); }
  void visitTShortArray(TShortArray *p) { draw("TShortArray", p); }
  void visitTLongArray(TLongArray *p) { draw("TLongArray", p); }
  void visitTTDIntArray(TTDIntArray *p) { draw("TTDIntArray", p); }
  void visitTTDCharArray(TTDCharArray *p) { draw("TTDCharArray", p); }
  void visitTTDBoolArray(TTDBoolArray *p) { draw("TTDBoolArray", p); }
  void visitTTDShortArray(TTDShortArray *p) { draw("TTDShortArray", p); }
  void visitTTDLongArray(TTDLongArray *p) { draw("TTDLongArray", p); }
  void visitTString(TString *p) { draw("TString", p); }
  void visitNo_type(No_type *p) { draw("No_type", p); }
  void visitListImpl(ListImpl *p) { draw("ListImpl", p); }
  void visitIncre_op(Incre_op *p) { draw("Incre_op", p); }
  void visitIncre_t_add(Incre_t_add *p) { draw("Incre_t_add", p); }
  void visitIncre_t_min(Incre_t_min *p) { draw("Incre_t_min", p); }
  void visitIncre_add_t(Incre_add_t *p) { draw("Incre_add_t", p); }
  void visitIncre_min_t(Incre_min_t *p) { draw("Incre_min_t", p); }
  void visitAnd_assign(And_assign *p) { draw("And_assign", p); }
  void visitXor_assign(Xor_assign *p) { draw("Xor_assign", p); }
  void visitOr_assign(Or_assign *p) { draw("Or_assign", p); }
  void visitSl_assign(Sl_assign *p) { draw("Sl_assign", p); }
  void visitSr_assign(Sr_assign *p) { draw("Sr_assign", p); }
  void visitTimes_assign(Times_assign *p) { draw("Times_assign", p); }
  void visitDiv_assign(Div_assign *p) { draw("Div_assign", p); }
  void visitRem_assign(Rem_assign *p) { draw("Rem_assign", p); }
  void visitAdd_assign(Add_assign *p) { draw("Add_assign", p); }
  void visitMinus_assign(Minus_assign *p) { draw("Minus_assign", p); }
  void visitAnd(And *p) { draw("And", p); }
  void visitTimes(Times *p) { draw("Times", p); }
  void visitArithAnd(ArithAnd *p) { draw("ArithAnd", p); }
  void visitArithOr(ArithOr *p) { draw("ArithOr", p); }
  void visitArithXor(ArithXor *p) { draw("ArithXor", p); }
  void visitRem(Rem *p) { draw("Rem", p); }
  void visitShiftL(ShiftL *p) { draw("ShiftL", p); }
  void visitShiftR(ShiftR *p) { draw("ShiftR", p); }
  void visitDiv(Div *p) { draw("Div", p); }
  void visitCompare(Compare *p) { draw("Compare", p); }
  void visitGt(Gt *p) { draw("Gt", p); }
  void visitGteq(Gteq *p) { draw("Gteq", p); }
  void visitLt(Lt *p) { draw("Lt", p); }
  void visitLteq(Lteq *p) { draw("Lteq", p); }
  void visitMinus(Minus *p) { draw("Minus", p); }
  void visitNoteq(Noteq *p) { draw("Noteq", p); }
  void visitOr(Or *p) { draw("Or", p); }
  void visitPlus(Plus *p) { draw("Plus", p); }
  void visitNot(Not *p) { draw("Not", p); }
  void visitUminus(Uminus *p) { draw("Uminus", p); }
  void visitIdent(Ident *p) { draw("Ident", p); }
  void visitArrayAccess(ArrayAccess *p) { draw("ArrayAccess", p); }
  void visitArrayDoubleAccess(ArrayDoubleAccess *p) { draw("ArrayDoubleAccess", p); }
  void visitDotAccess(DotAccess *p) { draw("DotAccess", p); }
  void visitArrowAccess(ArrowAccess *p) { draw("ArrowAccess", p); }
  void visitIntLit(IntLit *p) { draw("IntLit", p); }
  void visitCharLit(CharLit *p) { draw("CharLit", p); }
  void visitBoolLit(BoolLit *p) { draw("BoolLit", p); }
  void visitNullLit(NullLit *p) { draw("NullLit", p); }
  void visitStringLit(StringLit *p) { draw("StringLit", p); }
  void visitDeref(Deref *p) { draw("Deref", p); }
  void visitAddressOf(AddressOf *p) { draw("AddressOf", p); }
  void visitEList(EList *p) { draw("Elist", p); }
  void visitETDList(ETDList *p) { draw("ETDlist", p); }
  void visitECall(ECall *p) { draw("ECall", p); }
  void visitVariable(Variable *p) { draw("Variable", p); }
  void visitDerefVariable(DerefVariable *p) { draw("DerefVariable", p); }
  void visitArrayElement(ArrayElement *p) { draw("ArrayElement", p); }
  void visitArrayDoubleElement(ArrayDoubleElement *p) { draw("ArrayDoubleElement", p); }
  void visitArrowElement(ArrowElement *p) { draw("ArrowElement", p); }
  void visitDotElement(DotElement *p) { draw("DotElement", p); }
  
  // Special cases
  void visitSymName(SymName *p) { draw_symname("SymName",p); }
  void visitPrimitive(Primitive *p) { draw_primitive("Primitive",p); }
  void visitStringPrimitive(StringPrimitive *p) { draw_string_primitive("StringPrimitive",p); }
};

void dopass_ast2dot(Program_ptr ast)
{
  Ast2dot* ast2dot = new Ast2dot(stdout);     // Create new visitor
  ast->accept(ast2dot);                       // Walk the tree with the visitor above
  ast2dot->finish();                          // Finalize printout
  delete ast2dot;
}
