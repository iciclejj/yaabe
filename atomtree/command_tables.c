#include "command_tables.h"

void atom_op_move(struct atom_command* command, uint8_t** ptr_ptr);
void atom_op_and(struct atom_command* command, uint8_t** ptr_ptr) { assert(0); /* Not implemented (yet) */}
void atom_op_or(struct atom_command* command, uint8_t** ptr_ptr) { assert(0); /* Not implemented (yet) */}
void atom_op_shift_left(struct atom_command* command, uint8_t** ptr_ptr);
void atom_op_shift_right(struct atom_command* command, uint8_t** ptr_ptr);
void atom_op_mul(struct atom_command* command, uint8_t** ptr_ptr) { assert(0); /* Not implemented (yet) */}
void atom_op_div(struct atom_command* command, uint8_t** ptr_ptr) { assert(0); /* Not implemented (yet) */}
void atom_op_add(struct atom_command* command, uint8_t** ptr_ptr) { assert(0); /* Not implemented (yet) */}
void atom_op_sub(struct atom_command* command, uint8_t** ptr_ptr) { assert(0); /* Not implemented (yet) */}
void atom_op_setport(struct atom_command* command, uint8_t** ptr_ptr);
void atom_op_setregblock(struct atom_command* command, uint8_t** ptr_ptr);
void atom_op_setfbbase(struct atom_command* command, uint8_t** ptr_ptr) { assert(0); /* Not implemented (yet) */}
void atom_op_compare(struct atom_command* command, uint8_t** ptr_ptr) { assert(0); /* Not implemented (yet) */}
void atom_op_switch(struct atom_command* command, uint8_t** ptr_ptr) { assert(0); /* Not implemented (yet) */}
void atom_op_jump(struct atom_command* command, uint8_t** ptr_ptr);
void atom_op_test(struct atom_command* command, uint8_t** ptr_ptr) { assert(0); /* Not implemented (yet) */}
void atom_op_delay(struct atom_command* command, uint8_t** ptr_ptr);
void atom_op_calltable(struct atom_command* command, uint8_t** ptr_ptr);
void atom_op_repeat(struct atom_command* command, uint8_t** ptr_ptr) { assert(0); /* Not implemented (yet) */}
void atom_op_clear(struct atom_command* command, uint8_t** ptr_ptr);
void atom_op_nop(struct atom_command* command, uint8_t** ptr_ptr) { assert(0); /* Not implemented (yet) */}
void atom_op_eot(struct atom_command* command, uint8_t** ptr_ptr);
void atom_op_mask(struct atom_command* command, uint8_t** ptr_ptr);
void atom_op_postcard(struct atom_command* command, uint8_t** ptr_ptr) { assert(0); /* Not implemented (yet) */}
void atom_op_beep(struct atom_command* command, uint8_t** ptr_ptr);
void atom_op_savereg(struct atom_command* command, uint8_t** ptr_ptr) { assert(0); /* Not implemented (yet) */}
void atom_op_restorereg(struct atom_command* command, uint8_t** ptr_ptr) { assert(0); /* Not implemented (yet) */}
void atom_op_setdatablock(struct atom_command* command, uint8_t** ptr_ptr);
void atom_op_xor(struct atom_command* command, uint8_t** ptr_ptr) { assert(0); /* Not implemented (yet) */}
void atom_op_shl(struct atom_command* command, uint8_t** ptr_ptr) { assert(0); /* Not implemented (yet) */}
void atom_op_shr(struct atom_command* command, uint8_t** ptr_ptr) { assert(0); /* Not implemented (yet) */}
void atom_op_debug(struct atom_command* command, uint8_t** ptr_ptr) { assert(0); /* Not implemented (yet) */}
void atom_op_processds(struct atom_command* command, uint8_t** ptr_ptr);
void atom_op_mul32(struct atom_command* command, uint8_t** ptr_ptr) { assert(0); /* Not implemented (yet) */}
void atom_op_div32(struct atom_command* command, uint8_t** ptr_ptr) { assert(0); /* Not implemented (yet) */}

static struct {
	void (*func) (struct atom_command*, uint8_t**);
	int arg;
} opcode_table[ATOM_OP_CNT] = {
	{NULL, 0},
	{atom_op_move, ATOM_ARG_REG},
	{atom_op_move, ATOM_ARG_PS},
	{atom_op_move, ATOM_ARG_WS},
	{atom_op_move, ATOM_ARG_FB},
	{atom_op_move, ATOM_ARG_PLL},
	{atom_op_move, ATOM_ARG_MC},
	{atom_op_move, ATOM_ARG_REG} /* {atom_op_and, ATOM_ARG_REG} */,
	{atom_op_move, ATOM_ARG_PS} /* {atom_op_and, ATOM_ARG_PS} */,
	{atom_op_move, ATOM_ARG_WS} /* {atom_op_and, ATOM_ARG_WS} */,
	{atom_op_move, ATOM_ARG_FB} /* {atom_op_and, ATOM_ARG_FB} */,
	{atom_op_move, ATOM_ARG_PLL} /* {atom_op_and, ATOM_ARG_PLL} */,
	{atom_op_move, ATOM_ARG_MC} /* {atom_op_and, ATOM_ARG_MC} */,
	{atom_op_move, ATOM_ARG_REG} /* {atom_op_or, ATOM_ARG_REG} */,
	{atom_op_move, ATOM_ARG_PS} /* {atom_op_or, ATOM_ARG_PS} */,
	{atom_op_move, ATOM_ARG_WS} /* {atom_op_or, ATOM_ARG_WS} */,
	{atom_op_move, ATOM_ARG_FB} /* {atom_op_or, ATOM_ARG_FB} */,
	{atom_op_move, ATOM_ARG_PLL} /* {atom_op_or, ATOM_ARG_PLL} */,
	{atom_op_move, ATOM_ARG_MC} /* {atom_op_or, ATOM_ARG_MC} */,
	{atom_op_shift_left, ATOM_ARG_REG},
	{atom_op_shift_left, ATOM_ARG_PS},
	{atom_op_shift_left, ATOM_ARG_WS},
	{atom_op_shift_left, ATOM_ARG_FB},
	{atom_op_shift_left, ATOM_ARG_PLL},
	{atom_op_shift_left, ATOM_ARG_MC},
	{atom_op_shift_left, ATOM_ARG_REG}, /* {atom_op_shift_right, ATOM_ARG_REG} */
	{atom_op_shift_left, ATOM_ARG_PS}, /* {atom_op_shift_right, ATOM_ARG_PS} */
	{atom_op_shift_left, ATOM_ARG_WS}, /* {atom_op_shift_right, ATOM_ARG_WS} */
	{atom_op_shift_left, ATOM_ARG_FB}, /* {atom_op_shift_right, ATOM_ARG_FB} */
	{atom_op_shift_left, ATOM_ARG_PLL}, /* {atom_op_shift_right, ATOM_ARG_PLL} */
	{atom_op_shift_left, ATOM_ARG_MC}, /* {atom_op_shift_right, ATOM_ARG_MC} */
	{atom_op_move, ATOM_ARG_REG} /* {atom_op_mul, ATOM_ARG_REG} */,
	{atom_op_move, ATOM_ARG_PS} /* {atom_op_mul, ATOM_ARG_PS} */,
	{atom_op_move, ATOM_ARG_WS} /* {atom_op_mul, ATOM_ARG_WS} */,
	{atom_op_move, ATOM_ARG_FB} /* {atom_op_mul, ATOM_ARG_FB} */,
	{atom_op_move, ATOM_ARG_PLL} /* {atom_op_mul, ATOM_ARG_PLL} */,
	{atom_op_move, ATOM_ARG_MC} /* {atom_op_mul, ATOM_ARG_MC} */,
	{atom_op_move, ATOM_ARG_REG} /* {atom_op_div, ATOM_ARG_REG} */,
	{atom_op_move, ATOM_ARG_PS} /* {atom_op_div, ATOM_ARG_PS} */,
	{atom_op_move, ATOM_ARG_WS} /* {atom_op_div, ATOM_ARG_WS} */,
	{atom_op_move, ATOM_ARG_FB} /* {atom_op_div, ATOM_ARG_FB} */,
	{atom_op_move, ATOM_ARG_PLL} /* {atom_op_div, ATOM_ARG_PLL} */,
	{atom_op_move, ATOM_ARG_MC} /* {atom_op_div, ATOM_ARG_MC} */,
	{atom_op_move, ATOM_ARG_REG} /* {atom_op_add, ATOM_ARG_REG} */,
	{atom_op_move, ATOM_ARG_PS} /* {atom_op_add, ATOM_ARG_PS} */,
	{atom_op_move, ATOM_ARG_WS} /* {atom_op_add, ATOM_ARG_WS} */,
	{atom_op_move, ATOM_ARG_FB} /* {atom_op_add, ATOM_ARG_FB} */,
	{atom_op_move, ATOM_ARG_PLL} /* {atom_op_add, ATOM_ARG_PLL} */,
	{atom_op_move, ATOM_ARG_MC} /* {atom_op_add, ATOM_ARG_MC} */,
	{atom_op_move, ATOM_ARG_REG} /* {atom_op_sub, ATOM_ARG_REG} */,
	{atom_op_move, ATOM_ARG_PS} /* {atom_op_sub, ATOM_ARG_PS} */,
	{atom_op_move, ATOM_ARG_WS} /* {atom_op_sub, ATOM_ARG_WS} */,
	{atom_op_move, ATOM_ARG_FB} /* {atom_op_sub, ATOM_ARG_FB} */,
	{atom_op_move, ATOM_ARG_PLL} /* {atom_op_sub, ATOM_ARG_PLL} */,
	{atom_op_move, ATOM_ARG_MC} /* {atom_op_sub, ATOM_ARG_MC} */,
	{atom_op_setport, ATOM_PORT_ATI},
	{atom_op_setport, ATOM_PORT_PCI},
	{atom_op_setport, ATOM_PORT_SYSIO},
	{atom_op_setregblock, 0},
	{atom_op_setfbbase, 0},
	{atom_op_move, ATOM_ARG_REG} /* {atom_op_compare, ATOM_ARG_REG} */,
	{atom_op_move, ATOM_ARG_PS} /* {atom_op_compare, ATOM_ARG_PS} */,
	{atom_op_move, ATOM_ARG_WS} /* {atom_op_compare, ATOM_ARG_WS} */,
	{atom_op_move, ATOM_ARG_FB} /* {atom_op_compare, ATOM_ARG_FB} */,
	{atom_op_move, ATOM_ARG_PLL} /* {atom_op_compare, ATOM_ARG_PLL} */,
	{atom_op_move, ATOM_ARG_MC} /* {atom_op_compare, ATOM_ARG_MC} */,
	{atom_op_switch, 0},
	{atom_op_jump, ATOM_COND_ALWAYS},
	{atom_op_jump, ATOM_COND_EQUAL},
	{atom_op_jump, ATOM_COND_BELOW},
	{atom_op_jump, ATOM_COND_ABOVE},
	{atom_op_jump, ATOM_COND_BELOWOREQUAL},
	{atom_op_jump, ATOM_COND_ABOVEOREQUAL},
	{atom_op_jump, ATOM_COND_NOTEQUAL},
	{atom_op_move, ATOM_ARG_REG} /* {atom_op_test, ATOM_ARG_REG} */,
	{atom_op_move, ATOM_ARG_PS} /* {atom_op_test, ATOM_ARG_PS} */,
	{atom_op_move, ATOM_ARG_WS} /* {atom_op_test, ATOM_ARG_WS} */,
	{atom_op_move, ATOM_ARG_FB} /* {atom_op_test, ATOM_ARG_FB} */,
	{atom_op_move, ATOM_ARG_PLL} /* {atom_op_test, ATOM_ARG_PLL} */,
	{atom_op_move, ATOM_ARG_MC} /* {atom_op_test, ATOM_ARG_MC} */,
	{atom_op_delay, ATOM_UNIT_MILLISEC},
	{atom_op_delay, ATOM_UNIT_MICROSEC},
	{atom_op_calltable, 0},
	{atom_op_repeat, 0},
	{atom_op_clear, ATOM_ARG_REG},
	{atom_op_clear, ATOM_ARG_PS},
	{atom_op_clear, ATOM_ARG_WS},
	{atom_op_clear, ATOM_ARG_FB},
	{atom_op_clear, ATOM_ARG_PLL},
	{atom_op_clear, ATOM_ARG_MC},
	{atom_op_nop, 0},
	{atom_op_eot, 0},
	{atom_op_mask, ATOM_ARG_REG},
	{atom_op_mask, ATOM_ARG_PS},
	{atom_op_mask, ATOM_ARG_WS},
	{atom_op_mask, ATOM_ARG_FB},
	{atom_op_mask, ATOM_ARG_PLL},
	{atom_op_mask, ATOM_ARG_MC},
	{atom_op_postcard, 0},
	{atom_op_beep, 0},
	{atom_op_savereg, 0},
	{atom_op_restorereg, 0},
	{atom_op_setdatablock, 0},
	{atom_op_move, ATOM_ARG_REG} /* {atom_op_xor, ATOM_ARG_REG} */,
	{atom_op_move, ATOM_ARG_PS} /* {atom_op_xor, ATOM_ARG_PS} */,
	{atom_op_move, ATOM_ARG_WS} /* {atom_op_xor, ATOM_ARG_WS} */,
	{atom_op_move, ATOM_ARG_FB} /* {atom_op_xor, ATOM_ARG_FB} */,
	{atom_op_move, ATOM_ARG_PLL} /* {atom_op_xor, ATOM_ARG_PLL} */,
	{atom_op_move, ATOM_ARG_MC} /* {atom_op_xor, ATOM_ARG_MC} */,
	{atom_op_move, ATOM_ARG_REG} /* {atom_op_shl, ATOM_ARG_REG} */,
	{atom_op_move, ATOM_ARG_PS} /* {atom_op_shl, ATOM_ARG_PS} */,
	{atom_op_move, ATOM_ARG_WS} /* {atom_op_shl, ATOM_ARG_WS} */,
	{atom_op_move, ATOM_ARG_FB} /* {atom_op_shl, ATOM_ARG_FB} */,
	{atom_op_move, ATOM_ARG_PLL} /* {atom_op_shl, ATOM_ARG_PLL} */,
	{atom_op_move, ATOM_ARG_MC} /* {atom_op_shl, ATOM_ARG_MC} */,
	{atom_op_move, ATOM_ARG_REG} /* {atom_op_shr, ATOM_ARG_REG} */,
	{atom_op_move, ATOM_ARG_PS} /* {atom_op_shr, ATOM_ARG_PS} */,
	{atom_op_move, ATOM_ARG_WS} /* {atom_op_shr, ATOM_ARG_WS} */,
	{atom_op_move, ATOM_ARG_FB} /* {atom_op_shr, ATOM_ARG_FB} */,
	{atom_op_move, ATOM_ARG_PLL} /* {atom_op_shr, ATOM_ARG_PLL} */,
	{atom_op_move, ATOM_ARG_MC} /* {atom_op_shr, ATOM_ARG_MC} */,
	{atom_op_debug, 0},
	{atom_op_processds, 0},
	{atom_op_move, ATOM_ARG_PS} /* {atom_op_mul32, ATOM_ARG_PS} */,
	{atom_op_move, ATOM_ARG_WS} /* {atom_op_mul32, ATOM_ARG_WS} */,
	{atom_op_move, ATOM_ARG_PS} /* {atom_op_div32, ATOM_ARG_PS} */,
	{atom_op_move, ATOM_ARG_WS} /* {atom_op_div32, ATOM_ARG_WS} */,
};


static inline void
atom_handle_operand_srcdstptr(
        uint8_t** ptr_ptr,
        uint32_t** operand,
        size_t* operand_size,
        enum atom_command_arg_srcdstptr arg,
        enum atom_command_alignment align
        ) {
    switch (arg) {
        case ATOM_ARG_PS:
        case ATOM_ARG_WS:
        case ATOM_ARG_FB:
        case ATOM_ARG_PLL:
        case ATOM_ARG_MC:
            *operand = (void*)*ptr_ptr;
            *operand_size = 8;
            *ptr_ptr += 1;
            break;
        case ATOM_ARG_REG:
        case ATOM_ARG_ID:
            *operand = (void*)*ptr_ptr;
            *operand_size = 16;
            *ptr_ptr += 2;
            break;
        case ATOM_ARG_IMM:	// See atom_command_alignment
            switch (align) {
                case ATOM_SRC_DWORD:
                    *operand = (void*)*ptr_ptr;
                    *operand_size = 32;
                    *ptr_ptr += 4;
                    break;
                case ATOM_SRC_WORD0:
                case ATOM_SRC_WORD8:
                case ATOM_SRC_WORD16:
                    *operand = (void*)*ptr_ptr;
                    *operand_size = 16;
                    *ptr_ptr += 2;
                    break;
                case ATOM_SRC_BYTE0:
                case ATOM_SRC_BYTE8:
                case ATOM_SRC_BYTE16:
                case ATOM_SRC_BYTE24:
                    *operand = (void*)*ptr_ptr;
                    *operand_size = 8;
                    *ptr_ptr += 1;
                    break;
            }
    }
}

static int atom_dst_to_src[8][4] = {
    {0, 0, 0, 0},
    {1, 2, 3, 0},
    {1, 2, 3, 0},
    {1, 2, 3, 0},
    {4, 5, 6, 7},
    {4, 5, 6, 7},
    {4, 5, 6, 7},
    {4, 5, 6, 7},
};
static inline enum atom_command_alignment
dst_alignment_to_src_alignment(
        enum atom_command_arg_srcdstptr dst_arg,
        enum atom_command_alignment dst_align,
        enum atom_command_alignment src_align
        ) {
    return dst_arg | atom_dst_to_src[src_align][dst_align];
}

int src_alignment_to_dst_alignment_map[8] = { 0, 0, 1, 2, 0, 1, 2, 3 };

// TODO: Hardcode this for only used operands for performance?
static inline void
set_command_size(
        struct atom_command* command
        ) {
    command->size = (
            sizeof(enum atom_command_opcode)
            + command->operand_0_size
            + command->operand_1_size
            + command->operand_2_size
            + command->operand_3_size
    );
}


void
atom_op_move(
        struct atom_command* command,
        uint8_t** ptr_ptr
        ) {
    /* [U8 opcode, U8 attr, U8/U16/U32 dst_ptr, U8/U16/U32 src_ptr] */
    enum atom_command_arg_srcdstptr dst_arg, src_arg;
    enum atom_command_alignment dst_align, src_align;

    union atom_command_attribute* attr = (*ptr_ptr)++;
    command->operand_0_8 = attr;
    command->operand_0_size = 8;

    src_arg = attr->src_arg;
    src_align = attr->src_align;
    dst_arg = command->arg_dstptr;
    dst_align = dst_alignment_to_src_alignment(dst_arg, attr->dst_align, src_align);

    atom_handle_operand_srcdstptr(ptr_ptr, &command->operand_1, &command->operand_1_size, dst_arg, dst_align);
    atom_handle_operand_srcdstptr(ptr_ptr, &command->operand_2, &command->operand_2_size, src_arg, src_align);
    set_command_size(command);
}

void
atom_op_shift_left(
        struct atom_command* command,
        uint8_t** ptr_ptr
        ) {
	/* [U8 opcode, U8 attribute, U8/U16/U32 dst_ptr, U8/U16/U32 src] */
    enum atom_command_arg_srcdstptr dst_arg;
    enum atom_command_alignment dst_align;

    union atom_command_attribute* attr = (*ptr_ptr)++;
    command->operand_0_8 = attr;
    command->operand_0_size = 8;

    // TODO: double-check this when less tired

    /* This is unnecessary with the yaabe implementation, but driver does this, so
     *  keeping it for now until it's confirmed to not affect anything unexpected
     */
    attr->src_arg = 0;
    attr->dst_align = src_alignment_to_dst_alignment_map[attr->src_align];

    dst_arg = command->arg_dstptr;
    dst_align = attr->src_align; // Not a typo. See atom_command_opcode for details.

    atom_handle_operand_srcdstptr(ptr_ptr, &command->operand_1, &command->operand_1_size, dst_arg, dst_align);
    set_command_size(command);
}

void
atom_op_setport(
        struct atom_command* command,
        uint8_t** ptr_ptr
        ) {
    /* [U8 opcode, U8/U16 port] */
    enum atom_command_arg_port arg = command->arg_port;

    switch (arg) {
        case ATOM_PORT_ATI:
            command->operand_0 = *ptr_ptr;
            command->operand_0_size = 16;
            *ptr_ptr += 2;
            break;
    	case ATOM_PORT_PCI:
        case ATOM_PORT_SYSIO:
            command->operand_0 = *ptr_ptr;
            command->operand_0_size = 8;
            *ptr_ptr += 1;
            break;
    }
    set_command_size(command);
}

void
atom_op_setregblock(
        struct atom_command* command,
        uint8_t** ptr_ptr
        ) {
	/* [U8 opcode, U16 reg_block_ptr] */
    uint16_t* reg_block_ptr = *ptr_ptr;
    command->operand_0 = reg_block_ptr;
    command->operand_0_size = 16;
    *ptr_ptr += 2;

    set_command_size(command);
}

/* Near jump */
void
atom_op_jump(
        struct atom_command* command,
        uint8_t** ptr_ptr
        ){
    /* [U8 opcode, U16 target] */
    // TODO: Implement this.
    enum atom_command_arg_cond arg = command->arg_cond;

    set_command_size(command);
}

void atom_op_clear(
        struct atom_command* command,
        uint8_t** ptr_ptr) {
	/* [U8 opcode, U8 attribute, U8/U16/U32 dst_ptr] */
    enum atom_command_arg_srcdstptr dst_arg;
    enum atom_command_alignment dst_align;

    union atom_command_attribute* attr = (*ptr_ptr)++;
    command->operand_0_8 = attr;
    command->operand_0_size = 8;

    dst_arg = command->arg_dstptr;
    dst_align = dst_alignment_to_src_alignment(dst_arg, attr->dst_align, attr->src_align);

    atom_handle_operand_srcdstptr(ptr_ptr, &command->operand_1, &command->operand_1_size, dst_arg, dst_align);

    set_command_size(command);
}

void atom_op_calltable(
        struct atom_command* command,
        uint8_t** ptr_ptr
        ) {
    /* [U8 opcode, U8 idx] */
    uint8_t* idx = (*ptr_ptr)++; // master_data_table[idx]
    command->operand_0 = idx;
    command->operand_0_size = 8;

    set_command_size(command);
}

void
atom_op_delay(
        struct atom_command* command,
        uint8_t** ptr_ptr
        ) {
    /* [U8 opcode, U8 count] */
    enum atom_command_arg_unit arg = command->arg_unit;

    uint8_t* count = (*ptr_ptr)++;
    command->operand_0 = count;
    command->operand_0_size = 8;

    set_command_size(command);
}

void atom_op_eot(
        struct atom_command* command,
        uint8_t** ptr_ptr) {
    (*ptr_ptr)++;
    set_command_size(command);
    // return (See populate_commands)
}

void
atom_op_mask(
        struct atom_command* command,
        uint8_t** ptr_ptr
        ) {
	/* [U8 opcode, U8 attribute, U8/U16/U32 dst_ptr, U8/U16/U32 and_mask, U8/U16/U32 or_mask_ptr] */
    /* or_mask_ptr is implemented using src_ptr logic/attribute encoding (See atom_op_move) */
    enum atom_command_arg_srcdstptr dst_arg, src_arg;
    enum atom_command_alignment dst_align, src_align;

    union atom_command_attribute* attr = (*ptr_ptr)++;
    command->operand_0 = attr;
    command->operand_0_size = 8;

    // TODO: Make src/dst stuff prettier (and match the style in atom_op_move and others)?
    src_arg = attr->src_arg;
    src_align = attr->src_align;
    dst_arg = command->arg_dstptr;
    dst_align = dst_alignment_to_src_alignment(dst_arg, attr->dst_align, src_align);

    atom_handle_operand_srcdstptr(ptr_ptr, &command->operand_1, &command->operand_1_size, dst_arg, dst_align);

    uint8_t* and_mask = (*ptr_ptr)++;
    command->operand_2_8 = and_mask;
    command->operand_2_size = 8;

    atom_handle_operand_srcdstptr(ptr_ptr, &command->operand_3, &command->operand_3_size, src_arg, src_align);

    set_command_size(command);
}

void
atom_op_beep(
        struct atom_command* command,
        uint8_t** ptr_ptr
        ) {
    /* [U8 opcode] */
    (*ptr_ptr)++;
    set_command_size(command);
    // TODO?: printk("ATOM BIOS beeped!\n");
}

void
atom_op_setdatablock(
        struct atom_command* command,
        uint8_t** ptr_ptr
        ) {
	/* [U8 opcode, U8 idx] */
    uint8_t* idx = (*ptr_ptr)++; // master_data_table[idx]
    command->operand_0 = idx;
    command->operand_0_size = 8;

    set_command_size(command);
}

/* Short jump */
void
atom_op_processds(
        struct atom_command* command,
        uint8_t** ptr_ptr) {
    /* [U8 opcode, U16 offset] */
    uint16_t* offset = *ptr_ptr;
    command->operand_0 = offset;
    command->operand_0_size = 16;
    *ptr_ptr += 2 + *offset;

    set_command_size(command);
}

void
parse_command(
        uint8_t** ptr_ptr,
        struct atom_command* command
        ) {
    enum atom_command_opcode* opcode = (*ptr_ptr)++;
    assert(*opcode < ATOM_OP_CNT && *opcode > 0);

    command->opcode = opcode;
    command->arg = opcode_table[*command->opcode].arg;

    opcode_table[*command->opcode].func(command, ptr_ptr);
}

/* TODO: atom_exec_context implementation
 *          bounds checking of pointers and so on based on this 
 */
void
populate_commands(
        struct atomtree_command_table* const cmd_table,
        struct atom_tree* const atree
        ) {
	uint16_t structuresize = cmd_table->table_header->structuresize;
	enum atom_command_opcode* opcode = cmd_table->command_table->commands;
	size_t curr_table_size = sizeof(struct atom_command_table);
    struct atom_command* commands_buffer = calloc(1, sizeof(struct atom_command) * (structuresize - sizeof(struct atom_command_table))); // max possible commands (all opcode-only commands)

	cmd_table->atom_op_eot_hit = false;
    cmd_table->num_commands = 0;

	while (true) {
		/* XXX: Find out whether structuresize is a valid test. 
		 * TODO: Error handling? amdgpu driver does not treat op>ATOM_OP_CNT nor op==NULL as an error, but simply stops executing
         *       Move structuresize test into while loop condition
         *       Is EOT or NULL the intended "return" opcode? Is EOT simply always placed at the end of the entire table (doesn't seem like it)?
		 */
		if (curr_table_size >= structuresize
				|| !(*opcode < ATOM_OP_CNT && *opcode > 0)) {
			break;
		}


        struct atom_command* command = &commands_buffer[cmd_table->num_commands];

        // XXX: remove this once commands are implemented properly
        switch (*opcode) {
            case ATOM_OP_JUMP_ALWAYS ... ATOM_OP_JUMP_NOTEQUAL:
            case ATOM_OP_SWITCH:
                goto exit_loop;
        }

        // TODO: IMPORTANT: Finish verifying pointer incrementation
        parse_command(&opcode, command); /* Handles pointer incrementation */

        cmd_table->num_commands++;
        curr_table_size += command->size;

		if (*command->opcode == ATOM_OP_EOT) {
			cmd_table->atom_op_eot_hit = true; // TODO: move this into atom_op_eot?
            break;
		} 
	}
    exit_loop: ;

    // TODO: shrink to fit command size
    cmd_table->commands_size = curr_table_size - sizeof(struct atom_command_table); // TODO: not needed?
    cmd_table->commands = commands_buffer;
}