#ifndef H_LDASM
#define H_LDASM

#ifdef __cplusplus
extern "C" {
#endif



#define	F_INVALID		0x01
#define F_PREFIX		0x02
#define	F_REX			0x04
#define F_MODRM			0x08
#define F_SIB			0x10
#define F_DISP			0x20
#define F_IMM			0x40
#define F_RELATIVE		0x80


	typedef struct _ldasm_data{
		unsigned char		flags;
		unsigned char		rex;
		unsigned char		modrm;
		unsigned char		sib;
		unsigned char		opcd_offset;
		unsigned char		opcd_size;
		unsigned char		disp_offset;
		unsigned char		disp_size;
		unsigned char		imm_offset;
		unsigned char		imm_size;
	} ldasm_data;

	unsigned int ldasm(void *code, ldasm_data *ld, unsigned int is64);



#ifdef __cplusplus
}
#endif
#endif
