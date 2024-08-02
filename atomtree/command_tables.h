#ifndef COMMAND_TABLES_H
#define COMMAND_TABLES_H

#include "atomtree.h"

// TODO: Finish documenting command tables

#define ATOM_OP_CNT		127

enum atom_command_alignment {
						// stored as | value at
	ATOM_SRC_DWORD,		// U32       | [31:0]
	ATOM_SRC_WORD0,		// U16       | [15:0]
	ATOM_SRC_WORD8,		// U16       | [23:8]
	ATOM_SRC_WORD16,	// U16       | [31:16]
	ATOM_SRC_BYTE0,		// U8        | [7:0]
	ATOM_SRC_BYTE8,		// U8        | [15:8]
	ATOM_SRC_BYTE16,	// U8        | [23:16]
	ATOM_SRC_BYTE24,	// U8        | [31:24]
};

enum atom_ws_member_access {
    ATOM_WS_QUOTIENT = 0x40,
    ATOM_WS_REMAINDER,
    ATOM_WS_DATAPTR,
    ATOM_WS_SHIFT,
    ATOM_WS_OR_MASK,
    ATOM_WS_AND_MASK,
    ATOM_WS_FB_WINDOW,
    ATOM_WS_ATTRIBUTES,
    ATOM_WS_REGPTR,
};

/* TODO: Implement iio. atom_context::iio is zero-allocated by the driver's atombios parser.
 *       Finish documenting this.
 */
enum atom_iio_opcode {
	ATOM_IIO_NOP,


/* ATOM_IIO_START SYNTAX: [U8 opcode, U8 atom_context::iio pointer]
 *
 * TODO: Make sure if this is true
 * See driver's atom_index_iio. Seemingly ATOM_IIO_START is simply there to tell atom_context
 *  where to find the first opcode of an "IIO table"(?). iio[iio pointer] is set to the first
 *  address after the start instruction (&opcode + 2).
 */
	ATOM_IIO_START,         // U8
	ATOM_IIO_READ,
	ATOM_IIO_WRITE,
	ATOM_IIO_CLEAR,
	ATOM_IIO_SET,
	ATOM_IIO_MOVE_INDEX,
	ATOM_IIO_MOVE_ATTR,
	ATOM_IIO_MOVE_DATA,
	ATOM_IIO_END,           // U8
};

/* io_mode value, stored in driver (struct atom_context->io_mode)
 * Decides target of ATOM_ARG_REG
 * Is reset to ATOM_IO_MM at start of command table execution, but can be changed by ATOM_OP_SETPORT_xxx
 * Only ATOM_IO_MM seems to have any implemented functionality at all in the driver
 */
enum atom_io_mode {
    ATOM_IO_MM,
    ATOM_IO_PCI,
    ATOM_IO_SYSIO,
    ATOM_IO_IIO = 0x80
};

/* Decides dst/src_ptr categories (see atom_command_opcode) */
enum atom_command_arg_srcdstptr: uint8_t {
    /* TODO: make this nicer                        cail_xxx_read | cail_xxx_write 
     *                                              implemented   | implemented
     */
	ATOM_ARG_REG,	// U16                          YES             YES
	ATOM_ARG_PS,	// U8                           N/A (CAN read)  N/A (CAN write)
	ATOM_ARG_WS,	// U8                           N/A (CAN read)  N/A (CAN write)
	ATOM_ARG_FB,	// U8                           N/A             N/A
	ATOM_ARG_ID,	// U16                          N/A             N/A
	ATOM_ARG_IMM,	// See atom_command_alignment   N/A (CAN read)  N/A (CAN write)
	ATOM_ARG_PLL,	// U8                           NO              NO
	ATOM_ARG_MC		// U8                           NO              NO
};

/* Jump if above/above or equal/etc. Used it ATOM_OP_JUMP. See atom_command_opcode */
enum atom_command_arg_cond: uint8_t {
	ATOM_COND_ABOVE,
	ATOM_COND_ABOVEOREQUAL,
	ATOM_COND_ALWAYS,
	ATOM_COND_BELOW,
	ATOM_COND_BELOWOREQUAL,
	ATOM_COND_EQUAL,
	ATOM_COND_NOTEQUAL
};

enum atom_command_arg_port: uint8_t {
    ATOM_PORT_ATI,
    ATOM_PORT_PCI,
    ATOM_PORT_SYSIO,
};

enum atom_command_arg_unit: uint8_t {
	ATOM_UNIT_MICROSEC,
	ATOM_UNIT_MILLISEC
};

/* src_alignment is 3 bits, and is used as-is.
 * dst_alignment is compressed to 2 bits, and uses src_alignment to infer missing information:
 *     static int atom_dst_to_src[8][4] = {
 *         {0, 0, 0, 0},
 *         {1, 2, 3, 0},
 *         {1, 2, 3, 0},
 *         {1, 2, 3, 0},
 *         {4, 5, 6, 7},
 *         {4, 5, 6, 7},
 *         {4, 5, 6, 7},
 *         {4, 5, 6, 7},
 *     };
 *     dst_alignment_to_src_alignment = dst_arg | atom_dst_to_src[SRC_ALIGNMENT][DST_ALIGNMENT]
 *
 *     In other words:
 *         src_alignment == 0 								=> dst_alignment_converted == ATOM_SRC_DWORD == 0
 *         src_alignment  > 0, most significant bit == 0	=> dst_alignment_converted == dst_alignment + 1
 *         src_alignment  > 0, most significant bit == 1    => dst_alignment_converted == dst_alignemnt + 0b100
 *
 * Meaning of final alignment value is documented by enum atom_command_alignment
 */
union atom_command_attribute {
	uint8_t bitfield;
	struct {
		enum atom_command_arg_srcdstptr src_arg:         2-0 +1; // see atom_command_arg_srcdstptr
		// dst_arg is encoded in the opcode (see atom_command_opcode)
		enum atom_command_alignment src_align: 5-3 +1;
		enum atom_command_alignment dst_align: 7-6 +1;
	};
};

enum atom_command_opcode: uint8_t {
	_NULL,

	/* MOVE SYNTAX: [U8 opcode, U8 attribute, U8/U16/U32 dst_ptr, U8/U16/U32 src_ptr]
	 *     attribute:				See atom_command_attribute
	 *     dst_ptr:					Pointer to reg/ps/ws/etc (pointer accessed by driver, not part of atombios)
	 *     src_ptr:					See dst_ptr
	 *     dst_ptr/src_ptr size:	See atom_command_arg_srcdstptr
	 * 
	 * Moves value at src_ptr to value at dst_ptr
	 * TODO: explain atom_skip_dst?
	 */
	ATOM_OP_MOVE_REG,			// ATOM_OP_MOVE, ATOM_ARG_REG (See atom_command_arg_srcdstptr)
	ATOM_OP_MOVE_PS,			// ATOM_OP_MOVE, ATOM_ARG_PS
	ATOM_OP_MOVE_WS,			// ATOM_OP_MOVE, ATOM_ARG_WS
	ATOM_OP_MOVE_FB,			// ATOM_OP_MOVE, ATOM_ARG_FB
	ATOM_OP_MOVE_PLL,			// ATOM_OP_MOVE, ATOM_ARG_PLL
	ATOM_OP_MOVE_MC,			// ATOM_OP_MOVE, ATOM_ARG_MC

	/* AND SYNTAX: See MOVE SYNTAX */ // TODO: Describe function
	ATOM_OP_AND_REG,			// ATOM_OP_AND, ATOM_ARG_REG
	ATOM_OP_AND_PS,				// ...
	ATOM_OP_AND_WS,
	ATOM_OP_AND_FB,
	ATOM_OP_AND_PLL,
	ATOM_OP_AND_MC,

	/* OR SYNTAX: See MOVE SYNTAX */ // TODO: Describe function
	ATOM_OP_OR_REG,				// ATOM_OP_OR, ATOM_ARG_REG
	ATOM_OP_OR_PS,				// ...
	ATOM_OP_OR_WS,
	ATOM_OP_OR_FB,
	ATOM_OP_OR_PLL,
	ATOM_OP_OR_MC,

	/* SHIFT SYNTAX: [U8 opcode, U8 attribute, U8/U16/U32 dst_ptr, U8/U16/U32 src]
	 * 		attribute:			See atom_command_attribute, however driver performs the below edits before using it:
	 *                				attr           = (attr &= 38)
	 *                				src_alignment  = attr >> 3
	 *                				attr          |= atom_def_dst[src_alignment] << 6 // set dst alignment field to the src alignment's equivalent
	 *                				int atom_def_dst[8] = { 0, 0, 1, 2, 0, 1, 2, 3 };
     *                              In other words, we simply use src alignment, with dst arg? TODO: double-check
	 * 		dst_ptr:			See MOVE SYNTAX
	 * 		src:				Immediate value (aka not pointer) // TODO: more specific name
	 * 		dst_ptr size:	    See atom_command_arg_srcdstptr
	 * 
	 * TODO: Document behavior
	 */
	ATOM_OP_SHIFT_LEFT_REG,
	ATOM_OP_SHIFT_LEFT_PS,
	ATOM_OP_SHIFT_LEFT_WS,
	ATOM_OP_SHIFT_LEFT_FB,
	ATOM_OP_SHIFT_LEFT_PLL,
	ATOM_OP_SHIFT_LEFT_MC,
	ATOM_OP_SHIFT_RIGHT_REG,
	ATOM_OP_SHIFT_RIGHT_PS,
	ATOM_OP_SHIFT_RIGHT_WS,
	ATOM_OP_SHIFT_RIGHT_FB,
	ATOM_OP_SHIFT_RIGHT_PLL,
	ATOM_OP_SHIFT_RIGHT_MC,

	/* DIV/MUL SYNTAX: See MOVE SYNTAX
	 *
	 * DIV:
	 * 		value_at(dst_ptr) / value_at(src_ptr), result saved to driver's atom_context::divmul[0] buffer
	 * 		value_at(dst_ptr) % value_at(src_ptr), result saved to driver's atom_context::divmul[1] buffer
	 * MUL:
	 * 		value_at(dst_ptr) * value_at(src_ptr), result saved to driver's atom_context::divmul[0] buffer
	 */
	ATOM_OP_MUL_REG,
	ATOM_OP_MUL_PS,
	ATOM_OP_MUL_WS,
	ATOM_OP_MUL_FB,
	ATOM_OP_MUL_PLL,
	ATOM_OP_MUL_MC,
	ATOM_OP_DIV_REG,
	ATOM_OP_DIV_PS,
	ATOM_OP_DIV_WS,
	ATOM_OP_DIV_FB,
	ATOM_OP_DIV_PLL,
	ATOM_OP_DIV_MC,

	/* ADD/SUB SYNTAX: See MOVE SYNTAX
	 *
	 * ADD: value_at(dst_ptr) + value_at(src_ptr), result saved to value_at(dst_ptr)
	 * ADD: value_at(dst_ptr) - value_at(src_ptr), result saved to value_at(dst_ptr)
	 */
	ATOM_OP_ADD_REG,
	ATOM_OP_ADD_PS,
	ATOM_OP_ADD_WS,
	ATOM_OP_ADD_FB,
	ATOM_OP_ADD_PLL,
	ATOM_OP_ADD_MC,
	ATOM_OP_SUB_REG,
	ATOM_OP_SUB_PS,
	ATOM_OP_SUB_WS,
	ATOM_OP_SUB_FB,
	ATOM_OP_SUB_PLL,
	ATOM_OP_SUB_MC,

	/* SETPORT SYNTAX: [U8 opcode, U8/U16 port]
	 *		port: U16 if ATOM_OP_SETPORT_ATI, otherwise U8 (and seemingly unused).
	 *
	 * TODO: Document
	 */
	// TODO: enum atom_command_arg_port
	ATOM_OP_SETPORT_ATI,	// ATOM_PORT_ATI,	Sets either ATOM_IO_MM or (port | ATOM_IO_IIO)
	ATOM_OP_SETPORT_PCI,	// ATOM_PORT_PCI,	Sets ATOM_IO_PCI
	ATOM_OP_SETPORT_SYSIO,	// ATOM_PORT_SYSIO,	Sets ATOM_IO_SYSIO

	/* SETREGBLOCK SYNTAX: [U8 opcode, U16 reg_block_ptr]
	 *
	 * Saves reg_block_ptr to driver's atom_context::reg_block buffer
	 */
	ATOM_OP_SETREGBLOCK,

	/* SETFBBASE SYNTAX: [U8 opcode, U8 attribute, U8/U16/U32 src_ptr]
	 *		attribute:	see MOVE SYNTAX
	 *		src_ptr:	see MOVE SYNTAX
	 */
	ATOM_OP_SETFBBASE,

	/* COMPARE SYNTAX: See MOVE SYNTAX
	 *	
	 * value_at(dst_ptr) == value_at(src_ptr), result saved to driver's atom_context::cs_equal buffer
	 * value_at(dst_ptr)  > value_at(src_ptr), result saved to driver's atom_context::cs_above buffer
	 */
	ATOM_OP_COMPARE_REG,
	ATOM_OP_COMPARE_PS,
	ATOM_OP_COMPARE_WS,
	ATOM_OP_COMPARE_FB,
	ATOM_OP_COMPARE_PLL,
	ATOM_OP_COMPARE_MC,

	/* SWITCH SYNTAX: [U8 opcode, U8 attribute, U8/U16/U32 src_ptr, switch_logic_table[]]
	 *		attribute:			see MOVE SYNTAX
	 *		src_ptr:			see MOVE SYNTAX
	 *		switch_logic_table:	TODO
     * TODO: src_ptr seems to only use ATOM_ARG_IMM? verify if this makes it act the same
     *        same as atom_get_src_direct, aka we should call it `src` instead of `src_ptr`
     
	 */
	ATOM_OP_SWITCH,

	/* JUMP SYNTAX: [U8 opcode, U16 target]
	 *		target: Jump offset from start of command table's commands
	 *
	 * If condition is met, jumps to different command within same command table.
	 * Condition is checked by checking atom_context::cs_above/cs_equal/etc flags set by previous commands.
	 */
	ATOM_OP_JUMP_ALWAYS,		// ATOM_COND_ABOVE // NOTE: Not in order of enum, see atom_command_arg_cond
	ATOM_OP_JUMP_EQUAL,			// ATOM_COND_EQUAL
	ATOM_OP_JUMP_BELOW,			// ATOM_COND_EQUAL
	ATOM_OP_JUMP_ABOVE,			// ATOM_COND_ABOVE
	ATOM_OP_JUMP_BELOWOREQUAL,	// ATOM_COND_BELOWOREQUAL
	ATOM_OP_JUMP_ABOVEOREQUAL,  // ATOM_COND_ABOVEOREQUAL
	ATOM_OP_JUMP_NOTEQUAL,      // ATOM_COND_NOTEQUAL

	/* TEST SYNTAX: See MOVE SYNTAX
	 *
	 * (value_at(dst_prt) & value_at(src_ptr)) == 0, result saved to driver's atom_context::cs_equal buffer
	 */
	ATOM_OP_TEST_REG,
	ATOM_OP_TEST_PS,
	ATOM_OP_TEST_WS,
	ATOM_OP_TEST_FB,
	ATOM_OP_TEST_PLL,
	ATOM_OP_TEST_MC,

	/* DELAY SYNTAX: [U8 opcode, U8 count]
	 *		count: ms/us delay
	 * 
	 * Driver delays execution by `count` ms/us
	 */
	ATOM_OP_DELAY_MILLISEC,		// ATOM_UNIT_MILLISEC // NOTE: Not in order of enum, see atom_command_arg_unit
	ATOM_OP_DELAY_MICROSEC,		// ATOM_UNIT_MICROSEC

	/* CALLTABLE SYNTAX: [U8 opcode, U8 idx]
	 *		idx: Index into master list of command tables
	 *
	 * Executes command table at idx
	 */
	ATOM_OP_CALLTABLE,

	/* REPEAT SYNTAX: Not implemented in driver */
	ATOM_OP_REPEAT,

	/* CLEAR SYNTAX: [U8 opcode, U8 attribute, U8/U16/U32 dst_ptr]
	 *		attribute:	see SHIFT SYNTAX
	 *		dst_ptr:	see MOVE SYNTAX
	 *
	 * value_at(dst_ptr) = 0
	 */
	ATOM_OP_CLEAR_REG,
	ATOM_OP_CLEAR_PS,
	ATOM_OP_CLEAR_WS,
	ATOM_OP_CLEAR_FB,
	ATOM_OP_CLEAR_PLL,
	ATOM_OP_CLEAR_MC,

	/* NOP SYNTAX: [U8 opcode]
	 *
	 * No-op
	 */
	ATOM_OP_NOP,

	/* EOT SYNTAX: [U8 opcode]
	 *
	 * No-op, but is never actually executed; acts as a `return` statement to end execution of the command table.
	 */
	ATOM_OP_EOT, // "End of table"?

	/* MASK SYNTAX: [U8 opcode, U8 attribute, U8/U16/U32 dst_ptr, U8/U16/U32 and_mask, U8/U16/U32 or_mask_ptr]
	 *		attribute:		see MOVE SYNTAX
	 *		dst_ptr:		see MOVE SYNTAX
	 *		and_mask:		see SHIFT SYNTAX (src)
	 *		or_mask_ptr:	see MOVE SYNTAX (src_ptr)
	 *
	 * value_at(dst) &= and_mask;
	 * value_at(dst) |= value_at(or_mask_ptr);
	 */
	ATOM_OP_MASK_REG,
	ATOM_OP_MASK_PS,
	ATOM_OP_MASK_WS,
	ATOM_OP_MASK_FB,
	ATOM_OP_MASK_PLL,
	ATOM_OP_MASK_MC,

	/* POSTCARD SYNTAX: [U8 opcode, U8 val]
	 *		val: 
	 *
	 * Prints debug message including val
	 */
	ATOM_OP_POSTCARD,

	/* BEEP SYNTAX: [U8 opcode]
	 *
	 * Prints kernel message
	 */
	ATOM_OP_BEEP,

	/* SAVEREG SYNTAX: Not implemented in driver */
	ATOM_OP_SAVEREG,

	/* RESTOREREG SYNTAX: Not implemented in driver */
	ATOM_OP_RESTOREREG,

	/* SETDATABLOCK SYNTAX: [U8 opcode, U8 idx]
	 *		idx: Index into master data table
	 *
	 * idx == 0		=> driver's atom_context::data_block = 0
	 * idx == 255	=> driver's atom_context::data_block = atom_context::ctx_start
	 * idx == 0		=> driver's atom_context::data_block = pointer stored at master_data_table[idx] // NOTE: indexing logic may differ
	 */
	ATOM_OP_SETDATABLOCK,

	/* XOR SYNTAX: See MOVE SYNTAX
	 *
	 * value_at(dst_ptr) ^= value_at(src_ptr)
	 */
	ATOM_OP_XOR_REG,
	ATOM_OP_XOR_PS,
	ATOM_OP_XOR_WS,
	ATOM_OP_XOR_FB,
	ATOM_OP_XOR_PLL,
	ATOM_OP_XOR_MC,

	/* SHL/SHR SYNTAX: See MOVE SYNTAX
	 *
	 *
	 * uint32_t atom_arg_mask[8]  = {0xFFFFFFFF, 0xFFFF, 0xFFFF00, 0xFFFF0000, 0xFF, 0xFF00, 0xFF0000, 0xFF000000};
	 * int      atom_arg_shift[8] = { 0, 0, 8, 16, 0, 8, 16, 24 };
	 *
	 * value_at(dst_ptr) <<= value_at(src_ptr)
	 * value_at(dst_ptr)  &= atom_arg_mask[dst_alignment]	// See MOVE SYNTAX attribute/atom_command_attribute
	 * value_at(dst_ptr) >>= atom_arg_shift[dst_alignment]	// See MOVE SYNTAX attribute/atom_command_attribute
	 */
	ATOM_OP_SHL_REG,
	ATOM_OP_SHL_PS,
	ATOM_OP_SHL_WS,
	ATOM_OP_SHL_FB,
	ATOM_OP_SHL_PLL,
	ATOM_OP_SHL_MC,
	ATOM_OP_SHR_REG,
	ATOM_OP_SHR_PS,
	ATOM_OP_SHR_WS,
	ATOM_OP_SHR_FB,
	ATOM_OP_SHR_PLL,
	ATOM_OP_SHR_MC,

	/* DEBUG SYNTAX: [U8 opcode, U8 val]
	 *
	 * Prints debug message including val
	 */
	ATOM_OP_DEBUG,

	/* PROCESSDS SYNTAX: [U8 opcode, U16 val]
	 *
	 * Increments command pointer by val
	 */
	ATOM_OP_PROCESSDS,

	/* MUL32/DIV32 SYNTAX: See MOVE SYNTAX
	 *
	 * DIV:
	 *		((driver's atom_context::divmul[1] << 32) | value_at(dst_ptr)) / value_at(src_ptr)
	 *				atom_context::divmul[0] = lower 32 bits of result
	 *				atom_context::divmul[1] = upper 32 bits of result
	 * MUL:
	 * 		value_at(dst_ptr) * value_at(src_ptr)
	 *				atom_context::divmul[0] = lower 32 bits of result
	 *				atom_context::divmul[1] = upper 32 bits of result
	 *
	 * NOTE: Actual division logic may be more complex and implemented by kernel
	 */
	ATOM_OP_MUL32_PS,
	ATOM_OP_MUL32_WS,
	ATOM_OP_DIV32_PS,
	ATOM_OP_DIV32_WS,
};

/* TODO: This doesn't really fit in with other atom_xxx structs, as it doesn't
 *        map directly onto any atombios struct. Find a better name.
 *
 */
struct atom_command {
	enum atom_command_opcode* opcode;
	union { /* Inferred from opcode (see atom_command_opcode)*/
        uint8_t arg;
        enum atom_command_arg_srcdstptr arg_dstptr;
        enum atom_command_arg_port arg_port;
        enum atom_command_arg_unit arg_unit;
        enum atom_command_arg_cond arg_cond;
        // TODO: fill this
    };
    size_t size;

	size_t operand_0_size; // TODO: uint8_t (max size atm is 32)
	union {
		uint32_t* operand_0;
		uint16_t* operand_0_16;
		uint8_t* operand_0_8;
	};

	size_t operand_1_size;
	union {
		uint32_t* operand_1;
		uint16_t* operand_1_16;
		uint8_t* operand_1_8;
	};

	size_t operand_2_size;
	union {
		uint32_t* operand_2;
		uint16_t* operand_2_16;
		uint8_t* operand_2_8;
	};

	size_t operand_3_size;
	union {
		uint32_t* operand_3;
		uint16_t* operand_3_16;
		uint8_t* operand_3_8;
	};
};

void
populate_commands(
        struct atomtree_command_table* const cmd_table,
        struct atom_tree* const atree
        );

#endif