@echo off
echo Foundation Fieldbus DD Standard Library
echo (c) 1996-2010 Fieldbus Foundation.  All rights reserved.
echo Revision:  3.60
echo Date:      30-Jul-2010
echo This will tokenize the complete library.
pause Press ctrl-c to stop now; otherwise press a key to continue...

echo fftok -4 -a -u aal_block.ddl
call fftok -4 -a -u -O aal_block.ddl

echo fftok -4 -a -u adv_parm.ddl
call fftok -4 -a -u -O adv_parm.ddl

echo fftok -4 -a -u adv_pvb.ddl
call fftok -4 -a -u -O adv_pvb.ddl

echo fftok -4 -a -u ahi_block.ddl
call fftok -4 -a -u -O ahi_block.ddl

echo fftok -4 -a -u ai_block.ddl
call fftok -4 -a -u -O ai_block.ddl

echo fftok -4 -a -u ao_block.ddl
call fftok -4 -a -u -O ao_block.ddl

echo fftok -4 -a -u ar_block.ddl
call fftok -4 -a -u -O ar_block.ddl

echo fftok -4 -a -u bas_pvb.ddl
call fftok -4 -a -u -O bas_pvb.ddl

echo fftok -4 -a -u bg_block.ddl
call fftok -4 -a -u -O bg_block.ddl

echo fftok -4 -a -u calca_block.ddl
call fftok -4 -a -u -O calca_block.ddl

echo fftok -4 -a -u calcd_block.ddl
call fftok -4 -a -u -O calcd_block.ddl

echo fftok -4 -a -u cao_block.ddl
call fftok -4 -a -u -O cao_block.ddl

echo fftok -4 -a -u cdo_block.ddl
call fftok -4 -a -u -O cdo_block.ddl

echo fftok -4 -a -u cmplx_xdcr_block.ddl
call fftok -4 -a -u -O cmplx_xdcr_block.ddl

echo fftok -4 -a -u cs_block.ddl
call fftok -4 -a -u -O cs_block.ddl

echo fftok -4 -a -u cust_calc_block.ddl
call fftok -4 -a -u -O cust_calc_block.ddl

echo fftok -4 -a -u cust_cntrl_block.ddl
call fftok -4 -a -u -O cust_cntrl_block.ddl

echo fftok -4 -a -u cust_in_block.ddl
call fftok -4 -a -u -O cust_in_block.ddl

echo fftok -4 -a -u cust_out_block.ddl
call fftok -4 -a -u -O cust_out_block.ddl

echo fftok -4 -a -u dal_block.ddl
call fftok -4 -a -u -O dal_block.ddl

echo fftok -4 -a -u dc_block.ddl
call fftok -4 -a -u -O dc_block.ddl

echo fftok -4 -a -u dhi_block.ddl
call fftok -4 -a -u -O dhi_block.ddl

echo fftok -4 -a -u di_block.ddl
call fftok -4 -a -u -O di_block.ddl

echo fftok -4 -a -u do_block.ddl
call fftok -4 -a -u -O do_block.ddl

echo fftok -4 -a -u dsc_pvb.ddl
call fftok -4 -a -u -O dsc_pvb.ddl

echo fftok -4 -a -u dt_block.ddl
call fftok -4 -a -u -O dt_block.ddl

echo fftok -4 -a -u flow_cb.ddl
call fftok -4 -a -u -O flow_cb.ddl

echo fftok -4 -a -u ft_block.ddl
call fftok -4 -a -u -O ft_block.ddl

echo fftok -4 -a -u gen_xdcr_block.ddl
call fftok -4 -a -u -O gen_xdcr_block.ddl

echo fftok -4 -a -u is_block.ddl
call fftok -4 -a -u -O is_block.ddl

echo fftok -4 -a -u it_block.ddl
call fftok -4 -a -u -O it_block.ddl

echo fftok -4 -a -u ll_block.ddl
call fftok -4 -a -u -O ll_block.ddl

echo fftok -4 -a -u mai.ddl
call fftok -4 -a -u -O mai.ddl

echo fftok -4 -a -u mao.ddl
call fftok -4 -a -u -O mao.ddl

echo fftok -4 -a -u mdi.ddl
call fftok -4 -a -u -O mdi.ddl

echo fftok -4 -a -u mdo.ddl
call fftok -4 -a -u -O mdo.ddl

echo fftok -4 -a -u mio_parm.ddl
call fftok -4 -a -u -O mio_parm.ddl

echo fftok -4 -a -u ml_block.ddl
call fftok -4 -a -u -O ml_block.ddl

echo fftok -4 -a -u os_block.ddl
call fftok -4 -a -u -O os_block.ddl

echo fftok -4 -a -u pd_block.ddl
call fftok -4 -a -u -O pd_block.ddl

echo fftok -4 -a -u pi_block.ddl
call fftok -4 -a -u -O pi_block.ddl

echo fftok -4 -a -u pidblock.ddl
call fftok -4 -a -u -O pidblock.ddl

echo fftok -4 -a -u pos_a_block.ddl
call fftok -4 -a -u -O pos_a_block.ddl

echo fftok -4 -a -u pos_a_d_block.ddl
call fftok -4 -a -u -O pos_a_d_block.ddl

echo fftok -4 -a -u pos_d_block.ddl
call fftok -4 -a -u -O pos_d_block.ddl

echo fftok -4 -a -u press_cb.ddl
call fftok -4 -a -u -O press_cb.ddl

echo fftok -4 -a -u press_cb2.ddl
call fftok -4 -a -u -O press_cb2.ddl

echo fftok -4 -a -u prog_resblock.ddl
call fftok -4 -a -u -O prog_resblock.ddl

echo fftok -4 -a -u ra_block.ddl
call fftok -4 -a -u -O ra_block.ddl

echo fftok -4 -a -u rdrl_cb.ddl
call fftok -4 -a -u -O rdrl_cb.ddl

echo fftok -4 -a -u resblock2.ddl
call fftok -4 -a -u -O resblock2.ddl

echo fftok -4 -a -u resblock.ddl
call fftok -4 -a -u -O resblock.ddl

echo fftok -4 -a -u sc_block.ddl
call fftok -4 -a -u -O sc_block.ddl

echo fftok -4 -a -u sif_aiblock.ddl
call fftok -4 -a -u -O sif_aiblock.ddl

echo fftok -4 -a -u sif_doblock.ddl
call fftok -4 -a -u -O sif_doblock.ddl

echo fftok -4 -a -u sif_parm.ddl
call fftok -4 -a -u -O sif_parm.ddl

echo fftok -4 -a -u sif_resblock.ddl
call fftok -4 -a -u -O sif_resblock.ddl

echo fftok -4 -a -u spg_block.ddl
call fftok -4 -a -u -O spg_block.ddl

echo fftok -4 -a -u spid_block.ddl
call fftok -4 -a -u -O spid_block.ddl

echo fftok -4 -a -u std_parm.ddl
call fftok -4 -a -u -O std_parm.ddl

echo fftok -4 -a -u temp_c2s.ddl
call fftok -4 -a -u -O temp_c2s.ddl

echo fftok -4 -a -u temp_c2s2.ddl
call fftok -4 -a -u -O temp_c2s2.ddl

echo fftok -4 -a -u temp_cb.ddl
call fftok -4 -a -u -O temp_cb.ddl

echo fftok -4 -a -u temp_cb2.ddl
call fftok -4 -a -u -O temp_cb2.ddl

echo fftok -4 -a -u tmr_block.ddl
call fftok -4 -a -u -O tmr_block.ddl

echo fftok -4 -a -u xdcr_parm.ddl
call fftok -4 -a -u -O xdcr_parm.ddl

echo fftok -4 -a -u rio_parm.ddl
call fftok -4 -a -u -O rio_parm.ddl

echo fftok -4 -a -u rio_mai16_block.ddl
call fftok -4 -a -u -O rio_mai16_block.ddl

echo fftok -4 -a -u rio_mao16_block.ddl
call fftok -4 -a -u -O rio_mao16_block.ddl

echo fftok -4 -a -u rio_mbi64_block.ddl
call fftok -4 -a -u -O rio_mbi64_block.ddl

echo fftok -4 -a -u rio_mbo64_block.ddl
call fftok -4 -a -u -O rio_mbo64_block.ddl

echo fftok -4 -a -u rio_assoc_prim_block.ddl
call fftok -4 -a -u -O rio_assoc_prim_block.ddl

echo fftok -4 -a -u rio_assoc_block.ddl
call fftok -4 -a -u -O rio_assoc_block.ddl

echo fftok -4 -a -u rio_xdcr_parm.ddl
call fftok -4 -a -u -O rio_xdcr_parm.ddl

echo fftok -4 -a -u rio_hart_xdcr_parm.ddl
call fftok -4 -a -u -O rio_hart_xdcr_parm.ddl

echo fftok -4 -a -u rio_hart_block.ddl
call fftok -4 -a -u -O rio_hart_block.ddl

echo fftok -4 -a -u rio_wless_hart_block.ddl
call fftok -4 -a -u -O rio_wless_hart_block.ddl

echo fftok -4 -a -u rio_vfd_block.ddl
call fftok -4 -a -u -O rio_vfd_block.ddl

echo fftok -4 -a -u rio_h1_block.ddl
call fftok -4 -a -u -O rio_h1_block.ddl

goto END

:END

ECHO DONE
