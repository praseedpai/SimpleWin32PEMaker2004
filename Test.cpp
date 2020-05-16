// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <process.h>
#include <stdlib.h>
#include <string.h>
///////////////////////////////
//
// enumerations for tokens
//
//
//

enum  TOKEN {
  ILLEGAL_TOKEN=-1,
  TOK_PLUS=1,
  TOK_MUL,
  TOK_DIV, 
  TOK_SUB,
  TOK_OPAREN,
  TOK_CPAREN,
  TOK_NUMBER,
  TOK_NULL ,
  TOK_LT,
  TOK_GT,
  TOK_LTE,
  TOK_GTE,
  TOK_NE,
  TOK_EQ,
  TOK_AND,
  TOK_OR,
  TOK_NOT,
  TOK_BIT_OR,
  TOK_BIT_AND,
  TOK_BIT_NOT,
  TOK_BIT_XOR
};

enum DATA_TYPE {
	ILLEGAL_DATA_TYPE=-1,
	LONG_DATA_TYPE,
	DOUBLE_DATA_TYPE,
	BOOL_DATA_TYPE
};

enum OP_TYPE {
   ILLEGAL_OP_TYPE=-1,
   PLUS_OP_TYPE,
   MINUS_OP_TYPE,
   DIV_OP_TYPE,
   MUL_OP_TYPE,
   PLUS_UN_OP_TYPE,
   MINUS_UN_OP_TYPE,
   VALUE_OP_TYPE,
   LT_OP_TYPE,
   GT_OP_TYPE,
   LTE_OP_TYPE,
   GTE_OP_TYPE,
   NE_OP_TYPE,
   EQ_OP_TYPE,
   AND_OP_TYPE,
   OR_OP_TYPE,
   NOT_OP_TYPE,
   BIT_OR_OP_TYPE,
   BIT_AND_OP_TYPER,
   BIT_NOT_OP_TYPE,
   BIT_XOR_OP_TYPE
};

enum NODE_TYPE
{
   Operator,
   Number,
   IfStatement,
   UnaryExp,
   Exp
};
///////////////////////////////////////////////////
//
//
//  A stack for long values (  a negroe one written for HTIJA )
//
//
//
//

class Stack
{

 private:
     long values[256];
     long stk_ptr; 

     long HIGH_DWORD_FROM_DOUBLE(double d)
     {
         long *x = (long *)(void *)&d;
         return x[1];    

     }
     long LOW_DWORD_FROM_DOUBLE(double d)
     {
        long *x = (long *)(void *)&d;
        return x[0];     
     }
 public:
     Stack() {
        stk_ptr = 0;  
     } 
     void Clear() {

        stk_ptr=0;  

     }

     void Push( long nval ) 
        { 
            if ( stk_ptr == 255 )
             {
                printf("Stack OverFlow\n");
                exit(0);
              } 
            values[stk_ptr++]=nval; 

        }

		void Push(double d )
		{
           Push(LOW_DWORD_FROM_DOUBLE(d));
           Push(HIGH_DWORD_FROM_DOUBLE(d));
		}

		double PopD()
		{
             long hd = Pop();
             long ld = Pop();
			 long dbfr[2] = { ld , hd };
             return * ( (double *) (void *) &dbfr[0]); 
              
		}

     long Pop( )
      {


         if ( stk_ptr == 0 )
           {
                printf("underflow\n");
                exit(0);
           }   

           return values[--stk_ptr];

      }   







};


struct TreeNode
{
   NODE_TYPE nt;
   OP_TYPE   op_type;
   DATA_TYPE data_type;
   union DATA {
    double db;
    long   lb;
   }DATA_TAG;
   struct TreeNode *Child[10];
   struct TreeNode *Next;

};


TreeNode *AllocTreeNode()
{
   TreeNode * xt = (TreeNode *)malloc(sizeof(TreeNode));
   memset(xt,0,sizeof(TreeNode));
   
   xt->data_type = ILLEGAL_DATA_TYPE;
   
   return xt;

}

/////////////////////////////////////////////////
//
//
//
//
//
class Lexer
{
  private:
        char ExprString[1024];
        long value; 
        TOKEN last_token; 
        char *curr_ptr; 
  public:
         Lexer( char*  Expr)
         {
             memset(ExprString,0,1024);
             strcpy(ExprString,Expr);
             curr_ptr = ExprString;
         }  


         TOKEN GetNextToken()
          {
                 while ( *curr_ptr == '  ' || *curr_ptr =='\t' )
                               curr_ptr++;

                  switch( *curr_ptr)
                  {
                    case '+':   
                      last_token = TOK_PLUS;
                      *curr_ptr++; 
                      break;  
					case '=':
                       last_token = TOK_EQ;
					   *curr_ptr++;
					   break;
					case '|':
						if ( *(curr_ptr + 1 ) == '|' ) 
						{
                              last_token = TOK_OR;
							  curr_ptr++;
						}
						else
							  last_token = TOK_BIT_OR;
						break;
						curr_ptr++;
                     case '&':
						if ( *(curr_ptr + 1 ) == '&' ) 
						{
                              last_token = TOK_AND;
							  curr_ptr++;
						}
						else
							  last_token = TOK_BIT_AND;
						curr_ptr++;
						break;
					 case '^':
						 last_token = TOK_BIT_XOR;
						 curr_ptr++;
						 break;
					 case '~':
						 last_token = TOK_BIT_NOT;
						 curr_ptr++;
						 break;
					 case '!':
                         last_token = TOK_NOT;
						 curr_ptr++;
						 break; 
					 case '>':
						 if ( *(curr_ptr + 1 ) == '=' ) 
						 {
                              last_token = TOK_GTE;
							  curr_ptr++;
						 }
						 else
							  last_token = TOK_GT;
						 curr_ptr++;
						 break;
					 case '<':
                         if ( *(curr_ptr + 1 ) == '=' ) 
						 {
                              last_token = TOK_LTE;
							  curr_ptr++;
						 }
						 else if (*( curr_ptr + 1 ) == '>' )
						 {
                              last_token = TOK_NE;
							  curr_ptr++;
						 }
						 else
							  last_token = TOK_LT;
                         break;
                         curr_ptr++;
                     case '-':   
                      last_token = TOK_SUB;
                      *curr_ptr++; 
                      break;  
                     case '/':   
                      last_token = TOK_DIV;
                      *curr_ptr++; 
                      break;  
                     case '*':   
                      last_token = TOK_MUL;
                      *curr_ptr++; 
                      break;  
                     case '(':   
                      last_token = TOK_OPAREN;
                      *curr_ptr++; 
                      break;  
                     case ')':   
                      last_token = TOK_CPAREN;
                      *curr_ptr++; 
                       break;  
                     case 0:
                      last_token = TOK_NULL;
                      break;             
                     case '0':
                     case '1':
                     case '2':
                     case '3':
                     case '4':
                     case '5':
                     case '6':
                     case '7':
                     case '8':
                     case '9': 
                       {
                          printf("reached here\n");
                          char num_val[100];
                          memset(num_val,0,100);
                          char *num_ptr = &(num_val[0]); 
                          *num_ptr++ = *curr_ptr++;  

                          while ( *curr_ptr >= '0' && *curr_ptr <='9' )
                                   *num_ptr++ = *curr_ptr++;

                          last_token = TOK_NUMBER;
                          value=atol(num_val); 
                          printf("Value = %d\n",value); 
                        
                        break;
                         } 
                      default: 
                       {                            
                         printf("\nIllegal token found in stream");
                         exit(0);     
  

                       }
                      }    

                         
                   

                     return last_token; 

               }

       long GetValue() { return value; }
 

};

//////////////////////////////////////////////////////////////////
//
//
//
//
//
//
//
class RDParser : public Lexer
{

  private:
      TOKEN Current_Token;
      Stack ValueStack;


  public:
       RDParser(char *sExpr):Lexer(sExpr) 
       {

           Current_Token = ILLEGAL_TOKEN;

       }  

       TreeNode *CallExpr(); 
	   TreeNode *LogicExpr();
	   TreeNode *RelExpr();
       TreeNode *Expr();  
       TreeNode *Term();  
       TreeNode *Factor();




};



TreeNode *RDParser::CallExpr()
{
   Current_Token= GetNextToken();
   TreeNode *RetValue = LogicExpr(); 
   return RetValue;
}

TreeNode *RDParser::LogicExpr()
{
    TOKEN l_token;
    TreeNode *Temp = RelExpr();
   if  ( Current_Token == TOK_AND ||
         Current_Token == TOK_OR  ||
         Current_Token == TOK_BIT_OR ||
         Current_Token == TOK_BIT_AND ||
         Current_Token == TOK_BIT_XOR ) 
   {

          TreeNode *RetValue = AllocTreeNode();
		if ( RetValue != 0 ) {
			RetValue->Child[0] =  Temp;
			RetValue->op_type = 
				(Current_Token == TOK_AND ) ?  AND_OP_TYPE : 
			    (Current_Token == TOK_OR ) ?  OR_OP_TYPE :
                (Current_Token == TOK_BIT_OR ) ? BIT_OR_OP_TYPE :
				(Current_Token == TOK_BIT_AND  ) ? BIT_AND_OP_TYPE 
							: BIT_XOR_OP_TYPE;
			RetValue->nt = Exp;
            Temp = RetValue;
			l_token = Current_Token;
		    Current_Token = GetNextToken();
            RetValue->Child[1] = LogicExpr();
		} 





   }


}


TreeNode *RDParser::RelExpr()
{
   TOKEN l_token;
   TreeNode *Temp = Expr();
   if  ( Current_Token == TOK_LT  || 
	     Current_Token == TOK_GT  ||
		 Current_Token == TOK_LTE ||
		 Current_Token == TOK_GTE ||
		 Current_Token == TOK_NEQ ||
		 Current_Token == TOK_EQ )  
   {

        TreeNode *RetValue = AllocTreeNode();
		if ( RetValue != 0 ) {
			RetValue->Child[0] =  Temp;
			RetValue->op_type = 
				(Current_Token == TOK_LT ) ?  LT_OP_TYPE : 
			    (Current_Token == TOK_GT ) ?  GT_OP_TYPE :
                (Current_Token == TOK_GTE ) ? GTE_OP_TYPE :
				(Current_Token == TOK_LTE ) ? LTE_OP_TYPE :
				(Current_Token == TOK_EQ  ) ? EQ_OP_TYPE : NEQ_OP_TYPE;
			RetValue->nt = Exp;
            Temp = RetValue;
			l_token = Current_Token;
		    Current_Token = GetNextToken();
            RetValue->Child[1] = RelExpr();
		} 







   }

}

TreeNode *RDParser::Expr()
{

   TOKEN l_token;

   TreeNode *Temp = Term();

   if  ( Current_Token == TOK_PLUS  || Current_Token == TOK_SUB ) 
   {
        TreeNode *RetValue = AllocTreeNode();
		if ( RetValue != 0 ) {
			RetValue->Child[0] =  Temp;
			RetValue->op_type = (Current_Token == TOK_PLUS ) ?
             PLUS_OP_TYPE : MINUS_OP_TYPE;  
			RetValue->nt = Exp;
            Temp = RetValue;
			l_token = Current_Token;
		    Current_Token = GetNextToken();
            RetValue->Child[1] = Expr();
		} 
   }
   return Temp;        
}


TreeNode *RDParser::Term()
{
  TOKEN l_token;

  TreeNode *Temp = Factor();

   if ( Current_Token == TOK_MUL  || Current_Token == TOK_DIV ) 
   {
        TreeNode *RetValue = AllocTreeNode();
		if ( RetValue != 0 ) {
			RetValue->Child[0] =  Temp;
			RetValue->op_type = (Current_Token == TOK_MUL ) ?
                                 MUL_OP_TYPE : DIV_OP_TYPE;  
			RetValue->nt = Exp;
            Temp = RetValue;

			l_token = Current_Token;
		    Current_Token = GetNextToken();
                          
            RetValue->Child[1] = Term();
		} 
	   
	   	    
        
        
   }
  

      return Temp;


}

TreeNode *RDParser::Factor()
{
	TOKEN l_token;
    if ( Current_Token == TOK_NUMBER )
    {     
           TreeNode *RetValue = AllocTreeNode();
		   RetValue->data_type = DOUBLE_DATA_TYPE;
		   RetValue->nt = Exp;
           RetValue->op_type = VALUE_OP_TYPE;
		   RetValue->DATA_TAG.db = GetValue(); 
           Current_Token = GetNextToken();  
		   return RetValue;
    } 
    else if ( Current_Token == TOK_OPAREN )
    {

          Current_Token = GetNextToken();   

          TreeNode *RetValue = Expr();  // Recurse

          if ( Current_Token != TOK_CPAREN )
           {
                printf("Missing Closing Parenthesis\n");
                exit(0);

           }   
          Current_Token = GetNextToken();            
		  return RetValue;
    } 

	else if ( Current_Token == TOK_PLUS || Current_Token == TOK_SUB )
	{
        TreeNode *RetValue = AllocTreeNode();
		if ( RetValue != 0 ) {
			RetValue->op_type = (Current_Token == TOK_PLUS ) ?
                                 PLUS_UN_OP_TYPE : MINUS_UN_OP_TYPE;  
            RetValue->nt = Exp;
            
			l_token = Current_Token;
		    Current_Token = GetNextToken();
            RetValue->Child[0]=0;               
            RetValue->Child[1] = Factor();
		} 
        return RetValue; 
	}
    else {

           printf("ILLegal Token\n");
           exit(0);


    } 



}

class AbstractTreeInterpreter 
{

public :
  double Evaluate( TreeNode *Tree )
{
    printf("Entered the Loop\n");
	fflush(stdout);
	if ( Tree->nt == Exp)
	 {
		 if ( Tree->op_type == PLUS_OP_TYPE )
		       return Evaluate(Tree->Child[0]) + Evaluate(Tree->Child[1]);  
		 else if ( Tree->op_type == MINUS_OP_TYPE )
               return Evaluate(Tree->Child[0]) - Evaluate(Tree->Child[1]);
		 else if ( Tree->op_type == MUL_OP_TYPE )
			   return Evaluate(Tree->Child[0]) * Evaluate(Tree->Child[1]); 
		 else if ( Tree->op_type == PLUS_UN_OP_TYPE ) 
			  return Evaluate(Tree->Child[1]); 
         else if ( Tree->op_type == MINUS_UN_OP_TYPE )   
					 return -Evaluate(Tree->Child[1]); 
		 else if ( Tree->op_type == DIV_OP_TYPE )
		 {
                 double xt = Evaluate(Tree->Child[1]);
		    	 if ( xt == 0.0 )
				  {
						  printf("Error: Division by Zero \n");
						  exit(0);
                  }
					  return Evaluate(Tree->Child[0])/xt; 

		 }
		 else if ( Tree->op_type  == VALUE_OP_TYPE )
		 {
			        printf("Value returned = %g\n",  Tree->DATA_TAG.db );
					fflush(stdout);
			        return Tree->DATA_TAG.db;  
		 }
		 else
		 {
                        printf("Error: Evaluating Expression \n");
						exit(0);
						return 0.0;
		 }


	 }
	else {
      printf("Illegal at this point of time \n");
      exit(0);
	  return 0.0;
	}
		
   }
	
};


/////////////////////////////////////////
//
// Derivation of a virtual machine 
//  
// I_LOAD  - Load an integer to the stack 
// R_LOAD  - Load  a Real to the stack
// D_LOAD  - Load an IEEE double to the stack 
// I_ADD   - Add integers from the top of the stack
// I_SUB   - Substract Two members of the stack
// I_DIV   - Divide Two members on the top of the stack
// I_MUL   - Multiply Two members on the  top of the stack
// I_NEG   - Negate the Value on the top of the stack


enum INSTRUCTION_CODE
{
   ILLEGAL_OP = -1,
   I_LOAD = 0,
   I_ADD  = 1,
   I_SUB  = 2,
   I_MUL  = 3,
   I_DIV  = 4,
   I_NEG  = 5,
   R_LOAD = 6,
   R_ADD  = 7,
   R_SUB  = 8,
   R_MUL  = 9,
   R_DIV  = 10,
   R_NEG  = 11,
   D_LOAD = 12,
   D_ADD  = 13,
   D_SUB  = 14,
   D_MUL  = 15,
   D_DIV  = 16,
   D_NEG  = 17,
   HLT    = 18,
   NOP    = 19
};



class InstructionEmitter
{
  char Code[8192];
  int  ip;

  long HIGH_DWORD_FROM_DOUBLE(double d)
  {
    long *x = (long *)(void *)&d;
    return x[1];    

  }
  long LOW_DWORD_FROM_DOUBLE(double d)
  {
    long *x = (long *)(void *)&d;
    return x[0];     
  }
public:
  InstructionEmitter()
  {
      ip=0;
	  memset(Code,(char)HLT,8192);
       
  }
public:

	void Interpret()
	{
       Stack rtstack; 
       int cip = 0;
       int opcode = 19;
	   double a,b;
	   while ( ( opcode = Code[cip++] ) != HLT )
	   {
            switch(opcode)
			{
			  case D_LOAD:
				  {
                  double d =  * ( (double *) (void *)&Code[cip]);
                  cip += 8;
                  rtstack.Push(d);
				  break;
				  }
			  case D_ADD:
				  {
                     a=  rtstack.PopD();
					 b = rtstack.PopD(); 
				     rtstack.Push(a+b); 
				  }
				   break;
              case D_SUB:
				   rtstack.Push(-(rtstack.PopD()-rtstack.PopD())); 
				   break;  
              case D_MUL:
				  {
				     a =  rtstack.PopD();
					 b =  rtstack.PopD(); 
				     rtstack.Push(a*b); 

				  }
				   break;  
              case D_NEG:
				   rtstack.Push(-rtstack.PopD()); 
				   break;   
			  case D_DIV:
				   {
                     double a = rtstack.PopD();
					 if ( a == 0.0 )
					 {
						 printf("Division by Zero \n");
						 exit(0);
					 }
					 rtstack.Push(rtstack.PopD()/a);  

				   }
				   break;
			  case NOP:
				   break;
			  default:
				   printf("Invalid op \n");
                   exit(0);
            }

	   }

	   double xt = rtstack.PopD();

	   printf("return value is %g\n",xt);

	}

	void Emit( TreeNode *Tree )
	{
          printf("Entered the Loop\n");
	      fflush(stdout);
          if ( Tree->nt == Exp)
	      {
		      if ( Tree->op_type == PLUS_OP_TYPE )
			  {
				    
                    Emit(Tree->Child[0]);
					Emit(Tree->Child[1]);
					Code[ip++]=D_ADD;
					
			   }
		       else if ( Tree->op_type == MINUS_OP_TYPE )
			   {
				    
                    Emit(Tree->Child[0]);
					Emit(Tree->Child[1]); 
					Code[ip++]=D_SUB;
                    
			   }
               else if ( Tree->op_type == MUL_OP_TYPE )
			   {
				    
			        Emit(Tree->Child[0]);
					Emit(Tree->Child[1]); 
					Code[ip++]=D_MUL;
					
			   }
		       else if ( Tree->op_type == PLUS_UN_OP_TYPE ) 
			   {
			        Emit(Tree->Child[1]); 
			   }
               else if ( Tree->op_type == MINUS_UN_OP_TYPE )   
			   {
				     
					 Emit(Tree->Child[1]); 
					 Code[ip++]=D_NEG;
					 
			   }
		       else if ( Tree->op_type == DIV_OP_TYPE )
		       {
				     
                     Emit(Tree->Child[0]);
		    	     Emit(Tree->Child[1]); 
					 Code[ip++]=D_DIV;  
                     
		       }
		       else if ( Tree->op_type  == VALUE_OP_TYPE )
		       {
				    Code[ip++] = D_LOAD;
		            long temp  = LOW_DWORD_FROM_DOUBLE(Tree->DATA_TAG.db);	        
					long temp1 = HIGH_DWORD_FROM_DOUBLE(Tree->DATA_TAG.db);
			        *((long *)(&Code[ip]))=temp;
                    ip+=sizeof(long);
                    *((long *)(&Code[ip]))=temp1; 
					ip+=sizeof(long);
					
					
		       } 
		  	 else
		      {
                        printf("Error: Inalid Code Generation\n");
						exit(0);
						return ;
		      }


	 }
	else {
      printf("Illegal at this point of time \n");
      exit(0);
	  return ;
	}




	}


};


////////////////////////////////////////////////////////////////////
//
// 
// Entry Point
//
//
//

void main(int argc , char **argv)
{
#if 1  
 if ( argc == 1  || argc > 2 ) {

       printf("usage :  expr \"<expr>\" - Expression should be delimited by \"   ");
        exit(0); 
 }
#endif

 

 RDParser *rdp = new RDParser(argv[1]);

  //RDParser *rdp = new RDParser("2+3*4");
  TreeNode *Ret = rdp->CallExpr();
 
#if 0 
  AbstractTreeInterpreter *Inter = new AbstractTreeInterpreter();
  printf("%g\n", Inter->Evaluate(Ret));
  delete Inter;
#else
  InstructionEmitter *emr = new InstructionEmitter();

  emr->Emit(Ret);
  emr->Interpret(); 
  delete emr;
#endif


  
  

  
  delete rdp;

}

