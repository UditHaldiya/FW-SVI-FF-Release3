#ifndef APPL_PTB_H_
#define APPL_PTB_H_

extern USIGN8 * const rcv_buf;
extern USIGN8 * const  snd_buf;

//Self-repairing flags of background routines completion
extern bool_t rb_HasRun;
extern bool_t tb_HasRun;

#endif // APPL_PTB_H_
