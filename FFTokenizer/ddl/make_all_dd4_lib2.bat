@echo off
echo Foundation Fieldbus DD Standard Library
echo (c) 1996-2010 Fieldbus Foundation.  All rights reserved.
echo Revision:  3.60
echo Date:      30-Jul-2010
echo This will tokenize the complete library.
pause Press ctrl-c to stop now; otherwise press a key to continue...

echo fftok -4 -a -u -DLIB2 aal_block.ddl
call fftok -4 -a -u -DLIB2 -O aal_block.ddl

echo fftok -4 -a -u -DLIB2 adv_parm.ddl
call fftok -4 -a -u -DLIB2 -O adv_parm.ddl

echo fftok -4 -a -u -DLIB2 adv_pvb.ddl
call fftok -4 -a -u -DLIB2 -O adv_pvb.ddl

echo fftok -4 -a -u -DLIB2 ahi_block.ddl
call fftok -4 -a -u -DLIB2 -O ahi_block.ddl

echo fftok -4 -a -u -DLIB2 ai_block.ddl
call fftok -4 -a -u -DLIB2 -O ai_block.ddl

echo fftok -4 -a -u -DLIB2 ao_block.ddl
call fftok -4 -a -u -DLIB2 -O ao_block.ddl

echo fftok -4 -a -u -DLIB2 ar_block.ddl
call fftok -4 -a -u -DLIB2 -O ar_block.ddl

echo fftok -4 -a -u -DLIB2 bas_pvb.ddl
call fftok -4 -a -u -DLIB2 -O bas_pvb.ddl

echo fftok -4 -a -u -DLIB2 bg_block.ddl
call fftok -4 -a -u -DLIB2 -O bg_block.ddl

echo fftok -4 -a -u -DLIB2 calca_block.ddl
call fftok -4 -a -u -DLIB2 -O calca_block.ddl

echo fftok -4 -a -u -DLIB2 calcd_block.ddl
call fftok -4 -a -u -DLIB2 -O calcd_block.ddl

echo fftok -4 -a -u -DLIB2 cao_block.ddl
call fftok -4 -a -u -DLIB2 -O cao_block.ddl

echo fftok -4 -a -u -DLIB2 cdo_block.ddl
call fftok -4 -a -u -DLIB2 -O cdo_block.ddl

echo fftok -4 -a -u -DLIB2 cmplx_xdcr_block.ddl
call fftok -4 -a -u -DLIB2 -O cmplx_xdcr_block.ddl

echo fftok -4 -a -u -DLIB2 cs_block.ddl
call fftok -4 -a -u -DLIB2 -O cs_block.ddl

echo fftok -4 -a -u -DLIB2 cust_calc_block.ddl
call fftok -4 -a -u -DLIB2 -O cust_calc_block.ddl

echo fftok -4 -a -u -DLIB2 cust_cntrl_block.ddl
call fftok -4 -a -u -DLIB2 -O cust_cntrl_block.ddl

echo fftok -4 -a -u -DLIB2 cust_in_block.ddl
call fftok -4 -a -u -DLIB2 -O cust_in_block.ddl

echo fftok -4 -a -u -DLIB2 cust_out_block.ddl
call fftok -4 -a -u -DLIB2 -O cust_out_block.ddl

echo fftok -4 -a -u -DLIB2 dal_block.ddl
call fftok -4 -a -u -DLIB2 -O dal_block.ddl

echo fftok -4 -a -u -DLIB2 dc_block.ddl
call fftok -4 -a -u -DLIB2 -O dc_block.ddl

echo fftok -4 -a -u -DLIB2 dhi_block.ddl
call fftok -4 -a -u -DLIB2 -O dhi_block.ddl

echo fftok -4 -a -u -DLIB2 di_block.ddl
call fftok -4 -a -u -DLIB2 -O di_block.ddl

echo fftok -4 -a -u -DLIB2 do_block.ddl
call fftok -4 -a -u -DLIB2 -O do_block.ddl

echo fftok -4 -a -u -DLIB2 dsc_pvb.ddl
call fftok -4 -a -u -DLIB2 -O dsc_pvb.ddl

echo fftok -4 -a -u -DLIB2 dt_block.ddl
call fftok -4 -a -u -DLIB2 -O dt_block.ddl

echo fftok -4 -a -u -DLIB2 flow_cb.ddl
call fftok -4 -a -u -DLIB2 -O flow_cb.ddl

echo fftok -4 -a -u -DLIB2 ft_block.ddl
call fftok -4 -a -u -DLIB2 -O ft_block.ddl

echo fftok -4 -a -u -DLIB2  gen_xdcr_block.ddl
call fftok -4 -a -u -DLIB2  -O gen_xdcr_block.ddl

echo fftok -4 -a -u -DLIB2 is_block.ddl
call fftok -4 -a -u -DLIB2 -O is_block.ddl

echo fftok -4 -a -u -DLIB2 it_block.ddl
call fftok -4 -a -u -DLIB2 -O it_block.ddl

echo fftok -4 -a -u -DLIB2 ll_block.ddl
call fftok -4 -a -u -DLIB2 -O ll_block.ddl

echo fftok -4 -a -u -DLIB2 mai.ddl
call fftok -4 -a -u -DLIB2 -O mai.ddl

echo fftok -4 -a -u -DLIB2 mao.ddl
call fftok -4 -a -u -DLIB2 -O mao.ddl

echo fftok -4 -a -u -DLIB2 mdi.ddl
call fftok -4 -a -u -DLIB2 -O mdi.ddl

echo fftok -4 -a -u -DLIB2 mdo.ddl
call fftok -4 -a -u -DLIB2 -O mdo.ddl

echo fftok -4 -a -u -DLIB2 mio_parm.ddl
call fftok -4 -a -u -DLIB2 -O mio_parm.ddl

echo fftok -4 -a -u -DLIB2 ml_block.ddl
call fftok -4 -a -u -DLIB2 -O ml_block.ddl

echo fftok -4 -a -u -DLIB2 os_block.ddl
call fftok -4 -a -u -DLIB2 -O os_block.ddl

echo fftok -4 -a -u -DLIB2 pd_block.ddl
call fftok -4 -a -u -DLIB2 -O pd_block.ddl

echo fftok -4 -a -u -DLIB2 pi_block.ddl
call fftok -4 -a -u -DLIB2 -O pi_block.ddl

echo fftok -4 -a -u -DLIB2 pidblock.ddl
call fftok -4 -a -u -DLIB2 -O pidblock.ddl

echo fftok -4 -a -u -DLIB2 pos_a_block.ddl
call fftok -4 -a -u -DLIB2 -O pos_a_block.ddl

echo fftok -4 -a -u -DLIB2 pos_a_d_block.ddl
call fftok -4 -a -u -DLIB2 -O pos_a_d_block.ddl

echo fftok -4 -a -u -DLIB2 pos_d_block.ddl
call fftok -4 -a -u -DLIB2 -O pos_d_block.ddl

echo fftok -4 -a -u -DLIB2 press_cb.ddl
call fftok -4 -a -u -DLIB2 -O press_cb.ddl

echo fftok -4 -a -u -DLIB2 press_cb2.ddl
call fftok -4 -a -u -DLIB2 -O press_cb2.ddl

echo fftok -4 -a -u -DLIB2 prog_resblock.ddl
call fftok -4 -a -u -DLIB2 -O prog_resblock.ddl

echo fftok -4 -a -u -DLIB2 ra_block.ddl
call fftok -4 -a -u -DLIB2 -O ra_block.ddl

echo fftok -4 -a -u -DLIB2 rdrl_cb.ddl
call fftok -4 -a -u -DLIB2 -O rdrl_cb.ddl

echo fftok -4 -a -u -DLIB2 resblock2.ddl
call fftok -4 -a -u -DLIB2 -O resblock2.ddl

echo fftok -4 -a -u -DLIB2 resblock.ddl
call fftok -4 -a -u -DLIB2 -O resblock.ddl

echo fftok -4 -a -u -DLIB2 sc_block.ddl
call fftok -4 -a -u -DLIB2 -O sc_block.ddl

echo fftok -4 -a -u -DLIB2 sif_aiblock.ddl
call fftok -4 -a -u -DLIB2 -O sif_aiblock.ddl

echo fftok -4 -a -u -DLIB2 sif_doblock.ddl
call fftok -4 -a -u -DLIB2 -O sif_doblock.ddl

echo fftok -4 -a -u -DLIB2 sif_parm.ddl
call fftok -4 -a -u -DLIB2 -O sif_parm.ddl

echo fftok -4 -a -u -DLIB2 sif_resblock.ddl
call fftok -4 -a -u -DLIB2 -O sif_resblock.ddl

echo fftok -4 -a -u -DLIB2 spg_block.ddl
call fftok -4 -a -u -DLIB2 -O spg_block.ddl

echo fftok -4 -a -u -DLIB2 spid_block.ddl
call fftok -4 -a -u -DLIB2 -O spid_block.ddl

echo fftok -4 -a -u -DLIB2 std_parm.ddl
call fftok -4 -a -u -DLIB2 -O std_parm.ddl

echo fftok -4 -a -u -DLIB2 temp_c2s.ddl
call fftok -4 -a -u -DLIB2 -O temp_c2s.ddl

echo fftok -4 -a -u -DLIB2 temp_c2s2.ddl
call fftok -4 -a -u -DLIB2 -O temp_c2s2.ddl

echo fftok -4 -a -u -DLIB2 temp_cb.ddl
call fftok -4 -a -u -DLIB2 -O temp_cb.ddl

echo fftok -4 -a -u -DLIB2 temp_cb2.ddl
call fftok -4 -a -u -DLIB2 -O temp_cb2.ddl

echo fftok -4 -a -u -DLIB2 tmr_block.ddl
call fftok -4 -a -u -DLIB2 -O tmr_block.ddl

echo fftok -4 -a -u -DLIB2 xdcr_parm.ddl
call fftok -4 -a -u -DLIB2 -O xdcr_parm.ddl

echo fftok -4 -a -u -DLIB2 rio_parm.ddl
call fftok -4 -a -u -DLIB2 -O rio_parm.ddl

echo fftok -4 -a -u -DLIB2 rio_mai16_block.ddl
call fftok -4 -a -u -DLIB2 -O rio_mai16_block.ddl

echo fftok -4 -a -u -DLIB2 rio_mao16_block.ddl
call fftok -4 -a -u -DLIB2 -O rio_mao16_block.ddl

echo fftok -4 -a -u -DLIB2 rio_mbi64_block.ddl
call fftok -4 -a -u -DLIB2 -O rio_mbi64_block.ddl

echo fftok -4 -a -u -DLIB2 rio_mbo64_block.ddl
call fftok -4 -a -u -DLIB2 -O rio_mbo64_block.ddl

echo fftok -4 -a -u -DLIB2 rio_assoc_prim_block.ddl
call fftok -4 -a -u -DLIB2 -O rio_assoc_prim_block.ddl

echo fftok -4 -a -u -DLIB2 rio_assoc_block.ddl
call fftok -4 -a -u -DLIB2 -O rio_assoc_block.ddl

echo fftok -4 -a -u -DLIB2 rio_xdcr_parm.ddl
call fftok -4 -a -u -DLIB2 -O rio_xdcr_parm.ddl

echo fftok -4 -a -u -DLIB2 rio_hart_xdcr_parm.ddl
call fftok -4 -a -u -DLIB2 -O rio_hart_xdcr_parm.ddl

echo fftok -4 -a -u -DLIB2 rio_hart_block.ddl
call fftok -4 -a -u -DLIB2 -O rio_hart_block.ddl

echo fftok -4 -a -u -DLIB2 rio_wless_hart_block.ddl
call fftok -4 -a -u -DLIB2 -O rio_wless_hart_block.ddl

echo fftok -4 -a -u -DLIB2 rio_vfd_block.ddl
call fftok -4 -a -u -DLIB2 -O rio_vfd_block.ddl

echo fftok -4 -a -u -DLIB2 rio_h1_block.ddl
call fftok -4 -a -u -DLIB2 -O rio_h1_block.ddl

goto END

:END

ECHO DONE
