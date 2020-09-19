#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include "computer.h"

#include<string.h>
#undef mips			/* gcc already has a def for mips */

unsigned int endianSwap(unsigned int);




void PrintInfo (int changedReg, int changedMem);
unsigned int Fetch (int);
void Decode (unsigned int, DecodedInstr*, RegVals*);
int Execute (DecodedInstr*, RegVals*);
int Mem(DecodedInstr*, int, int *);
void RegWrite(DecodedInstr*, int, int *);
void UpdatePC(DecodedInstr*, int);
void PrintInstruction (DecodedInstr*);

/*Globally accessible Computer variable*/
Computer mips;
RegVals rVals;

/*
 *  Return an initialized computer with the stack pointer set to the
 *  address of the end of data memory, the remaining registers initialized
 *  to zero, and the instructions read from the given file.
 *  The other arguments govern how the program interacts with the user.
 */
void InitComputer (FILE* filein, int printingRegisters, int printingMemory,
  int debugging, int interactive) {
    int k;
    unsigned int instr;

    /* Initialize registers and memory */

    for (k=0; k<32; k++) {
        mips.registers[k] = 0;
    }
    
    /* stack pointer - Initialize to highest address of data segment */
    mips.registers[29] = 0x00400000 + (MAXNUMINSTRS+MAXNUMDATA)*4;

    for (k=0; k<MAXNUMINSTRS+MAXNUMDATA; k++) {
        mips.memory[k] = 0;
    }

    k = 0;
    while (fread(&instr, 4, 1, filein)) {
	/*swap to big endian, convert to host byte order. Ignore this.*/
        mips.memory[k] = ntohl(endianSwap(instr));
        k++;
        if (k>MAXNUMINSTRS) {
            fprintf (stderr, "Program too big.\n");
            exit (1);
        }
    }

    mips.printingRegisters = printingRegisters;
    mips.printingMemory = printingMemory;
    mips.interactive = interactive;
    mips.debugging = debugging;
}

unsigned int endianSwap(unsigned int i) 
{
    return (i>>24)|(i>>8&0x0000ff00)|(i<<8&0x00ff0000)|(i<<24);
}

/*
 *  Run the simulation.
 */
void Simulate () {
    char s[40];  /* used for handling interactive input */
    unsigned int instr;
    int changedReg=-1, changedMem=-1, val;
    DecodedInstr d;
    
    /* Initialize the PC to the start of the code section */
    mips.pc = 0x00400000;
    while (1) {
        if (mips.interactive) {
            printf ("> ");
            fgets (s,sizeof(s),stdin);
            if (s[0] == 'q') {
                return;
            }
        }

		


        /* Fetch instr at mips.pc, returning it in instr */
        instr = Fetch (mips.pc);



        printf ("Executing instruction at %8.8x: %8.8x\n", mips.pc, instr);

        /* 
	 * Decode instr, putting decoded instr in d
	 * Note that we reuse the d struct for each instruction.
	 */
        Decode (instr, &d, &rVals);

        /*Print decoded instruction*/
        PrintInstruction(&d);

        /* 
	 * Perform computation needed to execute d, returning computed value 
	 * in val 
	 */

        val = Execute(&d, &rVals);




		UpdatePC(&d,val);



        /* 
	 * Perform memory load or store. Place the
	 * address of any updated memory in *changedMem, 
	 * otherwise put -1 in *changedMem. 
	 * Return any memory value that is read, otherwise return -1.
         */

        val = Mem(&d, val, &changedMem);


		


        /* 
	 * Write back to register. If the instruction modified a register--
	 * (including jal, which modifies $ra) --
         * put the index of the modified register in *changedReg,
         * otherwise put -1 in *changedReg.
         */


        RegWrite(&d, val, &changedReg);


        


        PrintInfo (changedReg, changedMem);



    }
}

/*
 *  Print relevant information about the state of the computer.
 *  changedReg is the index of the register changed by the instruction
 *  being simulated, otherwise -1.
 *  changedMem is the address of the memory location changed by the
 *  simulated instruction, otherwise -1.
 *  Previously initialized flags indicate whether to print all the
 *  registers or just the one that changed, and whether to print
 *  all the nonzero memory or just the memory location that changed.
 */
void PrintInfo ( int changedReg, int changedMem) {
    int k, addr;
    printf ("New pc = %8.8x\n", mips.pc);
    if (!mips.printingRegisters && changedReg == -1) {
        printf ("No register was updated.\n");
    } else if (!mips.printingRegisters) {

        printf ("Updated r%2.2d to %8.8x\n", changedReg, mips.registers[changedReg]);
    } else {
        for (k=0; k<32; k++) {
            printf ("r%2.2d: %8.8x  ", k, mips.registers[k]);
            if ((k+1)%4 == 0) {
                printf ("\n");
            }
        }
    }

    


    if (!mips.printingMemory && changedMem == -1) {
        printf ("No memory location was updated.\n");
    } else if (!mips.printingMemory) {
        printf ("Updated memory at address %8.8x to %8.8x\n",
        changedMem, Fetch (changedMem));
    } else {
        printf ("Nonzero memory\n");
        printf ("ADDR	  CONTENTS\n");
        for (addr = 0x00400000+4*MAXNUMINSTRS;
             addr < 0x00400000+4*(MAXNUMINSTRS+MAXNUMDATA);
             addr = addr+4) {
            if (Fetch (addr) != 0) {
                printf ("%8.8x  %8.8x\n", addr, Fetch (addr));
            }
        }
    }
}

/*
 *  Return the contents of memory at the given address. Simulates
 *  instruction fetch. 
 */
unsigned int Fetch ( int addr) {
    return mips.memory[(addr-0x00400000)/4];
}


unsigned int Fetch_memory( int addr) {
    return mips.memory[(addr-0x00404000)/4];
}


int binpower(int n){
    int ret = 1;
    for(int i =1; i<=n; i+=1)
    {
        ret = ret*2;
    }
    return ret;}

void R_instructions_decode( unsigned int instr, DecodedInstr* d, RegVals* rVals){


    int rs_inst = 0, rt_inst = 0, rd_inst = 0, shamt_inst = 0, funct_inst = 0;

    for(int i =25; i>=21; i--)
    {
        
        if( instr>=binpower(i))
        {
            rs_inst+=binpower(i-21);
            instr-=binpower(i);
        }
    }


    for(int i =20; i>=16; i--)
    {
        
        if( instr>=binpower(i))
        {
            rt_inst+=binpower(i-16);
            instr-=binpower(i);
        }
    }


    for(int i =15; i>=11; i--)
    {
        
        if( instr>=binpower(i))
        {
            rd_inst+=binpower(i-11);
            instr-=binpower(i);
        }
    }

    for(int i =10; i>=6; i--)
    {
        
        if( instr>=binpower(i))
        {
            shamt_inst+=binpower(i-6);
            instr-=binpower(i);
        }
    }


    for(int i =5; i>=0; i--)
    {
        
        if( instr>=binpower(i))
        {
            funct_inst+=binpower(i);
            instr-=binpower(i);
        }
    }

    d->regs.r.rs = rs_inst;
    rVals->R_rs=rs_inst;

    d->regs.r.rt = rt_inst;
    rVals->R_rt = rt_inst;

    d->regs.r.rd = rd_inst;
    rVals->R_rd = rd_inst;

    d->regs.r.shamt = shamt_inst;
    d->regs.r.funct = funct_inst;}

void I_instructions_decode( unsigned int instr, DecodedInstr* d, RegVals* rVals){


    int rs_inst = 0, rt_inst = 0, immed_inst = 0;

    for(int i =25; i>=21; i--)
    {
        
        if( instr>=binpower(i))
        {
            rs_inst+=binpower(i-21);
            instr-=binpower(i);
        }
    }


    for(int i =20; i>=16; i--)
    {
        
        if( instr>=binpower(i))
        {
            rt_inst+=binpower(i-16);
            instr-=binpower(i);
        }
    }


    for(int i =15; i>=0; i--)
    {
        
        if( instr>=binpower(i))
        {
            immed_inst+=binpower(i);
            instr-=binpower(i);
        }
    }


    d->regs.i.rs = rs_inst;
    rVals->R_rs=rs_inst;

    d->regs.i.rt = rt_inst;
    rVals->R_rt = rt_inst;

    d->regs.i.addr_or_immed = immed_inst;}

void J_instructions_decode( unsigned int instr, DecodedInstr* d, RegVals* rVals){


    int immed_inst = 0;

    for(int i =25; i>=0; i--)
    {
        
        if( instr>=binpower(i))
        {
            immed_inst+=binpower(i);
            instr-=binpower(i);
        }
    }

    d->regs.j.target = immed_inst;}

/* Decode instr, returning decoded instruction. */
void Decode ( unsigned int instr, DecodedInstr* d, RegVals* rVals) {
    /* Your code goes here */

    int opcode = 0;
    for(int i =31; i>=26; i--)
    {
        
        if( instr>=binpower(i))
        {
            opcode+=binpower(i-26);
            instr-=binpower(i);
        }
    }

    d->op = opcode;

    if(opcode==0)
    {
        d->type = R;
        
        R_instructions_decode( instr, d, rVals);

        //printf("number R:   ");
    }
    else if(opcode==2 || opcode==3)
    {
        d->type = J;

        J_instructions_decode( instr, d, rVals);

        //printf("number J:   ");
    }
    else
    {
        d->type = I;

        I_instructions_decode( instr, d, rVals);

        //printf("number I:   ");
    }

    //printf("instrtype act : %d\n", d->type);}
}




/*
 *  Print the disassembled version of the given instruction
 *  followed by a newline.
 */
void PrintInstruction ( DecodedInstr* d)
{

    if(d->type == R)
    {

        //printf("funct %d\n", d->regs.r.funct);

        char func_name[] = "        ";

        if( d->regs.r.funct==32)
        {

            strcpy(func_name, "add");
            printf("%s", func_name);

            printf("\t$%d, $%d, $%d\n", d->regs.r.rd, d->regs.r.rs, d->regs.r.rt);
        }
        
        else if( d->regs.r.funct ==33)
        {

            strcpy(func_name, "addu");
            printf("%s", func_name);

            printf("\t$%d, $%d, $%d\n", d->regs.r.rd, d->regs.r.rs, d->regs.r.rt);

        }

        else if(d->regs.r.funct ==34)
        {
            strcpy(func_name, "sub");
            printf("%s", func_name);

            printf("\t$%d, $%d, $%d\n", d->regs.r.rd, d->regs.r.rs, d->regs.r.rt);

        }

        else if( d->regs.r.funct ==35)
        {
            strcpy(func_name, "subu");
            printf("%s", func_name);

            printf("\t$%d, $%d, $%d\n", d->regs.r.rd, d->regs.r.rs, d->regs.r.rt);

        }
        
        else if( d->regs.r.funct ==36)
        {
            strcpy(func_name, "and");
            printf("%s", func_name);

            printf("\t$%d, $%d, $%d\n", d->regs.r.rd, d->regs.r.rs, d->regs.r.rt);

        }

        else if( d->regs.r.funct ==37)
        {
            strcpy(func_name, "or");
            printf("%s", func_name);

            printf("\t$%d, $%d, $%d\n", d->regs.r.rd, d->regs.r.rs, d->regs.r.rt);

        }

        else if( d->regs.r.funct ==39)
        {
            strcpy(func_name, "nor");
            printf("%s", func_name);

            printf("\t$%d, $%d, $%d\n", d->regs.r.rd, d->regs.r.rs, d->regs.r.rt);

        }

        else if( d->regs.r.funct ==42)
        {
            strcpy(func_name, "slt");
            printf("%s", func_name);

            printf("\t$%d, $%d, $%d\n", d->regs.r.rd, d->regs.r.rs, d->regs.r.rt);

        }


        else if( d->regs.r.funct ==43)
        {
            strcpy(func_name, "sltu");
            printf("%s", func_name);

            printf("\t$%d, $%d, $%d\n", d->regs.r.rd, d->regs.r.rs, d->regs.r.rt);

        }


        else if( d->regs.r.funct ==0)
        {
            strcpy(func_name, "sll");
            printf("%s", func_name);

            printf("\t$%d, $%d, %d\n", d->regs.r.rd, d->regs.r.rt, d->regs.r.shamt);

        }


        else if( d->regs.r.funct ==2)
        {
            strcpy(func_name, "srl");
            printf("%s", func_name);

            printf("\t$%d, $%d, %d\n", d->regs.r.rd, d->regs.r.rt, d->regs.r.shamt);

        }

        else if (d->regs.r.funct == 8)
        {
            strcpy(func_name, "jr");
            printf("%s", func_name);

            printf("\t$%d\n", d->regs.r.rs);

        }
        

    }
    else if(d->type == I)
    {
        char func_name[] = "        ";

        if( d->op==9)
        {
            strcpy(func_name, "addiu");

            printf("%s", func_name);


            int imm_out = d->regs.i.addr_or_immed;

            if(imm_out>=binpower(15))
                imm_out = imm_out - binpower(16);



            printf("\t$%d, $%d, %d\n", d->regs.i.rt, d->regs.i.rs, imm_out);

        }
        else if( d->op ==8)
        {
            strcpy(func_name, "addi");

            printf("%s", func_name);
            printf("\t$%d, $%d, %d\n", d->regs.i.rt, d->regs.i.rs, d->regs.i.addr_or_immed);
        }
        else if( d->op ==12)
        {
            strcpy(func_name, "andi");

            printf("%s", func_name);
            printf("\t$%d, $%d, %d\n", d->regs.i.rt, d->regs.i.rs, d->regs.i.addr_or_immed);
        }
        else if(d->op ==13)
        {
            strcpy(func_name, "ori");

            printf("%s", func_name);
            printf("\t$%d, $%d, %d\n", d->regs.i.rt, d->regs.i.rs, d->regs.i.addr_or_immed);
        }
        else if( d->op ==15)
        {
            strcpy(func_name, "lui");

            printf("%s", func_name);
            printf("\t$%d, 0x%4.4x\n", d->regs.i.rt,  d->regs.i.addr_or_immed);
        }
        else if( d->op ==4)
        {
            strcpy(func_name, "beq");

            printf("%s", func_name);
            printf("\t$%d, $%d, 0x%8.8x\n", d->regs.i.rt, d->regs.i.rs, d->regs.i.addr_or_immed);
        }
        else if( d->op ==5)
        {
            strcpy(func_name, "bne");

            printf("%s", func_name);
            printf("\t$%d, $%d, 0x%8.8x\n", d->regs.i.rt, d->regs.i.rs, d->regs.i.addr_or_immed);
        }
        else if( d->op ==35)
        {
            strcpy(func_name, "lw");



            int imm = d->regs.i.addr_or_immed;

            if(imm>=binpower(15))
                imm = imm - binpower(16);

            printf("%s", func_name);
            printf("\t$%d, %d($%d)\n", d->regs.i.rt, imm, d->regs.i.rs);
        }
        else if( d->op ==43)
        {
            strcpy(func_name, "sw");


            int imm = d->regs.i.addr_or_immed;

            if(imm>=binpower(15))
                imm = imm - binpower(16);

            printf("%s", func_name);
            printf("\t$%d, %d($%d)\n", d->regs.i.rt, imm, d->regs.i.rs);
        }

    }
    else
    {
        if( d->op==2)
        {
            printf("j\t 0x%8.8x\n",  d->regs.j.target);
        }
        else
        {
            printf("jal\t 0x%8.8x\n",  d->regs.j.target);
        }
    }
    /* Your code goes here */
}





/* Perform computation needed to execute d, returning computed value */
int Execute ( DecodedInstr* d, RegVals* rVals) {
    /* Your code goes here */

    int rs = rVals->R_rs;
    int rt = rVals->R_rt;

    if(d->type == R)
    {

        int shamt = d->regs.r.shamt;

        if( d->regs.r.funct ==33)
        {
            //strcpy(func_name, "addu");


            int ret = mips.registers[rs] + mips.registers[rt];

            return ret;

        }

        else if( d->regs.r.funct ==35)
        {
            //strcpy(func_name, "subu");

            int ret = mips.registers[rs] - mips.registers[rt];

            return ret;
        }
        
        else if( d->regs.r.funct ==36)
        {
            return mips.registers[rt]&mips.registers[rs];
            //strcpy(func_name, "and");
        }

        else if( d->regs.r.funct ==37)
        {
            return mips.registers[rt] | mips.registers[rs];
            //strcpy(func_name, "or");
        }


        else if( d->regs.r.funct ==42)
        {
            //strcpy(func_name, "slt");

            if(mips.registers[rs] < mips.registers[rt])
                return mips.registers[rs]; 
            else
                return mips.registers[rt]; 

        }

        else if( d->regs.r.funct ==0)
        {
            //strcpy(func_name, "sll");

            return mips.registers[rt] << shamt;
        }

        else if( d->regs.r.funct ==2)
        {
            //strcpy(func_name, "srl");

            return mips.registers[rt] >> shamt;
        }

        else if (d->regs.r.funct == 8)
        {
            //strcpy(func_name, "jr");

            return mips.registers[rs];
        }


    }

    else if(d->type == I)
    {

        int imm = d->regs.i.addr_or_immed;

        if( d->op==9)
        {

        	if(imm>=binpower(15))
                imm = imm - binpower(16);


            int ret = mips.registers[rs] + imm;

            return ret;
            //strcpy(func_name, "addiu");
        }
        else if( d->op ==12)
        {
            return imm & mips.registers[rs];
            //strcpy(func_name, "andi");
        }
        else if(d->op ==13)
        {
            return imm | mips.registers[rs];
            //strcpy(func_name, "ori");
        }
        else if( d->op ==15)
        {
            //strcpy(func_name, "lui");
             return imm << 16;
        }
        else if( d->op ==4)
        {
            //strcpy(func_name, "beq");

            if(mips.registers[rt] == mips.registers[rs])
                return imm;
            else
                return 0;
        }
        else if( d->op ==5)
        {
            //strcpy(func_name, "bne");

            if(mips.registers[rt] == mips.registers[rs])
                return 0;
            else
                return imm;

        }
        else if( d->op ==35)
        {
            if(imm>=binpower(15))
                imm = imm - binpower(16);




            return Fetch_memory(mips.registers[rs]) + imm;
            //strcpy(func_name, "lw");

            

        }

        else if( d->op ==43)
        {
            if(imm>=binpower(15))
                imm = imm - binpower(16);

            return Fetch_memory(mips.registers[rs]) + imm;
            //strcpy(func_name, "sw");
        }

    }
    else
    {
        if( d->op==2)
        {
            //printf("j\n");

            return d->regs.j.target;
        }
        else
        {
            //printf("jal\n");

            return d->regs.j.target;

        }
    }

  return 0;
}





/* 
 * Update the program counter based on the current instruction. For
 * instructions other than branches and jumps, for example, the PC
 * increments by 4 (which we have provided).
 */
void UpdatePC ( DecodedInstr* d, int val) {


    if( d->op==2 )
    {
        mips.pc = val;
    }
    else if(d->op==0 & d->regs.r.funct == 8)
    {
        mips.pc = mips.registers[d->regs.r.rs];
    }
    else 
    {
        mips.pc+=4;

        if(d->op==4 || d->op ==5)
        {
            mips.pc += val;
        }
        if (d->op==3)
        {


            mips.registers[31] = mips.pc +4;
            mips.pc = val;


            printf ("MIPS Register: %8.8x\n", mips.pc);

        }

    }




    /* Your code goes here */
}

/*
 * Perform memory load or store. Place the address of any updated memory 
 * in *changedMem, otherwise put -1 in *changedMem. Return any memory value 
 * that is read, otherwise return -1. 
 *
 * Remember that we're mapping MIPS addresses to indices in the mips.memory 
 * array. mips.memory[0] corresponds with address 0x00400000, mips.memory[1] 
 * with address 0x00400004, and so forth.
 *
 */
int Mem( DecodedInstr* d, int val, int *changedMem) {
    /* Your code goes here */
    *changedMem = -1;
    if( d->op==35)
    {
        
        return mips.memory[val];
    }
    else if( d->op==43)
    {
        *changedMem = val*4+0x00404000;
        mips.memory[val] = mips.registers[d->regs.i.rt];

    }

  return val;
}

/* 
 * Write back to register. If the instruction modified a register--
 * (including jal, which modifies $ra) --
 * put the index of the modified register in *changedReg,
 * otherwise put -1 in *changedReg.
 */
void RegWrite( DecodedInstr* d, int val, int *changedReg) {
    /* Your code goes here */
    
    if( d->op==9 || d->op==12 || d->op==13 || d->op==15 || d->op==35)
    {


    	if(d->regs.i.rt!=0)

    	{
    		*changedReg = d->regs.i.rt;
        	mips.registers[d->regs.i.rt] = val;
    	}
    	else
    		*changedReg = -1;

    }
    else if(  d->op==0 && (d->regs.r.funct==33 || d->regs.r.funct==35 || d->regs.r.funct==0 || d->regs.r.funct==2 || d->regs.r.funct==36 || d->regs.r.funct==37 || d->regs.r.funct==42) )
    {

    	if(d->regs.r.rd!=0)
    	{
	        *changedReg = d->regs.r.rd;
	        mips.registers[d->regs.r.rd] = val;
	    }
	    else
    		*changedReg = -1;
    	
    }
    else if(d->op==3 )
    {
    	 *changedReg = 31;
    }
    else
    {
    	 *changedReg = -1;
    }



}





